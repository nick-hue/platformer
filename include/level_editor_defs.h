// level_editor_defs.h
#pragma once
#include <string>

// Keep this header *standalone*: no project headers here (no grid.h, cell.h, etc.)

// --- Window / grid config ---

// EDITOR DIMENSIONS
constexpr int EDITOR_WIDTH  = 1024;
constexpr int EDITOR_HEIGHT = 512;

// GUI DIMENSIONS
constexpr int GUI_WIDTH  = 256;
constexpr int GUI_HEIGHT = EDITOR_HEIGHT;

// WINDOW DIMENSIONS
constexpr int EDITOR_SCREEN_WIDTH  = EDITOR_WIDTH + GUI_WIDTH;
constexpr int EDITOR_SCREEN_HEIGHT  = EDITOR_HEIGHT;

constexpr int CELL_SIZE = 32;
constexpr int GRID_WIDTH  = EDITOR_WIDTH  / CELL_SIZE;
constexpr int GRID_HEIGHT = EDITOR_HEIGHT / CELL_SIZE;

// --- Editor state ---
enum class ActionMode {
    INSERT,
    REMOVE,
    BUCKET,
    MOVE
};

inline const char* ToString(ActionMode m) {
    switch (m) {
        case ActionMode::INSERT: return "INSERT";
        case ActionMode::REMOVE: return "REMOVE";
        case ActionMode::BUCKET: return "BUCKET";
        case ActionMode::MOVE: return "MOVE";
        default:                 return "Unknown";
    }
}

inline const char* ToDrawString(ActionMode m) {
    switch (m) {
        case ActionMode::INSERT: return "Action Mode : INSERT";
        case ActionMode::REMOVE: return "Action Mode : REMOVE";
        case ActionMode::BUCKET: return "Action Mode : BUCKET";
        case ActionMode::MOVE: return "Action Mode : MOVE";
        default:                 return "Action Mode : Unknown";
    }
}

void ExportMap(const char *filename);