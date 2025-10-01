#include "raylib.h"
#include "level_editor_defs.h"
#include "grid.h"
#include "cell.h"
#include "info_screen.h"
#include "raygui.h"
#include "game.h"

class State {
    public:
        Grid grid;
        DebugManager debugMenu;
        ActionMode actionMode{ActionMode::NONE};
        TriangleMode triangleMode{TriangleMode::NONE};
        std::string exportedMapName{"exported_map_1.txt"};
        std::string importedMapName{"imported_map_1.txt"};
        InfoScreen infoScreen;

    State()
        : grid(), debugMenu(), actionMode(ActionMode::NONE), triangleMode(TriangleMode::NONE), exportedMapName("exported_map_1.txt"), importedMapName("imported_map_1.txt"), infoScreen(actionMode, triangleMode, exportedMapName, importedMapName, grid) 
        {}

};
State state;

void HandleInput(){
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_E)) {
        printf("Exporting...\n");
        state.infoScreen.showExportMessageBox = true;
        state.actionMode = ActionMode::NONE;
        state.triangleMode = TriangleMode::NONE;
        // state.grid.ExportMap(state.exportedMapName.c_str());
    }

    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_I)) {
        printf("Importing...\n");
        state.infoScreen.showImportMessageBox = true;
        state.actionMode = ActionMode::NONE;
        state.triangleMode = TriangleMode::NONE;
        // state.grid.ImportMap(state.importedMapName.c_str());
    }

    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_C)) {
        printf("Clearing...\n");
        state.infoScreen.showClearGridMessageBox = true;
        state.actionMode = ActionMode::NONE;
        state.triangleMode = TriangleMode::NONE;
        // state.grid.ImportMap(state.importedMapName.c_str());
    }
    

    int pressedKey = GetKeyPressed();
    switch (pressedKey)
    {
    case KEY_I:
        state.actionMode = ActionMode::INSERT;
        state.triangleMode = TriangleMode::NONE;
        break;
    case KEY_R:
        state.actionMode = ActionMode::REMOVE;
        state.triangleMode = TriangleMode::NONE;
        break;
    case KEY_B:
        state.actionMode = ActionMode::BUCKET;
        state.triangleMode = TriangleMode::NONE;
        break;
    case KEY_M:
        state.actionMode = ActionMode::MOVE;
        state.triangleMode = TriangleMode::NONE;
        break;
    case KEY_S:
        state.actionMode = ActionMode::START_POINT;
        state.triangleMode = TriangleMode::NONE;
        break;
    case KEY_E:
        state.actionMode = ActionMode::END_POINT;
        state.triangleMode = TriangleMode::NONE;
        break;
    case KEY_LEFT:
        state.actionMode = ActionMode::TRIANGLE;
        state.triangleMode = TriangleMode::LEFT;
        break;
    case KEY_RIGHT:
        state.actionMode = ActionMode::TRIANGLE;
        state.triangleMode = TriangleMode::RIGHT;
        break;  
    case KEY_UP:
        state.actionMode = ActionMode::TRIANGLE;
        state.triangleMode = TriangleMode::UP;
        break;
    case KEY_DOWN:
        state.actionMode = ActionMode::TRIANGLE;
        state.triangleMode = TriangleMode::DOWN;
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

                // printf("remove index : %d\n", removeIndex);
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
//TODO: add info label
//TODO: drag n drop level file

int main(void)
{
    InitWindow(EDITOR_SCREEN_WIDTH, EDITOR_SCREEN_HEIGHT, "Level Editor");
    const char *monitor_name = GetMonitorName(0);
    GuiLoadStyleDefault();
    printf("Monitor Name: %s\n", monitor_name);
    SetWindowPosition(300, 100);
    SetTargetFPS(60);              

    printf("GRID: %dx%d\n", GRID_WIDTH, GRID_HEIGHT);

    while (!WindowShouldClose())   
    {
        HandleInput();

        BeginDrawing();
            ClearBackground(RAYWHITE);
            state.grid.DrawEditor();
            state.grid.ShowSelectedCell();
            state.debugMenu.Draw();
            state.infoScreen.Draw(state.actionMode, state.triangleMode);
        EndDrawing();

    }

    CloseWindow();

    return 0;
}
