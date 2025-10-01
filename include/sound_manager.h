#pragma once
#include "raylib.h"
#include <cstdio>

class GameState;

class SoundManager {
public:
    Music background;
    Sound jump;
    Sound victory;
    Sound spikeBreak;

    float musicVolume{0.3f};
    float soundEffectsVolume{0.3f};

    bool isMuted{true};

    SoundManager() = default;
    void LoadSounds();
    void UnloadSounds();
    
    void EditVolume(Music music, float& oldMusicVolume, float editValue);
    void EditVolume(Sound sound, float& oldSoundVolume, float editValue);
    void ToggleMute();
};