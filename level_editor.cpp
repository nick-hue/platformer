#include "raylib.h"
#include <cstdio>
#include <string>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 512

#define CELL_SIZE 32

#define GRID_WIDTH SCREEN_WIDTH / CELL_SIZE
#define GRID_HEIGHT SCREEN_HEIGHT / CELL_SIZE

enum ActionMode {
    INSERT,
    REMOVE,
    UNKNOWN
};

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
            filledSelectionColor = MAROON;
            emptySelectionColor = GRAY;
            isOccupied = false;
        }

        Cell(Vector2 pos, Color filledCol, Color emptyCol, Color filledSelCol, Color emptySelCol) {
            position = pos;
            filledColor = filledCol;
            emptyColor = emptyCol;
            filledSelectionColor = filledSelCol;
            emptySelectionColor = emptySelCol;  
            isOccupied = false;
        }

        void Draw() {
            Color c;
            if (isOccupied) {
                c = filledColor;
            } else {
                c = emptyColor;
            }
            DrawRectangle(position.x, position.y, CELL_SIZE, CELL_SIZE, c);    
        }

        void Select(){
            Color c;
            if (isOccupied){
                c = filledSelectionColor;
            } else {
                c = emptySelectionColor;
            }
            DrawRectangle(position.x, position.y, CELL_SIZE, CELL_SIZE, c);
                
        }
};


class Grid{

    public:
        int width = GRID_WIDTH;
        int height = GRID_HEIGHT;
        Cell matrix[GRID_WIDTH][GRID_HEIGHT];

        Grid() {
            for (int i = 0; i < GRID_WIDTH; i++){
                for (int j = 0; j < GRID_HEIGHT; j++){
                    Vector2 pos = { float(i * CELL_SIZE), float(j * CELL_SIZE) };
                    // printf("position: (%f, %f)\n", pos.x, pos.y);
                    matrix[i][j] = Cell(pos, DARKGRAY, LIGHTGRAY, MAROON, GRAY);
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
            // printf("selected cell: (%f, %f)\n", grid_pos.x, grid_pos.y);
            if (grid_pos.x >= 0 && grid_pos.x < GRID_WIDTH && grid_pos.y >= 0 && grid_pos.y < GRID_HEIGHT) {
                matrix[int(grid_pos.x)][int(grid_pos.y)].Select();
            }
        }

        bool IsInbounds(Vector2 grid_pos) {
            return (grid_pos.x >= 0 && grid_pos.x < GRID_WIDTH && grid_pos.y >= 0 && grid_pos.y < GRID_HEIGHT);
        }

};
Grid grid;

class DebugMenu {
    public:
        bool active = false;
        Rectangle box;
        Color currentColor;
        Color mainColor;
        Color outlineColor;

        DebugMenu() {
            box = { 0, 0, 200, 100 };
            mainColor = SKYBLUE;
            outlineColor = BLUE;
        }

        void GetMenuColor(){
           Vector2 mouse_pos = GetMousePosition();
            if (CheckCollisionPointRec(mouse_pos, box))
                currentColor = Fade(mainColor, 0.5f);
            else{
                currentColor = mainColor;    
            }
        }

        void Draw() {
            if (!active) return;

            GetMenuColor();
            DrawRectangleRec(box, currentColor);
            DrawRectangleLinesEx(box, 1, outlineColor);
            DrawText("Debug Mode: ON", 10, 10, 20, RED);
        }
};

class InfoScreen {
    public:
        Rectangle box;
        Color currentColor;
        Color mainColor;
        Color outlineColor;


        InfoScreen() {
            box = { SCREEN_WIDTH - 200, 0, 200, 100 };
            mainColor = LIGHTGRAY;
            outlineColor = MAROON;
        }

        void GetMenuColor(){
           Vector2 mouse_pos = GetMousePosition();
            if (CheckCollisionPointRec(mouse_pos, box))
                currentColor = Fade(mainColor, 0.5f);
            else{
                currentColor = mainColor;    
            }
        }

        void Draw(ActionMode mode) {
            GetMenuColor();
            DrawRectangleRec(box, currentColor);
            DrawRectangleLinesEx(box, 1, outlineColor);
            DrawText("Info Screen", box.x + 10, box.y + 10, 20, DARKGRAY);
            DrawText(("Action mode: " + GetActionModeString(mode)).c_str(), box.x + 10, box.y + 40, 18, DARKGRAY);
        }

        std::string GetActionModeString(ActionMode mode) {
            switch (mode) {
                case INSERT: return "Insert";
                case REMOVE: return "Remove";
                default: return "Unknown";
            }
        }
};

class State {
    public:
        DebugMenu debugMenu;
        ActionMode actionMode;
        InfoScreen infoScreen;
        Grid grid;

        State() {
            debugMenu = DebugMenu();
            actionMode = INSERT;
            infoScreen = InfoScreen();
            grid = Grid();
        }
};
State state;

void HandleInput(){
    if (IsKeyPressed(KEY_I)){
        state.actionMode = INSERT;
    }
    if (IsKeyPressed(KEY_R)) {
        state.actionMode = REMOVE;
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 mouse_pos = GetMousePosition();
        Vector2 grid_pos = {mouse_pos.x / CELL_SIZE, mouse_pos.y / CELL_SIZE};

        if (!grid.IsInbounds(grid_pos)) {
            printf("Out of bounds: (%f, %f)\n", grid_pos.x, grid_pos.y);
            return;
        }

        switch(state.actionMode) {
            case INSERT:
                printf("insert mode\n");
                grid.matrix[int(grid_pos.x)][int(grid_pos.y)].isOccupied = true;
                break;
            case REMOVE:
                printf("remove mode\n");
                grid.matrix[int(grid_pos.x)][int(grid_pos.y)].isOccupied = false;
                break;
            default:
                printf("unknown mode\n");
                // code block
            }
    }

    if (IsKeyPressed(KEY_TAB)) state.debugMenu.active = !state.debugMenu.active;
}
//TODO: make adding mode, removing mode for cells



int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Level Editor");
    SetWindowPosition(300, 100);
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    printf("GRID: %dx%d\n", GRID_WIDTH, GRID_HEIGHT);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        HandleInput();

        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);
            grid.Draw();
            grid.ShowSelectedCell();
            state.debugMenu.Draw();
            state.infoScreen.Draw(state.actionMode);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
