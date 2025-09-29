#pragma once
#include "raylib.h"
#include "item_sprite.h"
#include <utility>

class GameState;

class MovingPlatform {
public:
    Vector2 position{.0f, .0f};
    Vector2 velocity{100.0f, .0f};
    Color color{BLACK};
    Color outlineColor{RED};
    ItemSprite sprite{}; 
    Rectangle box{position.x, position.y, 100.0f, 30.0f};
    int startPos{0};
    int endPos{200};
    int movingDirection{1}; // moving right initially
    int id{-100};

    MovingPlatform() = default;

    void Update(GameState& gameState);
    void Draw() const ;
    void SyncRect() { box.x = position.x; box.y = position.y; };

    void Move(GameState& gameState);

};