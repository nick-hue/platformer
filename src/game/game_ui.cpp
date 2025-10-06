#include "game_ui.h"
#include "game.h"

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

void GameUI::UpdateBackground(GameState& gameState){
    wrapW = gameState.textureHandler.background.width * bgScale;
    float dx = gameState.player.position.x - gameState.player.previousPosition.x;
    gameState.player.previousPosition = gameState.player.position;

    scrollBack -= dx * backgroundSlowdown;
    if (scrollBack <= -wrapW) scrollBack += wrapW;
    if (scrollBack >= 0.0f)    scrollBack -= wrapW; // handle moving right too
}

void GameUI::Update(GameState& gameState) {
    UpdateBackground(gameState);
    
}