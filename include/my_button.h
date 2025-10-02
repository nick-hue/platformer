#pragma once
#include "raylib.h"
#include "raygui.h"
#include <functional>
#include <string>

class MyButton {
public:
    Rectangle box{};
    std::string text{};
    std::function<void()> onClick;
    int icon{};
    std::string selectLetter{};
    std::string displayText{};
    int fontSize{32};

    // default button styles
    int muteColor = 0xB21E2AFF;
    int oldNormal  = GuiGetStyle(BUTTON, BASE_COLOR_NORMAL);

    MyButton();
    MyButton(float x, float y, float width, float height, const char* text, int icon, const char* selectLetter);
    int Draw();
    int Draw(bool value);
};
