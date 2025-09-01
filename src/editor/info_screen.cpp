#include "info_screen.h"

InfoScreen::InfoScreen(ActionMode& actionModeRef, TriangleMode& triangleModeRef, std::string& exportedMapNameRef, Grid& gridRef) : actionMode(actionModeRef), triangleMode(triangleModeRef), exportedMapName(exportedMapNameRef), grid(gridRef) {
    // use floats to avoid narrowing
    box = { (float)EDITOR_WIDTH, 0.0f, (float)GUI_WIDTH, (float)GUI_HEIGHT};
    mainColor = LIGHTGRAY;
    outlineColor = MAROON;
    currentColor = mainColor;

    MakeButtons();
}

void InfoScreen::MakeButtons(){
    float height_placement = 64.0f;

    insertButton = { EDITOR_WIDTH + SIDE_OFFSET, height_placement, BUTTON_WIDTH, BUTTON_HEIGHT, " Insert", "#22#", " [I]"};
    insertButton.onClick = [&]{ actionMode = ActionMode::INSERT; };
    buttons.push_back(insertButton);

    height_placement+=BUTTON_TOP_PADDING;
    removeButton = { EDITOR_WIDTH + SIDE_OFFSET, height_placement, BUTTON_WIDTH, BUTTON_HEIGHT, "Remove", "#28#", " [R]"};
    removeButton.onClick = [&]{ actionMode = ActionMode::REMOVE; };
    buttons.push_back(removeButton);

    height_placement+=BUTTON_TOP_PADDING;
    bucketButton = { EDITOR_WIDTH + SIDE_OFFSET, height_placement, BUTTON_WIDTH, BUTTON_HEIGHT, "Bucket", "#29#", " [B]"};
    bucketButton.onClick = [&]{ actionMode = ActionMode::BUCKET; };
    buttons.push_back(bucketButton);

    height_placement+=BUTTON_TOP_PADDING;
    moveButton = { EDITOR_WIDTH + SIDE_OFFSET, height_placement, BUTTON_WIDTH, BUTTON_HEIGHT, "Move", "#68#", " [M]"};
    moveButton.onClick = [&]{ actionMode = ActionMode::MOVE; };
    buttons.push_back(moveButton);

    height_placement+=BUTTON_TOP_PADDING;
    exportButton = { EDITOR_WIDTH + SIDE_OFFSET, height_placement, BUTTON_WIDTH, BUTTON_HEIGHT, "Export", "#05#", " [CTRL + E]"};
    exportButton.onClick = [&]{ ExportMap(exportedMapName.c_str()); };
    buttons.push_back(exportButton);

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
    clearButton.onClick = [&]{ grid.Clear(); };
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

void InfoScreen::DrawBase(ActionMode mode){
    GetMenuColor();
    DrawRectangleRec(box, currentColor);
    DrawLineEx({EDITOR_WIDTH+3, 0}, {EDITOR_WIDTH+3, EDITOR_HEIGHT}, 5.0f, DARKGRAY);
    DrawText("Info Screen", (int)(box.x + 10), (int)(box.y + 10), 20, DARKGRAY);
    DrawText(ToDrawString(mode), (int)(box.x + 10), (int)(box.y + 40), 18, DARKGRAY);
}

void InfoScreen::DrawWidgets(){
    for (auto &button : buttons){
        // printf("%s\n", button.displayText.c_str());
        button.Draw();
    }
}

void InfoScreen::Draw(ActionMode mode) {
    DrawBase(mode);
    DrawWidgets();
}
