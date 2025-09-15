#pragma once
#include "raylib.h"
#include "player.h"
#include "item_sprite.h"    
#include "heart.h"
#include "game_world_config.h"
#include <array>

class GameState;

class GameUI {
public:
    Vector2 heartPosition{100.0f, 100.0f};
    std::array<Heart, MAX_LIVES> hearts;

    GameUI() = default;

    GameUI(Vector2 position, int maxLives);

    void Update(int lives);
    void Draw(GameState& gameState);
    void DrawHearts(GameState& gameState);
};