#ifndef BATTLECITY_PROJECTILE_H
#define BATTLECITY_PROJECTILE_H

#include "GameObject.h"
#include "Direction.h"

class Projectile : GameObject {
public:
    Direction GetDirection() const;

private:
    Direction direction_;

    int damage_;
};


#endif //BATTLECITY_PROJECTILE_H
