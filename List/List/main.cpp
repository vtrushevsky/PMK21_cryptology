#include <iostream>
#include "List.h"
#include "Point.h"
#include "Triangle.h"

using namespace std;

int main(){
    ifstream fin("../triangles.txt");

    List<Triangle> trianglesList;
    double x1, y1, x2, y2, x3, y3;
    while (fin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3) {
        Point p1(x1, y1);
        Point p2(x2, y2);
        Point p3(x3, y3);
        Triangle triangle(p1, p2, p3);
        trianglesList.add(triangle);
    }

    fin.close();

    ofstream outputFile("../triangles_output.txt");
// запис кожного трикутника у файл
    for (auto triangle : trianglesList) {
        outputFile << "Triangle: ";

        outputFile << triangle.getA().getX() << " " << triangle.getA().getY() << " ";
        outputFile << triangle.getB().getX() << " " << triangle.getB().getY() << " ";
        outputFile << triangle.getC().getX() << " " << triangle.getC().getY() << endl;
        outputFile << endl;
    }
    outputFile.close();
    return 0;
}