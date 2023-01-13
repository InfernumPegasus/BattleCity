#ifndef BATTLECITY_MEDIUMTANK_H
#define BATTLECITY_MEDIUMTANK_H

#include "Tank.h"

class MediumTank : public Tank, public GameObject {
public:
    MediumTank(const Point2D &position, double speed) :
            GameObject(position),
            Tank(speed, MEDIUM_TANK_HP) {}

    ~MediumTank() override;

public:
    void MoveUp() override;
    void MoveDown() override;
    void MoveLeft() override;
    void MoveRight() override;

    void Destroy() override;
    void OnHit() override;
    void Shoot() override;

public:
    static constexpr int MEDIUM_TANK_HP = 2;
};


#endif //BATTLECITY_MEDIUMTANK_H
