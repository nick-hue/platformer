#include "sound_manager.h"

void SoundManager::LoadSounds() {
    background = LoadMusicStream("assets/resources/background_sound.wav");
    jump = LoadSound("assets/resources/jump.wav");         
    victory = LoadSound("assets/resources/victory.wav");   
    spike_break = LoadSound("assets/resources/spike_break.wav");

    SetMusicVolume(background, 0.1f);
    SetSoundVolume(jump, 0.25f); 
}

void SoundManager::UnloadSounds(){
    UnloadMusicStream(background);
    UnloadSound(victory);   
    UnloadSound(jump);  
    UnloadSound(spike_break);
}