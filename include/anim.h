#pragma once 

enum class AnimState {
    IDLE,
    WALK,
    UNKNOWN
};
//TODO: 
//FIXME:

struct Anim {
    int row;        // which row in the sheet
    int startCol;   // first column index of this anim
    int frames;     // how many frames this anim has
    float fps;      // playback speed
};