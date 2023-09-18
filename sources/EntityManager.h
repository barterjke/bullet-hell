#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <optional>
#include <sys/_types/_size_t.h>
#include <typeindex>
#include <unordered_map>
#include <vector>

struct Entity;

struct EntityManager {
    std::unordered_map<std::type_index, std::vector<Entity *>> entities;

    template <typename T> std::vector<T *> get_active_entities() {
        auto &t_ents = entities[typeid(T)];
        std::vector<T *> result;
        result.reserve(t_ents.size());
        for (auto *ent : t_ents) {
            auto t_ptr = dynamic_cast<T *>(ent);
            assert(t_ptr != nullptr);
            if (t_ptr->deleted)
                continue;
            result.push_back(dynamic_cast<T *>(ent));
        }
        // std::transform(
        //     t_ents.begin(), t_ents.end(), result.begin(), [](auto *ent) {
        //         return dynamic_cast<T *>(ent);
        //     });
        return result;
    }
    template <typename T> size_t add_entity(T *ent) {
        auto &t_ents = entities[typeid(T)];
        t_ents.push_back(ent);
        return t_ents.size() - 1;
    }
    template <typename T> std::optional<T *> get_entity(size_t index) {
        T *ptr = dynamic_cast<T *>(entities.at(typeid(T)).at(index));
        if (ptr == nullptr)
            return std::nullopt;
        return ptr;
    }
    template <typename T> void cleanup() {
        auto &t_ents = entities.at(typeid(T));
        t_ents.erase(
            std::remove_if(t_ents.begin(), t_ents.end(), [](auto *&ent) {
                if (ent->deleted) {
                    delete ent;
                    ent = nullptr;
                    return true;
                }
                return false;
            }));
    }
    ~EntityManager();
};