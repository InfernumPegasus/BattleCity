#ifndef BATTLECITY_OBSTACLE_H
#define BATTLECITY_OBSTACLE_H

#include "../GameObject.h"
#include "ObstacleProperties.h"
#include "../Projectile.h"

class Obstacle {
public:
    explicit Obstacle(const ObstacleProperties &properties);
    Obstacle(bool tankPassable, bool projectilePassable, bool tankVisionDisabling);

public:
    [[nodiscard]] ObstacleProperties GetProperties() const;

public:
    virtual void CollideWith(const GameObject &obj) = 0;
    virtual void CollideWith(const Projectile &projectile) = 0;

private:
    const ObstacleProperties obstacleProperties_;
};


#endif //BATTLECITY_OBSTACLE_H
