#include "texture.h"
#include "item_sprite.h"
#include "my_triangle.h"
#include "game.h"

void TextureHandler::LoadTextures() {
    background = LoadTexture("assets/resources/background.png");
    if (background.id == 0) { TraceLog(LOG_ERROR, "Failed to load background texture"); }
    textures.emplace_back(background);

    player = LoadTexture("assets/sprites/characters/penguin.png");
    if (player.id == 0) { TraceLog(LOG_ERROR, "Failed to load player texture"); }
    textures.emplace_back(player);

    keyGoal = LoadTexture("assets/sprites/world/items/key/goal_key.png");
    if (keyGoal.id == 0) { TraceLog(LOG_ERROR, "Failed to load key goal texture"); }
    textures.emplace_back(keyGoal);

    heart = LoadTexture("assets/sprites/ui/heart/heart_32x32.png");
    if (heart.id == 0) { TraceLog(LOG_ERROR, "Failed to load heart texture"); }
    textures.emplace_back(heart);

    spike = LoadTexture("assets/sprites/world/items/spike/spikes.png");
    if (spike.id == 0) { TraceLog(LOG_ERROR, "Failed to load spike texture"); }
    textures.emplace_back(spike);
    
    ground = LoadTexture("assets/sprites/world/ground-Sheet.png");
    if (ground.id == 0) { TraceLog(LOG_ERROR, "Failed to load ground texture"); }
    textures.emplace_back(ground);

    platform.left = LoadTexture("assets/sprites/world/platform/platform_left.png");
    if (platform.left.id == 0) { TraceLog(LOG_ERROR, "Failed to left platform texture"); }
    textures.emplace_back(platform.left);

    platform.mid = LoadTexture("assets/sprites/world/platform/platform_mid.png");
    if (platform.mid.id == 0) { TraceLog(LOG_ERROR, "Failed to mid platform texture"); }
    textures.emplace_back(platform.mid);

    platform.right = LoadTexture("assets/sprites/world/platform/platform_right.png");
    if (platform.right.id == 0) { TraceLog(LOG_ERROR, "Failed to right platform texture"); }
    textures.emplace_back(platform.right);

}

void TextureHandler::SetupTextures(GameState& gameState) {
    SetupPlayerTexture(gameState);
    SetupKeyGoalTexture(gameState);
    SetupHeartTextures(gameState);
    SetupSpikeTextures(gameState);
    SetupFloorTileTextures(gameState);
    SetupPlatformTextures(gameState);
}

void TextureHandler::UnloadTextures() {
    for (auto& tex : textures){
        if (tex.id != 0) UnloadTexture(tex);    
    };
}

void TextureHandler::SetupPlayerTexture(GameState& gameState){
    gameState.playerSprite.SetSprite(player, 8, 2);
    gameState.playerSprite.idle = Anim{0, 0, 4, 6.f};   // row 0, cols [0..3]
    gameState.playerSprite.scale = 1.4f;
    gameState.playerSprite.walk = Anim{1, 0, 8, 6.f};  // row 1, cols [0..8]
}

void TextureHandler::SetupKeyGoalTexture(GameState& gameState){
    gameState.keyGoalSprite.SetSprite(keyGoal, gameState.map.grid.endingPoint, 24, 1);
    gameState.keyGoalSprite.idle = Anim{0, 0, 24, 12.f};     
}

void TextureHandler::SetupHeartTextures(GameState& gameState) {
    for (int i = 0; i < gameState.maxLives; ++i) {
        gameState.gameUI.hearts[i].position = Vector2{(i+1) * gameState.gameUI.startingPosition.x, gameState.gameUI.startingPosition.y};
        gameState.gameUI.hearts[i].sprite.SetSprite(heart
                                    , gameState.gameUI.hearts[i].position,
                                    3, 1);
        gameState.gameUI.hearts[i].sprite.idle = Anim{0, 0, 1, 12.f};
    }
}

void TextureHandler::SetupSpikeTextures(GameState& gameState) {
    for (MyTriangle& tri : gameState.map.grid.triangles) {
        tri.sprite.SetSprite(spike, tri.position, 4, 1);
        tri.sprite.idle = Anim{0, 0, 1, 12.f};
        tri.sprite.scale = 1.0f;
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

std::pair<int, int> GetSpriteLocation(GroundTileType type){
    switch (type)
    {
    case GroundTileType::GRASS_1: return {0, 0};
    case GroundTileType::GRASS_2: return {0, 1};
    case GroundTileType::GRASS_3: return {0, 2};
    case GroundTileType::UNDERGROUND_1: return {1,0}; 
    case GroundTileType::UNDERGROUND_2: return {1,1}; 
    case GroundTileType::UNDERGROUND_3: return {1,2}; 
    case GroundTileType::UNDERGROUND_4: return {2,0}; 
    case GroundTileType::UNDERGROUND_5: return {2,1}; 
    case GroundTileType::UNDERGROUND_6: return {2,2}; 
    case GroundTileType::UNKNOWN: return {-1,-1};
    default: return {-1, -1};
    }
}

void TextureHandler::SetupFloorTileTextures(GameState& gameState){
    for (auto& tile : gameState.map.tiles){
        if (!tile.sprite) tile.sprite = std::make_unique<TileSprite>();
        tile.sprite->SetSprite(ground, tile.position, 3, 3);   
        tile.sprite->scale = 1.0f;
        tile.spriteSheetLocation = GetSpriteLocation(tile.type);
    }
}


void TextureHandler::SetupPlatformTextures(GameState& gameState){
    for (auto& plat : gameState.map.grid.platforms){
        printf("Setting up platform : %d\n", plat.id);
        plat.sprite.SetSprite(platform.left, platform.mid, platform.right, plat.position, plat.length);
    }

}