#include "my_button.h"

MyButton::MyButton() {
    box = {0,0,100,30};
    text = "Button";
    selectLetter = "-";
    icon = -1;
    onClick = nullptr;
}

MyButton::MyButton(float x, float y, float width, float height, const char* text, int id, const char* selectLetter){
    box = { x, y, width, height };

    this->text = std::string(text ? text : "");
    this->selectLetter = std::string(selectLetter ? selectLetter : "");
    this->icon = id;

    displayText = this->icon + " " + this->text + this->selectLetter;
}

int MyButton::Draw() {
    const std::string base = text + selectLetter;

    const char* label = (icon >= 0) ? GuiIconText(icon, base.c_str())
                                    : base.c_str();

    if (GuiButton(box, label)) {
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