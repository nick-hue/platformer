// level_editor_defs.h
#pragma once
#include <string>

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
    MOVE,
    START_POINT,
    END_POINT,
    TRIANGLE
};

enum class TriangleMode {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

inline const char* ToString(ActionMode m) {
    switch (m) {
        case ActionMode::INSERT: return "INSERT";
        case ActionMode::REMOVE: return "REMOVE";
        case ActionMode::BUCKET: return "BUCKET";
        case ActionMode::MOVE: return "MOVE";
        case ActionMode::START_POINT: return "START_POINT";
        case ActionMode::END_POINT: return "END_POINT";
        case ActionMode::TRIANGLE: return "TRIANGLE";
        default:                 return "Unknown";
    }
}

inline const char* ToDrawString(ActionMode m) {
    switch (m) {
        case ActionMode::INSERT: return "Action Mode : INSERT";
        case ActionMode::REMOVE: return "Action Mode : REMOVE";
        case ActionMode::BUCKET: return "Action Mode : BUCKET";
        case ActionMode::MOVE: return "Action Mode : MOVE";
        case ActionMode::START_POINT: return "Action Mode : START_POINT";
        case ActionMode::END_POINT: return "Action Mode : END_POINT";
        case ActionMode::TRIANGLE: return "Action Mode : TRIANGLE";
        default:                 return "Action Mode : Unknown";
        
    }
}

inline const char* ToString(TriangleMode m) {
    switch (m) {
        case TriangleMode::UP: return "UP";
        case TriangleMode::DOWN: return "DOWN";
        case TriangleMode::RIGHT: return "RIGHT";
        case TriangleMode::LEFT: return "LEFT";
        default:                 return "Unknown";
    }
}

inline const char* ToDrawString(TriangleMode m) {
    switch (m) {
        case TriangleMode::UP: return "Triangle Mode : UP";
        case TriangleMode::DOWN: return "Triangle Mode : DOWN";
        case TriangleMode::LEFT: return "Triangle Mode : LEFT";
        case TriangleMode::RIGHT: return "Triangle Mode : RIGHT";
        case TriangleMode::NONE: return "Triangle Mode : NONE";
        default:                 return "Triangle Mode : Unknown";
        
    }
}

void ExportMap(const char *filename);