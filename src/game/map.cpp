#include "map.h"

Map::Map(){
    printf("Default Constructor\n");
}

Map::Map(const char *filename){
    LoadMap(filename);
}

void Map::LoadMap(const char *filename){
    std::ifstream in(filename);
    if (!in) {
        TraceLog(LOG_WARNING, "Map::LoadMap: could not open file: %s", filename);
        return;
    }
    
    std::string line;
    int mapWidth, mapHeight, cellSize, startPosX, startPosY, endPosX, endPosY;

    if (!std::getline(in, line)) {
        TraceLog(LOG_WARNING, "Map::LoadMap: missing header line");
        return;
    }

    printf("Reading map dimensions\n");
    std::replace(line.begin(), line.end(), ',', ' ');
    std::istringstream iss(line);
    iss >> mapWidth >> mapHeight >> cellSize >> startPosX >> startPosY >> endPosX >> endPosY;
    std::cout << "Width=" << mapWidth << " Height=" << mapHeight << " CellSize=" << cellSize << 
                " StartPosX=" << startPosX << " StartPosY=" << startPosY << 
                " EndPosX=" << endPosX << " EndPosY=" << endPosY << "\n";

    MAP_WIDTH = mapWidth;
    MAP_HEIGHT = mapHeight;
    TILE_WIDTH = cellSize;
    TILE_HEIGHT = cellSize;
    // startingPoint = { (float)(startPosX * cellSize), (float)(startPosY * cellSize) };
    // -1 to go one up
    startingPoint = { (float)(startPosX * cellSize), (float)((startPosY - 1) * cellSize) };
    endingPoint = { (float)(endPosX * cellSize), (float)((endPosY - 1) * cellSize) };

    printf("%f-%f\n", endingPoint.x, endingPoint.y);

    matrix.assign(MAP_HEIGHT, std::vector<Cell>(MAP_WIDTH));

    for (int y = 0; y < MAP_HEIGHT; ++y) {
        if (!std::getline(in, line)) {
            printf("Unexpected end of file at row %d\n", y);
            break;
        }
        std::stringstream ss(line);
        std::string token;
        for (int x = 0; x < MAP_WIDTH && std::getline(ss, token, ','); ++x) {
            int v = std::stoi(token);
            matrix[y][x] = Cell(x, y, TILE_WIDTH, (v == 1));
        }
    }

    CellToTiles();
}

void Map::CellToTiles() {
    tiles.clear();
    for (const auto& row : matrix) {
        for (const Cell& cell : row) {
            if (cell.isOccupied) {
                tiles.emplace_back(cell.position.x, cell.position.y, cell.cellSize, cell.cellSize, DARKGRAY);
            }
        }
    }
}

void Map::DrawEndPoint() {
    DrawRectangleV(endingPoint, {(float)TILE_WIDTH, (float)TILE_HEIGHT}, GREEN);
    DrawRectangleLinesEx({endingPoint.x, endingPoint.y, (float)TILE_WIDTH, (float)TILE_HEIGHT}, 2.0f, BLACK);
}
