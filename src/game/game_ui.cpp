#include "game_ui.h"
#include "game_world_config.h"

GameUI::GameUI(Vector2 position, int maxLives) {
    heartPosition = position;
    for (int i = 0; i < maxLives; ++i) {
        hearts[i] = Heart();
    }
}

void GameUI::DrawHearts(GameState& gameState) {
    for (int i = 0; i < gameState.maxLives; ++i) {
        if (i < gameState.currentLives) {
            hearts[i].DrawFilled();
        } else {
            hearts[i].DrawEmpty();
        }
    }
}

void GameUI::Draw(GameState& gameState) {
    DrawHearts(gameState);
}

void GameUI::Update(int lives) {
    printf("lives  : %d\n", lives);
}