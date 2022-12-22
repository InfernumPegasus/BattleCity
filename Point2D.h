#ifndef BATTLECITY_POINT2D_H
#define BATTLECITY_POINT2D_H


/*
 * Class that describes position of the object in 2D
 */
class Point2D {
private:
    int x;
    int y;

public:
    Point2D();
    Point2D(int x, int y);
    Point2D(const Point2D &other);

public:
    void SetX(int x);
    void SetY(int y);
    [[nodiscard]] int GetX() const;
    [[nodiscard]] int GetY() const;
};


#endif //BATTLECITY_POINT2D_H
