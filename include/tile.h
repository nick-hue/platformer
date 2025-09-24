#pragma once
#include "raylib.h"
#include <vector>
#include "item_sprite.h"
#include <utility>

enum TileType {
    GRASS,
    GROUND,
    BROKEN,
    UNKNOWN  
};

inline void TileTypeToString(TileType type){
    switch (type)
    {
    case TileType::GRASS: printf("TileType: GRASS\n"); break;
    case TileType::GROUND: printf("TileType: GROUND\n"); break;
    case TileType::BROKEN: printf("TileType: BROKEN\n"); break;
    case TileType::UNKNOWN: printf("TileType: UNKNOWN\n"); break;
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
    TileType type;
    std::pair<int, int> spriteSheetLocation;
    ItemSprite sprite;
    std::pair<int, int> gridPos;

    Tile(float x, float y, float w, float h, Color c, TileType t)
        : position{ x, y }, width{ w }, height{ h }, rect{ x, y, w, h }, color{ c }, type{t}, gridPos{position.x / w, position.y / h} {}

    void Sync() { rect = { position.x, position.y, width, height }; }

    void Draw() { sprite.Draw(spriteSheetLocation); }

    void DrawOutline() { DrawRectangleLinesEx(rect, 1.0f, RED); }
    // void Draw() { DrawRectangleRec(rect, color); }
};

// Global container for tiles/platforms in your level
extern std::vector<Tile> platforms;
