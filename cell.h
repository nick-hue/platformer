#pragma once
#include "raylib.h"
#include "level_editor_defs.h" // for CELL_SIZE

class Cell {
public:
    Vector2 position{0.0f, 0.0f};
    
    Color   filledColor{DARKGRAY};
    Color   emptyColor{LIGHTGRAY};
    Color   filledSelectionColor{MAROON};
    Color   emptySelectionColor{GRAY};

    bool    isOccupied{false};

    Cell() = default;
    Cell(Vector2 pos, Color filledCol = DARKGRAY, Color emptyCol = LIGHTGRAY, Color filledSelCol = MAROON, Color emptySelCol = GRAY);

    // Draw Cell
    void Draw() const;

    // Show selected cell
    void Select() const; 

    // Axis-aligned rectangle helper
    Rectangle Rect() const {
        return Rectangle{ position.x, position.y, (float)CELL_SIZE, (float)CELL_SIZE };
    }
};
