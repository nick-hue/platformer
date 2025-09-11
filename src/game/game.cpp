#include "game.h"

// TODO: load sprite
// TODO: add pause 
// TODO: gravity change button
// TODO: add moving platforms

void PauseGame(GameState& gameState) {
    // simple pause screen
    gameState.gamePaused = true;
    while (gameState.gamePaused && !WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            gameState.gamePaused = false;
        }

        BeginDrawing();
            ClearBackground(DARKGRAY);
            DrawText("Game Paused", 20, 20, 40, LIGHTGRAY);
            DrawText("Press ESC to resume", 20, 80, 20, LIGHTGRAY);
        EndDrawing();
    }
}

int main(void) {
    InitWindow(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, "Platformer");
    SetWindowPosition(300, 200);
    SetTargetFPS(60);
    DrawFPS(GAME_SCREEN_WIDTH - 100, 10);

    GameState gameState;    
    printf("Map Size: %dx%d\n", gameState.map.MAP_WIDTH, gameState.map.MAP_HEIGHT);

    SetWindowSize(gameState.map.MAP_WIDTH, gameState.map.MAP_HEIGHT);
    gameState.player.position = gameState.map.grid.startingPoint;

    bool debug_show = true;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_P)) PauseGame(gameState);

        if (IsKeyPressed(KEY_TAB)) debug_show = !debug_show;
        
        // make this somewhere else
        if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_R)) {
            printf("Reloading level: %s\n", gameState.currLevelFilename.c_str());
            gameState.map.LoadMap(gameState.currLevelFilename.c_str());
            gameState.player.position = gameState.map.grid.startingPoint;
        }

        float dt = GetFrameTime();

        // Update player and map
        gameState.player.Update(dt, gameState);
        gameState.map.grid.Update(dt, gameState);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            // Draw obstacles
            for (const auto& tile : gameState.map.tiles) {
                tile.Draw();
            }
            // Draw player
            gameState.player.Draw();
            gameState.map.Draw();
            // Draw end point
            gameState.map.DrawEndPoint();

            if (debug_show) ShowDebug(gameState.player);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

