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

    GameState() : player((float)GAME_SCREEN_WIDTH/2.0f - 25.0f, (float)GAME_SCREEN_HEIGHT/2.0f, 50, 50, MAROON), map("exported_map.txt") {}
};