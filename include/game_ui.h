#pragma once
#include "raylib.h"
#include "player.h"
#include "item_sprite.h"    
#include "heart.h"
#include <array>
#include <cstdio>
// #include "game.h"

class GameState;

class GameUI {
public:
    Vector2 heartPosition{50.0f, 100.0f};
    std::array<Heart, 3> hearts;
    float wrapW{0.0f};
    float scrollBack{0.0f};
    const float bgScale = 0.75f;     
    const float yOffset = -275.0f;
    const float backgroundSlowdown = 0.05f;

    GameUI() = default;

    GameUI(Vector2 position, int maxLives);

    void Update(GameState& gameState);
    void Draw(GameState& gameState);
    void DrawHearts(GameState& gameState);
};