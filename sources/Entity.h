#pragma once
#include "EntityManager.h"

extern struct EntityManager manager;

struct Entity {
    size_t id;
    size_t parent_id;
    bool deleted = false;
    std::unordered_map<std::type_index, size_t> children;
    template <typename T> void add_child(T *ent) {
        ent->parent_id = id;
        assert(!children.contains(typeid(T)));
        children[typeid(T)] = manager.add_entity(ent);
    }
    template <typename T> std::optional<T*> get_child() {
        size_t child_id = children.at(typeid(T));
        return manager.get_entity<T>(child_id);
    }
    virtual void tick() {
    }
    virtual ~Entity() = default;
};