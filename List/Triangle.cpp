//
// Created by dmytro on 5/3/23.
//
#include <math.h>
#include "Triangle.h"

Triangle::Triangle() {
    coord[0] = new Point;
    coord[1] = new Point;
    coord[2] = new Point;
}

void Triangle::setPoint(int x, int y){

    for (auto & i : coord){
        if  (i->x == 0 and  i->y ==0)
        {
            i->x= x;
            i->y= y;
            break;
        }

    }
}
double Triangle::getArea() const {
    double a = sqrt(pow(coord[0]->x - coord[1]->x, 2) + pow(coord[0]->y - coord[1]->y, 2));
    double b = sqrt(pow(coord[1]->x - coord[2]->x, 2) + pow(coord[1]->y - coord[2]->y, 2));
    double c = sqrt(pow(coord[2]->x - coord[0]->x, 2) + pow(coord[2]->y - coord[0]->y, 2));
    double p = (a + b + c) / 2;
    double area = sqrt(p * (p - a) * (p - b) * (p - c));
    return area;
}

std::ostream &operator<<(std::ostream &os, const Triangle &triangle) {
    os << "My area " << triangle.getArea() << " ";

    for(auto & i : triangle.coord)
    {
        os << "X >> "  << i->x  << " ";
        os << "Y >> "  << i->y << " ";
    }
    return os;
}

Triangle& Triangle::operator=(Triangle &triangle) {
    coord[0] = triangle.coord[0];
    coord[1] = triangle.coord[1];
    coord[2] = triangle.coord[2];

    return *this;
}
bool Triangle::operator== ( const Triangle &other) const{
    bool res = false;
    if (coord[0] == other.coord[0] and coord[1] == other.coord[1] and coord[2] == other.coord[2]){
        res = true;
    }

    return res;
}
bool Triangle::operator> (const Triangle& other) const {
    return this->getArea() > other.getArea();
}

bool Triangle::operator> (int area)  {
//    std::cout << this->getArea() << std::endl;
    return this->getArea() > area;
}





