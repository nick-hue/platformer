#pragma once
#include "raylib.h"

class GameState;

class SoundManager {
public:
    Music background;
    Sound jump;
    Sound victory;
    Sound spikeBreak;

    SoundManager() = default;
    void LoadSounds();
    void UnloadSounds();
};