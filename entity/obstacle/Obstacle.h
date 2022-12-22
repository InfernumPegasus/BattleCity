#ifndef BATTLECITY_OBSTACLE_H
#define BATTLECITY_OBSTACLE_H

class Obstacle : protected GameObject {
protected:
    const bool tankPassable;
    const bool projectilePassable;
    const bool tankVisionDisabling;

protected:
    Obstacle(const Point2D &position, bool tankPassable, bool projectilePassable, bool tankVisionDisable);
    Obstacle(const Obstacle &other);

public:
    bool TankPassable() const;
    bool ProjectilePassable() const;
    bool TankVisionDisabling() const;
};


#endif //BATTLECITY_OBSTACLE_H
