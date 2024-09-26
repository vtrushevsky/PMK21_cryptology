#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

class Triangle {
public:
    Triangle(double a, double b, double c) : a(a), b(b), c(c) {}

    double getPerimeter() const {
        return a + b + c;
    }

    double getArea() const {
        double s = getPerimeter() / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    friend ostream& operator<<(ostream& os, const Triangle& triangle) {
        os << "Triangle: sides = " << triangle.a << ", " << triangle.b << ", " << triangle.c;
        return os;
    }

private:
    double a, b, c;
};

template<typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(const T& data, Node* prev = nullptr, Node* next = nullptr) : data(data), prev(prev), next(next) {}
    };

public:
    class Iterator {
    public:
        Iterator(Node* node) : current(node) {}

        T& operator*() const {
            return current->data;
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            current = current->next;
            return temp;
        }

        Iterator& operator--() {
            current = current->prev;
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            current = current->prev;
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

    private:
        Node* current;
    };

    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), size(0) {
        Node* currentNode = other.head;
        while (currentNode != nullptr) {
            pushBack(currentNode->data);
            currentNode = currentNode->next;
        }
    }

    DoublyLinkedList(DoublyLinkedList&& other) noexcept : head(other.head), tail(other.tail), size(other.size) {
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this != &other) {
            clear();
            Node* currentNode = other.head;
            while (currentNode != nullptr) {
                pushBack(currentNode->data);
                currentNode = currentNode->next;
            }
        }
        return *this;
    }

    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            size = other.size;
            other.head = nullptr;
            other.tail = nullptr;
            other.size = 0;
        }
        return *this;
    }

    ~DoublyLinkedList() {
        clear();
    }

    void pushBack(const T& data) {
        Node* newNode = new Node(data, tail, nullptr);
        if (tail != nullptr) {
            tail->next = newNode;
        }
        else {
            head = newNode;
        }
        tail = newNode;
        size++;
    }

    void remove(const Iterator& it) {
        if (it == end()) {
            return;
        }
        Node* current = it.current;
        if (current == head) {
            head = current->next;
        }
        else {
            current->prev->next = current->next;
        }
        if (current == tail) {
            tail = current->prev;
        }
        else {
            current->next->prev = current->prev;
        }
        delete current;
        size--;
    }

    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

    void sort() {
        if (size <= 1) {
            return;
        }
        bool swapped;
        do {
            swapped = false;
            Node* current = head;
            while (current->next != nullptr) {
                if (current->data.getArea() > current->next->data.getArea()) {
                    swapNodes(current, current->next);
                    swapped = true;
                }
                else {
                    current = current->next;
                }
            }
        } while (swapped);
    }

    DoublyLinkedList filterByPerimeter(double minPerimeter, double maxPerimeter) const {
        DoublyLinkedList filteredList;
        for (const auto& triangle : *this) {
            double perimeter = triangle.getPerimeter();
            if (perimeter >= minPerimeter && perimeter <= maxPerimeter) {
                filteredList.pushBack(triangle);
            }
        }
        return filteredList;
    }

private:
    Node* head;
    Node* tail;
    int size;

    void swapNodes(Node* node1, Node* node2) {
        if (node1 == node2) {
            return;
        }

        if (node1->prev != nullptr) {
            node1->prev->next = node2;
        }
        else {
            head = node2;
        }

        if (node2->next != nullptr) {
            node2->next->prev = node1;
        }
        else {
            tail = node1;
        }

        node1->next = node2->next;
        node2->prev = node1->prev;

        node2->next = node1;
        node1->prev = node2;
    }

    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
};

void readTrianglesFromFile(const string& filename, DoublyLinkedList<Triangle>& triangles) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Failed to open file: " + filename);
    }

    double a, b, c;
    while (file >> a >> b >> c) {
        Triangle triangle(a, b, c);
        triangles.pushBack(triangle);
    }

    file.close();
}

void writeTrianglesToFile(const string& filename, const DoublyLinkedList<Triangle>& triangles) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Failed to open file for writing: " + filename);
    }

    for (const auto& triangle : triangles) {
        file << triangle << endl;
    }

    file.close();
}

void runTriangleFiltering() {
    DoublyLinkedList<Triangle> triangles;

    try {
        readTrianglesFromFile("triangles.txt", triangles);

        cout << "Original list of triangles:" << endl;
        for (const auto& triangle : triangles) {
            cout << triangle << endl;
        }

        triangles.sort();

        cout << "\nSorted list of triangles:" << endl;
        for (const auto& triangle : triangles) {
            cout << triangle << endl;
        }

        double minPerimeter = 10.0;
        double maxPerimeter = 30.0;
        DoublyLinkedList<Triangle> filteredTriangles = triangles.filterByPerimeter(minPerimeter, maxPerimeter);

        cout << "\nFiltered list of triangles with perimeter between " << minPerimeter << " and " << maxPerimeter << ":" << endl;
        for (const auto& triangle : filteredTriangles) {
            cout << triangle << endl;
        }

        writeTrianglesToFile("filtered_triangles.txt", filteredTriangles);

        cout << "\nFiltered triangles have been written to file 'filtered_triangles.txt'" << endl;
    }
    catch (const exception& e) {
        cerr << "Exception occurred: " << e.what() << endl;
    }
}

int main() {
    runTriangleFiltering();

    return 0;
}
