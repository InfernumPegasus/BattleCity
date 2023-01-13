#ifndef BATTLECITY_HEAVYTANK_H
#define BATTLECITY_HEAVYTANK_H

#include "Tank.h"

class HeavyTank : public Tank, public GameObject {
public:
    HeavyTank(const Point2D &position, double speed) :
            GameObject(position),
            Tank(speed, HEAVY_TANK_HP) {}

    ~HeavyTank() override;

public:
    void MoveUp() override;
    void MoveDown() override;
    void MoveLeft() override;
    void MoveRight() override;

    void Destroy() override;
    void OnHit() override;
    void Shoot() override;

public:
    static constexpr int HEAVY_TANK_HP = 3;
};


#endif //BATTLECITY_HEAVYTANK_H
