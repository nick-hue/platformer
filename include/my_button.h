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
    char selectLetter{};
    std::string displayText{};


    MyButton();
    MyButton(float x, float y, float width, float height, const char* text, const char* iconId, char selectLetter);
    int Draw();

};
