#ifndef BATTLECITY_GAMEMAP_H
#define BATTLECITY_GAMEMAP_H

#include <vector>
#include <array>
#include "../entity/GameObject.h"
#include "../entity/tank/Tank.h"
#include "../entity/obstacle/Obstacle.h"
#include "../entity/tank/LightTank.h"
#include "../entity/tank/MediumTank.h"
#include "../entity/tank/HeavyTank.h"

class GameMap final {
public:
    // Matrix size
    static constexpr int GAME_MAP_SIZE = 15;

    // Matrix which represents game map
    using Map = std::vector<std::array<GameObject, GAME_MAP_SIZE>>;

public:
    GameMap() = delete;
    GameMap(const std::vector<Tank> &tanks, const std::vector<Obstacle> &obstacles);

public:
    void SetObjectByPosition(const GameObject &object, const Point2D &position);

    void Init();
    void Update();
    void CheckCorrectness();

private:
    Map map_;
};


#endif //BATTLECITY_GAMEMAP_H
