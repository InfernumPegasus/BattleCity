#ifndef BATTLECITY_HEAVYTANK_H
#define BATTLECITY_HEAVYTANK_H

#include "Tank.h"

class HeavyTank : public Tank {
public:
    HeavyTank(double speed, int hp) : Tank(speed, hp) {}

public:
    void MoveUp() override {}
    void MoveDown() override {}
    void MoveLeft() override {}
    void MoveRight() override {}

    void Destroy() override {}
    void OnHit() override {}
    void Shoot() override {}
};


#endif //BATTLECITY_HEAVYTANK_H
