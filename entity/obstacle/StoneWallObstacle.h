#ifndef BATTLECITY_STONEWALLOBSTACLE_H
#define BATTLECITY_STONEWALLOBSTACLE_H

#include "WallObstacle.h"

class StoneWallObstacle : public WallObstacle, public GameObject {
public:
    static constexpr int STONE_WALL_DURABILITY = 1;

    /* Wall obstacle type
     * 1) Tank cannot pass it
     * 2) Projectile cannot pass it
     * 3) It reduces visibility
     * 4) It can be destroyed
     */
    explicit StoneWallObstacle(const Point2D &position) :
            GameObject(position),
            WallObstacle(false, false, true, STONE_WALL_DURABILITY) {}

public:
    void CollideWith(const GameObject &obj) override;
    void CollideWith(const Projectile &projectile) override;

protected:
    void OnHit() override;
    void OnDestroy() override;
};


#endif //BATTLECITY_STONEWALLOBSTACLE_H
