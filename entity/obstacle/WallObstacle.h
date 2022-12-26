#ifndef BATTLECITY_WALLOBSTACLE_H
#define BATTLECITY_WALLOBSTACLE_H

#include "Obstacle.h"

/*
 * Interface that describes wall objects
 */
class WallObstacle : public Obstacle {
public:
    [[nodiscard]] int GetDurability() const;

public:
    WallObstacle(const ObstacleProperties &properties, int durability) :
            Obstacle(properties), durability_(durability) {}

    WallObstacle(bool tankPassable, bool projectilePassable, bool tankVisionDisabling, int durability) :
            Obstacle(tankPassable, projectilePassable, tankVisionDisabling), durability_(durability) {}

protected:
    virtual void OnHit() = 0;
    virtual void OnDestroy() = 0;

protected:
    int durability_;
};


#endif //BATTLECITY_WALLOBSTACLE_H
