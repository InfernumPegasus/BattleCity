#ifndef BATTLECITY_OBSTACLEPROPERTIES_H
#define BATTLECITY_OBSTACLEPROPERTIES_H


struct ObstacleProperties {
    const bool tankPassable_;
    const bool projectilePassable_;
    const bool tankVisionDisabling_;

    ObstacleProperties(const bool tankPassable,
                       const bool projectilePassable,
                       const bool tankVisionDisabling);
};


#endif //BATTLECITY_OBSTACLEPROPERTIES_H
