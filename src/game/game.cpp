#include "game.h"

// todo: load sprite

void GameState::CheckWin()
{
    if (CheckCollisionRecs(player.rect, {GameState::map.endingPoint.x, GameState::map.endingPoint.y, (float)map.TILE_WIDTH, (float)map.TILE_HEIGHT})) {
        // Reset player position to starting point
        player.position = map.startingPoint;
        // Reload the map
        // map.LoadMap("exported_map.txt");
        // Message, show next map
        printf("Congratulations! You've completed the level!\n");
    }
}

int main(void) {
    InitWindow(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, "Platformer");
    SetWindowPosition(300, 200);
    SetTargetFPS(60);
    DrawFPS(GAME_SCREEN_WIDTH - 100, 10);

    GameState gameState;    
    SetWindowSize(gameState.map.MAP_WIDTH * gameState.map.TILE_WIDTH, 
                  gameState.map.MAP_HEIGHT * gameState.map.TILE_HEIGHT);
    gameState.player.position = gameState.map.startingPoint;

    bool debug_show = true;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_TAB)) debug_show = !debug_show;
        float dt = GetFrameTime();
        
        // printf("%f %f\n", gameState.player.position.x, gameState.player.position.y);
        // printf("%f %f\n", gameState.map.endingPoint.x, gameState.map.endingPoint.y);
        gameState.player.Update(dt, gameState.map.tiles);
        gameState.CheckWin();

        BeginDrawing();
            ClearBackground(RAYWHITE);
            // Draw obstacles
            for (const auto& tile : gameState.map.tiles) {
                tile.Draw();
            }
            // Draw player
            gameState.player.Draw();
            // Draw end point
            gameState.map.DrawEndPoint();

            if (debug_show) ShowDebug(gameState.player);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

