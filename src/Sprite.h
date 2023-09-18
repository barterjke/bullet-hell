#pragma once
#include "raylib.h"

#include "BaseEntity.h"
#include "Scene.h"

class Sprite : public BaseEntity {
  public:
    Vector2 position;
    Texture texture;
    Color color = WHITE;
    Sprite(Vector2 position, Texture texture) :
        position(position), texture(texture) {
    }
    bool isOutsideScreen() {
        return position.x + texture.width <= 0 ||
               position.x - texture.width >= GetScreenWidth() ||
               position.y + texture.height <= 0 ||
               position.y - texture.height >= GetScreenHeight();
    }
    void Think() override {
        DrawTexture(texture, position.x, position.y, color);
    }
};