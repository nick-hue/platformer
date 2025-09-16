#include "game.h"

// TODO: gravity change button
// TODO: add moving platforms
// TODO: make pause menu better

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

void LoadTextures(){    
    Texture2D playerTexture = LoadTexture("assets/sprites/characters/Soldier/Soldier/Soldier.png");
    if (playerTexture.id == 0) { TraceLog(LOG_ERROR, "Failed to load player texture"); }

    gameState.playerSprite.SetSprite(playerTexture, 9, 7);
    gameState.playerSprite.idle = Anim{0, 0, 4, 8.f};   // row 0, cols [0..3]
    gameState.playerSprite.walk = Anim{1, 0, 9, 12.f};  // row 1, cols [0..8]

    Texture2D keyGoalTexture = LoadTexture("assets/sprites/items/key/goal_key.png");
    if (keyGoalTexture.id == 0) { TraceLog(LOG_ERROR, "Failed to load key goal texture"); }

    gameState.keyGoalSprite.SetSprite(keyGoalTexture, gameState.map.grid.endingPoint, 24, 1);
    gameState.keyGoalSprite.idle = Anim{0, 0, 24, 12.f};  

    Texture2D heartTexture = LoadTexture("assets/sprites/ui/heart/heart_32x32.png");
    if (heartTexture.id == 0) { TraceLog(LOG_ERROR, "Failed to load heart texture"); }
    printf("heart pos : %.fx%.f\n", gameState.gameUI.heartPosition.x, gameState.gameUI.heartPosition.y);

    for (int i = 0; i < gameState.maxLives; ++i) {
        gameState.gameUI.hearts[i].position = Vector2{(i+1) * gameState.gameUI.heartPosition.x, gameState.gameUI.heartPosition.y};
        gameState.gameUI.hearts[i].sprite.SetSprite(heartTexture
                                    , gameState.gameUI.hearts[i].position,
                                    3, 1);
        gameState.gameUI.hearts[i].sprite.idle = Anim{0, 0, 1, 12.f};
    }

}

void UnloadTextures(){
    UnloadTexture(gameState.playerSprite.sprite);
    UnloadTexture(gameState.keyGoalSprite.sprite);
}

int main(void) {
    InitWindow(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, "Platformer");
    SetWindowPosition(300, 200);
    SetTargetFPS(60);

    LoadTextures();
    printf("Map Size: %dx%d\n", gameState.map.MAP_WIDTH, gameState.map.MAP_HEIGHT);

    SetWindowSize(gameState.map.MAP_WIDTH, gameState.map.MAP_HEIGHT);
    gameState.player.position = gameState.map.grid.startingPoint;

    bool debug_show = true;

    while (!WindowShouldClose()) {
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

        // Update player and map
        gameState.player.Update(dt, gameState);
        gameState.playerSprite.UpdateAnimation(dt, gameState.player);
        gameState.keyGoalSprite.UpdateAnimation(dt);
        gameState.map.grid.Update(dt, gameState);
        gameState.gameUI.Update(gameState.currentLives);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            if (debug_show) ShowDebug(gameState);
            
            gameState.map.Draw();
            gameState.playerSprite.Draw(gameState.player);
            gameState.keyGoalSprite.Draw();
            gameState.gameUI.Draw(gameState);
        EndDrawing();
    }

    UnloadTextures();
    CloseWindow();
    return 0;
}

