#pragma once
#include "raylib.h"
#include "anim.h"
#include <cstdio>

class ItemSprite {
public:
    Texture2D sprite{};
    Vector2 position{0.0f, 0.0f}; // Example position
    int cols{1};
    int rows{1};
    int frameWidth{sprite.width/cols};  // frame width
    int frameHeight{sprite.height/rows}; // frame height
    float animFPS{12.0f};
    float scale = 1.0f;
    
    int currentFrame{0};   
    float animTimer{0.0f};
    bool facingRight{true};

    Anim idle{ 0, 0, 0, 0.0f };  

    ItemSprite() = default;
    void SetSprite(Texture2D tex, Vector2 pos, int cols_, int rows_);
    void UpdateAnimation(float dt);
    void Draw() const;
    void Draw(int col) const;
};
