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

    ActionMode& mode;            // reference to external state
    MyButton insertButton{};
    MyButton removeButton{};
    MyButton bucketButton{};
    MyButton moveButton{};

    InfoScreen();
    explicit InfoScreen(ActionMode& modeRef);

    std::vector<MyButton> buttons;
    // Update hover color based on mouse
    void GetMenuColor();

    // Drawing background and title of the section
    void DrawBase(ActionMode mode);

    void DrawWidgets();

    // Draw the panel
    void Draw(ActionMode mode);
};
