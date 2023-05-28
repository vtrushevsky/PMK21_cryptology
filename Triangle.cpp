#include "Triangle.h"
using namespace std;

template <typename T>
Triangle<T>::Triangle(T side_1, T side_2, T side_3) : side_1(side_1), side_2(side_2), side_3(side_3), next(nullptr) {}

template <typename T>
T Triangle<T>::triangle_area() const
{
    T s = (side_1 + side_2 + side_3) / 2.0;
    return sqrt(s * (s - side_1) * (s - side_2) * (s - side_3));
}

template <typename T>
T Triangle<T>::getPerimeter() const {
    return side_1 + side_2 + side_3;
}