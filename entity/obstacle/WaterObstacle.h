#ifndef BATTLECITY_WATEROBSTACLE_H
#define BATTLECITY_WATEROBSTACLE_H

#include "Obstacle.h"

class WaterObstacle : public Obstacle, public GameObject {
public:
    /* Floor obstacle type
     * 1) Tank cannot pass it
     * 2) Projectile can pass it
     * 3) It does not reduce visibility
     */
    explicit WaterObstacle(const Point2D &position) :
            GameObject(position),
            Obstacle(false, true, false) {}

    WaterObstacle(int x, int y) :
            GameObject(x, y),
            Obstacle(false, true, false) {}

    ~WaterObstacle() override;

public:
    void CollideWith(const GameObject &obj) override;
    void CollideWith(const Projectile &projectile) override;
};


#endif //BATTLECITY_WATEROBSTACLE_H
