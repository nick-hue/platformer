#pragma once
#include "raylib.h"

class GameState;

class SoundManager {
public:
    Sound background;
    Sound jump;
    Sound victory;

    SoundManager() = default;
    void LoadSounds();
    void UnloadSounds();
};