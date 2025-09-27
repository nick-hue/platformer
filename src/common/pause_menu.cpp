#include "pause_menu.h"
#include "game.h"

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
