#include "raylib.h"
#include <cstdio>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 512

#define CELL_SIZE 32

#define GRID_WIDTH SCREEN_WIDTH / CELL_SIZE
#define GRID_HEIGHT SCREEN_HEIGHT / CELL_SIZE

class Cell {
    public:
        Vector2 position;
        Color filledColor;
        Color emptyColor;
        Color filledSelectionColor;
        Color emptySelectionColor;
        bool isOccupied;

        Cell() {
            position = {0, 0};
            filledColor = DARKGRAY;
            emptyColor = LIGHTGRAY;
            isOccupied = false;
        }

        Cell(Vector2 pos, Color filledCol, Color emptyCol) {
            position = pos;
            filledColor = filledCol;
            emptyColor = emptyCol;
            isOccupied = false;
        }

        void Draw() {
            if (isOccupied) {
                DrawRectangle(position.x, position.y, CELL_SIZE, CELL_SIZE, filledColor);
            } else {
                DrawRectangle(position.x, position.y, CELL_SIZE, CELL_SIZE, emptyColor);    
            }
        }

        void Select(){
            if (isOccupied){
                DrawRectangle(position.x, position.y, CELL_SIZE, CELL_SIZE, filledSelectionColor);
            } else {
                DrawRectangle(position.x, position.y, CELL_SIZE, CELL_SIZE, emptySelectionColor);
            }
                
        }
};


class Grid{

    public:
        int width = GRID_WIDTH;
        int height = GRID_HEIGHT;
        Cell matrix[GRID_WIDTH][GRID_HEIGHT];

        Grid() {
            Initialize();
        }

        void Initialize(){
            for (int i = 0; i < GRID_WIDTH; i++){
                for (int j = 0; j < GRID_HEIGHT; j++){
                    Vector2 pos = { float(i * CELL_SIZE), float(j * CELL_SIZE) };
                    // printf("position: (%f, %f)\n", pos.x, pos.y);
                    matrix[i][j] = Cell(pos, DARKGRAY, LIGHTGRAY);
                }
            }
        }

        void Draw() {

            for (int i = 0; i < GRID_WIDTH; i++){
                DrawLine(i * CELL_SIZE, 0, i * CELL_SIZE, SCREEN_HEIGHT, GRAY);
                for (int j = 0; j < GRID_HEIGHT; j++){
                    DrawLine(0, j * CELL_SIZE, SCREEN_WIDTH, j * CELL_SIZE, GRAY);
                    matrix[i][j].Draw();
                }
            }
        }
        
        void ShowSelectedCell() {
            Vector2 mouse_pos = GetMousePosition();
            Vector2 grid_pos = {mouse_pos.x / CELL_SIZE, mouse_pos.y / CELL_SIZE};
            printf("selected cell: (%.f, %.f)\n", grid_pos.x, grid_pos.y);
            if (grid_pos.x >= 0 && grid_pos.x < GRID_WIDTH && grid_pos.y >= 0 && grid_pos.y < GRID_HEIGHT) {
                matrix[int(grid_pos.x)][int(grid_pos.y)].Select();
            }
        }
};

Grid grid;

void HandleInput(){
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mouse_pos = GetMousePosition();
        Vector2 grid_pos = {mouse_pos.x / CELL_SIZE, mouse_pos.y / CELL_SIZE};
        if (grid_pos.x >= 0 && grid_pos.x < GRID_WIDTH && grid_pos.y >= 0 && grid_pos.y < GRID_HEIGHT) {
            grid.matrix[int(grid_pos.x)][int(grid_pos.y)].isOccupied = !grid.matrix[int(grid_pos.x)][int(grid_pos.y)].isOccupied;
        }
    }
}
//TODO: make adding mode, removing mode for cells


int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Level Editor");
    SetWindowPosition(300, 100);
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    grid.Initialize();

    printf("GRID: %dx%d\n", GRID_WIDTH, GRID_HEIGHT);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        HandleInput();

        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);
            grid.Draw();
            grid.ShowSelectedCell();
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
