#include "player.h"
#include "game.h"

Player::Player(float x, float y, float w, float h, Color c) {
    position = { x, y };
    width = w; height = h;
    rect = { position.x, position.y, width, height };
    color = c;
}

void Player::HandleInput(float dt) {
    // Horizontal
    float dir = 0.0f;
    if (IsKeyDown(KEY_D)) dir += 1.0f;
    if (IsKeyDown(KEY_A)) dir -= 1.0f;
    velocity.x = dir * MOVE_SPEED;

    // Jump input handling with buffer
    if (IsKeyPressed(KEY_SPACE)) {
        jumpBufferTimer = JUMP_BUFFER_TIME;
    }

    // Variable jump height: if releasing jump while rising, cut velocity
    if (IsKeyReleased(KEY_SPACE) && velocity.y < 0.0f) {
        velocity.y *= JUMP_CUT_MULT;
    }

    // Timers tick down
    coyoteTimer      = std::max(0.0f, coyoteTimer - dt);
    jumpBufferTimer  = std::max(0.0f, jumpBufferTimer - dt);

    // Try to consume buffered jump when allowed
    if (jumpBufferTimer > 0.0f && (onGround || coyoteTimer > 0.0f)) {
        Jump();
        jumpBufferTimer = 0.0f;
    }
}

void Player::Jump() {
    velocity.y = JUMP_VELOCITY;
    onGround = false;
    coyoteTimer = 0.0f;
}

void LoadNextLevel(GameState& gameState){
    printf("Congratulations! You've completed the level!\n");
    gameState.levelIndex++;
    gameState.currLevelFilename = "exported_map_" + std::to_string(gameState.levelIndex) + ".txt";
    printf("Loading next level: %s\n", gameState.currLevelFilename.c_str());
    gameState.map.LoadMap(gameState.currLevelFilename.c_str());
    gameState.player.position = gameState.map.grid.startingPoint;
    gameState.keyGoalSprite.position = gameState.map.grid.endingPoint;

}

void Player::CheckWin(GameState& gameState)
{
    if (CheckCollisionRecs(rect, {gameState.map.grid.endingPoint.x, gameState.map.grid.endingPoint.y, (float)gameState.map.TILE_WIDTH, (float)gameState.map.TILE_HEIGHT})) {
        // Player reached end point load next level
        LoadNextLevel(gameState);       
    }
}

inline bool PointInRectInclusive(Vector2 p, const Rectangle& r) {
    return (p.x >= r.x) && (p.x <= r.x + r.width) &&
           (p.y >= r.y) && (p.y <= r.y + r.height);
}

void Player::CheckTriangleCollisions(GameState& gameState) {
    
    for (MyTriangle tri : gameState.map.grid.triangles){
        for (Vector2 vert : tri.vertices){
            if (PointInRectInclusive(vert, rect)) {
                gameState.map.ReloadMap(gameState);
                gameState.currentLives--;
                return;
            }
        }
    }
}

void Player::CheckOutOfMap(GameState& gameState){
    if (position.y > gameState.map.MAP_HEIGHT) {
        gameState.map.ReloadMap(gameState);
        gameState.currentLives--;
        return;
    }
}

void Player::CheckWorldDeath(GameState& gameState) {
    CheckTriangleCollisions(gameState);
    CheckOutOfMap(gameState);
}

    // Move and collide with world
void Player::Update(float dt, GameState& gameState) {
    HandleInput(dt);

    printf("lives : %d\n", gameState.currentLives);

    CheckWin(gameState);
    CheckWorldDeath(gameState);

    // Gravity
    velocity.y += GRAVITY * dt;

    // --- X axis move & collide ---
    position.x += velocity.x * dt;
    SyncRect();
    ResolveCollisionsX(gameState.map.tiles);

    // --- Y axis move & collide ---
    position.y += velocity.y * dt;
    SyncRect();
    
    bool wasOnGround = onGround;
    onGround = false;
    ResolveCollisionsY(gameState.map.tiles); // will set onGround and zero vy if landing

    ClampToScreenHorizontal(gameState.map.MAP_WIDTH);

    // Start coyote time when just left the ground
    if (wasOnGround && !onGround) {
        coyoteTimer = COYOTE_TIME;
    }
}

void Player::Draw() const { DrawRectangleRec(rect, color); }

void Player::SyncRect() { rect = { position.x, position.y, width, height }; }

void Player::ClampToScreenHorizontal(int world_width) {
    if (position.x < 0) position.x = 0;
    if (position.x + width > world_width) position.x = world_width - width;
    // if (position.y < 0) position.y = 0;
    // if (position.y + height > world_height) position.y = world_height - height;
    SyncRect();
}

void Player::ResolveCollisionsX(const std::vector<Tile>& world) {
    for (const auto& p : world) {
        if (CheckCollisionRecs(rect, p.rect)) {
            // compute penetration on X
            float playerRight = rect.x + rect.width;
            float playerLeft  = rect.x;
            float platRight   = p.rect.x + p.rect.width;
            float platLeft    = p.rect.x;

            float overlapLeft  = playerRight - platLeft;   // if >0, overlapped from left
            float overlapRight = platRight - playerLeft;   // if >0, overlapped from right

            // push out by the smaller magnitude
            if (overlapLeft < overlapRight) {
                // collided from left side: push player left
                rect.x -= overlapLeft;
            } else {
                // collided from right side: push player right
                rect.x += overlapRight;
            }
            position.x = rect.x;
        }
    }
}

void Player::ResolveCollisionsY(const std::vector<Tile>& world) {
    for (const auto& p : world) {
        if (CheckCollisionRecs(rect, p.rect)) {
            float playerBottom = rect.y + rect.height;
            float playerTop    = rect.y;
            float platBottom   = p.rect.y + p.rect.height;
            float platTop      = p.rect.y;

            float overlapTop    = playerBottom - platTop;   // landed on top
            float overlapBottom = platBottom - playerTop;   // hit head

            if (overlapTop < overlapBottom) {
                // Landed on platform
                rect.y -= overlapTop;
                position.y = rect.y;
                velocity.y = 0.0f;
                onGround = true;
            } else {
                // Hit underside of platform
                rect.y += overlapBottom;
                position.y = rect.y;
                if (velocity.y < 0.0f) velocity.y = 0.0f;
            }
        }
    }
}

// Sprite code moved to sprite.cpp
void PlayerSprite::SetSprite(Texture2D tex, int cols_, int rows_) {
    sprite = tex;    // copy is fine (Texture2D is small handle)
    cols = cols_;
    rows = rows_;
    frameWidth = sprite.width  / cols;
    frameHeight = sprite.height / rows;
    currentFrame = 0;
    animTimer = 0.0f;
}

Anim& PlayerSprite::CurrentAnim() {
    return (state == AnimState::WALK) ? walk : idle;
}

void PlayerSprite::UpdateAnimation(float dt, Player& player) {
    state = (std::abs(player.velocity.x) > 2.0f) ? AnimState::WALK : AnimState::IDLE;

    // face
    if (player.velocity.x > 1.0f) facingRight = true;
    if (player.velocity.x < -1.0f) facingRight = false;

    Anim& anim = CurrentAnim();
    animTimer += dt;
    const float spf = 1.0f / animFPS;   // seconds per frame
    while (animTimer >= spf) {
        animTimer -= spf;
        currentFrame = (currentFrame + 1) % anim.frames;
    }
}

void PlayerSprite::Draw(Player& player) const {
    if (sprite.id == 0) {                 // fallback if no texture yet
        DrawRectangleRec(player.rect, player.color);
        return;
    }

    // Determine which row to use based on state
    int row = (std::abs(player.velocity.x) > 2.0f) ? walk.row : idle.row;
    
    // Get the rectangle to draw from the sprite sheet
    Rectangle src{
        (float)(currentFrame * frameWidth),
        (float)(row   * frameHeight),
        (float)frameWidth,
        (float)frameHeight
    };
    
    // Source frame (flip by setting width negative when facing left)
    if (!facingRight) {
        src.x += src.width;   
        src.width = -src.width; 
    }

    // draw rectangle 
    Rectangle dst = { player.position.x, player.position.y, frameWidth * scale, frameHeight * scale };
    dst.x = player.rect.x - (dst.width - player.rect.width) * 0.5f;
    dst.y = player.rect.y - (dst.height - player.rect.height) * 0.47f;

    Vector2 origin = { 0, 0 };
    DrawTexturePro(sprite, src, dst, origin, 0.0f, WHITE);
}