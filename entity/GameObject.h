#ifndef BATTLECITY_GAMEOBJECT_H
#define BATTLECITY_GAMEOBJECT_H

#include "Point2D.h"

class GameObject {
protected:
    Point2D position;

public:
    GameObject(int x, int y);
    explicit GameObject(const Point2D &pos);

protected:
    void SetPosition(const Point2D &pos);
    void SetX(int x);
    void SetY(int y);
    [[nodiscard]] Point2D GetPosition() const;
};


#endif //BATTLECITY_GAMEOBJECT_H
