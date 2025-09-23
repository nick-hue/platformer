#include "texture.h"
#include "item_sprite.h"
#include "my_triangle.h"
#include "game_world_config.h"

void TextureHandler::LoadTextures() {
    background = LoadTexture("assets/resources/background.png");
    if (background.id == 0) { TraceLog(LOG_ERROR, "Failed to load background texture"); }

    player = LoadTexture("assets/sprites/characters/Soldier/Soldier/Soldier.png");
    if (player.id == 0) { TraceLog(LOG_ERROR, "Failed to load player texture"); }

    keyGoal = LoadTexture("assets/sprites/items/key/goal_key.png");
    if (keyGoal.id == 0) { TraceLog(LOG_ERROR, "Failed to load key goal texture"); }

    heart = LoadTexture("assets/sprites/ui/heart/heart_32x32.png");
    if (heart.id == 0) { TraceLog(LOG_ERROR, "Failed to load heart texture"); }

    spike = LoadTexture("assets/sprites/items/spike/spikes.png");
    if (spike.id == 0) { TraceLog(LOG_ERROR, "Failed to load spike texture"); }

    floor = LoadTexture("assets/resources/floor_tiles/cobblestone_3.png");
    if (floor.id == 0) { TraceLog(LOG_ERROR, "Failed to load floor cobble texture"); }
}

void TextureHandler::SetupTextures(GameState& gameState) {
    SetupPlayerTexture(gameState);
    SetupKeyGoalTexture(gameState);
    SetupHeartTextures(gameState);
    SetupSpikeTextures(gameState);
    SetupFloorTileTexture(gameState);
}

void TextureHandler::UnloadTextures() {
    if (background.id != 0) UnloadTexture(background);
    if (player.id != 0) UnloadTexture(player);
    if (keyGoal.id != 0) UnloadTexture(keyGoal);
    if (heart.id != 0) UnloadTexture(heart);
    if (spike.id != 0) UnloadTexture(spike);
    if (floor.id != 0) UnloadTexture(floor);
}

void TextureHandler::SetupPlayerTexture(GameState& gameState){
    gameState.playerSprite.SetSprite(player, 9, 7);
    gameState.playerSprite.idle = Anim{0, 0, 4, 12.f};   // row 0, cols [0..3]
    gameState.playerSprite.walk = Anim{1, 0, 9, 12.f};  // row 1, cols [0..8]
}

void TextureHandler::SetupKeyGoalTexture(GameState& gameState){
    gameState.keyGoalSprite.SetSprite(keyGoal, gameState.map.grid.endingPoint, 24, 1);
    gameState.keyGoalSprite.idle = Anim{0, 0, 24, 12.f};     
}

void TextureHandler::SetupHeartTextures(GameState& gameState) {
    for (int i = 0; i < gameState.maxLives; ++i) {
        gameState.gameUI.hearts[i].position = Vector2{(i+1) * gameState.gameUI.heartPosition.x, gameState.gameUI.heartPosition.y};
        gameState.gameUI.hearts[i].sprite.SetSprite(heart
                                    , gameState.gameUI.hearts[i].position,
                                    3, 1);
        gameState.gameUI.hearts[i].sprite.idle = Anim{0, 0, 1, 12.f};
    }
}

void TextureHandler::SetupSpikeTextures(GameState& gameState) {
    // spikes
    for (MyTriangle& tri : gameState.map.grid.triangles) {
        tri.sprite.SetSprite(spike, tri.position, 4, 1);
        tri.sprite.idle = Anim{0, 0, 1, 12.f};
        tri.sprite.scale = 2.0f;
        switch (tri.mode)
        {
            case TriangleMode::UP:      tri.spriteCol = 0; break;
            case TriangleMode::RIGHT:   tri.spriteCol = 1; break;
            case TriangleMode::DOWN:    tri.spriteCol = 2; break;
            case TriangleMode::LEFT:    tri.spriteCol = 3; break;
            default: break;
        }
    }
}

void TextureHandler::SetupFloorTileTexture(GameState& gameState){
    for (auto& tile : gameState.map.tiles){
        tile.sprite.SetSprite(floor, tile.position, 1, 1);
        tile.sprite.scale = 0.031f;
    }
}