#ifndef BATTLECITY_GAMEOBJECT_H
#define BATTLECITY_GAMEOBJECT_H

#include "Point2D.h"

class GameObject {
public:
    GameObject(int x, int y);
    explicit GameObject(const Point2D &pos);

public:
    void SetPosition(const Point2D &pos);
    void SetX(int x);
    void SetY(int y);

    [[nodiscard]] Point2D GetPosition() const;

protected:
    Point2D position_;
};


#endif //BATTLECITY_GAMEOBJECT_H
