#pragma once
#include "raylib.h"
#include "level_editor_defs.h" // for CELL_SIZE
#include "item_sprite.h"
#include <iostream>
#include <array>


class MyTriangle {
public:
    int gridPosX{-1};
    int gridPosY{-1};
    Vector2 position{-1.0f, -1.0f};
    float velocityY{0.0f};
    Color   color{YELLOW};
    TriangleMode mode{TriangleMode::NONE};    
    bool falling{false};
    ItemSprite sprite;
    int spriteCol = 0;
    
    std::array<Vector2,3> vertices{ Vector2{0,0}, Vector2{0,0}, Vector2{0,0} };
    
    MyTriangle(int gridPosX, int gridPosY, Color c, TriangleMode mode);
    
    // Draw Cell
    void Draw() const ;
    void DrawEditor() const ;
    void DrawVertices() const ;
    void ToString();
    void UpdateGeometry();
    const std::array<Vector2,3>& Points() const { return vertices; }

    
};
