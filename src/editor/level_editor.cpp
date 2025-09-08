#include "raylib.h"
#include "level_editor_defs.h"
#include "grid.h"
#include "cell.h"
#include "debug_menu.h"
#include "info_screen.h"
#include "raygui.h"

class State {
    public:
        Grid grid;
        DebugMenu debugMenu;
        ActionMode actionMode{ActionMode::INSERT};
        TriangleMode triangleMode{TriangleMode::NONE};
        std::string exportedMapName{"assets/maps/exported_map_1.txt"};
        InfoScreen infoScreen;

    State()
        : grid(), debugMenu(), actionMode(ActionMode::INSERT), triangleMode(TriangleMode::NONE), exportedMapName("assets/maps/exported_map_1.txt"), infoScreen(actionMode, triangleMode, exportedMapName, grid) // now grid is constructed
        {}

};
State state;

void HandleInput(){
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_E)) {
        printf("Exporting...\n");
        state.grid.ExportMap(state.exportedMapName.c_str());
    }
    
    int pressedKey = GetKeyPressed();
    switch (pressedKey)
    {
    case KEY_I:
        state.actionMode = ActionMode::INSERT;
        break;
    case KEY_R:
        state.actionMode = ActionMode::REMOVE;
        break;
    case KEY_B:
        state.actionMode = ActionMode::BUCKET;
        break;
    case KEY_M:
        state.actionMode = ActionMode::MOVE;
        break;
    case KEY_S:
        state.actionMode = ActionMode::START_POINT;
        break;
    case KEY_E:
        state.actionMode = ActionMode::END_POINT;
        break;
    default:
        break;
    }

    if (state.actionMode == ActionMode::NONE) return;

    Vector2 mouse_pos = GetMousePosition();
    int gx = (int)mouse_pos.x / CELL_SIZE;
    int gy = (int)mouse_pos.y / CELL_SIZE;

    int removeIndex = -1;
    // check continuous button press actions
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (!state.grid.IsInbounds(gx, gy)) {
            return;
        }

        switch (state.actionMode) {
            case ActionMode::INSERT:
                // set occupied
                state.grid.matrix[gx][gy].isOccupied = true;
                break;
            case ActionMode::REMOVE:
                // clear occupied
                state.grid.matrix[gx][gy].isOccupied = false;
                removeIndex = state.grid.GetTriangleIndex(gx,gy);
                if (removeIndex == -1) return;

                printf("remove index : %d\n", removeIndex);
                state.grid.triangles.erase(state.grid.triangles.begin() + removeIndex);
                state.grid.triangleSpots.erase(state.grid.triangleSpots.begin() + removeIndex);
                break;
            case ActionMode::TRIANGLE:
                if (state.grid.matrix[gx][gy].isOccupied) break;
                state.grid.MakeCustomTriangle(gx, gy, state.triangleMode);
                break;
            default:
                break;
        }
    }

    // check one-time button press actions
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        switch (state.actionMode) {
            case ActionMode::BUCKET:
                state.grid.BucketFill(gx, gy);
                break;
            case ActionMode::MOVE: // TODO: Implement move
                state.grid.MoveFrom(gx, gy);
                break;
            case ActionMode::START_POINT:
                state.grid.SetStartPoint(gx, gy);
                break;
            case ActionMode::END_POINT:
                state.grid.SetEndPoint(gx, gy);
                break;
            default:
                break;
        }
    }

    if (IsKeyPressed(KEY_TAB)) state.debugMenu.active = !state.debugMenu.active;
}



//TODO: move mode 
//TODO: make connected tiles into one bigger
//TODO: load prexisting editor
//TODO: add info label

int main(void)
{
    InitWindow(EDITOR_SCREEN_WIDTH, EDITOR_SCREEN_HEIGHT, "Level Editor");
    SetWindowPosition(300, 100);
    SetTargetFPS(60);              

    printf("GRID: %dx%d\n", GRID_WIDTH, GRID_HEIGHT);

    while (!WindowShouldClose())   
    {
        HandleInput();

        BeginDrawing();
            ClearBackground(RAYWHITE);
            state.grid.Draw();
            state.grid.ShowSelectedCell();
            state.debugMenu.Draw();
            state.infoScreen.Draw(state.actionMode, state.triangleMode);

        EndDrawing();

    }

    CloseWindow();

    return 0;
}
