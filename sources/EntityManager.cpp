#include "EntityManager.h"
#include "Entity.h"

EntityManager::~EntityManager() {
    for (auto &[_, entities] : entities) {
        for (auto *& ent : entities) {
            delete ent;
            ent = nullptr;
        }
    }
    std::cout << "EntityManager is cleaned\n";
}