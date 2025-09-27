#include "debug_manager.h"
#include "game.h"

DebugManager::DebugManager() {
    box = { 0.0f, 0.0f, 200.0f, 100.0f };
    mainColor = SKYBLUE;
    outlineColor = BLUE;
    currentColor = mainColor;
}

void DebugManager::GetMenuColor() {
    Vector2 mouse_pos = GetMousePosition();
    if (CheckCollisionPointRec(mouse_pos, box))
        currentColor = Fade(mainColor, 0.5f);
    else
        currentColor = mainColor;
}

void DebugManager::Draw() {
    if (!active) return;

    GetMenuColor();
    DrawRectangleRec(box, currentColor);
    DrawRectangleLinesEx(box, 1.0f, outlineColor);
    DrawText("Debug Mode: ON", 10, 10, 20, RED);
}

void DebugManager::Show(GameState& gameState){
    ShowHitboxes(gameState);
    ShowMenu(gameState);

}

void DebugManager::ShowMenu(GameState& gameState){
    GetMenuColor();
    box.x = gameState.map.MAP_WIDTH - box.width;
    box.y = 20;

    DrawRectangleRec(box, currentColor);
    DrawRectangleLinesEx(box, 1.0f, outlineColor);

    DrawFPS(box.x + 10, box.y + 10);
    DrawText((std::string("Player position : {") + std::to_string((int)gameState.player.position.x) 
        + "-" + std::to_string((int)gameState.player.position.y) + "}").c_str(), box.x + 10, box.y + 40, 12, DARKGRAY);
    DrawText((std::string("Player velocity : {") + std::to_string((int)gameState.player.velocity.x) 
        + "-" + std::to_string((int)gameState.player.velocity.y) + "}").c_str(), box.x + 10, box.y + 70, 12, DARKGRAY);
}

void DebugManager::ShowHitboxes(GameState& gameState){
    // player hitbox
    gameState.player.DrawHitBox();

    // drawing ending point
    gameState.map.grid.DrawEndingPointHitbox();
    
    // triangle hitbox
    for (MyTriangle tri : gameState.map.grid.triangles){
        tri.DrawVertices();
    }

}

