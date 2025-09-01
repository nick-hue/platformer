#pragma once
#include "raylib.h"
#include "level_editor_defs.h" // for CELL_SIZE
#include <iostream>

class MyTriangle {
public:
    Vector2 position{0.0f, 0.0f};
    Color   color{YELLOW};
    TriangleMode mode{TriangleMode::UP};    

    // MyTriangle() = default;
    MyTriangle(Vector2 pos, Color c, TriangleMode mode);
    
    // Draw Cell
    void Draw();

    // notimpleemtn
    void ToString();
};
