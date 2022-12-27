#ifndef BATTLECITY_LIGHTTANK_H
#define BATTLECITY_LIGHTTANK_H

#include "Tank.h"

class LightTank : public Tank, public GameObject {
public:
    LightTank(const Point2D &position, double speed) :
            GameObject(position),
            Tank(speed, LIGHT_TANK_HP) {}

public:
    void MoveUp() override;
    void MoveDown() override;
    void MoveLeft() override;
    void MoveRight() override;

    void Destroy() override;
    void OnHit() override;
    void Shoot() override;

public:
    static constexpr int LIGHT_TANK_HP = 1;
};


#endif //BATTLECITY_LIGHTTANK_H
