#ifndef BATTLECITY_WALLOBSTACLE_H
#define BATTLECITY_WALLOBSTACLE_H

#include "Obstacle.h"

class WallObstacle : protected Obstacle {
protected:
    const bool destroyable;

protected:
    bool Destroyable() const;

protected:
    WallObstacle(const Obstacle &obstacle, bool destroyable);
    WallObstacle(bool tankPassable, bool projectilePassable, bool tankVisionDisable, bool destroyable);

protected:
    virtual void OnHit();
    virtual void OnDestroy();
};


#endif //BATTLECITY_WALLOBSTACLE_H
