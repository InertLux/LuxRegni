// RegniByte/src/AsciiTableEditor.cpp
#include "Editors/AsciiTableEditor.h"
#include <cstdio>
#include <unistd.h>
#include <iostream>


AsciiTableEditor::AsciiTableEditor(int rows, int cols) : table(rows, cols) {
    bindKey("q", [this]() { this->exit(); });
    bindKey("A", [this]() { if (table.active_row > 0) table.active_row--; });
    bindKey("B", [this]() { if (table.active_row < table.rows - 1) table.active_row++; });
    bindKey("D", [this]() { if (table.active_col > 0) table.active_col--; });
    bindKey("C", [this]() { if (table.active_col < table.cols - 1) table.active_col++; });
    bindKey("\r", [this]() { enterEditMode(); });
    bindKey("\n", [this]() { enterEditMode(); });
}




void AsciiTableEditor::enterEditMode() {
    std::string input = table.grid[table.active_row][table.active_col].content;
    in_edit_mode = true;
    char c;
    
    while (read(STDIN_FILENO, &c, 1) == 1) {
        if (c == 27) break; // ESC
        if (c == '\r' || c == '\n') {
            if (input.length() > (size_t)table.col_width) {
                input = input.substr(0, table.col_width);
            }
            table.grid[table.active_row][table.active_col].content = input;
            in_edit_mode = false;
            renderFrame();
            return;
        }
        if (c == 127 || c == 8) { // Backspace
            if (!input.empty()) input.pop_back();
        } else if (c >= 32 && c < 127) {
            input += c;
        }
        table.grid[table.active_row][table.active_col].content = input;
        renderFrame();
    }
    in_edit_mode = false;
    renderFrame();
}
void AsciiTableEditor::setRowData(int row, const std::vector<std::string>& data) {
    for (size_t i = 0; i < data.size() && i < (size_t)table.cols; ++i) {
        table.grid[row][i].content = data[i];
    }
}

void AsciiTableEditor::setCell(int row, int col, const std::string& content) {
    if (row >= 0 && row < table.rows && col >= 0 && col < table.cols) {
        table.grid[row][col].content = content;
    }
}

std::string AsciiTableEditor::getCell(int row, int col) const {
    if (row >= 0 && row < table.rows && col >= 0 && col < table.cols) {
        return table.grid[row][col].content;
    }
    return "";
}

std::pair<int, int> AsciiTableEditor::getSelectedCell() const {
    return {table.active_row, table.active_col};
}


void AsciiTableEditor::renderBackground(int table_x, int table_y, int table_width, int table_height) {
    int shadow_left = 4;
    int shadow_top = 1;
    int shadow_right = 3;
    int shadow_bottom = 1;
    
    for (int y = 0; y < term_height; ++y) {
        for (int x = 0; x < term_width; ++x) {
            // Skip table area
            if (x >= table_x && x < table_x + table_width &&
                y >= table_y && y < table_y + table_height) {
                continue;
            }
            
            // Check if in shadow zone (left, top, right, bottom of table)
            int shadow_x_min = table_x - shadow_left;
            int shadow_x_max = table_x + table_width + shadow_right;
            int shadow_y_min = table_y - shadow_top;
            int shadow_y_max = table_y + table_height + shadow_bottom;
            
            if (x >= shadow_x_min && x < shadow_x_max &&
                y >= shadow_y_min && y < shadow_y_max) {

                if ((x + y) % 2 == 0) {
                    int hash = ((x * 73856093) ^ (y * 19349663)) & 0x7FFFFFFF;
                    int color = 31 + (hash % 6);  // 31-36: black, red, green, yellow, blue, magenta, cyan
                    framebuffer += "\033[" + std::to_string(color) + "m.\033[0m";
                } else {
                    framebuffer += " ";
                }
            } else {
                framebuffer += " ";
            }
        }
        framebuffer += "\n";
    }
}


void AsciiTableEditor::renderTable(int table_x, int table_y, int table_width, int table_height) {
    // Draw border
    for (int y = 0; y < table_height; ++y) {
        framebuffer += "\033[" + std::to_string(table_y + y) + ";" + std::to_string(table_x) + "H";
        for (int x = 0; x < table_width; ++x) {
            std::string ch = " ";
            if (y == 0 && x == 0) ch = "┌";
            else if (y == 0 && x == table_width - 1) ch = "┐";
            else if (y == table_height - 1 && x == 0) ch = "└";
            else if (y == table_height - 1 && x == table_width - 1) ch = "┘";
            else if (y == 0 && x > 0 && x < table_width - 1) ch = "─";
            else if (y == table_height - 1 && x > 0 && x < table_width - 1) ch = "─";
            else if (x == 0 || x == table_width - 1) ch = "│";
            
            if (y == 1 && x > 0 && x < table_width - 1) ch = "─";
            if (y == 1 && x == 0) ch = "├";
            if (y == 1 && x == table_width - 1) ch = "┤";
            framebuffer += ch;
        }
    }

    // Draw cells
    for (int r = 0; r < table.rows; ++r) {
        framebuffer += "\033[" + std::to_string(table_y + r + 2) + ";" + std::to_string(table_x + 2) + "H";
        for (int c = 0; c < table.cols; ++c) {
            if (r == table.active_row && c == table.active_col) framebuffer += "\033[7m";
            std::string cell_content = table.grid[r][c].content;
            if (cell_content.length() > (size_t)table.col_width) {
                cell_content = cell_content.substr(0, table.col_width);
            }
            char buf[64];
            snprintf(buf, sizeof(buf), "%-*s", table.col_width, cell_content.c_str());
            framebuffer += buf;
            framebuffer += "\033[0m";
            if (c < table.cols - 1) framebuffer += "│";
        }
    }

    // Draw metadata below
    int metadata_y = table_y + table_height + 1;
    framebuffer += "\033[" + std::to_string(metadata_y) + ";" + std::to_string(table_x) + "H";
    framebuffer += "Cell [" + std::to_string(table.active_row) + "," + std::to_string(table.active_col) + "]: ";
    framebuffer += table.grid[table.active_row][table.active_col].content;
    
    framebuffer += "\033[" + std::to_string(metadata_y + 1) + ";" + std::to_string(table_x) + "H";
    if (in_edit_mode) {
        framebuffer += "ENTER: save | ESC: cancel";
    } else {
        framebuffer += "ENTER: edit | q: quit | Arrow keys: navigate";
    }
}

void AsciiTableEditor::renderFrame() {
    framebuffer.clear();
    framebuffer += "\033[2J\033[H";
    
    int table_width = table.cols * (table.col_width + 1) + 1;
    int table_height = table.rows + 2;
    int table_x = (term_width - table_width) / 2;
    int table_y = (term_height - table_height) / 2;
    
    if (in_edit_mode) {
        framebuffer += "\033[1;1H[EDIT]\n";
    }
    
    renderBackground(table_x, table_y, table_width, table_height);
    renderTable(table_x, table_y, table_width, table_height);
    
    write(STDOUT_FILENO, framebuffer.c_str(), framebuffer.length());
    fflush(stdout);
}

void AsciiTableEditor::handleInput(const std::string& seq) {
    if (seq == "q") exit();
    else AsciiScene::handleInput(seq);
}
