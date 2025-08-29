#include "info_screen.h"

InfoScreen::InfoScreen() {
    // use floats to avoid narrowing
    box = { (float)SCREEN_WIDTH - 200.0f, 0.0f, 200.0f, 100.0f };
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

void InfoScreen::Draw(ActionMode mode) {
    GetMenuColor();
    DrawRectangleRec(box, currentColor);
    DrawRectangleLinesEx(box, 1.0f, outlineColor);
    DrawText("Info Screen", (int)(box.x + 10), (int)(box.y + 10), 20, DARKGRAY);

    DrawText(ModeToText(mode), (int)(box.x + 10), (int)(box.y + 40), 18, DARKGRAY);
}

const char* InfoScreen::ModeToText(ActionMode mode) {
    switch (mode) {
        case ActionMode::INSERT: return "Action mode: INSERT";
        case ActionMode::REMOVE: return "Action mode: REMOVE";
        default:                 return "Action mode: Unknown";
    }
}
