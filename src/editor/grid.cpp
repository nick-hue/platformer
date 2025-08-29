#include "grid.h"

Grid::Grid() {
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            Vector2 pos = { float(i * CELL_SIZE), float(j * CELL_SIZE) };
            matrix[i][j] = Cell(pos, DARKGRAY, LIGHTGRAY, MAROON, GRAY);
        }
    }
}

void Grid::Draw() {
    for (int i = 0; i < GRID_WIDTH; i++) {
        DrawLine(i * CELL_SIZE, 0, i * CELL_SIZE, EDITOR_HEIGHT, GRAY);
        for (int j = 0; j < GRID_HEIGHT; j++) {
            DrawLine(0, j * CELL_SIZE, EDITOR_WIDTH, j * CELL_SIZE, GRAY);
            matrix[i][j].Draw();
        }
    }
}

void Grid::ShowSelectedCell() {
    Vector2 mouse_pos = GetMousePosition();
    Vector2 grid_pos = { mouse_pos.x / CELL_SIZE, mouse_pos.y / CELL_SIZE };
    if (grid_pos.x >= 0 && grid_pos.x < GRID_WIDTH && grid_pos.y >= 0 && grid_pos.y < GRID_HEIGHT) {
        matrix[int(grid_pos.x)][int(grid_pos.y)].Select();
    }
}

bool Grid::IsInbounds(int gx, int gy) {
    return (gx >= 0 && gx < GRID_WIDTH &&
            gy >= 0 && gy < GRID_HEIGHT);
}
