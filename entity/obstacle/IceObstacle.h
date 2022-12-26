#ifndef BATTLECITY_ICEOBSTACLE_H
#define BATTLECITY_ICEOBSTACLE_H

#include "Obstacle.h"

class IceObstacle : public Obstacle, public GameObject {
public:
    /* Floor obstacle type
     * 1) Tank can pass it
     * 2) Projectile can pass it
     * 3) It does not reduce visibility
     */
    explicit IceObstacle(const Point2D &position) :
            GameObject(position),
            Obstacle(true, true, false) {}

public:
    void CollideWith(const GameObject &obj) override;

    void CollideWith(const Projectile &projectile) override;
};


#endif //BATTLECITY_ICEOBSTACLE_H
