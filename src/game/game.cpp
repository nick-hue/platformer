#include "game.h"

// TODO: gravity change button
// TODO: add moving platforms
// TODO: make pause menu better (audio menu)
// TODO: pitch variety to jumps


GameState gameState;    

void PauseGame() {
    gameState.isGamePaused = true;
    while (gameState.isGamePaused && !WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            gameState.isGamePaused = false;
        }

        BeginDrawing();
            ClearBackground(DARKGRAY);
            DrawText("Game Paused", 20, 20, 40, LIGHTGRAY);
            DrawText("Press ESC to resume", 20, 80, 20, LIGHTGRAY);
        EndDrawing();
    }
}


int main(void) {
    srand(static_cast<unsigned>(time(nullptr))); // seed once

    InitWindow(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, "Platformer");
    SetWindowPosition(300, 200);
    SetTargetFPS(60);

    InitAudioDevice();

    printf("Map Size: %dx%d\n", gameState.map.MAP_WIDTH, gameState.map.MAP_HEIGHT);

    SetWindowSize(gameState.map.MAP_WIDTH, gameState.map.MAP_HEIGHT);
    gameState.player.position = gameState.map.grid.startingPoint;
    gameState.textureHandler.LoadTextures();
    gameState.textureHandler.SetupTextures(gameState);
    gameState.soundManager.LoadSounds();

    // PlayMusicStream(gameState.soundManager.background);

    bool debug_show = true;
    
    while (!WindowShouldClose()) {
        UpdateMusicStream(gameState.soundManager.background); 
        if (IsKeyPressed(KEY_P)) PauseGame();
        if (IsKeyPressed(KEY_TAB)) debug_show = !debug_show;
        
        // make this somewhere else
        if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_R)) {
            printf("Reloading level: %s\n", gameState.currLevelFilename.c_str());
            gameState.map.ReloadMap(gameState);
        }

        if (gameState.currentLives <= 0) {
            printf("Game Over! You've run out of lives.\n");
            // go to losing screen
            break;  // Exit the game loop
        }

        float dt = GetFrameTime();
        if (dt > 0.033f) dt = 0.033f;

        // Update player and map
        gameState.player.Update(dt, gameState);
        gameState.playerSprite.UpdateAnimation(dt, gameState.player);
        gameState.keyGoalSprite.UpdateAnimation(dt);
        gameState.map.grid.Update(dt, gameState);
        gameState.gameUI.Update(gameState);


        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            gameState.map.Draw(gameState);
            
            if (debug_show) ShowDebug(gameState);
            gameState.playerSprite.Draw(gameState.player);
            gameState.keyGoalSprite.Draw();
            gameState.gameUI.Draw(gameState);
        EndDrawing();
    }

    gameState.textureHandler.UnloadTextures();
    gameState.soundManager.UnloadSounds();   
    CloseAudioDevice();     
    CloseWindow();

    return 0;
}

