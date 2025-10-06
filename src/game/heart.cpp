#include "heart.h"

void Heart::DrawFilled() const {
    if (sprite.texture.id == 0) {  // fallback if no sprite yet
        DrawRectangle(position.x, position.y, 32, 32, RED);
        return;
    }

    Rectangle src{
        (float)(sprite.currentFrame * sprite.frameWidth),
        (float)(sprite.idle.row * sprite.frameHeight),
        (float)sprite.frameWidth,
        (float)sprite.frameHeight
    };

    Rectangle dst = { position.x, position.y, sprite.frameWidth * sprite.scale, sprite.frameHeight * sprite.scale };
    
    Vector2 origin = {0.0f, 0.0f};       // Top-left origin
    DrawTexturePro(sprite.texture, src, dst, origin, 0.0f, WHITE);
}

void Heart::DrawEmpty() const {
    if (sprite.texture.id == 0) {  // fallback if no sprite yet
        DrawRectangle(position.x, position.y, 32, 32, GRAY);
        return;
    }

    Rectangle src{
        (float)( (sprite.currentFrame + 2) * sprite.frameWidth),  // assuming empty heart is the next frame
        (float)(sprite.idle.row * sprite.frameHeight),
        (float)sprite.frameWidth,
        (float)sprite.frameHeight
    };

    Rectangle dst = { position.x, position.y, sprite.frameWidth * sprite.scale, sprite.frameHeight * sprite.scale };
    
    Vector2 origin = {0.0f, 0.0f};       // Top-left origin
    DrawTexturePro(sprite.texture, src, dst, origin, 0.0f, WHITE);
}