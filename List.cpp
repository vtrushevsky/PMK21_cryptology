#include "List.h"
#include <fstream>
using namespace std;


template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), sz(0) {}

template <typename T>
List<T>::List(const List& other) : head(nullptr), tail(nullptr), sz(0) {
        //викликається оператор копіювання
        Triangle<T>* current = other.head;
        while (current != nullptr) {
            add(current->side_1, current->side_2, current->side_3);
            current = current->next;
        }
    }

template <typename T>
List<T>::List(List&& other) noexcept : head(nullptr), tail(nullptr), sz(0) {
        //викликається оператор переміщення
        head = other.head;
        tail = other.tail;
        sz = other.sz;
        other.head = nullptr;
        other.tail = nullptr;
        other.sz = 0;
    }

template <typename T>
List<T>& List<T>::operator=(const List& other) {
        if (this != &other) {
            clear();

            Triangle<T>* current = other.head;
            while (current != nullptr) {
                add(current->side_1, current->side_2, current->side_3);
                current = current->next;
            }
        }
        return *this;
    }

template <typename T>
List<T>& List<T>::operator=(List && other) noexcept {
        if (this != &other) {
            clear();

            head = other.head;
            tail = other.tail;
            sz = other.sz;
            other.head = nullptr;
            other.tail = nullptr;
            other.sz = 0;
        }
        return *this;
    }


template <typename T>
List<T>::~List()
    {
        clear();
    }
template <typename T>
Triangle<T>* List<T>::getHead() const {
    return head;
}

template <typename T>
void List<T>::filter(bool (*filterFunction)(const Triangle<T>&)) {
    Triangle<T>* current = head;
    Triangle<T>* prev = nullptr;

    while (current != nullptr) {
        if (!filterFunction(*current)) {
            if (prev == nullptr) {
                head = current->next;
            }
            else {
                prev->next = current->next;
            }
            Triangle<T>* temp = current;
            current = current->next;
            delete temp;
            sz--;
        }
        else {
            prev = current;
            current = current->next;
        }
    }

    if (prev == nullptr) {
        tail = nullptr;
    }
    else {
        tail = prev;
    }
    };

template <typename T>
bool List<T>::remove(Triangle<T>* triangle_to_remove)
{
    if (triangle_to_remove == nullptr || head == nullptr)
    {
        return false;
    }

    if (triangle_to_remove == head)
    {
        head = head->next;
    }
    else
    {
        Triangle<T>* current = head;
        while (current->next != triangle_to_remove)
        {
            current = current->next;
            if (current == nullptr)
            {
                return false;
            }
        }
        current->next = triangle_to_remove->next;

        if (triangle_to_remove == tail)
        {
            tail = current;
        }
    }

    delete triangle_to_remove;
    sz--;
    return true;
}

template <typename T>
void List<T>::add(T side_1, T side_2, T side_3)
{
    Triangle<T>* new_triangle = new Triangle<T>(side_1, side_2, side_3);

    if (head == nullptr)
    {
        head = new_triangle;
        tail = new_triangle;
    }
    else
    {
        tail->next = new_triangle;
        tail = new_triangle;
    }
    sz++;
}


template <typename T>
Triangle<T>* List<T>::find(T side_1, T side_2, T side_3)
{
    Triangle<T>* current = head;
    while (current != nullptr) {
        if (current->side_1 == side_1 && current->side_2 == side_2 && current->side_3 == side_3) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}


template <typename T>
void List<T>::writeToFile(const string& filename) {
    ofstream out(filename);
    Triangle<T>* current = head;
    while (current != nullptr) {
        out << current->triangle_area() << " " << current->getPerimeter() << endl;
        current = current->next;
    }
    out.close();
}


template <typename T>
void List<T>::filterTriangles(bool (*filterFunction)(const Triangle<T>&), const string& filename) {
    List<T> filteredList;
    Triangle<T>* current = head;

    while (current != nullptr) {
        if (filterFunction(*current)) {
            filteredList.add(current->side_1, current->side_2, current->side_3);
        }
        current = current->next;
    }

    filteredList.writeToFile(filename);
}

template <typename T>
bool List<T>::empty() const { return head == nullptr; }

template <typename T>
size_t List<T>::size() const { return sz; }




template <typename T>
void List<T>::print(ostream& os) const
{
    Triangle<T>* current = head;
    while (current != nullptr) {
        os << "Side 1: " << current->side_1 << endl << "Side 2: " << current->side_2 << endl << "Side 3: " << current->side_3 << endl;
        current = current->next;
    }
    os << endl;
}

template <typename T>
void List<T>::clear() {
    Triangle<T>* current = head;
    while (current != nullptr)
    {
        Triangle<T>* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    sz = 0;
};
