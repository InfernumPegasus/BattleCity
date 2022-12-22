#ifndef BATTLECITY_HEADQUARTERS_H
#define BATTLECITY_HEADQUARTERS_H

#include <iostream>
#include "obstacle/Obstacle.h"
#include "GameObject.h"

/*
 * Key object of the game. If it is destroyed player lose
 */
class Headquarters : public GameObject {
private:
    int hp;

public:
    Headquarters();
    Headquarters(const Point2D &position, int hp);

public:
    void OnHit();
    void OnDestroy();
};


#endif //BATTLECITY_HEADQUARTERS_H
