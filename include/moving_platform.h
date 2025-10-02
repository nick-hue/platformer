#pragma once
#include "raylib.h"
#include "item_sprite.h"
#include <utility>
#include <string>
#include <sstream>

class GameState;

class MovingPlatform {
public:
    Vector2 position{.0f, .0f};
    Vector2 lastPosition{.0f, .0f};
    Vector2 velocity{100.0f, 100.0f};
    Color color{BLACK};
    Color outlineColor{RED};
    ItemSprite sprite{}; 
    Rectangle box{position.x, position.y, 100.0f, 30.0f};
    Vector4 movementBounds{position.x, position.x+200, position.y, position.y}; // {start_x, stop_x, start_y, stop_y}
    Vector2 movementDirection{1.0f, 1.0f};
    int movingDirection{1}; // moving right initially
    int id{-100};

    MovingPlatform() = default;
    MovingPlatform(Vector2 start_pos, Vector2 movement, int plat_id);

    void Update(GameState& gameState);
    void Draw() const ;
    void SyncRect() { box.x = position.x; box.y = position.y; };

    void Move(GameState& gameState);


    inline std::string ToString(const MovingPlatform& plat);
};