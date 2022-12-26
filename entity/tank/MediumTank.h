#ifndef BATTLECITY_MEDIUMTANK_H
#define BATTLECITY_MEDIUMTANK_H

#include "Tank.h"

class MediumTank : public Tank {
public:
    MediumTank(double speed, int hp) : Tank(speed, hp) {}

public:
    void MoveUp() override;
    void MoveDown() override;
    void MoveLeft() override;
    void MoveRight() override;

    void Destroy() override;
    void OnHit() override;
    void Shoot() override;
};


#endif //BATTLECITY_MEDIUMTANK_H
