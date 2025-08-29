#pragma once
#include "raylib.h"
#include "level_editor_defs.h"  // for GRID_* and CELL_SIZE
#include "cell.h"               // Grid stores Cells, so we need the full type

class Grid {
public:
    int width  = GRID_WIDTH;
    int height = GRID_HEIGHT;
    Cell matrix[GRID_WIDTH][GRID_HEIGHT];

    Grid();
    void Draw();
    void ShowSelectedCell();
    bool IsInbounds(Vector2 grid_pos);
};


