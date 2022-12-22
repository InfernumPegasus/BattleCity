#ifndef BATTLECITY_ENEMYTANK_H
#define BATTLECITY_ENEMYTANK_H

#include "ITank.h"
#include "../../Point2D.h"
#include "TankType.h"

class EnemyTank : public ITank, public GameObject {
private:
    const TankType tankType { TankType::ENEMY_TANK };

public:
    EnemyTank();
    explicit EnemyTank(const Point2D &pos);
    EnemyTank(const EnemyTank &other);

public:
    void MoveUp() override;
    void MoveDown() override;
    void MoveLeft() override;
    void MoveRight() override;
    void OnHit() override;
};


#endif //BATTLECITY_ENEMYTANK_H
