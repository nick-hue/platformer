#pragma once
#include "raylib.h"

class DebugMenu {
public:
    bool active = false;
    Rectangle box{};
    Color currentColor{};
    Color mainColor{};
    Color outlineColor{};

    DebugMenu();

    void GetMenuColor();
    void Draw();
};