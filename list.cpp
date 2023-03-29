#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <algorithm>
#include <cmath>

//стракт для трикутників
struct Triangle
{
    double a, b, c;
    Triangle(double a, double b, double c): a(a), b(b), c(c) {}
    
    //площа за формулою герона
    double area() const 
    {
        double s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    double perimeter() const 
    {
        return a + b + c;
    }
};

// первантаження < для сортування площ
bool operator<(const Triangle& t1, const Triangle& t2)
{
    return t1.area() < t2.area();
}

int main() 
{
    std::ifstream infile("triangles.txt");
    if (!infile.is_open()) 
    {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    std::list<Triangle> triangleList;
    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        double a, b, c;
        if (!(iss >> a >> b >> c)) 
        {
            std::cerr << "Invalid input\n";
            continue;
        }
        triangleList.push_back(Triangle(a, b, c));
    }
    infile.close();

    triangleList.sort();

    std::list<Triangle> newTriangleList;
    double minPerimeter = 10, maxPerimeter = 20;

    auto it = triangleList.begin();
    while (it != triangleList.end())
    {
        if (it->perimeter() >= minPerimeter && it->perimeter() <= maxPerimeter)
        {
            newTriangleList.splice(newTriangleList.end(), triangleList, it++);
        }
        else
        {
            ++it;
        }
    }

    std::ofstream outfile("result.txt");
    if (!outfile.is_open())
    {
        std::cerr << "Failed to open output file\n";
        return 1;
    }

    outfile << "Triangles sorted by increasing area:\n";
    for (const auto& t : triangleList)
    {
        outfile << t.a << " " << t.b << " " << t.c << " Area: " << t.area() << "\n";
    }
    outfile << "\nTriangles with perimeter between " << minPerimeter << " and " << maxPerimeter << ":\n";
    for (const auto& t : newTriangleList)
    {
        outfile << t.a << " " << t.b << " " << t.c << " Area: " << t.area() << "\n";
    }
    outfile.close();

    return 0;
}
