#include "sound_manager.h"

void SoundManager::LoadSounds() {
    background = LoadMusicStream("assets/resources/background_sound.wav");
    jump = LoadSound("assets/resources/jump.wav");         
    victory = LoadSound("assets/resources/victory.wav");   
    spikeBreak = LoadSound("assets/resources/spike_break.wav");

    SetMusicVolume(background, musicVolume);
    SetSoundVolume(jump, soundEffectsVolume); 
    SetSoundVolume(victory, soundEffectsVolume); 
    SetSoundVolume(spikeBreak, soundEffectsVolume); 
}

void SoundManager::UnloadSounds(){
    UnloadMusicStream(background);
    UnloadSound(victory);   
    UnloadSound(jump);  
    UnloadSound(spikeBreak);
}

void SoundManager::EditVolume(Music music, float& oldMusicVolume, float editValue){
    if (oldMusicVolume + editValue < 0 || oldMusicVolume + editValue > 1.01f) return;
    printf("old music volume : %f\n", oldMusicVolume);
    oldMusicVolume += editValue;
    SetMusicVolume(music, oldMusicVolume);
    printf("new music volume : %f\n", oldMusicVolume);
}

void SoundManager::EditVolume(Sound sound, float& oldSoundVolume, float editValue){
    if (oldSoundVolume + editValue < 0 || oldSoundVolume + editValue > 1.01f) return;
    printf("old sound volume : %f\n", oldSoundVolume);
    oldSoundVolume += editValue;
    SetSoundVolume(sound, oldSoundVolume);
    printf("new sound volume : %f\n", oldSoundVolume);
}

void SoundManager::ToggleMute(){
    isMuted = !isMuted;
    SetMasterVolume(isMuted ? 0.0f : 1.0f);
}