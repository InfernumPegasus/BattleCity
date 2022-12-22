#ifndef BATTLECITY_IRONWALLOBSTACLE_H
#define BATTLECITY_IRONWALLOBSTACLE_H

#include "WallObstacle.h"

class IronWallObstacle : protected WallObstacle {
public:
    /* Wall obstacle type
     * 1) Tank cannot pass it
     * 2) Projectile cannot pass it
     * 3) It reduces visibility
     * 4) It cannot be destroyed
     */
    IronWallObstacle() : WallObstacle(false, false, true, false) {}

protected:
    void OnHit() override;
    void OnDestroy() override;
};


#endif //BATTLECITY_IRONWALLOBSTACLE_H
