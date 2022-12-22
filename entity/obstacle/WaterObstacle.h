#ifndef BATTLECITY_WATEROBSTACLE_H
#define BATTLECITY_WATEROBSTACLE_H


class WaterObstacle : protected Obstacle {
public:
    /* Floor obstacle type
     * 1) Tank cannot pass it
     * 2) Projectile can pass it
     * 3) It does not reduce visibility
     */
    explicit WaterObstacle(const Point2D &position) : Obstacle(position, false, true, false) {}
};


#endif //BATTLECITY_WATEROBSTACLE_H
