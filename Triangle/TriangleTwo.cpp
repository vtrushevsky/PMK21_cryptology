#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <exception>

using namespace std;

class MyException : public exception {
private:
    char * message;

public:
    MyException(char * msg) : message(msg) {}
    char * what () {
        return message;
    }
};

template <typename T>
class Triangle {
private:
    T sideA, sideB, sideC;

public:
    Triangle(T a, T b, T c) : sideA(a), sideB(b), sideC(c) {}

    T perimeter() const {
        return sideA + sideB + sideC;
    }

    T area() const {
        T s = (sideA + sideB + sideC) / 2.0;
        return sqrt(s * (s - sideA) * (s - sideB) * (s - sideC));
    }

    // Overload the less-than operator to compare triangles based on their area
    bool operator < (const Triangle<T>& other) const {
        return area() < other.area();
    }

    // Overload the output stream operator to print the triangle
    friend ostream& operator << (ostream& os, const Triangle<T>& triangle) {
        os << "Triangle(" << triangle.sideA << ", " << triangle.sideB << ", " << triangle.sideC << ")";
        return os;
    }
};


// Linked list class
template <typename T>
class LinkedList {
public:
    struct Node {
        T data;
        Node* next;

        Node(T data) : data(data), next(nullptr) {}
    };

    int size;

    Node* head;
    LinkedList() : head(nullptr), size(0) {}

    // Add a new node to the end of the linked list
    void add(T data) {
        Node* newNode = new Node(data);

        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* currentNode = head;
            while (currentNode->next != nullptr) {
                currentNode = currentNode->next;
            }
            currentNode->next = newNode;
        }

        size++;
    }

    void remove(T data) {
        Node* currentNode = head;
        Node* previousNode = nullptr;

        while (currentNode != nullptr) {
            if (currentNode->data == data) {
                if (previousNode == nullptr) {
                    head = currentNode->next;
                }
                else {
                    previousNode->next = currentNode->next;
                }
                delete currentNode;
                size--;
                return;
            }

            previousNode = currentNode;
            currentNode = currentNode->next;
        }
    }

    int getSize() const {
        return size;
    }

    // Overload the output stream operator to print the linked list
    friend ostream& operator << (ostream& os, const LinkedList& linkedList) {
        Node* currentNode = linkedList.head;
        while (currentNode != nullptr) {
            os << currentNode->data << " ";
            currentNode = currentNode->next;
        }
        return os;
    }
    // Sort the linked
    void sort() {
        if (size <= 1) {
        return;
    }
        Node* currentNode = head;
    while (currentNode != nullptr) {
        Node* minNode = currentNode;
        Node* searchNode = currentNode->next;
        while (searchNode != nullptr) {
            if (searchNode->data < minNode->data) {
                minNode = searchNode;
            }
            searchNode = searchNode->next;
        }
        if (minNode != currentNode) {
            T temp = currentNode->data;
            currentNode->data = minNode->data;
            minNode->data = temp;
        }
        currentNode = currentNode->next;
    }
    }
};


int main() {
    LinkedList<Triangle<double> > triangleList;

    // Open the file for reading
    try {
        cout << "Trying to open a file..." << endl;
    ifstream inputFile("triangles.txt");
    cout << "Success!" << endl;
    

    // Read the data from the file and create Triangle objects
    double sideA, sideB, sideC;
    while (inputFile >> sideA >> sideB >> sideC) {
        Triangle<double> triangle(sideA, sideB, sideC);
        triangleList.add(triangle);
    }

    // Sort the linked list by the area of the triangles
    triangleList.sort();

    // Output the sorted areas of triangles
    cout << "Sorted list of triangles by area:\n";
    typename LinkedList<Triangle<double> >::Node* currentNode = triangleList.head;
    while (currentNode != nullptr) {
        cout << currentNode->data.area() << "\n";
        currentNode = currentNode->next;
    }
    // Open the file for writing
ofstream outputFile("triangle.txt");

// Output the sorted areas of triangles to the file
while (currentNode != nullptr) {
    outputFile << currentNode->data.area() << "\n";
    currentNode = currentNode->next;
}

// Close the file
outputFile.close();
    }
    catch (MyException me) {
    cout << me.what() << endl;
    cout << "Error. Can not open a file!" << endl;
}

    return 0;
}
