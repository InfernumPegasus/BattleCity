#ifndef BATTLECITY_ITANK_H
#define BATTLECITY_ITANK_H

#include "../GameObject.h"
#include "../Projectile.h"

/*
 * Tank interface
 */
class ITank {
protected:
    virtual void MoveUp() = 0;
    virtual void MoveDown() = 0;
    virtual void MoveLeft() = 0;
    virtual void MoveRight() = 0;

    virtual void OnHit() = 0;
};

#endif //BATTLECITY_ITANK_H
