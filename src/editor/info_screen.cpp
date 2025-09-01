#include "info_screen.h"

InfoScreen::InfoScreen(ActionMode& modeRef, std::string& exportedMapNameRef, Grid& gridRef) : mode(modeRef), exportedMapName(exportedMapNameRef), grid(gridRef) {
    // use floats to avoid narrowing
    box = { (float)EDITOR_WIDTH, 0.0f, (float)GUI_WIDTH, (float)GUI_HEIGHT};
    mainColor = LIGHTGRAY;
    outlineColor = MAROON;
    currentColor = mainColor;

    float height_placement = 64.0f;

    insertButton = { EDITOR_WIDTH + SIDE_OFFSET, height_placement, BUTTON_WIDTH, BUTTON_HEIGHT, "Insert", "#22#", " [I]"};
    insertButton.onClick = [&]{ mode = ActionMode::INSERT; };

    height_placement+=BUTTON_TOP_PADDING;
    removeButton = { EDITOR_WIDTH + SIDE_OFFSET, height_placement, BUTTON_WIDTH, BUTTON_HEIGHT, "Remove", "#28#", " [R]"};
    removeButton.onClick = [&]{ mode = ActionMode::REMOVE; };

    height_placement+=BUTTON_TOP_PADDING;
    bucketButton = { EDITOR_WIDTH + SIDE_OFFSET, height_placement, BUTTON_WIDTH, BUTTON_HEIGHT, "Bucket", "#29#", " [B]"};
    bucketButton.onClick = [&]{ mode = ActionMode::BUCKET; };
    
    height_placement+=BUTTON_TOP_PADDING;
    moveButton = { EDITOR_WIDTH + SIDE_OFFSET, height_placement, BUTTON_WIDTH, BUTTON_HEIGHT, "Move", "#68#", " [M]"};
    moveButton.onClick = [&]{ mode = ActionMode::MOVE; };

    height_placement+=BUTTON_TOP_PADDING;
    exportButton = { EDITOR_WIDTH + SIDE_OFFSET, height_placement, BUTTON_WIDTH, BUTTON_HEIGHT, "Export", "#05#", " [CTRL + E]"};
    exportButton.onClick = [&]{ ExportMap(exportedMapName.c_str()); };

    height_placement+=BUTTON_TOP_PADDING;
    startPointButton = { EDITOR_WIDTH + SIDE_OFFSET, height_placement, BUTTON_WIDTH, BUTTON_HEIGHT, "Start Point", "#170#", " [S]"};
    startPointButton.onClick = [&]{ mode = ActionMode::START_POINT; };

    height_placement+=BUTTON_TOP_PADDING;
    endPointButton = { EDITOR_WIDTH + SIDE_OFFSET, height_placement, BUTTON_WIDTH, BUTTON_HEIGHT, "End Point", "#151#", " [E]"};
    endPointButton.onClick = [&]{ mode = ActionMode::END_POINT; };

    height_placement+=BUTTON_TOP_PADDING;
    clearButton = { EDITOR_WIDTH + SIDE_OFFSET, height_placement, BUTTON_WIDTH, NON_TEXT_BUTTON_HEIGHT, "Clear", "#24#", ""};
    clearButton.onClick = [&]{ grid.Clear(); };

    buttons = { insertButton, removeButton, bucketButton, moveButton, exportButton, startPointButton, endPointButton, clearButton};

}

void InfoScreen::InitializeButtons(){

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
        button.Draw();
    }
}

void InfoScreen::Draw(ActionMode mode) {
    DrawBase(mode);
    DrawWidgets();
}
