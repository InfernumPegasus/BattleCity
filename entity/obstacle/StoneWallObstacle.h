#ifndef BATTLECITY_STONEWALLOBSTACLE_H
#define BATTLECITY_STONEWALLOBSTACLE_H

#include "WallObstacle.h"

class StoneWallObstacle : protected WallObstacle {
public:
    /* Wall obstacle type
     * 1) Tank cannot pass it
     * 2) Projectile cannot pass it
     * 3) It reduces visibility
     * 4) It can be destroyed
     */
    StoneWallObstacle() : WallObstacle(false, false, true, true) {}

protected:
    void OnHit() override;
    void OnDestroy() override;
};


#endif //BATTLECITY_STONEWALLOBSTACLE_H
