#include "item_sprite.h"

void ItemSprite::SetSprite(Texture2D tex, Vector2 pos, int cols_, int rows_) {
    texture = tex;
    position = pos;
    cols = cols_;
    rows = rows_;
    frameWidth = texture.width  / cols;
    frameHeight = texture.height / rows;
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
    if (texture.id == 0) {  // fallback if no texture yet
        DrawRectangle(100, 100, 32, 32, BLUE);
        // printf("HERE\n");
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
    DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);
}

void SpikeSprite::Draw(int col) const {
    if (texture.id == 0) {   // fallback if no texture yet
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
    DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);
}

void TileSprite::Draw(std::pair<int,int> location) const {
    if (texture.id == 0) {  // fallback if no texture yet
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
    DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);
}

void PlatformSprite::SetSprite(Texture2D& tex_left, Texture2D& tex_mid, Texture2D& tex_right, Vector2 pos, int length){
    position = pos;
    left.SetSprite(tex_left, position, 1, 1);
    mid.SetSprite(tex_mid, Vector2{position.x + left.texture.width, position.y}, 1, 1);
    right.SetSprite(tex_right, Vector2{position.x + left.texture.width + mid.texture.width * length, position.y}, 1, 1);
    cols = 1;
    rows = 1;
    frameWidth = texture.width  / cols;
    frameHeight = texture.height / rows;
    currentFrame = 0;
    animTimer = 0.0f;
    scale = 1.0f;  
    texture = {};
}

void PlatformSprite::DrawMiddle(int length) const {
    if (mid.texture.id == 0) {  // fallback if no texture yet
        DrawRectangle(100, 100, 32, 32, BLUE);
        return;
    }
    printf("width : %d - height : %d\n", mid.texture.width, mid.texture.height);
    Rectangle src{
        (float)(currentFrame * mid.texture.width),
        (float)(idle.row * mid.texture.height),
        (float)mid.texture.width,
        (float)mid.texture.height
    };

    // printf("length %d\n", length);
    Rectangle dst = { mid.position.x, mid.position.y, mid.texture.width * scale * length, mid.texture.height * scale };
    
    Vector2 origin = {0.0f, 0.0f};       // Top-left origin
    DrawTexturePro(mid.texture, src, dst, origin, 0.0f, WHITE);
}
void PlatformSprite::Draw(int length) const {
    left.Draw();
    DrawMiddle(length);
    right.Draw();
}