#pragma once
#include <algorithm>
#include <vector>

#include "BaseEntity.h"

struct Player;

class Scene {
  public:
    Player *player;
    std::vector<BaseEntity *> entities;

    void remove(BaseEntity *entity) {
        entities[entity->id] = nullptr;
        delete entity;
    }
    void add(BaseEntity *entity) {
        entity->id = entities.size();
        entities.push_back(entity);
    }
    void cleanup(BaseEntity *entity) {
        entities.erase(std::remove(entities.begin(), entities.end(), nullptr));
    }
    ~Scene() {
        for (BaseEntity *entity : entities) {
            if (entity != nullptr)
                delete entity;
        }
    }
} Scene;