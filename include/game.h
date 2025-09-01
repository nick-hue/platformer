#pragma once

#include "raylib.h"
#include "player.h"
#include "tile.h"
#include "game_debug.h"
#include "map.h"
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

constexpr int GAME_SCREEN_WIDTH  = 1024;
constexpr int GAME_SCREEN_HEIGHT  = 512;

class GameState {
    public:
        Player player;
        Map map;
        int levelIndex{1};
        std::string currLevelFilename{"assets/maps/exported_map_1.txt"};

    // GameState() : player(), map(currLevelFilename.c_str()) {}
    GameState() : player(), map("assets/maps/exported_map_1.txt") {}

    void CheckWin();
};