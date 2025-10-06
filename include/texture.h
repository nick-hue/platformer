#pragma once
#include "raylib.h"
#include "tile.h"
class GameState;

class TextureHandler {
public:
    Texture2D background;
    Texture2D player;
    Texture2D keyGoal;
    Texture2D heart;
    Texture2D spike;
    Texture2D floor;
    Texture2D ground;

    TextureHandler() = default;
    void LoadTextures();
    void UnloadTextures();
    void SetupTextures(GameState& gameState);

    void SetupPlayerTexture(GameState& gameState);
    void SetupKeyGoalTexture(GameState& gameState);
    void SetupHeartTextures(GameState& gameState);
    void SetupSpikeTextures(GameState& gameState);
    void SetupFloorTileTextures(GameState& gameState);
};