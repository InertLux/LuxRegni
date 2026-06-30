// RegniByte/src/AsciiScene.cpp
#include "AsciiScene.h"
#include <unistd.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <cstring>
#include <algorithm>
#include <unistd.h>
#include <iostream> 
#include <sys/select.h> 

static AsciiScene* g_current_scene = nullptr;

void signal_handler(int sig) {
    if (g_current_scene) g_current_scene->exit();
}

AsciiScene::AsciiScene() {
    getTermSize();
    g_current_scene = this;
    signal(SIGINT, signal_handler);
}

AsciiScene::~AsciiScene() {
    if (running) disableRawMode();
    g_current_scene = nullptr;
}

void AsciiScene::getTermSize() {
    winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    term_width = ws.ws_col;
    term_height = ws.ws_row;
}

void AsciiScene::enableRawMode() {
    termios raw;
    tcgetattr(STDIN_FILENO, &orig_termios);
    raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void AsciiScene::disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

std::string AsciiScene::readInput() {
    std::string seq;
    char c;
    
    // Read first byte (blocking)
    if (read(STDIN_FILENO, &c, 1) != 1) return "";
    seq += c;
    
    // If escape sequence, collect remaining bytes
    if (c == '\033') {
        fd_set readfds;
        struct timeval tv = {0, 50000}; // 50ms timeout
        
        while (seq.length() < 10) {
            FD_ZERO(&readfds);
            FD_SET(STDIN_FILENO, &readfds);
            
            if (select(STDIN_FILENO + 1, &readfds, nullptr, nullptr, &tv) <= 0) break;
            if (read(STDIN_FILENO, &c, 1) != 1) break;
            
            seq += c;
            if (c >= 0x40 && c <= 0x7e) break; // Escape sequence terminator
        }
    }
    
    return seq;
}

void AsciiScene::bindKey(const std::string& sequence, KeyHandler handler) {
    keybindings[sequence] = handler;
}

void AsciiScene::handleInput(const std::string& seq) {
    if (auto it = keybindings.find(seq); it != keybindings.end()) {
        it->second();
    }
}

void AsciiScene::run() {
    enableRawMode();
    printf("\033[?1049h");
    fflush(stdout);
    
    running = true;
    while (running) {
        renderFrame();
        std::string seq = readInput();
        if (!seq.empty()) handleInput(seq);
        usleep(16667);
    }
    
    printf("\033[?1049l");
    fflush(stdout);
    disableRawMode();
    
    // Clear stdin buffer
    tcflush(STDIN_FILENO, TCIFLUSH);

    signal(SIGINT, SIG_DFL);  
    
    std::cout << "\n" << QuitMessage << "\n";
}
void AsciiScene::exit(std::string quitMessage) {
    QuitMessage = quitMessage;
    running = false;
}

AsciiEditor::AsciiEditor(const std::string& initial_content) : buffer(initial_content) {
    bindKey("q", [this]() { this->exit(); });
    bindKey("\033[A", [this]() { if (cursor_y > 0) cursor_y--; });
    bindKey("\033[B", [this]() { cursor_y++; });
    bindKey("\033[C", [this]() { if (cursor_x < (int)buffer.length()) cursor_x++; });
    bindKey("\033[D", [this]() { if (cursor_x > 0) cursor_x--; });
}

void AsciiEditor::renderFrame() {
    framebuffer.clear();
    framebuffer += "\033[2J\033[H";
    framebuffer += "┌─ Editor (q to exit) ─┐\n";
    framebuffer += "│\n";
    
    size_t start = scroll_offset;
    size_t end = std::min(start + (term_height - 4), buffer.length());
    
    for (size_t i = start; i < end; i++) {
        framebuffer += buffer[i];
    }
    framebuffer += "\n│\n";
    framebuffer += "└────────────────────┘\n";
    
    write(STDOUT_FILENO, framebuffer.c_str(), framebuffer.length());
    fflush(stdout);
}

void AsciiEditor::handleInput(const std::string& seq) {
    if (seq == "q") exit();
    else AsciiScene::handleInput(seq);
}
