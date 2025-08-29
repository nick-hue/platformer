#pragma once
#include "raylib.h"
#include "raygui.h"

class MyButton {
public:
    Rectangle box{};
    char* text{};


    MyButton();

    MyButton(float x, float y, float width, float height, const char* text);

    void Draw();
};
