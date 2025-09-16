#pragma once
#include "raylib.h"
#include "item_sprite.h"

class Heart {
public:
    Vector2 position{10.0f, 10.0f}; 
    ItemSprite sprite{};

    Heart() = default;

    void DrawFilled() const ;
    void DrawEmpty() const ;
};