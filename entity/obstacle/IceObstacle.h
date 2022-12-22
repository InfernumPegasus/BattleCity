#ifndef BATTLECITY_ICEOBSTACLE_H
#define BATTLECITY_ICEOBSTACLE_H

#include "Obstacle.h"

class IceObstacle : protected Obstacle {
public:
    /* Floor obstacle type
     * 1) Tank can pass it
     * 2) Projectile can pass it
     * 3) It does not reduce visibility
     */
    explicit IceObstacle(const Point2D &position) : Obstacle(position, true, true, false) {}
};


#endif //BATTLECITY_ICEOBSTACLE_H
