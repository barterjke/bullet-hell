#pragma once

struct StatsComponent {
    int hp;
    float speed;
    bool isPlayer;
    StatsComponent(int hp, float speed, bool isPlayer) :
        hp(hp), speed(speed), isPlayer(isPlayer) {
    }
};
