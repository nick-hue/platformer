#pragma once
#include "raylib.h"
#include "level_editor_defs.h" // for SCREEN_WIDTH, ActionMode
#include "raygui.h"

class InfoScreen {
public:
    // UI state
    Rectangle box{};
    Color currentColor{};
    Color mainColor{};
    Color outlineColor{};

    InfoScreen();

    // Update hover color based on mouse
    void GetMenuColor();

    // Drawing background and title of the section
    void DrawBase(ActionMode mode);

    void DrawWidgets();

    // Draw the panel
    void Draw(ActionMode mode);
};
