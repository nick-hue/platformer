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
        ExportMap(state.exportedMapName.c_str());
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

    Vector2 mouse_pos = GetMousePosition();
    int gx = (int)mouse_pos.x / CELL_SIZE;
    int gy = (int)mouse_pos.y / CELL_SIZE;

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
            case ActionMode::MOVE:
                // TODO: Implement move
                state.grid.MoveFrom(gx, gy);
                break;
            case ActionMode::START_POINT:
                state.grid.SetStartPoint(gx, gy);
                break;
            case ActionMode::END_POINT:
                state.grid.SetEndPoint(gx, gy);
                break;
            case ActionMode::TRIANGLE:
                printf("%s\n", ToDrawString(state.actionMode));
                printf("%s\n", ToString(state.triangleMode));
                state.grid.MakeCustomTriangle(gx, gy, state.triangleMode);
                break;
            default:
                break;
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
//TODO: add spikes
//TODO: add info label
//TODO: make remove remove spikes
//TODO: spikes not be able to fill occupied spots
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
