// cell.cpp
#include "cell.h"

Cell::Cell(Vector2 pos, Color filledCol, Color emptyCol, Color filledSelCol, Color emptySelCol, Color startingPointColor)
{
    position = pos;
    filledColor = filledCol;
    emptyColor = emptyCol;
    filledSelectionColor = filledSelCol;
    emptySelectionColor = emptySelCol;
    startingPointColor = startingPointColor;
    isOccupied = false;
}

Cell::Cell(int gx, int gy, int cell_size, bool occupied)
{
    position = { (float)(gx * cell_size), (float)(gy * cell_size) };
    isOccupied = occupied;
    cellSize = cell_size;
}

void Cell::Draw() const {
    const Rectangle r = Rect();
    DrawRectangleRec(r, isOccupied ? filledColor : emptyColor);
    DrawRectangleLinesEx(r, 1.0f, Fade(BLACK, 0.15f));
}

void Cell::Select() const {
    const Rectangle r = Rect();
    Color overlay = isOccupied ? filledSelectionColor : emptySelectionColor;
    DrawRectangleLinesEx(r, 2.0f, overlay);
}
