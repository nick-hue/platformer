#include "moving_platform.h"

void MovingPlatform::Draw() const {
    DrawRectangleRec(box, color);
    DrawRectangleLinesEx(box, 1.0f, color);
}