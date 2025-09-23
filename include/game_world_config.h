#pragma once
#include <string>
#include "player.h"
#include "grid.h"
#include "map.h"
#include "item_sprite.h"
#include "game_ui.h"
#include "texture.h"

inline constexpr int GAME_SCREEN_WIDTH  = 1280;
inline constexpr int GAME_SCREEN_HEIGHT = 720;
inline constexpr int MAX_LIVES = 3;

class GameState {
public:
    Player       player;
    PlayerSprite playerSprite;
    TextureHandler textureHandler;
    ItemSprite   keyGoalSprite;
    ItemSprite   spikeSprite;
    int          currentLives{MAX_LIVES};
    int          maxLives{MAX_LIVES};
    GameUI       gameUI;                 
    std::string  currLevelFilename{"exported_map_1.txt"};
    Map          map;
    TriangleMode movingSpikeMode{TriangleMode::DOWN};
    bool         isGamePaused{false};
    int          levelIndex{1};

    GameState()
    : player()
    , playerSprite()
    , textureHandler()
    , keyGoalSprite()
    , currentLives(MAX_LIVES)
    , maxLives(MAX_LIVES)
    , gameUI(Vector2{35.0f, 25.0f}, maxLives)     
    , currLevelFilename("exported_map_1.txt")
    , map(currLevelFilename.c_str())
    , movingSpikeMode(TriangleMode::DOWN)
    , isGamePaused(false)
    , levelIndex(1)
    {}
};