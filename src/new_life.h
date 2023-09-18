#include "raylib.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "BaseEntity.h"
#include "Bullet.h"
#include "Collider.h"
#include "Scene.h"
#include "Sprite.h"
#include "Stats.h"
#include "Timer.h"

class Shooter : public Collider {
  public:
    std::vector<Vector2> bulletVelocities;
    Bullet::MovementType bulletMoveType;
    bool isPlayer;
    Shooter(
        Vector2 position,
        Texture texture,
        std::vector<Vector2> bulletVelocities,
        Bullet::MovementType bulletMoveType,
        bool isPlayer,
        float spawnDelay) :
        Collider(position, texture),
        bulletVelocities(bulletVelocities), bulletMoveType(bulletMoveType),
        isPlayer(isPlayer), spawnDelay(spawnDelay) {
        shootTimer = new Timer(spawnDelay);
        Scene.add(shootTimer);
    }

    void Think() override {
        Collider::Think();
        if (shootTimer->IsActive()) {
            for (auto &velocity : bulletVelocities) {
                Scene.add(new Bullet(
                    position,
                    LoadTexture(ASSETS_PATH "space_breaker_asset/Weapons/Small/"
                                            "Cannon/turret_01_bullet_01.png"),
                    velocity,
                    isPlayer,
                    bulletMoveType));
            }
        }
    }

  private:
    float spawnDelay;
    Timer *shootTimer;
};

class ShootingShip : public Shooter, public StatsComponent {
  public:
    ShootingShip(
        Vector2 position,
        Texture texture,
        std::vector<Vector2> bulletVelocities,
        Bullet::MovementType moveType,
        bool isPlayer,
        float spawnDelay,
        int hp,
        float speed) :
        Shooter(
            position,
            texture,
            bulletVelocities,
            moveType,
            isPlayer,
            spawnDelay),
        StatsComponent(hp, speed, isPlayer) {
    }
    void Think() override {
        Shooter::Think();
    }
};

struct Player : public ShootingShip {
    Player(
        Vector2 position,
        Texture texture,
        std::vector<Vector2> bulletVelocities,
        Bullet::MovementType moveType,
        float spawnDelay,
        int hp,
        float speed) :
        ShootingShip(
            position,
            texture,
            bulletVelocities,
            moveType,
            true,
            spawnDelay,
            hp,
            speed) {
    }

    void Think() override {
        Shooter::Think();
        if (IsKeyDown(KEY_UP))
            position.y -= speed * GetFrameTime();
        if (IsKeyDown(KEY_DOWN))
            position.y += speed * GetFrameTime();
        if (IsKeyDown(KEY_LEFT))
            position.x -= speed * GetFrameTime();
        if (IsKeyDown(KEY_RIGHT))
            position.x += speed * GetFrameTime();
    }
};

void Bullet::Collide(Collider *other) {
    auto stats = dynamic_cast<StatsComponent *>(other);
    if (stats != nullptr && stats->isPlayer != isPlayer) {
        stats->hp--;
        Scene.remove(this);
    }
}

struct AnimatedSprite : BaseEntity {
    Vector2 position;
    float rotation;
    Texture texture;
    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 8;
    int maxFrames;
    Color color = WHITE;
    AnimatedSprite(
        Vector2 position, float rotation, Texture texture, int maxFrames) :
        position(position),
        rotation(rotation), texture(texture), maxFrames(maxFrames) {
    }

    void Think() override {
        framesCounter++;
        Rectangle frameRec = {
            0.0f,
            0.0f,
            (float)texture.width / maxFrames,
            (float)texture.height};
        if (framesCounter >= (60 / framesSpeed)) {
            framesCounter = 0;
            currentFrame++;
            if (currentFrame > maxFrames - 1)
                currentFrame = 0;
        }
        frameRec.x = (float)currentFrame * (float)texture.width / maxFrames;
        DrawTextureRec(texture, frameRec, position, color);
    }
};