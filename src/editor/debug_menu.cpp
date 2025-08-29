#include "debug_menu.h"

DebugMenu::DebugMenu() {
    box = { 0.0f, 0.0f, 200.0f, 100.0f };
    mainColor = SKYBLUE;
    outlineColor = BLUE;
    currentColor = mainColor;
}

void DebugMenu::GetMenuColor() {
    Vector2 mouse_pos = GetMousePosition();
    if (CheckCollisionPointRec(mouse_pos, box))
        currentColor = Fade(mainColor, 0.5f);
    else
        currentColor = mainColor;
}

void DebugMenu::Draw() {
    if (!active) return;

    GetMenuColor();
    DrawRectangleRec(box, currentColor);
    DrawRectangleLinesEx(box, 1.0f, outlineColor);
    DrawText("Debug Mode: ON", 10, 10, 20, RED);
}
