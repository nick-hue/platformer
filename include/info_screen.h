#pragma once
#include "raylib.h"
#include "level_editor_defs.h"
#include "raygui.h"
#include "grid.h"
#include "my_button.h"
#include <vector>

constexpr float BUTTON_WIDTH = 150.0f;
constexpr float BUTTON_HEIGHT = 30.0f;
constexpr float NON_TEXT_BUTTON_WIDTH = 30.0f;
constexpr float NON_TEXT_BUTTON_HEIGHT = 30.0f;
constexpr float BUTTON_TOP_PADDING = 40.0f;
constexpr float SIDE_OFFSET = 20.0f;
constexpr float SMALL_BUTTONS_SIDE_PADDING = 40.0f;

class InfoScreen {
public:
    // UI state
    Rectangle box{};
    Color currentColor{};
    Color mainColor{};
    Color outlineColor{};

    ActionMode& actionMode;            // reference to external state
    TriangleMode& triangleMode;            // reference to external state
    std::string& exportedMapName;
    Grid& grid;

    MyButton insertButton{};
    MyButton removeButton{};
    MyButton bucketButton{};
    MyButton moveButton{};
    MyButton exportButton{};
    MyButton startPointButton{};
    MyButton endPointButton{};
    MyButton clearButton{};

    MyButton spikeButtonUP{};
    MyButton spikeButtonDOWN{};
    MyButton spikeButtonRIGHT{};
    MyButton spikeButtonLEFT{};

    InfoScreen();
    explicit InfoScreen(ActionMode& actionModeRef, TriangleMode& triangleModeRef, std::string& exportedMapNameRef, Grid& gridRef);

    std::vector<MyButton> buttons;
    // Update hover color based on mouse
    void MakeButtons();

    void GetMenuColor();

    // Drawing background and title of the section
    void DrawBase(ActionMode actionMode);
    void DrawWidgets();
    // Draw the panel
    void Draw(ActionMode actionMode);
};
