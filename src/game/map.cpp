#include "map.h"

Map::Map(){
    printf("Default Constructor\n");
    // LoadMap("exported_map_1.txt");
    LoadMap("exported_map_1.txt");
}

Map::Map(const char *filename){
    LoadMap("exported_map_1.txt");
    // LoadMap(filename);
}

void Map::LoadMap(const char *filename){
    std::string fullpath = grid.baseMapFilePath + filename;

    printf("Loading map from %s\n", fullpath.c_str());
    
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

    MAP_TILE_WIDTH   = fileW;
    MAP_TILE_HEIGHT  = fileH;
    TILE_HEIGHT = fileCell;
    TILE_WIDTH  = fileCell;

    MAP_WIDTH   = MAP_TILE_WIDTH * TILE_WIDTH;
    MAP_HEIGHT  = MAP_TILE_HEIGHT * TILE_HEIGHT;
    
    printf("Tile Size: %dx%d\n", TILE_WIDTH, TILE_HEIGHT);
    printf("Map Tile Size: %dx%d\n", MAP_TILE_WIDTH, MAP_TILE_HEIGHT);
    printf("Map Size: %dx%d\n", MAP_WIDTH, MAP_HEIGHT);

    grid.Clear();

    if (startX >= 0 && startX < GRID_WIDTH && startY >= 0 && startY < GRID_HEIGHT) {
        grid.startingPoint = { (float)startX * TILE_WIDTH, (float)startY * TILE_HEIGHT };
    } else {
        grid.startingPoint = { -1.0f, -1.0f };
    }

    if (endX >= 0 && endX < GRID_WIDTH && endY >= 0 && endY < GRID_HEIGHT) {
        grid.endingPoint = { (float)endX * TILE_WIDTH, (float)endY * TILE_HEIGHT };
    } else {
        grid.endingPoint = { -1.0f, -1.0f };
    }

    for (int y = 0; y < fileH && y < GRID_HEIGHT; ++y) {
        if (!std::getline(in, line)) break;
        std::stringstream ss(line);
        std::string token;

        for (int x = 0; x < fileW && x < GRID_WIDTH && std::getline(ss, token, ','); ++x) {
            int v = 0;
            try { v = std::stoi(token); } catch (...) { v = 0; }

            switch (v) {
                case 0: // EMPTY
                    grid.matrix[x][y].isOccupied = false;
                    break;
                case 1: // FILLED
                    grid.matrix[x][y].isOccupied = true;
                    break;
                case 2: // TRI_UP
                    grid.matrix[x][y].isOccupied = false;
                    grid.MakeCustomTriangle(x, y, TriangleMode::UP);
                    break;
                case 3: // TRI_DOWN
                    grid.matrix[x][y].isOccupied = false;
                    grid.MakeCustomTriangle(x, y, TriangleMode::DOWN);
                    break;
                case 4: // TRI_LEFT
                    grid.matrix[x][y].isOccupied = false;
                    grid.MakeCustomTriangle(x, y, TriangleMode::LEFT);
                    break;
                case 5: // TRI_RIGHT
                    grid.matrix[x][y].isOccupied = false;
                    grid.MakeCustomTriangle(x, y, TriangleMode::RIGHT);
                    break;
                default:
                    grid.matrix[x][y].isOccupied = false;
                    break;
            }
        }
    }

    CellToTiles();
}

void Map::CellToTiles() {
    tiles.clear();
    for (const auto& row : grid.matrix) {
        for (const Cell& cell : row) {
            if (cell.isOccupied) {
                tiles.emplace_back(cell.position.x, cell.position.y, cell.cellSize, cell.cellSize, DARKGRAY);
            }
        }
    }
}

void Map::DrawEndPoint() {
    DrawRectangleV(grid.endingPoint, {(float)TILE_WIDTH, (float)TILE_HEIGHT}, GREEN);
    DrawRectangleLinesEx({grid.endingPoint.x, grid.endingPoint.y, (float)TILE_WIDTH, (float)TILE_HEIGHT}, 2.0f, BLACK);
}

void Map::Draw() {
    for (const auto& tile : tiles) {
        tile.Draw();
    }

    for (MyTriangle tri : grid.triangles) {
        tri.Draw();
    }
}