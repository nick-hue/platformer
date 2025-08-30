#include "game.h"

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Platformer");
    SetWindowPosition(300, 200);
    SetTargetFPS(60);
    DrawFPS(10, 10);

    Player player((float)SCREEN_WIDTH/2.0f - 25.0f, (float)SCREEN_HEIGHT/2.0f, 50, 50, MAROON);

    // World geometry
    Tile platform(100, 350, 600, 20, DARKGRAY);
    Tile smallWall(400, 300, 25, 50, DARKGRAY);
    platforms.push_back(platform);
    platforms.push_back(smallWall);
    // for (auto& p : platforms) p.Sync();

    bool debug_show = true;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_TAB)) debug_show = !debug_show;

        float dt = GetFrameTime();

        player.Update(dt, platforms);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            for (const auto& p : platforms) p.Draw();
            player.Draw();
            if (debug_show) ShowDebug(player);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
