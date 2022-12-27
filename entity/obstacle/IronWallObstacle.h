#ifndef BATTLECITY_IRONWALLOBSTACLE_H
#define BATTLECITY_IRONWALLOBSTACLE_H

#include "WallObstacle.h"

class IronWallObstacle : public WallObstacle, public GameObject {
public:
    static constexpr int IRON_WALL_DURABILITY = 2;

    /* Wall obstacle type
     * 1) Tank cannot pass it
     * 2) Projectile cannot pass it
     * 3) It reduces visibility
     */
    explicit IronWallObstacle(const Point2D &position) :
            GameObject(position),
            WallObstacle(false, false, true, IRON_WALL_DURABILITY) {}

public:
    void CollideWith(const GameObject &obj) override;
    void CollideWith(const Projectile &projectile) override;

protected:
    void OnHit() override;
    void OnDestroy() override;
};


#endif //BATTLECITY_IRONWALLOBSTACLE_H
