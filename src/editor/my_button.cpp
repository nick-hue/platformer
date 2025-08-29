#include "my_button.h"

MyButton::MyButton() {
    box = { 0, 0, 100, 30 };
    text = "Button";
}

MyButton::MyButton(float x, float y, float width, float height, const char* text) {
    box = { x, y, width, height };
    text = text;
}

void MyButton::Draw() {
    GuiButton(box, text);
}
