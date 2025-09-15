#pragma once
#include <string>
#include "player.h"
#include "grid.h"
#include "map.h"

inline constexpr int GAME_SCREEN_WIDTH  = 1280;
inline constexpr int GAME_SCREEN_HEIGHT = 720;

class GameState {
    public:
        Player player;
        MySprite playerSprite;
        std::string currLevelFilename{"exported_map_1.txt"};
        Map map;
        TriangleMode movingSpikeMode{TriangleMode::DOWN};
        bool gamePaused{false};
        int levelIndex{1};

    GameState() : player(), map(currLevelFilename.c_str()) {}
};