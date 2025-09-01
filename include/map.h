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

        Vector2 startingPoint{-1.0f,-1.0f};
        Vector2 endingPoint{-1.0f,-1.0f};

        // cells: dynamic 2D matrix
        std::vector<std::vector<Cell>> matrix;
        // obstacles
        std::vector<Tile> tiles;

        Map();

        Map(const char *filename);

        // loads the map from a file
        void LoadMap(const char *filename);
        // makes the cells that were occupied (from the file) into tiles for the game
        void CellToTiles();
        void DrawEndPoint();
};

