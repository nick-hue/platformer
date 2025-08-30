#pragma once
#include "raylib.h"
#include "level_editor_defs.h"  // for GRID_* and CELL_SIZE
#include "cell.h"               // Grid stores Cells, so we need the full type
#include <vector>

class Grid {
public:
    int width  = GRID_WIDTH;
    int height = GRID_HEIGHT;
    Cell matrix[GRID_WIDTH][GRID_HEIGHT];

    Grid();
    void Draw();
    void ShowSelectedCell();
    bool IsInbounds(int gx, int gy);
    void BucketFill(int gx, int gy);
    void BucketHelper(int gx, int gy);
    void MoveFrom(int gx, int gy);
    int GetAdjacentCells(int gx, int gy, std::vector<Cell>& outCells);
};


