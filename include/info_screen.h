#pragma once
#include "raylib.h"
#include "level_editor_defs.h" // for SCREEN_WIDTH, ActionMode
#include "raygui.h"
#include "my_button.h"
#include <vector>

class InfoScreen {
public:
    // UI state
    Rectangle box{};
    Color currentColor{};
    Color mainColor{};
    Color outlineColor{};

    // Rectangle insertButton{};
    // Rectangle removeButton{};
    // Rectangle bucketButton{};
    // Rectangle moveButton{};

    MyButton insertButton{};
    MyButton removeButton{};
    MyButton bucketButton{};
    MyButton moveButton{};

    std::vector<MyButton> buttons;


    InfoScreen();

    // Update hover color based on mouse
    void GetMenuColor();

    // Drawing background and title of the section
    void DrawBase(ActionMode mode);

    void DrawWidgets();

    // Draw the panel
    void Draw(ActionMode mode);
};
