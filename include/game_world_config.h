#pragma once
#include <string>
#include "player.h"
#include "grid.h"
#include "map.h"
#include "item_sprite.h"
#include "game_ui.h"

inline constexpr int GAME_SCREEN_WIDTH  = 1280;
inline constexpr int GAME_SCREEN_HEIGHT = 720;
#define MAX_LIVES 3

class GameState {
public:
    Player      player;
    PlayerSprite playerSprite;
    ItemSprite   keyGoalSprite;
    int          currentLives{MAX_LIVES};
    int          maxLives{MAX_LIVES};
    GameUI       gameUI;                  // declared BEFORE map
    std::string  currLevelFilename{"exported_map_1.txt"};
    Map          map;                     // declared AFTER gameUI
    TriangleMode movingSpikeMode{TriangleMode::DOWN};
    bool         isGamePaused{false};
    int          levelIndex{1};

    GameState()
    : player()
    , playerSprite()
    , keyGoalSprite()
    , currentLives(MAX_LIVES)
    , maxLives(MAX_LIVES)
    , gameUI(Vector2{100.0f, 100.0f}, maxLives)     // gameUI comes before map
    , currLevelFilename("exported_map_1.txt")
    , map(currLevelFilename.c_str())                // map comes after gameUI
    , movingSpikeMode(TriangleMode::DOWN)
    , isGamePaused(false)
    , levelIndex(1)
    {}
};