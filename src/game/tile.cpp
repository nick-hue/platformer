#include "tile.h"
#include "item_sprite.h"   

Tile::Tile(float x, float y, float w, float h, Color c, GroundTileType t)
    : position{x, y}, width{w}, height{h}, rect{x, y, w, h}, color{c}, type{t},
      gridPos{ static_cast<int>(x / w), static_cast<int>(y / h) } {}

void Tile::Draw()  {
    if (sprite) sprite->Draw(spriteSheetLocation);    
    else DrawRectangleRec(rect, color);
}