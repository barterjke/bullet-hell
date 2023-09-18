#include "Entity.h"
#include "EntityManager.h"
#include "raylib.h"
#include <iostream>

EntityManager manager;

struct Stats : public Entity {};

struct Timer : public Entity {
    float elapsedTime;
    float cooldown;
};

struct Sprite : public Entity {
    Vector2 position;
};

struct Player : public Entity {
    int health;
    float speed;
    Player() {
        add_child(new Sprite());
    }
    Vector2 position() {
        auto sprite = *get_child<Sprite>();
        return sprite->position;
    }
    void tick() override {
    }
};

int main() {
    return 0;
}