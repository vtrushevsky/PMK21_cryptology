//
// Created by dmytro on 5/3/23.
//

#ifndef UNTITLED1_TRIANGLE_H
#define UNTITLED1_TRIANGLE_H


#include "Point.h"


class Triangle {
public:
       Point* coord[3]{};
public:
    Triangle();
    double getArea() const;

    void setPoint(int , int);

    friend std::ostream& operator<< (std::ostream &os, const Triangle &triangle);
    Triangle& operator=(Triangle &triangle);
    bool operator> (const Triangle& other) const;
    bool operator>(int area) ;
    bool operator==(const Triangle &other) const;
};



#endif //UNTITLED1_TRIANGLE_H
