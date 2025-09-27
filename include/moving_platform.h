#pragma once
#include "raylib.h"
#include "item_sprite.h"

class MovingPlatform {
public:
    Vector2 position;
    Vector2 velocity;
    Color color;
    ItemSprite sprite; 
    Rectangle box;


    MovingPlatform() = default;

    void Draw() const ;

};