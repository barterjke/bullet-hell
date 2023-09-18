#pragma once

#include "raylib.h"

#include "BaseEntity.h"
#include "Scene.h"
#include "Sprite.h"

class Collider : public Sprite {
  public:
    BoundingBox collisionBox;
    Collider(Vector2 position, Texture texture, BoundingBox collisionBox) :
        Sprite(position, texture), collisionBox(collisionBox) {
    }
    Collider(Vector2 position, Texture texture) : Sprite(position, texture) {
        collisionBox =
            BoundingBox{0, 0, float(texture.width), float(texture.height)};
    }
    virtual void Collide(Collider *other){};
    ~Collider() {
    }
};