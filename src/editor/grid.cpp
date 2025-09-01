#include "grid.h"

Grid::Grid() {
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            Vector2 pos = { float(i * CELL_SIZE), float(j * CELL_SIZE) };
            matrix[i][j] = Cell(pos, DARKGRAY, LIGHTGRAY, MAROON, GRAY);
        }
    }
}

void Grid::DrawStartingPoint(){
    DrawRectangleRec({ startingPoint.x * CELL_SIZE, startingPoint.y * CELL_SIZE, CELL_SIZE, CELL_SIZE }, matrix[int(startingPoint.x)][int(startingPoint.y)].startingPointColor);
    DrawRectangleLinesEx({ startingPoint.x * CELL_SIZE, startingPoint.y * CELL_SIZE, CELL_SIZE, CELL_SIZE }, 3.0f, RED);
}

void Grid::DrawEndingPoint(){
    DrawRectangleRec({ endingPoint.x * CELL_SIZE, endingPoint.y * CELL_SIZE, CELL_SIZE, CELL_SIZE }, matrix[int(endingPoint.x)][int(endingPoint.y)].endingPointColor);
    DrawRectangleLinesEx({ endingPoint.x * CELL_SIZE, endingPoint.y * CELL_SIZE, CELL_SIZE, CELL_SIZE }, 3.0f, RED);
}

void Grid::Draw() {
    for (int i = 0; i < GRID_WIDTH; i++) {
        DrawLine(i * CELL_SIZE, 0, i * CELL_SIZE, EDITOR_HEIGHT, GRAY);
        for (int j = 0; j < GRID_HEIGHT; j++) {
            DrawLine(0, j * CELL_SIZE, EDITOR_WIDTH, j * CELL_SIZE, GRAY);
            matrix[i][j].Draw();
        }
    }

    if (startingPoint.x != -1.0f && startingPoint.y != -1.0f) {
        DrawStartingPoint();
    }

    if (endingPoint.x != -1.0f && endingPoint.y != -1.0f) {
        DrawEndingPoint();
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

void Grid::BucketHelper(int gx, int gy) {
    if (!IsInbounds(gx, gy)) return;

    // If the cell is not occupied, fill it
    if (!matrix[gx][gy].isOccupied) {
        matrix[gx][gy].isOccupied = true;
        // Recursively fill adjacent cells
        BucketHelper(gx + 1, gy);
        BucketHelper(gx - 1, gy);
        BucketHelper(gx, gy + 1);
        BucketHelper(gx, gy - 1);
    }
}

void Grid::BucketFill(int gx, int gy) {
    if (matrix[gx][gy].isOccupied) {
        printf("Bucket fill aborted: Cell (%d, %d) is occupied\n", gx, gy);
        return;
    }    
    printf("Bucketing from (%d, %d)\n", gx, gy);

    BucketHelper(gx, gy);

}

int Grid::GetAdjacentCells(int gx, int gy, std::vector<Cell> &outCells)
{
    if (IsInbounds(gx + 1, gy) && matrix[gx + 1][gy].isOccupied) outCells.push_back(matrix[gx + 1][gy]);
    if (IsInbounds(gx - 1, gy) && matrix[gx - 1][gy].isOccupied) outCells.push_back(matrix[gx - 1][gy]);
    if (IsInbounds(gx, gy + 1) && matrix[gx][gy + 1].isOccupied) outCells.push_back(matrix[gx][gy + 1]);
    if (IsInbounds(gx, gy - 1) && matrix[gx][gy - 1].isOccupied) outCells.push_back(matrix[gx][gy - 1]);

    return outCells.size();
}


void Grid::MoveFrom(int gx, int gy) {
    // TODO: Implement move
    if (!matrix[gx][gy].isOccupied) {
        printf("Move aborted: Cell (%d, %d) is not occupied\n", gx, gy);
        return;
    }
    
    printf("Moving from (%d, %d)\n", gx, gy);

    // select all adjacent cells
    std::vector<Cell> adjacentCells;

    int check = GetAdjacentCells(gx, gy, adjacentCells);
    if (check > 0) {
        printf("Found %d adjacent cells\n", check);
    } else {
        printf("No adjacent cells found\n");
    }
    printf("Found %ld adjacent cells\n", adjacentCells.size());

    // TODO: Implement move
}

void Grid::SetStartPoint(int gx, int gy) {
    if (!IsInbounds(gx, gy)) {
        printf("SetStartPoint aborted: Cell (%d, %d) is out of bounds\n", gx, gy);
        return;
    }
    printf("Start point set to (%d, %d)\n", gx, gy);
    startingPoint = { float(gx), float(gy) };
}

void Grid::SetEndPoint(int gx, int gy){
    if (!IsInbounds(gx, gy)) {
        printf("SetEndPoint aborted: Cell (%d, %d) is out of bounds\n", gx, gy);
        return;
    }
    printf("End point set to (%d, %d)\n", gx, gy);
    endingPoint = { float(gx), float(gy) };
}
