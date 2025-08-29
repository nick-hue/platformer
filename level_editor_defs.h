// level_editor_defs.h
#pragma once
#include <string>

// Keep this header *standalone*: no project headers here (no grid.h, cell.h, etc.)

// --- Window / grid config ---
constexpr int SCREEN_WIDTH  = 1024;
constexpr int SCREEN_HEIGHT = 512;

constexpr int CELL_SIZE = 32;

constexpr int GRID_WIDTH  = SCREEN_WIDTH  / CELL_SIZE;
constexpr int GRID_HEIGHT = SCREEN_HEIGHT / CELL_SIZE;

// --- Editor state ---
enum class ActionMode {
    INSERT,
    REMOVE
};

inline const char* ToString(ActionMode m) {
    switch (m) {
        case ActionMode::INSERT: return "INSERT";
        case ActionMode::REMOVE: return "REMOVE";
        default:                 return "Unknown";
    }
}
