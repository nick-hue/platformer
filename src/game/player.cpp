#include "player.h"

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

    // Move and collide with world
void Player::Update(float dt, const std::vector<Tile>& world) {
    HandleInput(dt);

    // Gravity
    velocity.y += GRAVITY * dt;

    // --- X axis move & collide ---
    position.x += velocity.x * dt;
    SyncRect();
    ResolveCollisionsX(world);

    // --- Y axis move & collide ---
    position.y += velocity.y * dt;
    SyncRect();

    bool wasOnGround = onGround;
    onGround = false;
    ResolveCollisionsY(world); // will set onGround and zero vy if landing

    // Start coyote time when just left the ground
    if (wasOnGround && !onGround) {
        coyoteTimer = COYOTE_TIME;
    }
}

void Player::Draw() const { DrawRectangleRec(rect, color); }

void Player::SyncRect() { rect = { position.x, position.y, width, height }; }

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