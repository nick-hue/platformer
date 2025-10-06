#pragma once
#include "raylib.h"
#include "anim.h"
#include "texture.h"
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
};

class TileSprite : public ItemSprite
{
public:
    void Draw(std::pair<int,int> location) const;
};


class SpikeSprite : public ItemSprite
{
public:
    void Draw(int col) const;
};

class PlatformSprite : public ItemSprite
{
public:
    ItemSprite left;
    ItemSprite mid;
    ItemSprite right;

    void SetSprite(Texture2D& tex_left, Texture2D& tex_mid, Texture2D& tex_right, Vector2 pos, int length);
    void Draw(int length) const ; 
    void DrawMiddle(int length) const ;

};