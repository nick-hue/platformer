#pragma once
#include "raylib.h"
#include "level_editor_defs.h"  
#include "cell.h"               
#include <vector>
#include "my_triangle.h"


class Grid {
public:
    int width  = GRID_WIDTH;
    int height = GRID_HEIGHT;
    Cell matrix[GRID_WIDTH][GRID_HEIGHT];
    
    std::vector<MyTriangle> triangles;
    std::vector<Vector2> triangleSpots;

    Vector2 startingPoint{-1.0f,-1.0f};
    Vector2 endingPoint{-1.0f,-1.0f};

    Grid();
    void Draw();
    void Clear();
    void ShowSelectedCell();
    bool IsInbounds(int gx, int gy);
    void BucketFill(int gx, int gy);
    void BucketHelper(int gx, int gy);
    void MoveFrom(int gx, int gy);
    int GetAdjacentCells(int gx, int gy, std::vector<Cell>& outCells);
    void SetStartPoint(int gx, int gy);
    void SetEndPoint(int gx, int gy);
    void DrawStartingPoint();
    void DrawEndingPoint();
    void MakeCustomTriangle(int gx, int gy, TriangleMode mode);
    bool AvailableTriangleSpot(Vector2 pos);
};


