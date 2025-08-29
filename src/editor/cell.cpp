// cell.cpp
#include "cell.h"

Cell::Cell(Vector2 pos, Color filledCol, Color emptyCol, Color filledSelCol, Color emptySelCol)
: position{pos},
  filledColor{filledCol},
  emptyColor{emptyCol},
  filledSelectionColor{filledSelCol},
  emptySelectionColor{emptySelCol},
  isOccupied{false}
{}

void Cell::Draw() const {
    const Rectangle r = Rect();
    DrawRectangleRec(r, isOccupied ? filledColor : emptyColor);
    // Grid lines for readability
    DrawRectangleLinesEx(r, 1.0f, Fade(BLACK, 0.15f));
}

void Cell::Select() const {
    const Rectangle r = Rect();
    Color overlay = isOccupied ? filledSelectionColor : emptySelectionColor;
    DrawRectangleLinesEx(r, 2.0f, overlay);
}
