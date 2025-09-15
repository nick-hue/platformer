#include "my_triangle.h"

MyTriangle::MyTriangle(int gx, int gy, Color c, TriangleMode m) {
    gridPosX = gx;
    gridPosY = gy;
    position = {gx * (float) CELL_SIZE, gy * (float) CELL_SIZE};
    color    = c;
    mode     = m;
    UpdateGeometry();
}



void MyTriangle::UpdateGeometry() {
    const float x = position.x;
    const float y = position.y;
    const float s = static_cast<float>(CELL_SIZE);

    switch (mode) {
        case TriangleMode::UP:
            // tip (top edge center), base-left, base-right
            vertices = { Vector2{ x + s*0.5f, y },
                         Vector2{ x,           y + s },
                         Vector2{ x + s,       y + s } };
            break;

        case TriangleMode::DOWN:
            vertices = { Vector2{ x,           y },
                         Vector2{ x + s*0.5f, y + s },
                         Vector2{ x + s,       y } };
            break;

        case TriangleMode::LEFT:
            vertices = { Vector2{ x + s,       y + s },
                         Vector2{ x + s,       y },
                         Vector2{ x,           y + s*0.5f }};
            break;

        case TriangleMode::RIGHT:
            vertices = { Vector2{ x + s,       y + s*0.5f },
                         Vector2{ x,           y },
                         Vector2{ x,           y + s } };
            break;
    }
}

void MyTriangle::Draw() {
    // UpdateGeometry();
    DrawTriangle(vertices[0], vertices[1], vertices[2], color);
    DrawTriangleLines(vertices[0], vertices[1], vertices[2], BLACK);
}

void MyTriangle::DrawVertices() {
    DrawRectangle(vertices[0].x - 3, vertices[0].y - 3, 6, 6, RED);
    DrawRectangle(vertices[1].x - 3, vertices[1].y - 3, 6, 6, RED);
    DrawRectangle(vertices[2].x - 3, vertices[2].y - 3, 6, 6, RED);
}

void MyTriangle::ToString() {
    // IMPORTANT: print enums as int to avoid UB
    printf("Triangle: %f-%f - Grid : %d-%d, %d\n", position.x, position.y, gridPosX, gridPosY, (int)mode);
}
