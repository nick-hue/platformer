#pragma once
#include "player.h"
#include "grid.h"
#include "map.h"
#include "item_sprite.h"
#include "game_ui.h"
#include "texture.h"
#include "sound_manager.h"
#include "raylib.h"
#include "raygui.h"
#include "tile.h"
#include "my_button.h"
#include "pause_menu.h"
#include "debug_manager.h"
#include <string>
#include <cstdio>
#include <vector>
#include <algorithm>

inline constexpr int GAME_SCREEN_WIDTH  = 1280;
inline constexpr int GAME_SCREEN_HEIGHT = 720;
inline constexpr int MAX_LIVES = 3;

class GameState {
public:
    Player       player;
    PlayerSprite playerSprite;
    TextureHandler textureHandler;
    SoundManager soundManager;
    ItemSprite   keyGoalSprite;
    ItemSprite   spikeSprite;
    std::vector<ItemSprite>   floorTileSprites;
    int          currentLives{MAX_LIVES};
    int          maxLives{MAX_LIVES};
    GameUI       gameUI;                 
    std::string  currLevelFilename{"exported_map_1.txt"};
    Map          map;
    TriangleMode movingSpikeMode{TriangleMode::DOWN};
    bool         shouldRun{true};
    int          levelIndex{1};
    float        dt; // deltaTime between frames

    GameState()
    : player()
    , playerSprite()
    , textureHandler()
    , soundManager()
    , keyGoalSprite()
    , currentLives(MAX_LIVES)
    , maxLives(MAX_LIVES)
    , gameUI(Vector2{35.0f, 25.0f}, maxLives)     
    , currLevelFilename("exported_map_1.txt")
    , map(currLevelFilename.c_str())
    , movingSpikeMode(TriangleMode::DOWN)
    , shouldRun(true)
    , levelIndex(1)
    {}
};


class Game{
public:
    GameState gameState{};
    PauseMenu pauseMenu{};
    DebugManager debugMenu{};

    Game() = default;
    void Run();
    void Initialize();
    void Shutdown();
};