#include "game.h"

// TODO: load sprite
// TODO: gravity change button
// TODO: add moving platforms
// TODO: put lives mechanic
// TODO: make pause menu betterd
GameState gameState;    


void PauseGame() {
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

    
    Texture2D playerTexture = LoadTexture("assets/sprites/characters/Soldier/Soldier/Soldier.png");
    gameState.playerSprite.SetSprite(playerTexture, 9, 7);
    gameState.playerSprite.idle = Anim{0, 0, 4, 8.f};   // row 0, cols [0..3]
    gameState.playerSprite.walk = Anim{1, 0, 9, 12.f};  // row 1, cols [0..8]

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

        float dt = GetFrameTime();

        // Update player and map
        gameState.player.Update(dt, gameState);
        gameState.playerSprite.UpdateAnimation(dt, gameState.player);
        gameState.map.grid.Update(dt, gameState);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            if (debug_show) ShowDebug(gameState);
            
            gameState.map.Draw();
            gameState.playerSprite.Draw(gameState.player);


        EndDrawing();
    }

    UnloadTexture(playerTexture);
    CloseWindow();
    return 0;
}

