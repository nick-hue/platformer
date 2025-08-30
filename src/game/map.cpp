#include "map.h"

Map::Map(){
    printf("Default Constructor\n");
}

Map::Map(const char *filename){
    
    std::ifstream in(filename);
    if (!in) {
        TraceLog(LOG_WARNING, "Map::LoadMap: could not open file: %s", filename);
        return;
    }
    
    std::string line;
    int mapWidth, mapHeight, cell_size;

    if (!std::getline(in, line)) {
        TraceLog(LOG_WARNING, "Map::LoadMap: missing header line");
        return;
    }

    printf("Reading map dimensions\n");
    std::replace(line.begin(), line.end(), ',', ' ');
    std::istringstream iss(line);
    iss >> mapWidth >> mapHeight >> cell_size;
    std::cout << "Width=" << mapWidth << " Height=" << mapHeight << " CellSize=" << cell_size << "\n";

    MAP_WIDTH = mapWidth;
    MAP_HEIGHT = mapHeight;
    TILE_WIDTH = cell_size;
    TILE_HEIGHT = cell_size;

    matrix.assign(MAP_HEIGHT, std::vector<Cell>(MAP_WIDTH));

    // for (int y = 0; y < MAP_HEIGHT; ++y) {

    //     if (!std::getline(in, line)) {
    //         printf("Unexpected end of file at row %d\n", y);
    //         break;
    //     }
    //     for (int x = 0; x < line.size(); x++){
    //         if (x % 2 == 1) continue;
    //         int v = line[x] - '0'; // convert char to int
    //         printf("%d-", v);
    //         matrix[y][x] = Cell(x, y, cell_size, (v == 1));

    //     }
    //     printf("\n");
    // }

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

    // for (const auto& row : matrix) {
    //     for (Cell cell : row) {
    //         cell.ToString();
    //     }
    // }

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
