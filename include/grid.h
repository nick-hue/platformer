#pragma once
#include "raylib.h"
#include "level_editor_defs.h"  
#include "cell.h"               
#include <vector>
#include "my_triangle.h"
#include <fstream>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

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
    Vector2 endingPoint{-1.0f,-1.0f};

    Grid();
    void Draw();
    void Clear();
    
    // General 
    bool TriangleExistsAt(Vector2 pos);
    void MakeCustomTriangle(int gx, int gy, TriangleMode mode);
    bool IsInbounds(int gx, int gy);
    
    // For edit mode
    void ImportMap(const char *filename);
    void ExportMap(const char *filename);
    void DrawStartingPoint();
    void DrawEndingPoint();
    void SetStartPoint(int gx, int gy);
    void SetEndPoint(int gx, int gy);
    void BucketFill(int gx, int gy);
    void BucketHelper(int gx, int gy);
    void MoveFrom(int gx, int gy);
    int GetAdjacentCells(int gx, int gy, std::vector<Cell>& outCells);
    void ShowSelectedCell();
    int GetTriangleIndex(int gx, int gy) const;    
    
    // For game mode 
    void Update(float dt);
    std::vector<MyTriangle> GetMovingTriangles(std::vector<MyTriangle>& triangles, TriangleMode mode);
    
    StoreItem ClassifyCell(int x, int y) const;
    char GetOutputChar(int x, int y) const;
};


