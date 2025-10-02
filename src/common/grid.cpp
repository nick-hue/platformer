#include "grid.h"
#include "game.h"   
#include <cstdint>
Grid::Grid() {
    Clear();
}

void Grid::DrawStartingPoint() {
    DrawRectangleRec({ startingPoint.x, startingPoint.y, (float)CELL_SIZE, (float)CELL_SIZE },
                     matrix[startingPointGridPos.first][startingPointGridPos.second].startingPointColor);
    DrawRectangleLinesEx({ startingPoint.x, startingPoint.y, (float)CELL_SIZE, (float)CELL_SIZE }, 3.0f, RED);
}

void Grid::DrawEndingPointHitbox() {
    DrawRectangleRec(endingPointRect, GREEN);
    DrawRectangleLinesEx(endingPointRect, 1.0f, BLACK);
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
    platforms.clear();

    startingPointGridPos = {-1, -1};
    endingPointGridPos   = {-1, -1};
    SyncFromGridPositions(matrix[0]->cellSize);
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
        DrawEndingPointHitbox();
    }

    for (MyTriangle tri : triangles) {
        tri.Draw();
    }
}

void Grid::DrawEditor() {
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
        DrawEndingPointHitbox();
    }

    for (MyTriangle tri : triangles) {
        tri.DrawEditor();
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
    if (!IsInbounds(gx, gy)) { printf("SetStartPoint aborted: Cell (%d, %d) is out of bounds\n", gx, gy); return; }
    startingPointGridPos = { gx, gy };
    SyncFromGridPositions(matrix[0]->cellSize);
}

void Grid::SetEndPoint(int gx, int gy) {
    if (!IsInbounds(gx, gy)) { printf("SetEndPoint aborted: Cell (%d, %d) is out of bounds\n", gx, gy); return; }
    endingPointGridPos = { gx, gy };
    SyncFromGridPositions(matrix[0]->cellSize);
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
    // printf("triangles size: %ld\n", triangles.size());

}

void Grid::ImportMap(const char* filename) {
    // Build the same path you log/Export with
    std::string fullpath = baseMapFilePath + filename;
    printf("Importing map from %s\n", fullpath.c_str());  // simpler & accurate

    std::ifstream in(fullpath);
    if (!in) {
        TraceLog(LOG_WARNING, "Map::ImportMap: could not open file: %s", fullpath.c_str());
        return;
    }

    std::string line;
    int fileW=0, fileH=0, fileCell=0, startX=0, startY=0, endX=0, endY=0;

    if (!std::getline(in, line)) {
        TraceLog(LOG_WARNING, "Map::ImportMap: missing header line");
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
            int v = 0;
            try { v = std::stoi(token); } catch (...) { v = 0; }

            switch (v) {
                case 0: // EMPTY
                    matrix[x][y].isOccupied = false;
                    break;
                case 1: // FILLED
                    matrix[x][y].isOccupied = true;
                    break;
                case 2: // TRI_UP
                    matrix[x][y].isOccupied = false;
                    MakeCustomTriangle(x, y, TriangleMode::UP);
                    break;
                case 3: // TRI_DOWN
                    matrix[x][y].isOccupied = false;
                    MakeCustomTriangle(x, y, TriangleMode::DOWN);
                    break;
                case 4: // TRI_LEFT
                    matrix[x][y].isOccupied = false;
                    MakeCustomTriangle(x, y, TriangleMode::LEFT);
                    break;
                case 5: // TRI_RIGHT
                    matrix[x][y].isOccupied = false;
                    MakeCustomTriangle(x, y, TriangleMode::RIGHT);
                    break;
                default:
                    matrix[x][y].isOccupied = false;
                    break;
            }
        }
    }
    
}

StoreItem Grid::ClassifyCell(int x, int y) const {
    int idx = GetTriangleIndex(x, y);
    if (idx != -1) {
        switch (triangles[idx].mode) {
            case TriangleMode::UP:    return StoreItem::TRI_UP;
            case TriangleMode::DOWN:  return StoreItem::TRI_DOWN;
            case TriangleMode::LEFT:  return StoreItem::TRI_LEFT;
            case TriangleMode::RIGHT: return StoreItem::TRI_RIGHT;
            default: break;
        }
    }
    return matrix[x][y].isOccupied ? StoreItem::FILLED : StoreItem::EMPTY;
}

char Grid::GetOutputChar(int x, int y) const {
    return StoreItemToChar(ClassifyCell(x, y));
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
            char putChar = GetOutputChar(x, y);
            fputc(putChar, file);
            if (x < GRID_WIDTH - 1) fputc(',', file);
        }
        fputc('\n', file);
    }

    fclose(file);
    printf("Map exported to %s\n", fullPath.c_str());
}


int Grid::GetTriangleIndex(int gx, int gy) const {
    for (size_t i = 0; i < triangleSpots.size(); ++i) {
        if (triangleSpots[i].x == gx && triangleSpots[i].y == gy) {
            return static_cast<int>(i);
        }
    }
    return -1;  // Not found
}

void Grid::RemoveTriangleByIndex(int index) {
    if (index == -1) return;

    triangles.erase(triangles.begin() + index);
    triangleSpots.erase(triangleSpots.begin() + index);
}

bool IsPlayerBelowDownSpike(const Rectangle& player, const MyTriangle& tri) {
    return ((player.x < tri.position.x + CELL_SIZE) && (player.x + player.width > tri.position.x)) 
    && (player.y > tri.position.y);
}

void Grid::UpdateTriangles(GameState& gameState){
    for (MyTriangle& tri : triangles) {
        if (tri.mode == gameState.movingSpikeMode) {
            if (!tri.falling && IsPlayerBelowDownSpike(gameState.player.rect, tri)) {
                tri.falling = true;
                tri.velocityY = 0.0f;
            }
            if (tri.falling) {
                tri.velocityY += GRAVITY * gameState.dt;
                tri.position.y += tri.velocityY * gameState.dt;
                tri.UpdateGeometry();
            }
        }
    }

    for (int i = (int)triangles.size()-1; i >= 0; --i) {
        float triBottom = std::max({triangles[i].vertices[0].y,
                                    triangles[i].vertices[1].y,
                                    triangles[i].vertices[2].y});
        if (triBottom >= gameState.map.MAP_HEIGHT) RemoveTriangleByIndex(i);
        
        for (const Tile& tile : gameState.map.tiles) {
            if (triangles[i].falling && CheckCollisionPointRec({triangles[i].position.x + CELL_SIZE/2, triBottom}, tile.rect)) {
                RemoveTriangleByIndex(i);
                PlaySound(gameState.soundManager.spikeBreak);
                break;  // Exit the inner loop since the triangle is removed
            }
        }
    }
}

namespace {
    struct FileHeader {
        char magic[4] = {'G','R','I','D'}; // "GRID"
        uint32_t version = 1;
        uint32_t width;
        uint32_t height;
        uint32_t cellSize;
    };

    struct CellBlob {
        uint8_t occupied; // 0/1
    };

    struct TriBlob {
        int32_t gx, gy;     // grid coords (not pixels)
        int32_t mode;       // TriangleMode enum as int
    };
}

bool Grid::SaveBinary(const char* filename) const {
    std::string full = baseMapFilePath + filename;
    FILE* f = fopen(full.c_str(), "wb");
    if (!f) { printf("SaveBinary: can't open %s\n", full.c_str()); return false; }

    FileHeader hdr{ {'G','R','I','D'}, 1, GRID_WIDTH, GRID_HEIGHT, CELL_SIZE };
    fwrite(&hdr, sizeof(hdr), 1, f);

    // v3: write pixel positions first (screen-space)
    int32_t startPx = (int32_t)startingPoint.x;
    int32_t startPy = (int32_t)startingPoint.y;
    int32_t endPx   = (int32_t)endingPoint.x;
    int32_t endPy   = (int32_t)endingPoint.y;
    fwrite(&startPx, sizeof(startPx), 1, f);
    fwrite(&startPy, sizeof(startPy), 1, f);
    fwrite(&endPx,   sizeof(endPx),   1, f);
    fwrite(&endPy,   sizeof(endPy),   1, f);

    // v3: also write grid indices (authoritative for logic)
    int32_t sgx = startingPointGridPos.first,  sgy = startingPointGridPos.second;
    int32_t egx = endingPointGridPos.first,    egy = endingPointGridPos.second;
    fwrite(&sgx, sizeof(sgx), 1, f);
    fwrite(&sgy, sizeof(sgy), 1, f);
    fwrite(&egx, sizeof(egx), 1, f);
    fwrite(&egy, sizeof(egy), 1, f);

    // cells
    for (int y = 0; y < GRID_HEIGHT; ++y)
        for (int x = 0; x < GRID_WIDTH; ++x) {
            uint8_t occ = matrix[x][y].isOccupied ? 1u : 0u;
            fwrite(&occ, 1, 1, f);
        }

    // triangles
    uint32_t tcount = (uint32_t)triangles.size();
    fwrite(&tcount, sizeof(tcount), 1, f);
    for (size_t i = 0; i < triangles.size(); ++i) {
        TriBlob tb{ (int32_t)triangleSpots[i].x, (int32_t)triangleSpots[i].y, (int32_t)triangles[i].mode };
        fwrite(&tb, sizeof(tb), 1, f);
    }

    fclose(f);
    printf("Saved grid to %s\n", full.c_str());
    return true;
}

bool Grid::LoadBinary(const char* filename) {
    std::string full = baseMapFilePath + filename;
    FILE* f = fopen(full.c_str(), "rb");
    if (!f) { printf("LoadBinary: can't open %s\n", full.c_str()); return false; }

    FileHeader hdr{};
    if (fread(&hdr, sizeof(hdr), 1, f) != 1 || strncmp(hdr.magic, "GRID", 4) != 0) {
        printf("LoadBinary: bad header in %s\n", full.c_str()); fclose(f); return false;
    }

    int32_t sx_v1=0, sy_v1=0, ex_v1=0, ey_v1=0;   // old block (v1/v2 meaning: grid coords)
    int32_t startPx=0, startPy=0, endPx=0, endPy=0; // new block (v3)
    int32_t sgx=-1, sgy=-1, egx=-1, egy=-1;        // grid indices

    if (hdr.version >= 3) {
        // read pixel block
        fread(&startPx, sizeof(startPx), 1, f);
        fread(&startPy, sizeof(startPy), 1, f);
        fread(&endPx,   sizeof(endPx),   1, f);
        fread(&endPy,   sizeof(endPy),   1, f);
        // read grid indices
        fread(&sgx, sizeof(sgx), 1, f);
        fread(&sgy, sizeof(sgy), 1, f);
        fread(&egx, sizeof(egx), 1, f);
        fread(&egy, sizeof(egy), 1, f);
    } else if (hdr.version == 2) {
        // v2 wrote 4 ints "v1 block" as grid coords + 4 ints grid indices
        fread(&sx_v1, sizeof(sx_v1), 1, f);
        fread(&sy_v1, sizeof(sy_v1), 1, f);
        fread(&ex_v1, sizeof(ex_v1), 1, f);
        fread(&ey_v1, sizeof(ey_v1), 1, f);
        fread(&sgx, sizeof(sgx), 1, f);
        fread(&sgy, sizeof(sgy), 1, f);
        fread(&egx, sizeof(egx), 1, f);
        fread(&egy, sizeof(egy), 1, f);
    } else { // v1
        fread(&sx_v1, sizeof(sx_v1), 1, f);
        fread(&sy_v1, sizeof(sy_v1), 1, f);
        fread(&ex_v1, sizeof(ex_v1), 1, f);
        fread(&ey_v1, sizeof(ey_v1), 1, f);
        sgx = sx_v1; sgy = sy_v1;
        egx = ex_v1; egy = ey_v1;
    }

    Clear();

    // Authoritative: grid indices
    if (sgx < 0 || sgy < 0 || sgx >= GRID_WIDTH || sgy >= GRID_HEIGHT)
        startingPointGridPos = {-1,-1};
    else
        startingPointGridPos = { sgx, sgy };

    if (egx < 0 || egy < 0 || egx >= GRID_WIDTH || egy >= GRID_HEIGHT)
        endingPointGridPos = {-1,-1};
    else
        endingPointGridPos = { egx, egy };

    // compute pixel positions/rects from grid
    SyncFromGridPositions(matrix[0]->cellSize);

    // cells
    for (int y = 0; y < GRID_HEIGHT; ++y)
        for (int x = 0; x < GRID_WIDTH; ++x) {
            uint8_t occ = 0;
            fread(&occ, 1, 1, f);
            matrix[x][y].isOccupied = (occ != 0);
        }

    // triangles
    uint32_t tcount = 0;
    fread(&tcount, sizeof(tcount), 1, f);
    for (uint32_t i = 0; i < tcount; ++i) {
        TriBlob tb{};
        fread(&tb, sizeof(tb), 1, f);
        MakeCustomTriangle(tb.gx, tb.gy, (TriangleMode)tb.mode);
    }

    fclose(f);
    printf("Loaded grid from %s\n", full.c_str());

    Dump();

    return true;
}


std::string Grid::ToString() const {
    std::ostringstream oss;

    // Basic header
    oss << "GRID DEBUG\n";
    oss << "  Size: " << GRID_WIDTH << "x" << GRID_HEIGHT
        << "  CellSize: " << CELL_SIZE << "\n";

    // Start/End (grid coords)
    oss << "  Start: (" << int(startingPoint.x) << "," << int(startingPoint.y) << ")\n";
    oss << "  StartGridPos: (" << startingPointGridPos.first << "," << startingPointGridPos.second << ")\n";
    oss << "  End  : (" << int(endingPoint.x)   << "," << int(endingPoint.y)   << ")\n";
    oss << "  EndGridPos  : (" << endingPointGridPos.first   << "," << endingPointGridPos.second   << ")\n";

    // If you keep an endingPointRect, show it too
    oss << "  EndRect(px): { x:" << int(endingPointRect.x)
        << ", y:" << int(endingPointRect.y)
        << ", w:" << int(endingPointRect.width)
        << ", h:" << int(endingPointRect.height) << " }\n";

    // Cells summary
    int occupiedCount = 0;
    for (int y = 0; y < GRID_HEIGHT; ++y)
        for (int x = 0; x < GRID_WIDTH; ++x)
            occupiedCount += matrix[x][y].isOccupied ? 1 : 0;

    oss << "  Cells: occupied=" << occupiedCount
        << " / total=" << (GRID_WIDTH * GRID_HEIGHT) << "\n";

    // Triangles summary + list
    oss << "  Triangles: " << triangles.size() << "\n";
    for (size_t i = 0; i < triangles.size(); ++i) {
        const auto& t = triangles[i];
        // triangles[i].mode is your enum; cast to int for clarity
        // position is in pixels; triangleSpots[i] (if you keep it) is grid coords
        oss << "    [" << i << "] grid_pos=("
            << int(triangleSpots[i].x) << "," << int(triangleSpots[i].y) << ") "
            << "mode=" << int(t.mode) << " position=("
            << int(t.position.x) << "," << int(t.position.y) << ")\n";
    }

    // Optional: first few rows of the occupancy map (0/1), to spot obvious mismatches
    int showingRows = 16;
    oss << "  Occupancy preview (first " << showingRows << " rows):\n";
    int previewRows = std::min(GRID_HEIGHT, showingRows);
    for (int y = 0; y < previewRows; ++y) {
        oss << "    y=" << std::setw(2) << y << " : ";
        for (int x = 0; x < GRID_WIDTH; ++x) {
            oss << (matrix[x][y].isOccupied ? '1' : '0');
        }
        oss << "\n";
    }

    return oss.str();
}

void Grid::Dump() const {
    auto s = ToString();
    printf("%s", s.c_str());
}

static inline Rectangle CellRectFromGrid(int gx, int gy) {
    return { gx * (float)CELL_SIZE, gy * (float)CELL_SIZE,
             (float)CELL_SIZE, (float)CELL_SIZE };
}

void Grid::SyncFromGridPositions(int tileSize){
    startingPoint = { (float)startingPointGridPos.first * tileSize,  (float)startingPointGridPos.second * tileSize};
    endingPoint   = { (float)endingPointGridPos.first * tileSize,    (float)endingPointGridPos.second * tileSize};
    startingPointRect = CellRectFromGrid(startingPointGridPos.first, startingPointGridPos.second);
    endingPointRect   = CellRectFromGrid(endingPointGridPos.first,   endingPointGridPos.second);
}

void Grid::SyncFromPixelPositions() {
    // derive grid indices from pixel positions
    auto gx = (int)floorf(startingPoint.x / CELL_SIZE);
    auto gy = (int)floorf(startingPoint.y / CELL_SIZE);
    startingPointGridPos = { gx, gy };

    gx = (int)floorf(endingPoint.x / CELL_SIZE);
    gy = (int)floorf(endingPoint.y / CELL_SIZE);
    endingPointGridPos = { gx, gy };

    startingPointRect = { startingPoint.x, startingPoint.y, (float)CELL_SIZE, (float)CELL_SIZE };
    endingPointRect   = { endingPoint.x,   endingPoint.y,   (float)CELL_SIZE, (float)CELL_SIZE };
}

void Grid::UpdatePlatforms(GameState& gameState){
    for (MovingPlatform& platform : platforms){
        platform.Update(gameState);
    }
}

void Grid::Update(GameState& gameState) {
    // move spikes that are falling
    UpdateTriangles(gameState);
    // move platforms
    UpdatePlatforms(gameState);
}
