#include "game.h"


// ---------- Objects ----------
struct Object {
    Vector2 position;
    float width;
    float height;
    Rectangle rect;
    Color color;

    Object(float x, float y, float w, float h, Color c) {
        position = { x, y };
        width = w;
        height = h;
        rect = { position.x, position.y, width, height };
        color = c;
    }

    void Sync() { rect = { position.x, position.y, width, height }; }

    void Draw() const { DrawRectangleRec(rect, color); }
};

std::vector<Object> platforms;

// ---------- Player ----------
class Player {
public:
    Vector2 position{0,0};
    Vector2 velocity{0,0};
    float width{50}, height{50};
    Rectangle rect{};
    Color color{MAROON};

    bool onGround{false};
    float coyoteTimer{0.0f};
    float jumpBufferTimer{0.0f};

    Player(float x, float y, float w, float h, Color c) {
        position = { x, y };
        width = w; height = h;
        rect = { position.x, position.y, width, height };
        color = c;
    }

    void HandleInput(float dt) {
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

    void Jump() {
        velocity.y = JUMP_VELOCITY;
        onGround = false;
        coyoteTimer = 0.0f;
    }

    // Move and collide with world
    void Update(float dt, const std::vector<Object>& world) {
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

    void Draw() const { DrawRectangleRec(rect, color); }

    void SyncRect() { rect = { position.x, position.y, width, height }; }

private:
    // Separate axis collision: push out along the axis we moved
    void ResolveCollisionsX(const std::vector<Object>& world) {
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

    void ResolveCollisionsY(const std::vector<Object>& world) {
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
};

// ---------- Debug ----------
void ShowDebug(const Player& player) {
    DrawText("DEBUG INFO:", 10, 10, 20, BLACK);
    DrawText(TextFormat("Pos: (%.1f, %.1f)", player.position.x, player.position.y), 10, 40, 10, DARKGRAY);
    DrawText(TextFormat("Vel: (%.1f, %.1f)", player.velocity.x, player.velocity.y), 10, 60, 10, DARKGRAY);
}

// ---------- Main ----------
int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Platformer");
    SetWindowPosition(300, 200);
    SetTargetFPS(60);
    DrawFPS(10, 10);

    Player player((float)SCREEN_WIDTH/2.0f - 25.0f, (float)SCREEN_HEIGHT/2.0f, 50, 50, MAROON);

    // World geometry
    Object platform(100, 350, 600, 20, DARKGRAY);
    Object smallWall(400, 300, 25, 50, DARKGRAY);
    platforms.push_back(platform);
    platforms.push_back(smallWall);
    // for (auto& p : platforms) p.Sync();

    bool debug_show = true;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_TAB)) debug_show = !debug_show;

        float dt = GetFrameTime();

        player.Update(dt, platforms);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            for (const auto& p : platforms) p.Draw();
            player.Draw();
            if (debug_show) ShowDebug(player);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
