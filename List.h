#pragma once
#include "Triangle.h"
#include <fstream>
using namespace std;


template <typename T>
class List
{
public:
    List();
    List(const List& other);
    List(List&& other) noexcept;
    List& operator=(const List& other);
    List& operator=(List&& other) noexcept;
    ~List();

    bool remove(Triangle<T>* triangle_to_remove);
    void add(T side_1, T side_2, T side_3);
    Triangle<T>* find(T side_1, T side_2, T side_3);
    void writeToFile(const string& filename);
    void filterTriangles(bool (*filterFunction)(const Triangle<T>&), const string& filename);
    bool empty() const;
    size_t size() const;
    void print(ostream& os) const;
    void clear();

    friend ostream& operator<<(ostream& os, const List<T>& list)
    {
        Triangle<T>* current = list.head;
        while (current != nullptr) {
            os << "Side 1: " << current->side_1 << ", Side 2: " << current->side_2 << ", Side 3: " << current->side_3 << endl;
            current = current->next;
        }
        return os;
    }
    Triangle<T>* getHead() const;
    void filter(bool (*filterFunction)(const Triangle<T>&));

private:
    Triangle<T>* head;
    Triangle<T>* tail;
    size_t sz;
};

template <typename T>
ostream& operator<<(ostream& os, const List<T>& list);

template <typename T>
ostream& operator<<(ostream& os, const List<T>& list)
{
    Triangle<T>* current = list.head;
    while (current != nullptr) {
        os << "Side 1: " << current->side_1 << ", Side 2: " << current->side_2 << ", Side 3: " << current->side_3 << endl;
        current = current->next;
    }
    return os;
}

