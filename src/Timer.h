#include "raylib.h"

#include "BaseEntity.h"

class Timer : public BaseEntity {
  public:
    Timer(float spawnDelay) : spawnDelay(spawnDelay) {
    }
    ~Timer() {
    }
    void Think() override {
        if (active)
            return;
        elapsedTime += GetFrameTime();
        if (elapsedTime >= spawnDelay) {
            elapsedTime = 0;
            active = true;
        }
    }

    bool IsActive() {
        if (active) {
            active = false;
            return true;
        }
        return false;
    }

  private:
    bool active = false;
    float elapsedTime;
    float spawnDelay;
};