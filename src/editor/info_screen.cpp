#include "info_screen.h"

InfoScreen::InfoScreen(ActionMode& modeRef, std::string& exportedMapNameRef) : mode(modeRef), exportedMapName(exportedMapNameRef) {
    // use floats to avoid narrowing
    box = { (float)EDITOR_WIDTH, 0.0f, (float)GUI_WIDTH, (float)GUI_HEIGHT};
    mainColor = LIGHTGRAY;
    outlineColor = MAROON;
    currentColor = mainColor;

    insertButton = { EDITOR_WIDTH + 20.0f, 64.0f, 120.0f, 30.0f , "Insert", "#22#", 'I'};
    insertButton.onClick = [&]{ mode = ActionMode::INSERT; };

    removeButton = { EDITOR_WIDTH + 20.0f, 104.0f, 120.0f, 30.0f , "Remove", "#28#", 'R'};
    removeButton.onClick = [&]{ mode = ActionMode::REMOVE; };

    bucketButton = { EDITOR_WIDTH + 20.0f, 144.0f, 120.0f, 30.0f , "Bucket", "#29#", 'B'};
    bucketButton.onClick = [&]{ mode = ActionMode::BUCKET; };
    
    moveButton = { EDITOR_WIDTH + 20.0f, 184.0f, 120.0f, 30.0f , "Move", "#68#", 'M'};
    moveButton.onClick = [&]{ mode = ActionMode::MOVE; };

    exportButton = { EDITOR_WIDTH + 20.0f, 224.0f, 120.0f, 30.0f , "Export", "#05#", 'E'};
    exportButton.onClick = [&]{ ExportMap(exportedMapName.c_str()); };

    startPointButton = { EDITOR_WIDTH + 20.0f, 264.0f, 120.0f, 30.0f , "Start Point", "#170#", 'S'};
    startPointButton.onClick = [&]{ mode = ActionMode::START_POINT; };

    buttons = { insertButton, removeButton, bucketButton, moveButton, exportButton, startPointButton};

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
