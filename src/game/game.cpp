#include "game.h"

// TODO: gravity change button
// TODO: add moving platforms
// TODO: make pause menu better (audio menu)
// TODO: fix bug where if death from spikes when respawning they are gone
// TODO: make reusme quit button

void Game::Run(){
    // pauseMenu.isGamePaused = true;
    while (!WindowShouldClose()) {
        UpdateMusicStream(gameState.soundManager.background); 
        printf("menu paused : %s\n", pauseMenu.isGamePaused ? "true" : "false");

        if (IsKeyReleased(KEY_P)) pauseMenu.isGamePaused = !pauseMenu.isGamePaused;            
        if (IsKeyPressed(KEY_TAB)) debugMenu.active = !debugMenu.active;
        
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
            
            if (pauseMenu.isGamePaused) pauseMenu.PauseGame();
            if (debugMenu.active) debugMenu.Show(gameState);

            gameState.playerSprite.Draw(gameState.player);
            gameState.keyGoalSprite.Draw();
            gameState.gameUI.Draw(gameState);
        EndDrawing();
    }
}

void Game::Initialize(){
    srand(static_cast<unsigned>(time(nullptr))); // seed once
    
    printf("GAME WIDTH: %d-%d\n", GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);

    InitWindow(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, "Platformer");
    SetWindowPosition(300, 200);
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    InitAudioDevice();
    pauseMenu.InitPauseMenuButtons(gameState);

    printf("Map Size: %dx%d\n", gameState.map.MAP_WIDTH, gameState.map.MAP_HEIGHT);

    SetWindowSize(gameState.map.MAP_WIDTH, gameState.map.MAP_HEIGHT);
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

void PauseButtonController::Draw(){
    buttonDec.Draw();
    DrawRectangleRec(buttonMiddle, soundButtonColor);
    DrawRectangleLinesEx(buttonMiddle, 3.0f, DARKBROWN);
    buttonInc.Draw();

    if (volume) {
        int percent = (int)(*volume * 100.0f + 0.5f);
        std::string txt = std::string(label) + " Volume: " + std::to_string(percent) + "%";
        int pixels = MeasureText(txt.c_str(), middleTextFontSize);
        DrawText(txt.c_str(), buttonMiddle.x + buttonMiddle.width/2 - pixels/2, buttonMiddle.y + buttonMiddle.height/4, middleTextFontSize, BLACK);
    } else {
        DrawText("Unbound volume", (int)buttonMiddle.x, (int)buttonMiddle.y - 28, middleTextFontSize, RED);
    }

    
    
}

void PauseMenu::Show(){
    DrawText("Game Paused", 20, 20, 40, LIGHTGRAY);
    DrawText("Press ESC to resume", 20, 80, 20, LIGHTGRAY);

    // DrawRectangleRec(musicButtonDec.box, soundButtonColor);
    musicControl.Draw();
    soundEffectsControl.Draw();
}

void PauseMenu::InitPauseMenuButtons(GameState& gameState){
    float placementWidth = GetScreenWidth() / 9;
    float placementHeight = GetScreenHeight() / 5; 

    float buttonWidth = placementWidth;
    float buttonHeight = 40.0f;
    // musicRect.width = width;
    // musicRect.width = height;
    int padding = 20;

    printf("placement : %f-%f\n", placementWidth, placementHeight);

    // soundEffectsRect.width = width;
    // soundEffectsRect.width = 2 * height;    
    musicControl.buttonDec = MyButton{placementWidth, placementHeight, buttonWidth, buttonHeight, "-", "", ""};
    musicControl.buttonDec.onClick = [&]{ gameState.soundManager.EditVolume(gameState.soundManager.background, gameState.soundManager.musicVolume, -0.05f); };
    musicControl.buttonMiddle = {placementWidth + buttonWidth + padding, placementHeight, placementWidth * 3, buttonHeight};
    musicControl.buttonInc = MyButton{musicControl.buttonMiddle.x + musicControl.buttonMiddle.width + padding, placementHeight, buttonWidth, buttonHeight, "+", "", ""};
    musicControl.buttonInc.onClick = [&]{ gameState.soundManager.EditVolume(gameState.soundManager.background, gameState.soundManager.musicVolume, +0.05f); };

    placementHeight += placementHeight;

    soundEffectsControl.buttonDec = MyButton{placementWidth, placementHeight, buttonWidth, buttonHeight, "-", "", ""};
    soundEffectsControl.buttonDec.onClick = [&]{ gameState.soundManager.EditVolume(gameState.soundManager.spikeBreak, gameState.soundManager.soundEffectsVolume, -0.05f);
                                          gameState.soundManager.EditVolume(gameState.soundManager.jump, gameState.soundManager.soundEffectsVolume, -0.00f);
                                          gameState.soundManager.EditVolume(gameState.soundManager.victory, gameState.soundManager.soundEffectsVolume, -0.00f);  };   
    soundEffectsControl.buttonMiddle = {placementWidth + buttonWidth + padding, placementHeight, placementWidth * 3, buttonHeight};
    soundEffectsControl.buttonInc = MyButton{soundEffectsControl.buttonMiddle.x + soundEffectsControl.buttonMiddle.width + padding, placementHeight, buttonWidth, buttonHeight, "+", "", ""};
    soundEffectsControl.buttonInc.onClick = [&]{ gameState.soundManager.EditVolume(gameState.soundManager.spikeBreak, gameState.soundManager.soundEffectsVolume, +0.05f);
                                          gameState.soundManager.EditVolume(gameState.soundManager.jump, gameState.soundManager.soundEffectsVolume, +0.0f);
                                          gameState.soundManager.EditVolume(gameState.soundManager.victory, gameState.soundManager.soundEffectsVolume, +0.0f);  }; // put 0.0 here only to increment once per click and not 3 times since we dont want 0.15f total


    // Bind music volume
    musicControl.Bind(gameState.soundManager.musicVolume, "Music");

    // Bind sound effects volume
    soundEffectsControl.Bind(gameState.soundManager.soundEffectsVolume, "SFX");
}

void PauseMenu::PauseGame() {
    SetExitKey(KEY_NULL);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32); 

    printf("inside %s\n", isGamePaused ? "true" : "false");
    while (isGamePaused && !WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            isGamePaused = false;
            break;
        }

        BeginDrawing();
            ClearBackground(DARKGRAY);

            Show();
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

void DebugManager::Show(GameState& gameState){
    ShowHitboxes(gameState);
    ShowMenu(gameState);

}

void DebugManager::ShowMenu(GameState& gameState){
    GetMenuColor();
    box.x = gameState.map.MAP_WIDTH - box.width;
    box.y = 20;

    DrawRectangleRec(box, currentColor);
    DrawRectangleLinesEx(box, 1.0f, outlineColor);

    DrawFPS(box.x + 10, box.y + 10);
    DrawText((std::string("Player position : {") + std::to_string((int)gameState.player.position.x) 
        + "-" + std::to_string((int)gameState.player.position.y) + "}").c_str(), box.x + 10, box.y + 40, 12, DARKGRAY);
    DrawText((std::string("Player velocity : {") + std::to_string((int)gameState.player.velocity.x) 
        + "-" + std::to_string((int)gameState.player.velocity.y) + "}").c_str(), box.x + 10, box.y + 70, 12, DARKGRAY);
}

void DebugManager::ShowHitboxes(GameState& gameState){
    // player hitbox
    gameState.player.DrawHitBox();

    // drawing ending point
    gameState.map.grid.DrawEndingPointHitbox();
    
    // triangle hitbox
    for (MyTriangle tri : gameState.map.grid.triangles){
        tri.DrawVertices();
    }

}

