#ifndef BATTLECITY_POINT2D_H
#define BATTLECITY_POINT2D_H


/*
 * Class that describes position of the object in 2D
 */
class Point2D {
private:
    double x_;
    double y_;

public:
    Point2D(double x, double y);

    Point2D(const Point2D &other);

public:
    void SetX(double x);

    void SetY(double y);

    [[nodiscard]] double GetX() const;

    [[nodiscard]] double GetY() const;
};


#endif //BATTLECITY_POINT2D_H
