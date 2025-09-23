#pragma once
#include "raylib.h"
class GameState;

class TextureHandler {
public:
    Texture2D player;
    Texture2D keyGoal;
    Texture2D heart;
    Texture2D spike;

    TextureHandler() = default;
    void LoadTextures();
    void UnloadTextures();
    void SetupPlayerTexture(GameState& gameState);
    void SetupKeyGoalTexture(GameState& gameState);
    void SetupHeartTextures(GameState& gameState);
    void SetupSpikeTextures(GameState& gameState);
    void SetupTextures(GameState& gameState);

};