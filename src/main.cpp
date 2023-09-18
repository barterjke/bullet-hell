#include "new_life.h"
#include "raylib.h"

/*
cmake --build build && ./build/my_raylib_game
*/

const Vector2 SCREEN_SIZE = {800, 400};
const unsigned int FPS = 60;

void Init() {
    auto player = new Player(
        Vector2{100, SCREEN_SIZE.y / 2.0f},
        LoadTexture(ASSETS_PATH "space_breaker_asset/Ships/Small/body_01.png"),
        {Vector2{100, 0}},
        Bullet::REGULAR,
        0.5f,
        10,
        150);
    Scene.player = player;
    Scene.add(player);
    // {"stars_bg",
    //  LoadTexture(ASSETS_PATH
    //              "space_breaker_asset/Background/stars_texture.png")},
    // {"big_ship_1",
    //  LoadTexture(ASSETS_PATH "space_breaker_asset/Ships/Big/body_01.png")},
    // {"small_ship_1",
    //  LoadTexture(ASSETS_PATH "space_breaker_asset/Ships/Small/body_01.png")}
    // {"explosion_ss",
    //  LoadTexture(ASSETS_PATH "space_breaker_asset/Weapons/Small/Laser/"
    //                          "turret_02_explosion_01_anim.png")}};
}

void Think() {
    for (BaseEntity *entity : Scene.entities) {
        if (entity == nullptr)
            continue;
        entity->Think();
    }
    for (BaseEntity *entity : Scene.entities) {
        if (entity == nullptr)
            continue;
        Collider *collider = dynamic_cast<Collider *>(entity);
        if (collider != nullptr && collider != Scene.player &&
            CheckCollisionBoxes(
                Scene.player->collisionBox, collider->collisionBox)) {
            collider->Collide(Scene.player);
            Scene.player->Collide(collider);
        }
    }
}

int main() {
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, "bullet hell");
    SetTargetFPS(FPS);
    Init();
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Think();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}