#include "raylib.h"
#include "level_editor_defs.h"
#include "grid.h"
#include "cell.h"
#include "debug_menu.h"

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
                case ActionMode::INSERT: return "INSERT";
                case ActionMode::REMOVE: return "REMOVE";
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
            actionMode = ActionMode::INSERT;
            infoScreen = InfoScreen();
            grid = Grid();
        }
};
State state;

void HandleInput(){
    if (IsKeyPressed(KEY_I)){
        state.actionMode = ActionMode::INSERT;
    }
    if (IsKeyPressed(KEY_R)) {
        state.actionMode = ActionMode::REMOVE;
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 mouse_pos = GetMousePosition();
        Vector2 grid_pos = {mouse_pos.x / CELL_SIZE, mouse_pos.y / CELL_SIZE};

        if (!state.grid.IsInbounds(grid_pos)) {
            printf("Out of bounds: (%f, %f)\n", grid_pos.x, grid_pos.y);
            return;
        }

        switch (state.actionMode) {
            case ActionMode::INSERT:
                // set occupied
                // state.grid.At(gx, gy).isOccupied = true;
                state.grid.matrix[int(grid_pos.x)][int(grid_pos.y)].isOccupied = true;

                break;
            case ActionMode::REMOVE:
                // clear occupied
                // state.grid.At(gx, gy).isOccupied = false;
                state.grid.matrix[int(grid_pos.x)][int(grid_pos.y)].isOccupied = false;
                break;
        }  
    }

    if (IsKeyPressed(KEY_TAB)) state.debugMenu.active = !state.debugMenu.active;
}
//TODO: bucket mode 
//TODO: move mode 




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
            state.grid.Draw();
            state.grid.ShowSelectedCell();
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
