#pragma once
#include "raylib.h"
#include "level_editor_defs.h"
#include "raygui.h"
#include "grid.h"
#include "my_button.h"
#include <vector>
#include <cstring>

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

    Rectangle messageBox{};
    bool showMessageBox;

    bool editImportPath = false;
    bool editExportPath = false;
    char importBuf[256]  = "imported_map_1.txt";
    char exportBuf[256]  = "exported_map_1.txt";
    Rectangle exportBox;
    Rectangle importBox;

    ActionMode& actionMode;            
    TriangleMode& triangleMode;        
    std::string& exportedMapName;
    std::string& importedMapName;
    Grid& grid;

    MyButton insertButton{};
    MyButton removeButton{};
    MyButton bucketButton{};
    MyButton moveButton{};
    MyButton importButton{};
    MyButton exportButton{};
    MyButton startPointButton{};
    MyButton endPointButton{};
    MyButton clearButton{};

    MyButton spikeButtonUP{};
    MyButton spikeButtonDOWN{};
    MyButton spikeButtonRIGHT{};
    MyButton spikeButtonLEFT{};

    std::vector<MyButton> buttons;

    InfoScreen();
    explicit InfoScreen(ActionMode& actionModeRef, TriangleMode& triangleModeRef, std::string& exportedMapNameRef, std::string& importedMapNameRef, Grid& gridRef);

    void MakeButtons();
    
    // Update hover color based on mouse
    void GetMenuColor();

    // Drawing background and title of the section
    void DrawBase(ActionMode actionMode, TriangleMode triangleMode);
    // Draw Buttons and text boxes
    void DrawWidgets();
    // Draw Buttons
    void DrawButtons();
    // Draw Text Boxes
    void DrawTextBoxes();
    // Draw the panel
    void Draw(ActionMode actionMode, TriangleMode triMode);
    // Handle the behavior of the clear grid pop up box
    void HandleClearMessageBox();
    // Handle the behavior of the filepath text boxes
    void HandleFilePathTextBoxes();

    // check if user is editing import or export path
    bool IsEditingText() const { return editImportPath || editExportPath; }
    void ClearTextFocus() { editImportPath = editExportPath = false; }
};
