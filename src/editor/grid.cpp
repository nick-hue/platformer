#include "grid.h"

Grid::Grid() {
    Clear();
}

void Grid::DrawStartingPoint(){
    DrawRectangleRec({ startingPoint.x * CELL_SIZE, startingPoint.y * CELL_SIZE, CELL_SIZE, CELL_SIZE }, matrix[int(startingPoint.x)][int(startingPoint.y)].startingPointColor);
    DrawRectangleLinesEx({ startingPoint.x * CELL_SIZE, startingPoint.y * CELL_SIZE, CELL_SIZE, CELL_SIZE }, 3.0f, RED);
}

void Grid::DrawEndingPoint(){
    DrawRectangleRec({ endingPoint.x * CELL_SIZE, endingPoint.y * CELL_SIZE, CELL_SIZE, CELL_SIZE }, matrix[int(endingPoint.x)][int(endingPoint.y)].endingPointColor);
    DrawRectangleLinesEx({ endingPoint.x * CELL_SIZE, endingPoint.y * CELL_SIZE, CELL_SIZE, CELL_SIZE }, 3.0f, RED);
}

void Grid::Clear()
{
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            Vector2 pos = { float(i * CELL_SIZE), float(j * CELL_SIZE) };
            matrix[i][j] = Cell(pos, DARKGRAY, LIGHTGRAY, MAROON, GRAY);
        }
    }
    triangles.clear();
    triangleSpots.clear();

    startingPoint.x = -1.0f;
    startingPoint.y = -1.0f;
    
    endingPoint.x = -1.0f;
    endingPoint.y = -1.0f;
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

    for (MyTriangle tri : triangles) {
        tri.Draw();
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


// TODO: Implement move
void Grid::MoveFrom(int gx, int gy) {
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

bool Grid::TriangleExistsAt(Vector2 pos){
    for (Vector2 v : triangleSpots){
        if (v.x == pos.x && v.y == pos.y){
            printf("Triangle already on grid.\n");
            return true;
        }
    }
    return false;
}

void Grid::MakeCustomTriangle(int gx, int gy, TriangleMode mode){
    if (!IsInbounds(gx, gy)) {
        printf("DrawTriangle aborted: Cell (%d, %d) is out of bounds\n", gx, gy);
        return;
    }

    if (TriangleExistsAt(Vector2{ static_cast<float>(gx), static_cast<float>(gy) })) return;

    triangles.emplace_back(MyTriangle(gx, gy, BLUE, mode));
    triangleSpots.emplace_back(Vector2{ static_cast<float>(gx), static_cast<float>(gy) });
    printf("triangles size: %ld\n", triangles.size());

}

void Grid::ImportMap(const char* filename) {
    // Build the same path you log/Export with
    std::string fullpath = baseMapFilePath + filename;
    printf("Importing map from %s\n", fullpath.c_str());  // simpler & accurate

    std::ifstream in(fullpath);
    if (!in) {
        TraceLog(LOG_WARNING, "Map::LoadMap: could not open file: %s", fullpath.c_str());
        return;
    }

    std::string line;
    int fileW=0, fileH=0, fileCell=0, startX=0, startY=0, endX=0, endY=0;

    if (!std::getline(in, line)) {
        TraceLog(LOG_WARNING, "Map::LoadMap: missing header line");
        return;
    }

    // Header: "W, H, CELL, startX, startY, endX, endY"
    std::replace(line.begin(), line.end(), ',', ' ');
    std::istringstream iss(line);
    iss >> fileW >> fileH >> fileCell >> startX >> startY >> endX >> endY;

    printf("Width=%d Height=%d Cell=%d  Start=(%d,%d) End=(%d,%d)\n",
           fileW, fileH, fileCell, startX, startY, endX, endY);

    Clear();

    if (startX >= 0 && startX < GRID_WIDTH && startY >= 0 && startY < GRID_HEIGHT) {
        startingPoint = { (float)startX, (float)startY };
    } else {
        startingPoint = { -1.0f, -1.0f };
    }

    if (endX >= 0 && endX < GRID_WIDTH && endY >= 0 && endY < GRID_HEIGHT) {
        endingPoint = { (float)endX, (float)endY };
    } else {
        endingPoint = { -1.0f, -1.0f };
    }

    for (int y = 0; y < fileH && y < GRID_HEIGHT; ++y) {
        if (!std::getline(in, line)) break;
        std::stringstream ss(line);
        std::string token;
        for (int x = 0; x < fileW && x < GRID_WIDTH && std::getline(ss, token, ','); ++x) {
            int v = std::stoi(token);
            matrix[x][y].isOccupied = (v == 1);
        }
    }
}

void Grid::ExportMap(const char *filename){
    printf("Exporting map to %s/%s\n", baseMapFilePath.c_str(), filename);

    std::string fullPath = baseMapFilePath + filename;
    FILE *file = fopen(fullPath.c_str(), "w");
    if (!file) {
        printf("Failed to open file for writing: %s\n", fullPath.c_str());
        return;
    }

    if (startingPoint.x == -1.0f && startingPoint.y == -1.0f) {
        SetStartPoint(0,0);
    }
    if (endingPoint.x == -1.0f && endingPoint.y == -1.0f) {
        SetEndPoint(1,1);
    }

    std::string header = std::to_string(GRID_WIDTH) + ", " + std::to_string(GRID_HEIGHT) 
                        + ", " + std::to_string(CELL_SIZE)
                        + ", " + std::to_string(int(startingPoint.x)) + ", " + std::to_string(int(startingPoint.y)) + 
                        + ", " + std::to_string(int(endingPoint.x)) + ", " + std::to_string(int(endingPoint.y)) + "\n";

    fputs(header.c_str(), file);

    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            fputc(matrix[x][y].isOccupied ? '1' : '0', file);
            if (x < GRID_WIDTH - 1) fputc(',', file);
        }
        fputc('\n', file);
    }

    fclose(file);
    printf("Map exported to %s\n", fullPath.c_str());
}


int Grid::GetTriangleIndex(int gx, int gy) {
    for (size_t i = 0; i < triangleSpots.size(); ++i) {
        if (triangleSpots[i].x == gx && triangleSpots[i].y == gy) {
            return static_cast<int>(i);
        }
    }
    return -1;  // Not found
}