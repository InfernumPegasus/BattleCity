#ifndef BATTLECITY_PLAYERTANK_H
#define BATTLECITY_PLAYERTANK_H

#include "ITank.h"
#include "../../Point2D.h"
#include "TankType.h"

class PlayerTank : public ITank, public GameObject {
private:
    const TankType tankType { TankType::PLAYER_TANK };

public:
    PlayerTank();
    explicit PlayerTank(const Point2D &pos);
    PlayerTank(const PlayerTank &other);

public:
    void MoveUp() override;
    void MoveDown() override;
    void MoveLeft() override;
    void MoveRight() override;
    void OnHit() override;
};


#endif //BATTLECITY_PLAYERTANK_H
