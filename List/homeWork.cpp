#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iterator>
#include <exception>

using namespace std;

class MyException : public exception {
private:
    char * message;

public:
    MyException(char * msg) : message(msg) {}
    char* what () {
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

// Define a custom iterator for the linked list
template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(T data) : data(data), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // Add a new node to the end of the linked list
    void add(const T& data) {
        Node* newNode = new Node(data);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        size++;
    }

    // Define a custom iterator for the linked list
    class iterator {
    private:
        Node* currentNode;

    public:
        iterator(Node* node) : currentNode(node) {}

        bool operator==(const iterator& other) const {
            return currentNode == other.currentNode;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

        T& operator*() const {
            return currentNode->data;
        }

        iterator& operator++() {
            currentNode = currentNode->next;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        iterator& operator--() {
            currentNode = currentNode->prev;
            return *this;
        }

        iterator operator--(int) {
            iterator temp = *this;
            --(*this);
            return temp;
        }

        friend class DoublyLinkedList;
    };

    // Insert a new node
    void bubbleSort() {
        if (head == nullptr || head->next == nullptr) {
            return;
        }

        bool swapped;
        do {
            swapped = false;
            Node* current = head;
            while (current->next != nullptr) {
                if (current->data < current->next->data) {
                    // Swap the nodes
                    T temp = current->data;
                    current->data = current->
next->data;
current->next->data = temp;
swapped = true;
}
current = current->next;
}
} while (swapped);
}
// Overload the output stream operator to print the linked list
friend ostream& operator << (ostream& os, const DoublyLinkedList<T>& list) {
    if (list.head == nullptr) {
        os << "List is empty";
        return os;
    }

    for (auto it = list.begin(); it != list.end(); ++it) {
        os << *it << " ";
    }

    return os;
}

iterator begin() const {
    return iterator(head);
}

iterator end() const {
    return iterator(nullptr);
}

~DoublyLinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}
};

int main() {
// Create a linked list of triangles
DoublyLinkedList<Triangle<double> > triangles;
ifstream fin;
try {
    cout << "Trying to open a file" << endl;
    fin.open("triangles.txt");
    cout << "Success!" << endl;

    // Read the triangles from the file and add them to the linked list
    double a, b, c;
    while (fin >> a >> b >> c) {
        Triangle<double> triangle(a, b, c);
        triangles.add(triangle);
    }

    // Sort the list of triangles by their area
    triangles.bubbleSort();

    // Print the sorted list of triangles
    cout << "Sorted list of triangles by area:" << endl;
    cout << triangles << endl;

} catch (MyException& me) {
    cout << me.what() << endl;
    cout << "Error. Can not open a file!" << endl;
}
//!!!!!
try {
    ofstream outFile("results.txt");

    if (outFile.fail()) {
        throw MyException("Failed to open output file");
    }

    triangles.bubbleSort();

    // Iterate through the linked list and output each triangle to the console and to the output file
    for (auto triangle : triangles) {
        cout << triangle << endl;
        outFile << triangle << endl;
    }

    outFile.close();
}
catch (MyException& e) {
    cerr << e.what() << endl;
}

return 0;
}
