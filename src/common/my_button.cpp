#include "my_button.h"

MyButton::MyButton() {
    box = { 0, 0, 100, 30 };
    text = "Button";
    onClick = nullptr;
    selectLetter = "-";
    iconId = "#00#";
    displayText = iconId + std::string(" ") + text + selectLetter;
}

MyButton::MyButton(float x, float y, float width, float height, const char* text, const char* iconId, const char* selectLetter) {
    box = { x, y, width, height };
    this->text = text;
    this->selectLetter = selectLetter;
    this->iconId = iconId;
    displayText = this->iconId + this->text + this->selectLetter;
}

int MyButton::Draw() {
    
    if (GuiButton(box, displayText.c_str())) {
        if (onClick) onClick();
        return 1;
    }
    
    return 0;
}

int MyButton::Draw(bool value) {

    if (value) {
        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, muteColor);   
    }

    if (GuiButton(box, displayText.c_str())) {
        if (onClick) onClick();
        return 1;
    }
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, oldNormal);

    return 0;
}