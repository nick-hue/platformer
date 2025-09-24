#include "sound_manager.h"

void SoundManager::LoadSounds() {
    background = LoadSound("assets/resources/background_sound.wav");         
    jump = LoadSound("assets/resources/jump.wav");         
    victory = LoadSound("assets/resources/victory.wav");   

    SetSoundVolume(jump, 0.5f); 
}

void SoundManager::UnloadSounds(){
    UnloadSound(background);
    UnloadSound(victory);   
    UnloadSound(jump);  
}