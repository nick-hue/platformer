#include "my_triangle.h"

MyTriangle::MyTriangle(Vector2 pos, Color c, TriangleMode m) {
    position = pos;
    color    = c;
    mode     = m;
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
}

void MyTriangle::ToString() {
    // IMPORTANT: print enums as int to avoid UB
    printf("Triangle: %f-%f, %d\n", position.x, position.y, (int)mode);
}
