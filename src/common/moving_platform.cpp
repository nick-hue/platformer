#include "moving_platform.h"
#include "game.h"

MovingPlatform::MovingPlatform(Vector2 start_pos, Vector2 movement, int plat_length, int tile_size, int plat_id){
    gridPos = start_pos;
    position = Vector2{start_pos.x * tileSize, start_pos.y * tileSize};
    lastPosition = position;
    length = plat_length;
    
    
    tileSize = tile_size;
    box = Rectangle{position.x, position.y, (float) length * tileSize, (float) tileSize};
    
    printf("box width %f height %f\n", box.width, box.height);
    movementBounds = Vector4{position.x, position.x + movement.x * tileSize, position.y, position.y + movement.y * tileSize};
    id = plat_id;
    if (movementBounds.x == movementBounds.y)
        velocity.x = 0.0f;
    if (movementBounds.z == movementBounds.w)
        velocity.y = 0.0f;
}

void MovingPlatform::DrawOutline() const {
    DrawRectangleLinesEx(box, 2.0f, outlineColor);
}

void MovingPlatform::Draw() const {
    sprite.Draw(length);
    // printf("left %f-%f\n", sprite.left.position.x, sprite.left.position.y);
    // printf("mid %f-%f\n", sprite.mid.position.x, sprite.mid.position.y);
    // printf("right %f-%f\n", sprite.right.position.x, sprite.right.position.y);
    // printf("box %f-%f-%f-%f\n", box.x, box.y, box.width, box.height);
}

static inline void GetMovementDirection(Vector2 pos, const Vector4& bounds, Vector2& dir){  
    if (pos.x < bounds.x) dir.x = 1.0f;
    if (pos.x > bounds.y) dir.x = -1.0f;

    if (pos.y < bounds.z) dir.y = 1.0f;
    if (pos.y > bounds.w) dir.y = -1.0f;
}

void MovingPlatform::Move(GameState& gameState){
    
    GetMovementDirection(position, movementBounds, movementDirection);

    lastPosition.x = position.x;
    lastPosition.y = position.y;
    position.x += velocity.x * movementDirection.x * gameState.dt;    
    position.y += velocity.y * movementDirection.y * gameState.dt;    
}

void MovingPlatform::Update(GameState& gameState){
    Move(gameState);
    SyncRect();
    SyncAnimation();
}

inline std::string MovingPlatform::ToString(const MovingPlatform& plat){
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
    