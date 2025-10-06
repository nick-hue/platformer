#include "game.h"

// TODO: gravity change button

// FIXME: bug where if death from spikes when respawning they are gone
// TODO: object map loading
// TODO: move platforms to map
// TODO: bounding box collision checking
// TODO: vertical moving platforms
// TODO: inheritance sprite drawing
// TODO: make utils file

void Game::Run(){    
    while (gameState.shouldRun) {
        if (WindowShouldClose()) { gameState.shouldRun = false; continue; };

        if (gameState.currentLives <= 0) {
            printf("Game Over! You've run out of lives.\n");
            // go to losing screen
            gameState.shouldRun = false;
        }
        
        UpdateMusicStream(gameState.soundManager.background); 

        if (IsKeyReleased(KEY_P)) pauseMenu.isGamePaused = !pauseMenu.isGamePaused;            
        if (IsKeyPressed(KEY_TAB)) debugMenu.active = !debugMenu.active;
        
        // make this somewhere else
        if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_R)) {
            printf("Reloading level: %s\n", gameState.currLevelFilename.c_str());
            gameState.map.ReloadMap(gameState);
        }

        float dt = GetFrameTime();
        if (dt > 0.033f) dt = 0.033f;
        gameState.dt = dt;

        // Update player and map
        gameState.player.Update(gameState);
        gameState.playerSprite.UpdateAnimation(gameState.dt, gameState.player);
        gameState.keyGoalSprite.UpdateAnimation(gameState.dt);
        gameState.map.grid.Update(gameState);
        gameState.gameUI.Update(gameState);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            gameState.map.Draw(gameState);
            
            if (pauseMenu.isGamePaused) pauseMenu.PauseGame();
            if (debugMenu.active) debugMenu.Show(gameState);

            gameState.playerSprite.Draw(gameState.player);
            gameState.keyGoalSprite.Draw();
            gameState.gameUI.Draw(gameState);
        EndDrawing();
    }
}

void Game::Initialize(){
    // gameState.seed = rand

    printf("GAME WIDTH: %d-%d\n", GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);

    InitWindow(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, "Platformer");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    GuiLoadStyleDefault();
    SetWindowPosition(300, 200);
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    InitAudioDevice();
    pauseMenu.InitPauseMenuButtons(gameState);

    printf("Map Size: %dx%d\n", gameState.map.MAP_WIDTH, gameState.map.MAP_HEIGHT);

    SetWindowSize(gameState.map.MAP_WIDTH, gameState.map.MAP_HEIGHT);
    printf("starting point : %f-%f\n", gameState.map.grid.startingPoint.x, gameState.map.grid.startingPoint.y);
    gameState.player.position = gameState.map.grid.startingPoint;
    gameState.textureHandler.LoadTextures();
    gameState.textureHandler.SetupTextures(gameState);
    gameState.soundManager.LoadSounds();

    PlayMusicStream(gameState.soundManager.background);
}

void Game::Shutdown(){
    gameState.textureHandler.UnloadTextures();
    gameState.soundManager.UnloadSounds();   
    CloseAudioDevice();     
    CloseWindow();
}
