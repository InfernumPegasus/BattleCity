#ifndef BATTLECITY_LIGHTTANK_H
#define BATTLECITY_LIGHTTANK_H

#include "Tank.h"

class LightTank : public Tank {
public:
    LightTank(double speed, int hp);

public:
    void MoveUp() override;
    void MoveDown() override;
    void MoveLeft() override;
    void MoveRight() override;

    void Destroy() override;
    void OnHit() override;
    void Shoot() override;
};


#endif //BATTLECITY_LIGHTTANK_H
