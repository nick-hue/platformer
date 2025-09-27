#pragma once
#include "raylib.h"
#include "my_button.h"

class GameState;

class PauseButtonController{    
public:
    MyButton buttonDec;
    Rectangle buttonMiddle;
    int middleTextFontSize{24};
    MyButton buttonInc;

    Color soundButtonColor{235, 168, 52, 255};

    float* volume = nullptr;      
    const char* label = "Volume"; // optional label

    void Bind(float& volumeRef, const char* labelText) {
        volume = &volumeRef;
        label = labelText;
    }

    PauseButtonController() = default;

    void Draw();
};


class PauseMenu {
public:
    bool isGamePaused{false};

    MyButton resumeButton;
    MyButton muteButton;
    PauseButtonController musicControl;
    PauseButtonController soundEffectsControl;
    MyButton exitButton;
    GameState* pgs{nullptr};

    Color soundButtonColor{235, 168, 52, 255};

    PauseMenu() = default;

    void Show();
    void PauseGame();
    void InitPauseMenuButtons(GameState& gameState);
};