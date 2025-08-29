#include "my_button.h"

MyButton::MyButton() {
    box = { 0, 0, 100, 30 };
    text = "Button";
    onClick = nullptr;
    selectLetter = '\0';
}



MyButton::MyButton(float x, float y, float width, float height, const char* text, char selectLetter) {
    box = { x, y, width, height };
    this->text = text;
    this->selectLetter = selectLetter;
}

int MyButton::Draw() {
    GuiButton(box, text);

    if (GuiButton(box, text)) {
            if (onClick) onClick();
            return 1;
        }
        return 0;
}