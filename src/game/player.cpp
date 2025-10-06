#include "player.h"
#include "game.h"

Player::Player(float x, float y, float w, float h, Color c) {
    position = { x, y };
    width = w; height = h;
    rect = { position.x, position.y, width, height };
    color = c;
}

float GetRandomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / RAND_MAX * (max - min);
}

void Player::HandleInput(GameState& gameState) {
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
    coyoteTimer      = std::max(0.0f, coyoteTimer - gameState.dt);
    jumpBufferTimer  = std::max(0.0f, jumpBufferTimer - gameState.dt);

    // Try to consume buffered jump when allowed
    if (jumpBufferTimer > 0.0f && ((onGround || coyoteTimer > 0.0f) || ((onPlatform || coyoteTimer > 0.0f)))) {
        Jump();
        SetSoundPitch(gameState.soundManager.jump, GetRandomFloat(0.7f, 1.1f));
        PlaySound(gameState.soundManager.jump);
        jumpBufferTimer = 0.0f;
    }
}

void Player::Jump() {
    velocity.y = JUMP_VELOCITY;
    onGround = false;
    onPlatform = false;
    ridingPlatform = -1;          
    coyoteTimer = 0.0f;
}

void LoadNextLevel(GameState& gameState){
    printf("Congratulations! You've completed the level!\n");
    gameState.currLevelFilename = "exported_map_" + std::to_string(++gameState.levelIndex) + ".txt";
    gameState.map.LoadMap(gameState.currLevelFilename.c_str());
    gameState.player.position = gameState.map.grid.startingPoint;
    gameState.keyGoalSprite.position = gameState.map.grid.endingPoint;
    gameState.textureHandler.SetupTextures(gameState);  
}

void Player::CheckWin(GameState& gameState)
{
    if (CheckCollisionRecs(rect, {gameState.map.grid.endingPoint.x, gameState.map.grid.endingPoint.y, (float)gameState.map.TILE_WIDTH, (float)gameState.map.TILE_HEIGHT})) {
        // Player reached end point load next level
        LoadNextLevel(gameState);       
        PlaySound(gameState.soundManager.victory);
    }
}

inline bool PointInRectInclusive(Vector2 p, const Rectangle& r) {
    return (p.x >= r.x) && (p.x <= r.x + r.width) &&
           (p.y >= r.y) && (p.y <= r.y + r.height);
}

inline bool RectCollidingInclusive(const Rectangle& a, const Rectangle& b) {
    return !((a.x + a.width  < b.x) ||
             (b.x + b.width  < a.x) ||
             (a.y + a.height < b.y) ||
             (b.y + b.height < a.y));
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

int Player::GetCollidingPlatformIndex(GameState& gameState) {
    for (int i = 0; i < (int)gameState.map.grid.platforms.size(); ++i) {
        auto& plat = gameState.map.grid.platforms[i];
        if (CheckCollisionRecs(rect, plat.box)) return i;
    }
    return -1;
}
// Move and collide with world
void Player::Update(GameState& gameState) {
    HandleInput(gameState);

    
    // Gravity
    velocity.y += GRAVITY * gameState.dt;
    
    // save previous position
    previousPosition = position;
    
    // --- X axis move & collide ---
    position.x += velocity.x * gameState.dt;
    SyncRect();
    
    ResolveCollisionsX(gameState);
    
    // --- Y axis move & collide ---
    position.y += velocity.y * gameState.dt;
    SyncRect();
    
    bool wasOnGround = onGround; onGround = false;
    bool wasOnPlatform = onPlatform; onPlatform = false;    
    ResolveCollisionsY(gameState);
    // printf("standing on platform %d\n", );

    
    CarryWithPlatform(gameState);

    ClampToScreenHorizontal(gameState.map.MAP_WIDTH);

    bool wasSupported = wasOnGround || wasOnPlatform;
    bool supported    = onGround    || onPlatform;
    if (wasSupported && !supported) {
        coyoteTimer = COYOTE_TIME;
    }

    CheckWin(gameState);
    CheckWorldDeath(gameState);
}

void Player::DrawHitBox() const { DrawRectangleRec(rect, color); DrawRectangleLinesEx(rect, 1.0f, BLACK);}

void Player::SyncRect() { rect = { position.x, position.y, width, height }; }

void Player::ClampToScreenHorizontal(int world_width) {
    if (position.x < 0) position.x = 0;
    if (position.x + width > world_width) position.x = world_width - width;
    SyncRect();
}

void Player::ClampToScreenVertical(int world_height) {
    if (position.y < 0) position.y = 0;
    if (position.y + height > world_height) position.y = world_height - height;
    SyncRect();
}

void Player::CheckTilesXCollision(std::vector<Tile>& tiles){
    for (const auto& p : tiles) {
        if (CheckCollisionRecs(rect, p.rect)) {
            // compute penetration on X
            float playerRight = rect.x + rect.width;
            float playerLeft  = rect.x;
            float platRight   = p.rect.x + p.rect.width;
            float platLeft    = p.rect.x;

            float overlapLeft  = playerRight - platLeft;   // if >0, overlapped from left
            float overlapRight = platRight - playerLeft;   // if >0, overlapped from right

            if (overlapLeft < overlapRight) {
                rect.x -= overlapLeft;
            } else {
                rect.x += overlapRight;
            }
            position.x = rect.x;
        }
    }
}

void Player::CheckPlatformXCollision(std::vector<MovingPlatform>& plats){
    for (const auto& p : plats) {
        if (CheckCollisionRecs(rect, p.box)) {
            // compute penetration on X
            float playerRight = rect.x + rect.width;
            float playerLeft  = rect.x;
            float platRight   = p.box.x + p.box.width;
            float platLeft    = p.box.x;

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

void Player::ResolveCollisionsX(GameState& gameState) {
    CheckTilesXCollision(gameState.map.tiles);
    CheckPlatformXCollision(gameState.map.grid.platforms);
}

void Player::CheckTilesYCollision(std::vector<Tile>& tiles){
    for (const auto& p : tiles) {
        if (!CheckCollisionRecs(rect, p.rect)) continue;

        float playerBottom = rect.y + rect.height;
        float playerTop    = rect.y;
        float platBottom   = p.rect.y + p.rect.height;
        float platTop      = p.rect.y;

        float overlapTop    = playerBottom - platTop; // landing
        float overlapBottom = platBottom - playerTop; // head bonk

        if (overlapTop < overlapBottom) {
            rect.y = platTop - rect.height;
            position.y = rect.y;
            velocity.y = 0.0f;
            onGround = true;
        } else {
            rect.y = platBottom;
            position.y = rect.y;
            if (velocity.y < 0.0f) velocity.y = 0.0f;
        }
    }
}

void Player::CheckPlatformYCollision(std::vector<MovingPlatform>& plats){
    for (int i = 0; i < (int) plats.size(); ++i) {
        auto& plat = plats[i];
        if (!CheckCollisionRecs(rect, plat.box)) continue;

        const float prevBottom = previousPosition.y + rect.height;
        const float prevTop    = previousPosition.y;
        const float platTop    = plat.box.y;
        const float platBottom = plat.box.y + plat.box.height;

        // Landing from above
        if (prevBottom <= platTop && velocity.y > 0.0f) {
            rect.y = platTop - rect.height;
            position.y = rect.y;
            velocity.y = 0.0f;
            onPlatform = true;
            ridingPlatform = i;
            continue;
        }

        // Bonk from below
        if (prevTop >= platBottom && velocity.y < 0.0f) {
            rect.y = platBottom;
            position.y = rect.y;
            if (velocity.y < 0.0f) velocity.y = 0.0f;
            // not riding when under it
            if (ridingPlatform == i) ridingPlatform = -1;
            continue;
        }
    }
}

void Player::ResolveCollisionsY(GameState& gameState) {
    // world tiles
    CheckTilesYCollision(gameState.map.tiles);
    // platform check 
    CheckPlatformYCollision(gameState.map.grid.platforms);
    
}

void Player::CarryWithPlatform(GameState& gameState) {
    // printf("riding plat : %d\n", ridingPlatform);
    if (ridingPlatform < 0) return;

    // get platform
    auto& plat = gameState.map.grid.platforms[ridingPlatform];

    // check if player is still touching the platform
    bool stillTouching = RectCollidingInclusive(rect, plat.box);
    if (!stillTouching) { ridingPlatform = -1; printf("not still touching\n"); return; }

    // move the player by the platform's delta
    Vector2 delta = { plat.position.x - plat.lastPosition.x, plat.position.y - plat.lastPosition.y };
    position.x += delta.x;
    position.y += delta.y;
    printf("delta y : %f\n", delta.y);
    SyncRect();
}

void PlayerSprite::SetSprite(Texture2D tex, int cols_, int rows_) {
    texture = tex;    // copy is fine (Texture2D is small handle)
    cols = cols_;
    rows = rows_;
    frameWidth = texture.width  / cols;
    frameHeight = texture.height / rows;
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
    // printf("current anim : %s\n", (anim.frames == 4) ? "idle" : "walk");
    animTimer += dt;
    const float spf = 1.0f / animFPS;   // seconds per frame
    while (animTimer >= spf) {
        animTimer -= spf;
        currentFrame = (currentFrame + 1) % anim.frames;
    }
}

void PlayerSprite::Draw(Player& player) const {
    if (texture.id == 0) {                 // fallback if no texture yet
        DrawRectangleRec(player.rect, player.color);
        return;
    }

    // Determine which row to use based on state
    int row = (std::abs(player.velocity.x) > 2.0f) ? walk.row : idle.row;
    
    // Get the rectangle to draw from the texture sheet
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
    DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);
}