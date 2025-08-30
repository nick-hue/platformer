#include "game_debug.h"

void ShowDebug(const Player& player) {
    DrawText("DEBUG INFO:", 10, 10, 20, BLACK);
    DrawText(TextFormat("Pos: (%.1f, %.1f)", player.position.x, player.position.y), 10, 40, 10, DARKGRAY);
    DrawText(TextFormat("Vel: (%.1f, %.1f)", player.velocity.x, player.velocity.y), 10, 60, 10, DARKGRAY);
}