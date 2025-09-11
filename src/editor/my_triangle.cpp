#include "my_triangle.h"

MyTriangle::MyTriangle(int gx, int gy, Color c, TriangleMode m) {
    gridPosX = gx;
    gridPosY = gy;
    position.x = gx * CELL_SIZE;
    position.y = gy * CELL_SIZE;
    color    = c;
    mode     = m;

    switch (mode) {
        case TriangleMode::UP:
            tip = (Vector2) { position.x + (float)CELL_SIZE * 0.5f, position.y };            // center of top edge
            break;
        case TriangleMode::DOWN:  // pointing down
            tip = (Vector2) { position.x + (float)CELL_SIZE * 0.5f, position.y + (float)CELL_SIZE };        // center of bottom edge
            break;
        case TriangleMode::LEFT:  // pointing left
            tip = (Vector2) { position.x,            position.y + (float)CELL_SIZE * 0.5f }; // center of left edge
            break;
        case TriangleMode::RIGHT: // pointing right
            tip = (Vector2) { position.x + (float)CELL_SIZE,        position.y + (float)CELL_SIZE * 0.5f }; // center of right edge
            break;
        default:
            tip = (Vector2) { position.x + (float)CELL_SIZE * 0.5f, position.y + (float)CELL_SIZE * 0.5f }; // fallback: cell center
    }
}

void MyTriangle::Draw() {
    switch (mode) {
        case TriangleMode::UP:
            DrawTriangle(
                Vector2{ position.x + (float)CELL_SIZE * 0.5f, position.y },                 // top-center
                Vector2{ position.x,                           position.y + (float)CELL_SIZE }, // bottom-left
                Vector2{ position.x + (float)CELL_SIZE,        position.y + (float)CELL_SIZE }, // bottom-right
                color
            );
            break;

        case TriangleMode::DOWN:
            DrawTriangle(
                Vector2{ position.x,                           position.y },                   // top-left
                Vector2{ position.x + (float)CELL_SIZE * 0.5f, position.y + (float)CELL_SIZE },// bottom-center
                Vector2{ position.x + (float)CELL_SIZE,        position.y },                   // top-right
                color
            );
            break;

        case TriangleMode::LEFT:
            DrawTriangle(
                Vector2{ position.x,                           position.y + (float)CELL_SIZE * 0.5f }, // center-left (apex)
                Vector2{ position.x + (float)CELL_SIZE,        position.y + (float)CELL_SIZE },        // bottom-right
                Vector2{ position.x + (float)CELL_SIZE,        position.y },                           // top-right
                color
            );
            break;

        case TriangleMode::RIGHT:
            DrawTriangle(
                Vector2{ position.x,                           position.y },                           // top-left
                Vector2{ position.x,                           position.y + (float)CELL_SIZE },        // bottom-left
                Vector2{ position.x + (float)CELL_SIZE,        position.y + (float)CELL_SIZE * 0.5f }, // center-right (apex)
                color
            );
            break;

        default:
            // NONE: draw nothing
            break;
    }

    // DrawRectangle(tip.x - 3, tip.y - 3, 6, 6, RED); // draw tip for debugging
}

void MyTriangle::ToString() {
    // IMPORTANT: print enums as int to avoid UB
    printf("Triangle: %f-%f - Grid : %d-%d, %d\n", position.x, position.y, gridPosX, gridPosY, (int)mode);
}
