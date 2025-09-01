#pragma once
#include "raylib.h"
#include "tile.h"
#include <vector>
#include <algorithm> 

constexpr float GRAVITY          = 2000.0f;   // px/s^2
constexpr float JUMP_VELOCITY    = -700.0f;   // px/s
constexpr float JUMP_CUT_MULT    = 0.45f;     // jump cut when releasing early
constexpr float MOVE_SPEED       = 300.0f;    // px/s
constexpr float COYOTE_TIME      = 0.08f;     // seconds after leaving ground
constexpr float JUMP_BUFFER_TIME = 0.10f;     // seconds before landing

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

    Player() = default;
    Player(float x, float y, float w, float h, Color c);

    void HandleInput(float dt);
    void Jump();

    // Move and collide with world
    void Update(float dt, const std::vector<Tile>& world);

    void Draw() const;
    void SyncRect();

private:
    void ResolveCollisionsX(const std::vector<Tile>& world);
    void ResolveCollisionsY(const std::vector<Tile>& world);
};
