#pragma once
#include "raylib.h"
#include <vector>
#include "item_sprite.h"
#include <utility>

enum GroundTileType {
    GRASS,
    GROUND,
    BROKEN,
    UNKNOWN  
};

inline void TileTypeToString(GroundTileType type){
    switch (type)
    {
    case GroundTileType::GRASS: printf("GroundTileType: GRASS\n"); break;
    case GroundTileType::GROUND: printf("GroundTileType: GROUND\n"); break;
    case GroundTileType::BROKEN: printf("GroundTileType: BROKEN\n"); break;
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
