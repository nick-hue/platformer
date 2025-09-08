#include "info_screen.h"

InfoScreen::InfoScreen(ActionMode& actionModeRef, TriangleMode& triangleModeRef, std::string& exportedMapNameRef, std::string& importedMapNameRef, Grid& gridRef) : actionMode(actionModeRef), triangleMode(triangleModeRef), exportedMapName(exportedMapNameRef), importedMapName(importedMapNameRef), grid(gridRef) {
    // use floats to avoid narrowing
    box = { (float)EDITOR_WIDTH, 0.0f, (float)GUI_WIDTH, (float)GUI_HEIGHT};
    mainColor = LIGHTGRAY;
    outlineColor = MAROON;
    currentColor = mainColor;
    showMessageBox = false;
    messageBox = { 85, 70, 250, 100 };

    strncpy(importBuf,  importedMapName.c_str(), sizeof(importBuf)-1);
    strncpy(exportBuf,  exportedMapName.c_str(), sizeof(exportBuf)-1);

    MakeButtons();
}

void InfoScreen::MakeButtons(){
    float height_placement = 100.0f;

    insertButton = { EDITOR_WIDTH + SIDE_OFFSET, height_placement, BUTTON_WIDTH, BUTTON_HEIGHT, " Insert", "#22#", " [I]"};
    insertButton.onClick = [&]{ actionMode = ActionMode::INSERT; triangleMode = TriangleMode::NONE; };
    buttons.push_back(insertButton);

    height_placement+=BUTTON_TOP_PADDING;
    removeButton = { EDITOR_WIDTH + SIDE_OFFSET, height_placement, BUTTON_WIDTH, BUTTON_HEIGHT, "Remove", "#28#", " [R]"};
    removeButton.onClick = [&]{ actionMode = ActionMode::REMOVE; triangleMode = TriangleMode::NONE; };
    buttons.push_back(removeButton);

    height_placement+=BUTTON_TOP_PADDING;
    bucketButton = { EDITOR_WIDTH + SIDE_OFFSET, height_placement, BUTTON_WIDTH, BUTTON_HEIGHT, "Bucket", "#29#", " [B]"};
    bucketButton.onClick = [&]{ actionMode = ActionMode::BUCKET; triangleMode = TriangleMode::NONE; };
    buttons.push_back(bucketButton);

    height_placement+=BUTTON_TOP_PADDING;
    moveButton = { EDITOR_WIDTH + SIDE_OFFSET, height_placement, BUTTON_WIDTH, BUTTON_HEIGHT, "Move", "#68#", " [M]"};
    moveButton.onClick = [&]{ actionMode = ActionMode::MOVE; triangleMode = TriangleMode::NONE; };
    buttons.push_back(moveButton);

    height_placement+=BUTTON_TOP_PADDING;
    importButton = { EDITOR_WIDTH + SIDE_OFFSET, height_placement, BUTTON_WIDTH, BUTTON_HEIGHT, "Import", "#03#", " [CTRL + I]"};
    importButton.onClick = [&]{ grid.ImportMap(importedMapName.c_str()); };
    buttons.push_back(importButton);
    importBox = { EDITOR_WIDTH + SIDE_OFFSET + BUTTON_WIDTH + 5, height_placement,  BUTTON_WIDTH, 28 };

    height_placement+=BUTTON_TOP_PADDING;
    exportButton = { EDITOR_WIDTH + SIDE_OFFSET, height_placement, BUTTON_WIDTH, BUTTON_HEIGHT, "Export", "#04#", " [CTRL + E]"};
    exportButton.onClick = [&]{ grid.ExportMap(exportedMapName.c_str()); };
    buttons.push_back(exportButton);
    exportBox = { EDITOR_WIDTH + SIDE_OFFSET + BUTTON_WIDTH + 5, height_placement,  BUTTON_WIDTH, 28 };


    height_placement+=BUTTON_TOP_PADDING;
    startPointButton = { EDITOR_WIDTH + SIDE_OFFSET, height_placement, BUTTON_WIDTH, BUTTON_HEIGHT, "Start Point", "#170#", " [S]"};
    startPointButton.onClick = [&]{ actionMode = ActionMode::START_POINT; };
    buttons.push_back(startPointButton);

    height_placement+=BUTTON_TOP_PADDING;
    endPointButton = { EDITOR_WIDTH + SIDE_OFFSET, height_placement, BUTTON_WIDTH, BUTTON_HEIGHT, "End Point", "#151#", " [E]"};
    endPointButton.onClick = [&]{ actionMode = ActionMode::END_POINT; };
    buttons.push_back(endPointButton);

    height_placement+=BUTTON_TOP_PADDING;
    clearButton = { EDITOR_WIDTH + SIDE_OFFSET, height_placement, BUTTON_WIDTH, NON_TEXT_BUTTON_HEIGHT, "Clear", "#24#", ""};
    clearButton.onClick = [&]{ showMessageBox = true; actionMode = ActionMode::NONE; };
    buttons.push_back(clearButton);

    height_placement+=BUTTON_TOP_PADDING;
    float width_placement = EDITOR_WIDTH + SIDE_OFFSET;
    spikeButtonLEFT = { width_placement, height_placement, NON_TEXT_BUTTON_WIDTH, NON_TEXT_BUTTON_HEIGHT, "", "#118#", ""};
    spikeButtonLEFT.onClick = [&]{ actionMode = ActionMode::TRIANGLE; triangleMode = TriangleMode::LEFT;};
    buttons.push_back(spikeButtonLEFT);
    
    width_placement+=SMALL_BUTTONS_SIDE_PADDING;
    spikeButtonRIGHT = { width_placement, height_placement, NON_TEXT_BUTTON_WIDTH, NON_TEXT_BUTTON_HEIGHT, "", "#119#", ""};
    spikeButtonRIGHT.onClick = [&]{ actionMode = ActionMode::TRIANGLE; triangleMode = TriangleMode::RIGHT;};
    buttons.push_back(spikeButtonRIGHT);
    
    width_placement+=SMALL_BUTTONS_SIDE_PADDING;
    spikeButtonDOWN = { width_placement, height_placement, NON_TEXT_BUTTON_WIDTH, NON_TEXT_BUTTON_HEIGHT, "", "#120#", ""};
    spikeButtonDOWN.onClick = [&]{ actionMode = ActionMode::TRIANGLE; triangleMode = TriangleMode::DOWN;};
    buttons.push_back(spikeButtonDOWN);
    
    width_placement+=SMALL_BUTTONS_SIDE_PADDING;
    spikeButtonUP = { width_placement, height_placement, NON_TEXT_BUTTON_WIDTH, NON_TEXT_BUTTON_HEIGHT, "", "#121#", ""};
    spikeButtonUP.onClick = [&]{ actionMode = ActionMode::TRIANGLE; triangleMode = TriangleMode::UP;};
    buttons.push_back(spikeButtonUP);
}


void InfoScreen::GetMenuColor() {
    Vector2 mouse_pos = GetMousePosition();
    currentColor = CheckCollisionPointRec(mouse_pos, box) ? Fade(mainColor, 0.5f) : mainColor;
}

void InfoScreen::DrawBase(ActionMode mode, TriangleMode triangleMode){
    GetMenuColor();
    DrawRectangleRec(box, currentColor);
    DrawLineEx({EDITOR_WIDTH+3, 0}, {EDITOR_WIDTH+3, EDITOR_HEIGHT}, 5.0f, DARKGRAY);
    DrawText("Info Screen", (int)(box.x + 10), (int)(box.y + 10), 24, DARKGRAY);
    DrawText(ToDrawString(mode), (int)(box.x + 10), (int)(box.y + 40), 20, DARKGRAY);
    DrawText(ToDrawString(triangleMode), (int)(box.x + 10), (int)(box.y + 60), 20, DARKGRAY);
}

void InfoScreen::DrawButtons(){
    for (auto &button : buttons){
        button.Draw();
    }
}

void InfoScreen::DrawTextBoxes(){
    DrawRectangleRec(importBox, Fade(GRAY, 0.8f));
    DrawRectangleRec(exportBox, Fade(GRAY, 0.8f));
}

void InfoScreen::DrawWidgets(){
   DrawButtons();
   DrawTextBoxes();   
}

void InfoScreen::HandleClearMessageBox(){
    if (showMessageBox){
        int result = GuiMessageBox(messageBox, "#191#Clear Grid", "Are you sure you want to clear the grid?", "No;Yes");

        printf("result = %d\n", result);
        if (result == 1) {
            printf("Abort clearing screen\n");
            showMessageBox = false;
            return;
        } else if (result == 2) {
            printf("Clearing screen...\n");
            grid.Clear();
            showMessageBox = false;
        }
    }
}

void InfoScreen::HandleFilePathTextBoxes(){
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mp = GetMousePosition();
        bool inImport = CheckCollisionPointRec(mp, importBox);
        bool inExport = CheckCollisionPointRec(mp, exportBox);
        editImportPath = inImport;
        editExportPath = !inImport && inExport;
        if (!inImport && !inExport) ClearTextFocus();
    }

    if (GuiTextBox(importBox, importBuf,  sizeof(importBuf),  editImportPath)) {
        printf("Toggle import path...\n");
        actionMode = ActionMode::NONE;
        triangleMode = TriangleMode::NONE;
        editImportPath = false;                
        importedMapName = importBuf;
    }
    if (GuiTextBox(exportBox, exportBuf,  sizeof(exportBuf),  editExportPath)) {
        printf("Toggle export path...\n");
        actionMode = ActionMode::NONE;
        triangleMode = TriangleMode::NONE;
        editExportPath = false;
        exportedMapName = exportBuf;
    }

    // have to make it work with not wsl
    // Handle Drag n Drop
    // if (IsFileDropped()) {
    //     FilePathList dropped = LoadDroppedFiles();
    //     if (dropped.count > 0) {
    //         importedMapName = dropped.paths[0];
    //         printf("Dropped file: %s\n", importedMapName.c_str());
    //     }
    //     UnloadDroppedFiles(dropped);
    // }
}

void InfoScreen::Draw(ActionMode mode, TriangleMode triMode) {
    DrawBase(mode, triMode);
    DrawWidgets();
    HandleClearMessageBox();
    HandleFilePathTextBoxes();

}
