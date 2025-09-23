#pragma once
#include "raylib.h"
#include <vector>
#include "item_sprite.h"

// Simple solid object (floor, wall, ceiling, platform)
struct Tile {
    Vector2 position{};
    float width{};
    float height{};
    Rectangle rect{};
    Color color{};
    ItemSprite sprite;

    Tile(float x, float y, float w, float h, Color c)
        : position{ x, y }, width{ w }, height{ h }, rect{ x, y, w, h }, color{ c }{}

    void Sync() { rect = { position.x, position.y, width, height }; }

    void Draw() { sprite.Draw(); }

    void DrawOutline() { DrawRectangleLinesEx(rect, 1.0f, RED); }
    // void Draw() { DrawRectangleRec(rect, color); }
};

// Global container for tiles/platforms in your level
extern std::vector<Tile> platforms;
