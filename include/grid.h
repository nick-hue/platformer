#pragma once
#include "raylib.h"
#include "level_editor_defs.h"  
#include "cell.h"               
#include "my_triangle.h"

#include <sstream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <utility>
#include <cmath>

class GameState;       // ← forward declaration

class Grid {
public:
    int width  = GRID_WIDTH;
    int height = GRID_HEIGHT;
    Cell matrix[GRID_WIDTH][GRID_HEIGHT];
    std::string baseMapFilePath = "assets/maps/custom/";
    
    std::vector<MyTriangle> triangles;
    std::vector<Vector2> triangleSpots;
    std::vector<const MyTriangle*> downs;


    Vector2 startingPoint{-1.0f,-1.0f};
    std::pair<int, int> startingPointGridPos{-1, -1};
    Rectangle startingPointRect{0.0f, 0.0f, 30.0f, 30.f};

    Vector2 endingPoint{-1.0f,-1.0f};
    std::pair<int, int> endingPointGridPos{-1, -1};
    Rectangle endingPointRect{0.0f, 0.0f, 30.0f, 30.f};


    Grid();
    void Draw();
    void DrawEditor();
    void Clear();
    void SyncFromGridPositions();
    void SyncFromPixelPositions();   // pixels -> grid/rects

    std::string ToString() const;
    void Dump() const; 

    // General 
    bool TriangleExistsAt(Vector2 pos);
    void MakeCustomTriangle(int gx, int gy, TriangleMode mode);
    bool IsInbounds(int gx, int gy);
    int GetTriangleIndex(int gx, int gy) const;    
    void RemoveTriangleByIndex(int index);
    
    // For edit mode
    void ImportMap(const char *filename);
    void ExportMap(const char *filename);
    bool SaveBinary(const char* filename) const;
    bool LoadBinary(const char* filename);
    void DrawStartingPoint();
    void DrawEndingPointHitbox();
    void SetStartPoint(int gx, int gy);
    void SetEndPoint(int gx, int gy);
    void BucketFill(int gx, int gy);
    void BucketHelper(int gx, int gy);
    void MoveFrom(int gx, int gy);
    int GetAdjacentCells(int gx, int gy, std::vector<Cell>& outCells);
    void ShowSelectedCell();
    
    // For game mode 
    void Update(float dt, GameState& gameState);
    
    StoreItem ClassifyCell(int x, int y) const;
    char GetOutputChar(int x, int y) const;
};


