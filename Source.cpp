#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iterator>
#include <exception>
#include "Triangle.cpp"
#include "List.cpp"

using namespace std;


class CustomException : public exception {
private:
    string message;

public:
    CustomException(const string& msg) : message(msg) {}

    const char* what() const noexcept {
        return message.c_str();
    }
};


template <typename T>
bool filterFunction(const Triangle<T>& triangle) {

    return triangle.triangle_area() > 1;
}

template <typename T>
void moveTriangles(List<T>& sourceList, List<T>& destinationList, double minPerimeter, double maxPerimeter) {
    Triangle<T>* current = sourceList.getHead();
    while (current != nullptr) {
        double perimeter = current->getPerimeter();
        if (perimeter >= minPerimeter && perimeter <= maxPerimeter) {
            destinationList.add(current->side_1, current->side_2, current->side_3);
            sourceList.remove(current);
        }
        current = current->next;
    }
}

int main() {
    List<double> list;

    ifstream in("triangles.txt");
    if (!in) {
        throw CustomException("Unable to open the file.");
    }

    double side_1, side_2, side_3;

    while (in >> side_1 >> side_2 >> side_3) {
        list.add(side_1, side_2, side_3);
    }

    in.close();

    list.filterTriangles(filterFunction, "filtered_triangles.txt");

    cout << list;

    List<double> filteredList;
    moveTriangles(list, filteredList, 20, 30); 

    cout << "Filtered List:\n" << filteredList;

    return 0;
}
