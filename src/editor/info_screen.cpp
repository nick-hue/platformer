#include "info_screen.h"

InfoScreen::InfoScreen() {
    // use floats to avoid narrowing
    box = { (float)EDITOR_WIDTH, 0.0f, (float)GUI_WIDTH, (float)GUI_HEIGHT};
    mainColor = LIGHTGRAY;
    outlineColor = MAROON;
    currentColor = mainColor;
}

void InfoScreen::GetMenuColor() {
    Vector2 mouse_pos = GetMousePosition();
    if (CheckCollisionPointRec(mouse_pos, box))
        currentColor = Fade(mainColor, 0.5f);
    else
        currentColor = mainColor;
}

void InfoScreen::DrawBase(ActionMode mode){
    GetMenuColor();
    DrawRectangleRec(box, currentColor);
    DrawLineEx({EDITOR_WIDTH+3, 0}, {EDITOR_WIDTH+3, EDITOR_HEIGHT}, 5.0f, DARKGRAY);
    DrawText("Info Screen", (int)(box.x + 10), (int)(box.y + 10), 20, DARKGRAY);
    DrawText(ToDrawString(mode), (int)(box.x + 10), (int)(box.y + 40), 18, DARKGRAY);
}

void InfoScreen::DrawWidgets(){
    Rectangle btn = { 24.0f, 24.0f, 120.0f, 30.0f };
    if (GuiButton(btn, "#191#Show Message")) {
        printf("Show Message button pressed\n");
    }
}

void InfoScreen::Draw(ActionMode mode) {
    DrawBase(mode);
    DrawWidgets();

}
