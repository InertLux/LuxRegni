// RegniByte/include/AsciiTableEditor.h
#pragma once
#include "AsciiScene.h"
#include <vector>

struct Cell {
    std::string content;
};

struct Table {
    std::vector<std::vector<Cell>> grid;
    int active_row = 0, active_col = 0;
    int col_width = 12;
    int rows = 5, cols = 4;
    
    Table(int r = 5, int c = 4) : grid(r, std::vector<Cell>(c)), rows(r), cols(c) {}
};

class AsciiTableEditor : public AsciiScene {
protected:
    Table table;
    bool in_edit_mode = true;
    
    void renderFrame() override;
    void renderBackground(int table_x, int table_y, int table_width, int table_height) ;
    void renderTable(int table_x, int table_y, int table_width, int table_height) ;
    void handleInput(const std::string& seq) override;
    
public:
    AsciiTableEditor(int rows = 5, int cols = 4);
    void enterEditMode();
    
    void setRowData(int row, const std::vector<std::string>& data);
    void setCell(int row, int col, const std::string& content);
    std::string getCell(int row, int col) const;
    std::pair<int, int> getSelectedCell() const;
    Table& getTable() { return table; }
    const Table& getTable() const { return table; }


};
