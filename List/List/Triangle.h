#include <cmath>
#include <iostream>
#include "Point.h"

using namespace std;

class Triangle: public Point {
private:
    Point a;
    Point b;
    Point c;

public:
    Triangle(const Point& a, const Point& b, const Point& c) : a(a), b(b), c(c) {}

    Point getA() const { return a; }
    Point getB() const { return b; }
    Point getC() const { return c; }

    double perimeter() const {
        double ab = a.distanceTo(b);
        double bc = b.distanceTo(c);
        double ca = c.distanceTo(a);
        return ab + bc + ca;
    }

    double area() const {
        double ab = a.distanceTo(b);
        double bc = b.distanceTo(c);
        double ca = c.distanceTo(a);
        double p = (ab + bc + ca) / 2;
        return sqrt(p * (p - ab) * (p - bc) * (p - ca));
    }
};