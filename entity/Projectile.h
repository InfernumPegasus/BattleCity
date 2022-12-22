#ifndef BATTLECITY_PROJECTILE_H
#define BATTLECITY_PROJECTILE_H

#include "GameObject.h"
#include "tank/TankType.h"
#include "../Direction.h"

class Projectile : GameObject {
private:
    // Need to know is projectile 'friendly'
    TankType tankType;
    // Direction of projectile
    Direction direction;

public:
    Projectile(Direction direction, TankType tankType);

public:
    TankType GetTankType() const;
    Direction GetDirection() const;
};


#endif //BATTLECITY_PROJECTILE_H
