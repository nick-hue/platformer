#pragma once
#include "raylib.h"
#include "level_editor_defs.h" // for CELL_SIZE
#include <iostream>

class MyTriangle {
public:
    int gridPosX{-1};
    int gridPosY{-1};
    Vector2 position{-1.0f, -1.0f};
    Color   color{YELLOW};
    TriangleMode mode{TriangleMode::UP};    

    // MyTriangle() = default;
    // MyTriangle(Vector2 pos, gridPosXint gridPosY;, Color c, TriangleMode mode);
    MyTriangle(int gridPosX,int gridPosY, Color c, TriangleMode mode);
    
    // Draw Cell
    void Draw();

    // notimpleemtn
    void ToString();
};
