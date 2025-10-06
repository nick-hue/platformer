#include "moving_platform.h"
#include "game.h"

MovingPlatform::MovingPlatform(Vector2 start_pos, Vector2 movement, int plat_length, int tile_size, int plat_id){
    gridPos = start_pos;
    position = Vector2{start_pos.x * tileSize, start_pos.y * tileSize};
    lastPosition = position;
    length = plat_length;
    tileSize = tile_size;
    box = Rectangle{position.x, position.y, (float) length * tileSize, (float) tileSize};
    movementBounds = Vector4{position.x, position.x + movement.x * tileSize, position.y, position.y + movement.y * tileSize};
    id = plat_id;
    if (movementBounds.x == movementBounds.y)
        velocity.x = 0.0f;
    if (movementBounds.z == movementBounds.w)
        velocity.y = 0.0f;
}

void MovingPlatform::Draw() const {
    sprite.Draw(length);
    
    DrawRectangleRec(box, color);
    // DrawRectangleLinesEx(box, 1.0f, outlineColor);
}

static inline void GetMovementDirection(Vector2 pos, const Vector4& bounds, Vector2& dir){  
    if (pos.x < bounds.x) dir.x = 1.0f;
    if (pos.x > bounds.y) dir.x = -1.0f;

    if (pos.y < bounds.z) dir.y = 1.0f;
    if (pos.y > bounds.w) dir.y = -1.0f;
}

void MovingPlatform::Move(GameState& gameState){
    // printf("Moving...\n");
    
    GetMovementDirection(position, movementBounds, movementDirection);
    // printf("movement dir : %f-%f\n", movementDirection.x, movementDirection.y);

    lastPosition.x = position.x;
    lastPosition.y = position.y;
    position.x += velocity.x * movementDirection.x * gameState.dt;    
    position.y += velocity.y * movementDirection.y * gameState.dt;    
}

void MovingPlatform::Update(GameState& gameState){
    Move(gameState);
    SyncRect();
}

inline std::string ToString(const MovingPlatform& plat){
    std::ostringstream ss;
    ss << "MovingPlatform { "
    << "id=" << plat.id
    << ", pos=(" << plat.position.x << "," << plat.position.y << ")"
    << ", vel=(" << plat.velocity.x << "," << plat.velocity.y << ")"
    << ", dir=(" << plat.movementDirection.x << "," << plat.movementDirection.y << ")"
    << ", bounds=(minX" 
            << plat.movementBounds.x << ",maxX" 
            << plat.movementBounds.y << ",minY" 
            << plat.movementBounds.z << ",maxY" 
            << plat.movementBounds.w << ")"
    << " }";
    return ss.str();
}
    