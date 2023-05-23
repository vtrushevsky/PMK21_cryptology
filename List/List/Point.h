#include <cmath>

class Point {
private:
    double x;
    double y;

public:
    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    double distanceTo(const Point& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return sqrt(dx*dx + dy*dy);
    }
};