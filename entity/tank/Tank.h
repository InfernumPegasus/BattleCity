#ifndef BATTLECITY_TANK_H
#define BATTLECITY_TANK_H

#include "../Projectile.h"

class Tank {
public:
    Tank(double speed, int hp);

public:
    [[nodiscard]] double GetSpeed() const;
    [[nodiscard]] int GetHP() const;
    [[nodiscard]] Direction GetDirection() const;

protected:
    virtual void MoveUp() = 0;
    virtual void MoveDown() = 0;
    virtual void MoveLeft() = 0;
    virtual void MoveRight() = 0;

    virtual void Destroy() = 0;
    virtual void OnHit() = 0;
    virtual void Shoot() = 0;

private:
    double speed_;
    int hp_;
    Direction direction_{Direction::UP};
};

#endif //BATTLECITY_TANK_H
