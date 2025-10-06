#pragma once
#include "raylib.h"
#include <vector>
#include "item_sprite.h"
#include <utility>

// enum GroundTileType {
//     GRASS,
//     GROUND,
//     BROKEN,
//     UNKNOWN  
// };
enum GroundTileType {
    GRASS_1,
    GRASS_2,
    GRASS_3,
    UNDERGROUND_1,
    UNDERGROUND_2,
    UNDERGROUND_3,
    UNDERGROUND_4,
    UNDERGROUND_5,
    UNDERGROUND_6,
    UNKNOWN  
};

struct GroundTiles {
    std::vector<GroundTileType> grassTiles = {GRASS_1, GRASS_2, GRASS_3};
    std::vector<GroundTileType> undergroundTiles = {UNDERGROUND_1,
                                                    UNDERGROUND_2,
                                                    UNDERGROUND_3,
                                                    UNDERGROUND_4,    
                                                    UNDERGROUND_5,
                                                    UNDERGROUND_6};
};

inline void TileTypeToString(GroundTileType type){
    switch (type)
    {
    case GroundTileType::GRASS_1: printf("GroundTileType: GRASS_1\n"); break;
    case GroundTileType::GRASS_2: printf("GroundTileType: GRASS_2\n"); break;
    case GroundTileType::GRASS_3: printf("GroundTileType: GRASS_3\n"); break;
    case GroundTileType::UNDERGROUND_1: printf("GroundTileType: UNDERGROUND_1\n"); break;
    case GroundTileType::UNDERGROUND_2: printf("GroundTileType: UNDERGROUND_2\n"); break;
    case GroundTileType::UNDERGROUND_3: printf("GroundTileType: UNDERGROUND_3\n"); break;
    case GroundTileType::UNDERGROUND_4: printf("GroundTileType: UNDERGROUND_4\n"); break;
    case GroundTileType::UNDERGROUND_5: printf("GroundTileType: UNDERGROUND_5\n"); break;
    case GroundTileType::UNDERGROUND_6: printf("GroundTileType: UNDERGROUND_6\n"); break;
    case GroundTileType::UNKNOWN: printf("GroundTileType: UNKNOWN\n"); break;
    default: break;
    }
}

// Simple solid object (floor, wall, ceiling, platform)
struct Tile {
    Vector2 position{};
    float width{};
    float height{};
    Rectangle rect{};
    Color color{};
    GroundTileType type;
    std::pair<int, int> spriteSheetLocation;
    ItemSprite sprite;
    std::pair<int, int> gridPos;

    Tile(float x, float y, float w, float h, Color c, GroundTileType t)
        : position{ x, y }, width{ w }, height{ h }, rect{ x, y, w, h }, color{ c }, type{t}, gridPos{position.x / w, position.y / h} {}

    void Sync() { rect = { position.x, position.y, width, height }; }

    void Draw() { sprite.Draw(spriteSheetLocation); }

    void DrawOutline() { DrawRectangleLinesEx(rect, 1.0f, RED); }
    // void Draw() { DrawRectangleRec(rect, color); }
};

// Global container for tiles/platforms in your level
extern std::vector<Tile> platforms;
