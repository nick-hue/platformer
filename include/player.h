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

class GameState;

enum class AnimState {
    IDLE,
    WALK,
    UNKNOWN
};

struct Anim {
    int row;        // which row in the sheet
    int startCol;   // first column index of this anim
    int frames;     // how many frames this anim has
    float fps;      // playback speed
};

class Player {
public:
    Vector2 position{0,0};
    Vector2 previousPosition{0, 0};
    Vector2 velocity{0,0};
    float width{30}, height{40};
    Rectangle rect{position.x, position.y, width, height};
    Color color{MAROON};

    bool onGround{false};
    float coyoteTimer{0.0f};
    float jumpBufferTimer{0.0f};

    Player() = default;
    Player(float x, float y, float w, float h, Color c);

    void HandleInput(float dt);
    void Jump();

    // Move and collide with world
    void Update(float dt, GameState& gameState);

    void CheckWin(GameState& gameState);

    void Draw() const;
    void SyncRect();
    void ClampToScreenHorizontal(int world_width);

private:
    void ResolveCollisionsX(const std::vector<Tile>& world);
    void ResolveCollisionsY(const std::vector<Tile>& world);
    void CheckWorldDeath(GameState& gameState);
    void CheckTriangleCollisions(GameState& gameState);
    void CheckOutOfMap(GameState& gameState);
};


class PlayerSprite {
public:
    Texture2D sprite{};
    int cols{9};
    int rows{7};
    int frameWidth{sprite.width/cols};  // frame width
    int frameHeight{sprite.height/rows}; // frame height
    float animFPS{12.0f};
    float scale = 2.25f;
    
    int currentFrame{0};   
    float animTimer{0.0f};
    bool facingRight{true};

    Anim idle{ 0, 0, 0, 0.0f };  
    Anim walk{ 0, 0, 0, 0.0f }; 
    AnimState state{AnimState::IDLE};

    PlayerSprite() = default;
    void SetSprite(Texture2D tex, int cols_, int rows_);
    void UpdateAnimation(float dt, Player& player);

    Anim& CurrentAnim();

    void Draw(Player& player) const;
};
