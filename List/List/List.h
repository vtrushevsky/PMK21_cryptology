#include <fstream>
#include <iostream>

using namespace std;

template <typename T>
struct Element {
    T value;
    Element<T> *next;
    Element(T val): value(val), next(nullptr) {}
};

template <typename T>
class List {
    Element<T>* head;
    Element<T>* tail;
    size_t size;


public:
    class Iterator {
    private:
        Element<T>* current;

    public:
        Iterator(Element<T>* element) : current(element) {}

        T& operator*() const {
            return current->value;
        }
        Iterator& operator++() {
            if (current == nullptr) {
                throw out_of_range("Out of range");
            }
            else {
                current = current->next;
            }
            return *this;
        }
        bool operator==(const Iterator& other) const {
            return current == other.current;

        }
        bool operator!=(const Iterator& other) const {
            return current != other.current;

        }

        friend class List;
    };

    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

    Iterator find(const T& value) {
        for (auto it = begin(); it != end(); ++it) {
            if (value == *it) {
                return it;
            }
        }
        return end();
    }
    bool erase(const Iterator& pos) {

        if (pos == end()) {
            return false;
        }
        Element<T>* temp = pos.current;

        if (head == temp) {
            head = head->next;
        }
        else {

            Element<T>* prev_el = head;
            while (prev_el->next != temp) {
                prev_el = prev_el->next;
            }
            prev_el->next = temp->next;
            if (temp == tail) {
                tail == prev_el;
            }

        }
        delete temp;
        size--;

        return true;
    }

    List(const List& other) : head(nullptr), tail(nullptr), size(0) {
        for (const auto& el : other) {
            push_back(el);
        }
    }

    List(List&& other) noexcept : head(other.head), tail(other.tail), size(other.size)  {
        other.head = nullptr;
        other.tail = nullptr;
    }

    friend ostream& operator <<(ostream& os, const List& list) {
        for (const auto& el : list) {
            os << el << " ";
        }

        cout << endl;

        return os;
    }

    List() :
            head(nullptr),
            tail(nullptr),
            size(0)
    {

    }

    bool isEmpty() {
        bool result;
        result = head == nullptr;
        return result;
    }

    void add(T valueToAdd) {
        Element<T>* newElement = new Element<T>(valueToAdd);
        if (head != nullptr) {
            tail->next = newElement;
            tail = tail->next;
        }
        else {
            head = newElement;
            tail = newElement;
        }
        size++;
    }

};