#include "game.h"

// TODO: gravity change button
// TODO: add moving platforms
// TODO: make pause menu better (audio menu)
// TODO: fix show debug

Game::Game(){
}

void Game::Run(){
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
        if (IsKeyPressed(KEY_P)) pauseMenu.PauseGame();
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
            
            if (debug_show) {
                debugMenu.ShowMenu(gameState);

            }
            gameState.playerSprite.Draw(gameState.player);
            gameState.keyGoalSprite.Draw();
            gameState.gameUI.Draw(gameState);
        EndDrawing();
    }

    gameState.textureHandler.UnloadTextures();
    gameState.soundManager.UnloadSounds();   
    CloseAudioDevice();     
    CloseWindow();
}

void Game::Initialize(){

}

void Game::Shutdown(){
    
}

void PauseMenu::Show(){

}

void PauseMenu::PauseGame() {
    isGamePaused = true;

    while (isGamePaused && !WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            isGamePaused = false;
        }

        BeginDrawing();
            ClearBackground(DARKGRAY);

            Show();
            DrawText("Game Paused", 20, 20, 40, LIGHTGRAY);
            DrawText("Press ESC to resume", 20, 80, 20, LIGHTGRAY);
        EndDrawing();
    }
}

DebugManager::DebugManager() {
    box = { 0.0f, 0.0f, 200.0f, 100.0f };
    mainColor = SKYBLUE;
    outlineColor = BLUE;
    currentColor = mainColor;
}

void DebugManager::GetMenuColor() {
    Vector2 mouse_pos = GetMousePosition();
    if (CheckCollisionPointRec(mouse_pos, box))
        currentColor = Fade(mainColor, 0.5f);
    else
        currentColor = mainColor;
}

void DebugManager::Draw() {
    if (!active) return;

    GetMenuColor();
    DrawRectangleRec(box, currentColor);
    DrawRectangleLinesEx(box, 1.0f, outlineColor);
    DrawText("Debug Mode: ON", 10, 10, 20, RED);
}

void DebugManager::ShowMenu(GameState& gameState){
    GetMenuColor();
    box.x = gameState.map.MAP_WIDTH - box.width;
    box.y = 20;

    DrawRectangleRec(box, currentColor);
    DrawRectangleLinesEx(box, 1.0f, outlineColor);
    
    DrawText((std::string("Player position : ") + std::to_string(gameState.player.position.x) 
        + "-" + std::to_string(gameState.player.position.y) + "}").c_str(), box.x, box.y + 10, 12, DARKGRAY);
    DrawText((std::string("Player velocity : {") + std::to_string(gameState.player.velocity.x) 
        + "-" + std::to_string(gameState.player.velocity.y) + "}").c_str(), box.x, box.y + 40, 12, DARKGRAY);
}

void DebugManager::ShowHitboxes(GameState& gameState){
    
}

