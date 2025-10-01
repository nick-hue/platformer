#include "map.h"
#include "game.h"

Map::Map(){
    printf("Default Constructor\n");
}

Map::Map(const char *filename){
    // LoadMap(filename);
    LoadMapBinary(filename);
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
    
    // printf("Tile Size: %dx%d\n", TILE_WIDTH, TILE_HEIGHT);
    // printf("Map Tile Size: %dx%d\n", MAP_TILE_WIDTH, MAP_TILE_HEIGHT);
    // printf("Map Size: %dx%d\n", MAP_WIDTH, MAP_HEIGHT);

    grid.Clear();

    if (startX >= 0 && startX < GRID_WIDTH && startY >= 0 && startY < GRID_HEIGHT)
        grid.startingPointGridPos = {startX, startY};
    else
        grid.startingPointGridPos = {-1,-1};

    if (endX >= 0 && endX < GRID_WIDTH && endY >= 0 && endY < GRID_HEIGHT)
        grid.endingPointGridPos = {endX, endY};
    else
        grid.endingPointGridPos = {-1,-1};

    grid.SyncFromGridPositions();

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

TileType Map::GetTypeForTile(int i, int j){
    if (j-1 < 0) return TileType::GROUND;
    Cell cellAbove = grid.matrix[i][j-1];
    
    if (!cellAbove.isOccupied){
        return TileType::GRASS;
    } else {
        // one out of 10 times return broken
        int r = rand() % 10;  
        return (r != 0) ? TileType::GROUND : TileType::BROKEN;
    }

}

void Map::CellToTiles() {
    tiles.clear();
    for (int i = 0; i < grid.width; i++){
        for (int j = 0; j < grid.height; j++){
            Cell cell = grid.matrix[i][j];
            if (cell.isOccupied) {
                TileType type = GetTypeForTile(i, j);
                // printf("%d-%d -> ", i ,j); TileTypeToString(type);
                tiles.emplace_back(cell.position.x, cell.position.y, cell.cellSize, cell.cellSize, DARKGRAY, type);
            }
        }
    }
}

void Map::DrawEndPoint() {
    DrawRectangleV(grid.endingPoint, {(float)TILE_WIDTH, (float)TILE_HEIGHT}, GREEN);
    DrawRectangleLinesEx({grid.endingPoint.x, grid.endingPoint.y, (float)TILE_WIDTH, (float)TILE_HEIGHT}, 2.0f, BLACK);
}

void Map::DrawBackground(GameState& gameState){
    DrawTextureEx(gameState.textureHandler.background, Vector2{ gameState.gameUI.scrollBack, gameState.gameUI.yOffset }, 0.0f, gameState.gameUI.bgScale, WHITE);
    DrawTextureEx(gameState.textureHandler.background, Vector2{ gameState.gameUI.scrollBack + gameState.gameUI.wrapW, gameState.gameUI.yOffset }, 0.0f, gameState.gameUI.bgScale, WHITE);
}

void Map::Draw(GameState& gameState){
    DrawBackground(gameState);

    for (auto& tile : tiles) {
        tile.Draw();
    }

    for (MyTriangle tri : grid.triangles) {
        tri.Draw();
    }
}

void Map::ReloadMap(GameState& gameState) {
    gameState.player.position = grid.startingPoint;
    LoadMap(gameState.currLevelFilename.c_str());
    gameState.keyGoalSprite.position = grid.endingPoint;
    gameState.textureHandler.SetupTextures(gameState);  
}


void Map::LoadMapBinary(const char* filename) {
    if (!grid.LoadBinary(filename)) return;

    // Sync your map sizes if needed (you currently derive sizes from the header in text mode)
    MAP_TILE_WIDTH  = GRID_WIDTH;
    MAP_TILE_HEIGHT = GRID_HEIGHT;
    TILE_WIDTH = CELL_SIZE;
    TILE_HEIGHT = CELL_SIZE;
    MAP_WIDTH  = MAP_TILE_WIDTH * TILE_WIDTH;
    MAP_HEIGHT = MAP_TILE_HEIGHT * TILE_HEIGHT;

    CellToTiles();
}
