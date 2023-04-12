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
private:
    struct Node {
        T data;
        Node* next;

        Node(T data) : data(data), next(nullptr) {}
    };

    Node* head;
    int size;

public:
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

    // Sort the linked list using merge sort algorithm
    void mergeSort() {
        head = mergeSort(head);
    }

    // Helper function for merge sort
    Node* mergeSort(Node* node) {
        if (node == nullptr || node->next == nullptr) {
            return node;
        }

        // Find the middle node of the list
        Node* slow = node;
        Node* fast = node->next;
        while (fast != nullptr) {
            fast = fast->next;
            if (fast != nullptr) {
                slow = slow->next;
                fast = fast->next;
            }
        }
        Node* middle = slow->next;
        slow->next = nullptr;

        // Recursively merge sort the two halves
        Node* left = mergeSort(node);
        Node* right = mergeSort(middle);

        // Merge the sorted halves
        Node* merged = nullptr;
        if (left->data < right->data) {
            merged = left;
            left = left->next;
        }
        else {
            merged = right;
            right = right->next;
        }
        Node* currentNode = merged;

        while (left != nullptr && right != nullptr) {
            if (left->data < right->data) {
                currentNode->next = left;
                left = left->next;
            }
            else {
                currentNode->next = right;
                right = right->next;
            }
            currentNode = currentNode->next;
        }

        if (left != nullptr) {
            currentNode->next = left;
        }
        else {
            currentNode->next = right;
        }

        return merged;
    }
};
int main() {
// Create a linked list of triangles
LinkedList<Triangle<double> > triangles;
ifstream fin;

try {
    cout << "A try to open a file" << endl;
    fin.open("triangles.txt");
    cout << "Success!" << endl;

    // Read the triangles from the file and add them to the linked list
    double a, b, c;
    while (fin >> a >> b >> c) {
        Triangle<double> triangle(a, b, c);
        triangles.add(triangle);
    }

    // Sort the list of triangles by their area
    triangles.mergeSort();

    // Print the sorted list of triangles
    cout << "Sorted list of triangles by area:" << endl;
    cout << triangles << endl;

} catch (MyException me) {
    cout << me.what() << endl;
    cout << "Error. Can not open a file!" << endl;
}

return 0;
}