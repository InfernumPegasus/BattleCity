#ifndef BATTLECITY_PROJECTILE_H
#define BATTLECITY_PROJECTILE_H

#include "GameObject.h"
#include "Direction.h"

class Projectile : GameObject {
public:
    Projectile(const Point2D &pos, Direction direction, int damage) :
            GameObject(pos), direction_(direction),
            damage_(damage) {}

public:
    Direction GetDirection() const;
    int GetDamage() const;

private:
    Direction direction_;
    int damage_;
};


#endif //BATTLECITY_PROJECTILE_H
