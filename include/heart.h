#pragma once
#include "raylib.h"
#include "item_sprite.h"

class Heart {
public:
    Vector2 position{0.0f, 0.0f}; 
    ItemSprite sprite{};

    Heart() = default;

    void DrawFilled() const ;
    void DrawEmpty() const ;
};