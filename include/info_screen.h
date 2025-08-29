#pragma once
#include "raylib.h"
#include "level_editor_defs.h" // for SCREEN_WIDTH, ActionMode

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

    // Draw the panel
    void Draw(ActionMode mode);

private:
    // Utility: convert mode to text (no std::string to keep header light)
    static const char* ModeToText(ActionMode mode);
};
