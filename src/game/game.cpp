#include "game.h"

int main(void) {
    InitWindow(EDITOR_SCREEN_WIDTH, EDITOR_SCREEN_HEIGHT, "Platformer");
    SetWindowPosition(300, 200);
    SetTargetFPS(60);
    DrawFPS(10, 10);

    GameState gameState;    

    bool debug_show = true;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_TAB)) debug_show = !debug_show;

        float dt = GetFrameTime();

        gameState.player.Update(dt, gameState.map.tiles);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            // Draw obstacles
            for (const auto& tile : gameState.map.tiles) {
                tile.Draw();
            }
            // Draw player
            gameState.player.Draw();

            if (debug_show) ShowDebug(gameState.player);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
