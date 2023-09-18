#pragma once
#include "Collider.h"

class Bullet : public Collider {
  public:
    enum MovementType { REGULAR, SINLIKE };
    Vector2 velocity;
    bool isPlayer;
    MovementType moveType;
    Bullet(
        Vector2 position,
        Texture texture,
        Vector2 velocity,
        bool isPlayer,
        MovementType moveType) :
        Collider(position, texture),
        isPlayer(isPlayer), moveType(moveType), velocity(velocity) {
    }
    void Think() override {
        Collider::Think();
        if (isOutsideScreen()) {
            Scene.remove(this);
            return;
        }
        position.x += velocity.x * GetFrameTime();
        float coef =
            moveType == REGULAR ? 1 : sinf(position.x / 180.0f * 3.14f);
        position.y += 1 * velocity.y * GetFrameTime();
    }
    void Collide(Collider *other) override;

    ~Bullet() {
    }
};