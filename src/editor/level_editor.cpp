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
        std::string exportedMapName{"exported_map.txt"};

        State() : actionMode(ActionMode::INSERT), infoScreen(actionMode, exportedMapName), grid() {}

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
    if (IsKeyPressed(KEY_E) && IsKeyDown(KEY_LEFT_CONTROL)) {
        printf("Exporting...\n");
        ExportMap(state.exportedMapName.c_str());
    }
    if (IsKeyPressed(KEY_S)) {
        state.actionMode = ActionMode::START_POINT;
    }
    if (IsKeyPressed(KEY_E)) {
        state.actionMode = ActionMode::END_POINT;
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
                state.grid.BucketFill(gx, gy);
                break;
            case ActionMode::MOVE:
                // TODO: Implement move
                state.grid.MoveFrom(gx, gy);
                break;
            case ActionMode::START_POINT:
                state.grid.SetStartPoint(gx, gy);
                break;
            case ActionMode::END_POINT:
                state.grid.SetEndPoint(gx, gy);
        }
    }

    if (IsKeyPressed(KEY_TAB)) state.debugMenu.active = !state.debugMenu.active;
}

void ExportMap(const char *filename){
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Failed to open file for writing: %s\n", filename);
        return;
    }

    if (state.grid.startingPoint.x == -1.0f && state.grid.startingPoint.y == -1.0f) {
        state.grid.SetStartPoint(0,0);
    }

    std::string header = std::to_string(GRID_WIDTH) + ", " + std::to_string(GRID_HEIGHT) 
                        + ", " + std::to_string(CELL_SIZE)
                        + ", " + std::to_string(int(state.grid.startingPoint.x)) + ", " + std::to_string(int(state.grid.startingPoint.y)) + 
                        + ", " + std::to_string(int(state.grid.endingPoint.x)) + ", " + std::to_string(int(state.grid.endingPoint.y)) + "\n";

    fputs(header.c_str(), file);

    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            fputc(state.grid.matrix[x][y].isOccupied ? '1' : '0', file);
            if (x < GRID_WIDTH - 1) fputc(',', file);
        }
        fputc('\n', file);
    }

    fclose(file);
    printf("Map exported to %s\n", filename);
}

//TODO: move mode 
//TODO: make connected tiles into one bigger
//TODO: load prexisting editor
//

int main(void)
{
    InitWindow(EDITOR_SCREEN_WIDTH, EDITOR_SCREEN_HEIGHT, "Level Editor");
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
