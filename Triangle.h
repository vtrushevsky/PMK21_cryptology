#pragma once
using namespace std;

template <typename T>
class Triangle
{
public:
    Triangle(T side_1, T side_2, T side_3);

    T triangle_area() const;
    T getPerimeter() const;

    T side_1;
    T side_2;
    T side_3;
    Triangle* next;
};
