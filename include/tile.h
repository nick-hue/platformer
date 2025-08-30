#pragma once
#include "raylib.h"
#include <vector>

// Simple solid object (floor, wall, ceiling, platform)
struct Tile {
    Vector2 position{};
    float width{};
    float height{};
    Rectangle rect{};
    Color color{};

    Tile(float x, float y, float w, float h, Color c)
        : position{ x, y }, width{ w }, height{ h }, rect{ x, y, w, h }, color{ c } {}

    void Sync() { rect = { position.x, position.y, width, height }; }

    void Draw() const { DrawRectangleRec(rect, color); }
};

// Global container for tiles/platforms in your level
extern std::vector<Tile> platforms;
