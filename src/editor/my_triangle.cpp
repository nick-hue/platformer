#include <my_triangle.h>

MyTriangle::MyTriangle(Vector2 pos, Color c, TriangleMode m){
    position = pos;
    color = c;
    mode = m;
}

void MyTriangle::Draw() {
    printf("HERE : %f-%f\n", position.x, position.y);

    switch (mode){
        case TriangleMode::UP:
            DrawTriangle(
                Vector2{ position.x + (float)CELL_SIZE*0.5f, position.y },        // top
                Vector2{ position.x,         position.y + (float)CELL_SIZE },     // bottom-left
                Vector2{ position.x + (float)CELL_SIZE,     position.y + (float)CELL_SIZE },     // bottom-right
                color
            );
            break;

        case TriangleMode::DOWN:
            // printf("Drawing down\n");
            DrawTriangle(
                Vector2{ position.x,         position.y },         // top-left
                Vector2{ position.x + (float)CELL_SIZE,     position.y },         // top-right
                Vector2{ position.x + (float)CELL_SIZE*0.5f,position.y + (float)CELL_SIZE },     // bottom
                color
            );
            break;

        case TriangleMode::LEFT:
            DrawTriangle(
                Vector2{ position.x,         position.y + (float)CELL_SIZE*0.5f }, // left
                Vector2{ position.x + (float)CELL_SIZE,     position.y },          // top-right
                Vector2{ position.x + (float)CELL_SIZE,     position.y + (float)CELL_SIZE },      // bottom-right
                color
            );
            break;

        case TriangleMode::RIGHT:
            DrawTriangle(
                Vector2{ position.x,         position.y },          // top-left
                Vector2{ position.x + (float)CELL_SIZE,     position.y + (float)CELL_SIZE*0.5f }, // right
                Vector2{ position.x,         position.y + (float)CELL_SIZE },      // bottom-left
                color
            );
            break;

        default:
            // NONE: draw nothing
            printf("asdasd");
            break;
    }
}
