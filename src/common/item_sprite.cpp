#include "item_sprite.h"

void ItemSprite::SetSprite(Texture2D tex, Vector2 pos, int cols_, int rows_) {
    sprite = tex;
    position = pos;
    cols = cols_;
    rows = rows_;
    frameWidth = sprite.width  / cols;
    frameHeight = sprite.height / rows;
    currentFrame = 0;
    animTimer = 0.0f;
    scale = 1.0f;    
}

void ItemSprite::UpdateAnimation(float dt) {
    animTimer += dt;
    const float spf = 1.0f / animFPS;   // seconds per frame
    while (animTimer >= spf) {
        animTimer -= spf;
        currentFrame = (currentFrame + 1) % idle.frames;
    }
}

void ItemSprite::Draw() const {
    if (sprite.id == 0) {  // fallback if no texture yet
        DrawRectangle(100, 100, 32, 32, BLUE);
        return;
    }

    Rectangle src{
        (float)(currentFrame * frameWidth),
        (float)(idle.row * frameHeight),
        (float)frameWidth,
        (float)frameHeight
    };

    Rectangle dst = { position.x, position.y, frameWidth * scale, frameHeight * scale };
    
    Vector2 origin = {0.0f, 0.0f};       // Top-left origin
    DrawTexturePro(sprite, src, dst, origin, 0.0f, WHITE);
}

void ItemSprite::Draw(int col) const {
    if (sprite.id == 0) {  // fallback if no texture yet
        DrawRectangle(position.x, position.y, 32, 32, RED);
        return;
    }

    Rectangle src{
        (float)(col * frameWidth),
        (float)(idle.row * frameHeight),
        (float)frameWidth,
        (float)frameHeight
    };

    Rectangle dst = { position.x, position.y, frameWidth * scale, frameHeight * scale };
    
    Vector2 origin = {0.0f, 0.0f};       // Top-left origin
    DrawTexturePro(sprite, src, dst, origin, 0.0f, WHITE);
}

void ItemSprite::Draw(std::pair<int,int> location) const{
    if (sprite.id == 0) {  // fallback if no texture yet
        DrawRectangle(position.x, position.y, 32, 32, BLUE);
        return;
    }

    Rectangle src{
        (float)((location.second) * frameWidth),
        (float)(location.first * frameHeight),
        (float)frameWidth,
        (float)frameHeight
    };

    Rectangle dst = { position.x, position.y, frameWidth * scale, frameHeight * scale };
    
    Vector2 origin = {0.0f, 0.0f};       // Top-left origin
    DrawTexturePro(sprite, src, dst, origin, 0.0f, WHITE);
}
