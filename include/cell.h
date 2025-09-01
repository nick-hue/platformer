#pragma once
#include "raylib.h"
#include "level_editor_defs.h" // for CELL_SIZE
#include <iostream>

class Cell {
public:
    Vector2 position{0.0f, 0.0f};
    
    Color   filledColor{DARKGRAY};
    Color   emptyColor{LIGHTGRAY};
    Color   filledSelectionColor{MAROON};
    Color   emptySelectionColor{GRAY};
    Color   startingPointColor{GOLD};
    Color   endingPointColor{BLUE};

    bool    isOccupied{false};
    int     cellSize{CELL_SIZE};

    Cell() = default;
    Cell(int gx, int gy, int cell_size, bool occupied);
    Cell(Vector2 pos, Color filledCol = DARKGRAY, Color emptyCol = LIGHTGRAY, Color filledSelCol = MAROON, Color emptySelCol = GRAY, Color startingPointCol = GOLD, Color endingPointCol = BLUE);

    // Draw Cell
    void Draw() const;

    // Show selected cell
    void Select() const; 

    // Axis-aligned rectangle helper
    Rectangle Rect() const {
        return Rectangle{ position.x, position.y, (float)cellSize, (float)cellSize };
    }

    void ToString(){
        std::cout << "Cell(" << position.x << ", " << position.y << ", " << cellSize << ", " << isOccupied << ")\n";
    }
};
