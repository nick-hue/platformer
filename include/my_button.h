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
    std::string iconId{};
    std::string selectLetter{};
    std::string displayText{};
    int fontSize{32};

    // default button styles
    int muteColor = 0xB21E2AFF;
    int oldNormal  = GuiGetStyle(BUTTON, BASE_COLOR_NORMAL);

    MyButton();
    MyButton(float x, float y, float width, float height, const char* text, const char* iconId, const char* selectLetter);
    int Draw();
    int Draw(bool value);
};
