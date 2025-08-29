#include "raylib.h"
#include "level_editor_defs.h"
#include "grid.h"
#include "cell.h"
#include "debug_menu.h"
#include "info_screen.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

class State {
    public:
        DebugMenu debugMenu;
        ActionMode actionMode{ActionMode::INSERT};
        InfoScreen infoScreen;
        Grid grid;

        // State() {
        //     debugMenu = DebugMenu();
        //     actionMode = ActionMode::INSERT;
        //     infoScreen = InfoScreen(actionMode);
        //     grid = Grid();
        // }
        State() : actionMode(ActionMode::INSERT), infoScreen(actionMode), grid() {}

};
State state;

void HandleInput(){
    if (IsKeyPressed(KEY_I)){
        state.actionMode = ActionMode::INSERT;
    }
    if (IsKeyPressed(KEY_R)) {
        state.actionMode = ActionMode::REMOVE;
    }
    if (IsKeyPressed(KEY_B)) {
        state.actionMode = ActionMode::BUCKET;
    }
    if (IsKeyPressed(KEY_M)) {
        state.actionMode = ActionMode::MOVE;
    }


    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 mouse_pos = GetMousePosition();
        int gx = (int)mouse_pos.x / CELL_SIZE;
        int gy = (int)mouse_pos.y / CELL_SIZE;

        if (!state.grid.IsInbounds(gx, gy)) {
            // printf("Out of bounds: (%d, %d)\n", gx, gy);
            return;
        }

        switch (state.actionMode) {
            case ActionMode::INSERT:
                // set occupied
                // state.grid.At(gx, gy).isOccupied = true;
                state.grid.matrix[gx][gy].isOccupied = true;

                break;
            case ActionMode::REMOVE:
                // clear occupied
                // state.grid.At(gx, gy).isOccupied = false;
                state.grid.matrix[gx][gy].isOccupied = false;
                break;
            case ActionMode::BUCKET:
                // TODO: Implement bucket fill
                break;
            case ActionMode::MOVE:
                // TODO: Implement move
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
