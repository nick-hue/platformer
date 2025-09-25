#pragma once
#include "player.h"
#include "grid.h"
#include "map.h"
#include "item_sprite.h"
#include "game_ui.h"
#include "texture.h"
#include "sound_manager.h"
#include "raylib.h"
#include "tile.h"
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
    bool         isGamePaused{false};
    int          levelIndex{1};

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
    , isGamePaused(false)
    , levelIndex(1)
    {}
};

class PauseMenu {
public:
    bool isGamePaused = false;

    void Show();
    void PauseGame();
};

class DebugMenu {
public:
    bool active = false;
    Rectangle box{};
    Color currentColor{};
    Color mainColor{};
    Color outlineColor{};

    DebugMenu();

    void GetMenuColor();
    void Draw();
    void Show(GameState& gameState);
};

class Game{
public:
    PauseMenu pauseMenu;
    GameState gameState;
    DebugMenu debugMenu;

    Game();
    void Run();
    void Initialize();
    void Shutdown();
};