#pragma once
#include "raylib.h"
#include "anim.h"
#include <cstdio>
#include <utility>

class ItemSprite {
public:
    Texture2D texture{};
    Vector2 position{0.0f, 0.0f}; // Example position
    int cols{1};
    int rows{1};
    int frameWidth{texture.width/cols};  // frame width
    int frameHeight{texture.height/rows}; // frame height
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
    void Draw(std::pair<int,int> location) const;
    void Draw(bool meow, int length, ItemSprite sprite) const ;
};
