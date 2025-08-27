#include "raylib.h"
#include <cstdio>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

class Player {
    public:
        Vector2 position;
        float velocity;
        float width;
        float height;
        Rectangle rect;
        Color color;

        Player(float x, float y, float velocity, float width, float height, Color c) {
            position = { x, y };
            this->velocity = velocity;
            this->width = width;
            this->height = height;
            rect = { position.x, position.y, width, height };
            color = c;
        }

        void Update(){
            printf("Player Position: x: %f, y: %f\n", position.x, position.y);
            if (IsKeyDown(KEY_D)) Move({ 1, 0 });
            if (IsKeyDown(KEY_A)) Move({ -1, 0 });
            if (IsKeyDown(KEY_W)) Move({ 0, -1 });
            if (IsKeyDown(KEY_S)) Move({ 0, 1 });
        }

        void Move(Vector2 direction) {
            position.x += direction.x * velocity;
            position.y += direction.y * velocity;
            rect.x = position.x;
            rect.y = position.y;
        }

        void Draw() {
            DrawRectangleRec(rect, color);
        }
};

class Object{
    public:
        Vector2 position;
        float width;
        float height;
        Rectangle rect;
        Color color;

        Object(float x, float y, float width, float height, Color c) {
            position = { x, y };
            this->width = width;
            this->height = height;
            rect = { position.x, position.y, width, height };
            color = c;
        }

        void Draw() {
            DrawRectangleRec(rect, color);
        }
};

int main(void)
{

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Platformer");
    SetWindowPosition(300,200);
    SetTargetFPS(60);

    Player player = { (float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2, 2.0f, 50, 50, MAROON };
    Object platform = { 100, 350, 600, 20, DARKGRAY };


    while (!WindowShouldClose()) 
    {   
        if (CheckCollisionRecs(player.rect, platform.rect))
        {
            printf("Collision Detected\n");
        } else {
            player.Update();
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);
            player.Draw();
            platform.Draw();

        EndDrawing();
    }

    CloseWindow();        

    return 0;
}
