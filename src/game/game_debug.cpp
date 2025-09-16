#include "game_debug.h"

void ShowDebug(GameState& gameState) {
    
    int DEBUG_INFO_X = gameState.map.MAP_WIDTH - 150;
    int DEBUG_INFO_Y = 50;
    int DEBUG_LINE_SPACING = 15;

    DrawFPS(DEBUG_INFO_X, 10);
    DrawText("DEBUG INFO:", DEBUG_INFO_X, DEBUG_INFO_Y, 20, BLACK);
    DrawText(TextFormat("Pos: (%.1f, %.1f)", gameState.player.position.x, gameState.player.position.y), DEBUG_INFO_X, DEBUG_INFO_Y + DEBUG_LINE_SPACING * 2, 12, DARKGRAY);
    DrawText(TextFormat("Vel: (%.1f, %.1f)", gameState.player.velocity.x, gameState.player.velocity.y), DEBUG_INFO_X, DEBUG_INFO_Y + DEBUG_LINE_SPACING * 3, 12, DARKGRAY);

    gameState.player.Draw();

    for (MyTriangle& tri : gameState.map.grid.triangles) {
        tri.DrawVertices();
    }

    gameState.map.DrawEndPoint();


}