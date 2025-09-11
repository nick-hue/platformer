#include "game.h"

// TODO: load sprite
// TODO: add reset level 
// TODO: add pause 
// TODO: gravity change button
// TODO: add moving platforms


void GameState::CheckWin()
{
    if (CheckCollisionRecs(player.rect, {GameState::map.grid.endingPoint.x, GameState::map.grid.endingPoint.y, (float)map.TILE_WIDTH, (float)map.TILE_HEIGHT})) {
        // Reset player position to starting point
        // Reload the map
        printf("Congratulations! You've completed the level!\n");
        levelIndex++;
        
        std::string currLevelFilename = "exported_map_" + std::to_string(levelIndex) + ".txt";
        printf("Loading next level: %s\n", currLevelFilename.c_str());
        map.LoadMap(currLevelFilename.c_str());
        player.position = map.grid.startingPoint;
    }
}

int main(void) {
    InitWindow(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, "Platformer");
    SetWindowPosition(300, 200);
    SetTargetFPS(60);
    DrawFPS(GAME_SCREEN_WIDTH - 100, 10);

    GameState gameState;    
    // printf("Map Size: %dx%d\n", gameState.map.MAP_WIDTH * gameState.map.TILE_WIDTH, gameState.map.MAP_HEIGHT * gameState.map.TILE_HEIGHT);
    printf("Map Size: %dx%d\n", gameState.map.MAP_WIDTH, gameState.map.MAP_HEIGHT);

    SetWindowSize(gameState.map.MAP_WIDTH, gameState.map.MAP_HEIGHT);
    gameState.player.position = gameState.map.grid.startingPoint;

    bool debug_show = true;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_TAB)) debug_show = !debug_show;
        float dt = GetFrameTime();

        gameState.player.Update(dt, gameState);
        gameState.CheckWin();

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

