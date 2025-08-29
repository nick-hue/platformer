#pragma once
#include "raylib.h"
#include "raygui.h"
#include <functional>

class MyButton {
public:
    Rectangle box{};
    const char* text{};
    std::function<void()> onClick;  
    char selectLetter{};


    MyButton();
    MyButton(float x, float y, float width, float height, const char* text, char selectLetter);
    int Draw();

};
