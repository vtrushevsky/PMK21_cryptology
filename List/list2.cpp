#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdexcept>


class TriangleException : public std::exception {
private:
    std::string message_;

public:
    explicit TriangleException(const std::string& message) : message_(message) {}

    const char* what() const noexcept override {
        return message_.c_str();
    }
};


class Point {
private:
    double x_;
    double y_;

public:
    Point(double x = 0.0, double y = 0.0) : x_(x), y_(y) {}

    double getX() const {
        return x_;
    }

    double getY() const {
        return y_;
    }
};

// Клас трикутника
class Triangle {
private:
    Point a_;
    Point b_;
    Point c_;

public:
    Triangle(const Point& a, const Point& b, const Point& c) : a_(a), b_(b), c_(c) {}

    double calculatePerimeter() const {
        double ab = calculateDistance(a_, b_);
        double bc = calculateDistance(b_, c_);
        double ca = calculateDistance(c_, a_);
        return ab + bc + ca;
    }

    double calculateArea() const {
        double ab = calculateDistance(a_, b_);
        double bc = calculateDistance(b_, c_);
        double ca = calculateDistance(c_, a_);
        double p = (ab + bc + ca) / 2.0;
        return std::sqrt(p * (p - ab) * (p - bc) * (p - ca));
    }

    
    static double calculateDistance(const Point& p1, const Point& p2) {
        double dx = p1.getX() - p2.getX();
        double dy = p1.getY() - p2.getY();
        return std::sqrt(dx * dx + dy * dy);
    }

    friend std::ostream& operator<<(std::ostream& os, const Triangle& triangle) {
        os << "Triangle: (" << triangle.a_.getX() << ", " << triangle.a_.getY() << ") "
            << "(" << triangle.b_.getX() << ", " << triangle.b_.getY() << ") "
            << "(" << triangle.c_.getX() << ", " << triangle.c_.getY() << ")";
        return os;
    }
};


template<typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        explicit Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head_;
    Node* tail_;
    std::size_t size_;

public:
    class Iterator {
    private:
        Node* current_;

    public:
        explicit Iterator(Node* node) : current_(node) {}

        Iterator& operator++() {
            if (current_) {
                current_ = current_->next;
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator old = *this;
            ++(*this);
            return old;
        }

        T& operator*() const {
            return current_->data;
        }

        bool operator==(const Iterator& other) const {
            return current_ == other.current_;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };

    DoublyLinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}

    ~DoublyLinkedList() {
        clear();
    }

    DoublyLinkedList(const DoublyLinkedList& other) : DoublyLinkedList() {
        Node* current = other.head_;
        while (current) {
            pushBack(current->data);
            current = current->next;
        }
    }

    DoublyLinkedList(DoublyLinkedList&& other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }

    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this != &other) {
            clear();
            Node* current = other.head_;
            while (current) {
                pushBack(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    void pushBack(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            head_ = newNode;
            tail_ = newNode;
        }
        else {
            newNode->prev = tail_;
            tail_->next = newNode;
            tail_ = newNode;
        }
        size_++;
    }

    void remove(const Iterator& it) {
        Node* current = it.current_;
        if (!current) {
            throw TriangleException("Invalid iterator");
        }

        if (current == head_) {
            head_ = current->next;
        }
        if (current == tail_) {
            tail_ = current->prev;
        }

        if (current->prev) {
            current->prev->next = current->next;
        }
        if (current->next) {
            current->next->prev = current->prev;
        }

        delete current;
        size_--;
    }

    Iterator begin() const {
        return Iterator(head_);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

    bool isEmpty() const {
        return size_ == 0;
    }

    std::size_t size() const {
        return size_;
    }

    void clear() {
        Node* current = head_;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }

    void sort() {
        if (isEmpty() || size_ == 1) {
            return;
        }

        bool swapped;
        do {
            swapped = false;
            Node* current = head_;
            while (current->next) {
                if (current->data.calculateArea() > current->next->data.calculateArea()) {
                    std::swap(current->data, current->next->data);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }
};


DoublyLinkedList<Triangle> filterTriangles(const DoublyLinkedList<Triangle>& triangles, double minPerimeter, double maxPerimeter) {
    DoublyLinkedList<Triangle> filteredTriangles;

    for (const Triangle& triangle : triangles) {
        double perimeter = triangle.calculatePerimeter();
        if (perimeter >= minPerimeter && perimeter <= maxPerimeter) {
            filteredTriangles.pushBack(triangle);
        }
    }

    return filteredTriangles;
}


DoublyLinkedList<Triangle> readTrianglesFromFile(const std::string& filename) {
    DoublyLinkedList<Triangle> triangles;

    std::ifstream file(filename);
    if (!file) {
        throw TriangleException("Failed to open file");
    }

    double x1, y1, x2, y2, x3, y3;
    while (file >> x1 >> y1 >> x2 >> y2 >> x3 >> y3) {
        Point a(x1, y1);
        Point b(x2, y2);
        Point c(x3, y3);
        Triangle triangle(a, b, c);
        triangles.pushBack(triangle);
    }

    if (file.bad()) {
        throw TriangleException("Error while reading file");
    }

    file.close();

    return triangles;
}


void writeTrianglesToFile(const DoublyLinkedList<Triangle>& triangles, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        throw TriangleException("Failed to create file");
    }

    for (const Triangle& triangle : triangles) {
        file << triangle.calculatePerimeter() << " " << triangle.calculateArea() << "\n";
    }

    if (file.bad()) {
        throw TriangleException("Error while writing to file");
    }

    file.close();
}

int main() {
    try {
        DoublyLinkedList<Triangle> triangles = readTrianglesFromFile("triangles.txt");
        triangles.sort();

        double minPerimeter = 10.0;
        double maxPerimeter = 20.0;
        DoublyLinkedList<Triangle> filteredTriangles = filterTriangles(triangles, minPerimeter, maxPerimeter);

        writeTrianglesToFile(filteredTriangles, "filtered_triangles.txt");

        
        for (const Triangle& triangle : filteredTriangles) {
            std::cout << triangle << "\n";
        }
    }
    catch (const TriangleException& ex) {
        std::cerr << "Exception: " << ex.what() << "\n";
    }

    return 0;
}
