#pragma once
#include "raylib.h"
#include "level_editor_defs.h"
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
    std::string& exportedMapName;
    MyButton insertButton{};
    MyButton removeButton{};
    MyButton bucketButton{};
    MyButton moveButton{};
    MyButton exportButton{};
    MyButton startPointButton{};

    InfoScreen();
    explicit InfoScreen(ActionMode& modeRef, std::string& exportedMapNameRef);

    std::vector<MyButton> buttons;
    // Update hover color based on mouse
    void GetMenuColor();

    // Drawing background and title of the section
    void DrawBase(ActionMode mode);

    void DrawWidgets();

    // Draw the panel
    void Draw(ActionMode mode);
};
