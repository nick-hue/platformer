#include "game_debug.h"

void ShowDebug(GameState& gameState) {
    DrawText("DEBUG INFO:", 10, 10, 20, BLACK);
    DrawText(TextFormat("Pos: (%.1f, %.1f)", gameState.player.position.x, gameState.player.position.y), 10, 40, 10, DARKGRAY);
    DrawText(TextFormat("Vel: (%.1f, %.1f)", gameState.player.velocity.x, gameState.player.velocity.y), 10, 60, 10, DARKGRAY);

    gameState.player.Draw();

    for (MyTriangle& tri : gameState.map.grid.triangles) {
        tri.DrawVertices();
    }

}