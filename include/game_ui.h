#pragma once
#include "raylib.h"
#include "player.h"
#include "item_sprite.h"    
#include "heart.h"
#include <array>
#include <cstdio>
// #include "game_world_config.h"

class GameState;

class GameUI {
public:
    Vector2 heartPosition{50.0f, 100.0f};
    std::array<Heart, 3> hearts;

    GameUI() = default;

    GameUI(Vector2 position, int maxLives);

    void Update(int lives);
    void Draw(GameState& gameState);
    void DrawHearts(GameState& gameState);
};