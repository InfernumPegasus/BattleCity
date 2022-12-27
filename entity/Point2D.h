#ifndef BATTLECITY_POINT2D_H
#define BATTLECITY_POINT2D_H

/*
 * Class that describes position of the object in 2D
 */
class Point2D {
public:
    Point2D(int x, int y);
    Point2D(const Point2D &other);

public:
    void SetX(int x);
    void SetY(int y);

    [[nodiscard]] int GetX() const;
    [[nodiscard]] int GetY() const;

private:
    int x_;
    int y_;
};


#endif //BATTLECITY_POINT2D_H
