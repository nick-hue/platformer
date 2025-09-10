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
#include "game_world_config.h"

class GameState {
    public:
        Player player;
        Map map;
        int levelIndex{1};
        std::string currLevelFilename = "exported_map_1.txt";

    GameState() : player(), map(currLevelFilename.c_str()) {}

    void CheckWin();
};