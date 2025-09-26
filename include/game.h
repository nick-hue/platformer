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

class PauseButtonController{    
public:
    MyButton buttonDec;
    Rectangle buttonMiddle;
    int middleTextFontSize{24};
    MyButton buttonInc;

    Color soundButtonColor{235, 168, 52, 255};

    float* volume = nullptr;      
    const char* label = "Volume"; // optional label

    void Bind(float& volumeRef, const char* labelText) {
        volume = &volumeRef;
        label = labelText;
    }

    PauseButtonController() = default;

    void Draw();
};

class PauseMenu {
public:
    bool isGamePaused{false};

    PauseButtonController musicControl;
    PauseButtonController soundEffectsControl;

    Color soundButtonColor{235, 168, 52, 255};

    // PauseMenu(GameState& gameState);
    PauseMenu() = default;

    void Show();
    void PauseGame();
    void InitPauseMenuButtons(GameState& gameState);
};

class DebugManager {
public:
    bool active = false;
    Rectangle box{};
    Color currentColor{};
    Color mainColor{};
    Color outlineColor{};

    DebugManager();

    void GetMenuColor();
    void Draw(); // editor
    void Show(GameState& gameState); // Game
    void ShowMenu(GameState& gameState);
    void ShowHitboxes(GameState& gameState);
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