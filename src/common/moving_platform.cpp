#include "moving_platform.h"
#include "game.h"

void MovingPlatform::Draw() const {
    DrawRectangleRec(box, color);
    DrawRectangleLinesEx(box, 1.0f, color);
}

void MovingPlatform::Move(GameState& gameState){
    printf("Moving...\n");
    if (position.x > endPos) movingDirection = -1;
    if (position.x < startPos) movingDirection = 1;
    
    position.x += velocity.x * movingDirection * gameState.dt;
    
}

void MovingPlatform::Update(GameState& gameState){
    Move(gameState);
    SyncRect();
}