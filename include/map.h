#pragma once
#include "raylib.h"
#include "tile.h"
#include "cell.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

class Map {
    public:
        int MAP_WIDTH{0};
        int MAP_HEIGHT{0};
        int TILE_WIDTH{0};
        int TILE_HEIGHT{0};

        // cells: dynamic 2D matrix
        std::vector<std::vector<Cell>> matrix;
        // obstacles
        std::vector<Tile> tiles;

        Map();

        Map(const char *filename);

        void CellToTiles();
};

