#pragma once
#include "raylib.h"

class GameState;

class DebugManager {
public:
    bool active = false;
    Rectangle box{};
    Color currentColor{};
    Color mainColor{};
    Color outlineColor{};

    int platformIdFontSize{16};

    DebugManager();

    void GetMenuColor();
    void Draw(); // editor
    void Show(GameState& gameState); // Game
    void ShowMenu(GameState& gameState);
    void ShowHitboxes(GameState& gameState);
    void ShowPlatformDebug(GameState& gameState);
};
