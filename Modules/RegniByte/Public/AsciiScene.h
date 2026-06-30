// RegniByte/include/AsciiScene.h
#pragma once
#include <string>
#include <functional>
#include <unordered_map>
#include <termios.h>

class AsciiScene {
protected:
    int term_width = 80, term_height = 24;
    std::string framebuffer;
    termios orig_termios;
    bool running = false;
    std::string QuitMessage = "";
    
    using KeyHandler = std::function<void()>;
    std::unordered_map<std::string, KeyHandler> keybindings;
    
    void getTermSize();
    void enableRawMode();
    void disableRawMode();
    std::string readInput();
    void handleSignal(int sig);
    
    virtual void renderFrame() = 0;
    virtual void handleInput(const std::string& seq);
    
public:
    AsciiScene();
    virtual ~AsciiScene();
    
    void bindKey(const std::string& sequence, KeyHandler handler);
    void run();
    void exit(std::string quitMessage = "[Scene Closed]");
};



class AsciiEditor : public AsciiScene {
protected:
    std::string buffer;
    int cursor_x = 0, cursor_y = 0;
    int scroll_offset = 0;
    
    void renderFrame() override;
    void handleInput(const std::string& seq) override;
    
public:
    AsciiEditor(const std::string& initial_content = "");
    std::string getContent() const { return buffer; }
    void setContent(const std::string& content) { buffer = content; cursor_x = cursor_y = 0; }
};


