#include <iostream>
#include <fstream>
#include "Triangle.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
using namespace std;

class MyException: public std::exception{
public:
    MyException(const string& message): message_(message){};
    const char* what() const noexcept override{
        return  message_.c_str();
    }
private:
    string message_;
};

template<typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
    };
    Node* head;
    Node* tail;

public:
    class Iterator {
    private:
        Node* node;
    public:
        Iterator(Node* node) : node(node) {}
        T& operator*() const { return node->data; }
        Iterator& operator++() { node = node->next; return *this; }
        Iterator& operator--() { node = node->prev; return *this; }
        bool operator!=(const Iterator& other) const { return node != other.node; }
        bool operator==(const Iterator& other) const { return node == other.node; }
        friend class DoublyLinkedList;
    };

    DoublyLinkedList() {
        head = NULL;
        tail = NULL;
    }
    void insert(T data) {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = NULL;
        newNode->prev = NULL;
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this != &other) {
            // тут відбувається перекидування з одного списку елемінтів в інший, тобто в список this
            for (auto it = begin(); it !=end(); ++it){
                for (auto el: other){
                    it = el;
                    other.erase(el);
                    break;
                }
            }
        }
        return *this;
    }
    DoublyLinkedList(const DoublyLinkedList& other) {
        head = other.head;
        tail = other.tail;
    }


    friend std::ostream& operator<< (std::ostream& os, const DoublyLinkedList<T>& list) {
        // Range base loop
        for (const auto& el : list) {
            // тут спрацьовую оператор виведення із файлу Triangle
            os << el << " ";
        }
        return os;
    }


    ~DoublyLinkedList() {
        while (head != nullptr) {
            Node* node = head;
            head = head->next;
            delete node;
        }
    }
    void erase(Iterator pos) {
        if (pos == end()) {
            return;
        }

        Node *node = pos.node;

        if (node == head) {
            head = head->next;
        } else {
            Node *prev = head;
            while (prev->next != node) {
                prev = prev->next;
            }
            prev->next = node->next;
            if (node == tail) {
                tail = prev;
            }
        }
        delete node;
    }
    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }

    Iterator find(const T& data) const {

        for (Iterator it = begin(); it != end(); ++it) {
            //  Triangle::operator== ( const Triangle &other) у файлі  triangle
            if (data == it.node->data) {
                return it;
            }
        }
        return NULL;
    }
    bool sort(){
            for (Iterator it = begin(); it != end(); ++it) {
                auto next = ++it;
                if (*it > *next and next != NULL) {
                    Iterator temp = it;
                    it.node->data = next.node->data;
                    next.node->data = temp.node->data;
                }
            }
        return true;
    }
    DoublyLinkedList  filterByArea(int area, DoublyLinkedList<T>& list){
        DoublyLinkedList<Triangle> new_list;
        for (Iterator it = list.begin(); it != list.end(); ++it) {
            ///  спрацьовує operator > (int area)  у файлі  triangle
            if (*it > area and it != NULL){
                new_list.insert(*it);
                erase(it);
            }
        }
        return new_list;
    }
};

//bool write_to_file(const DoublyLinkedList<Triangle>& list, ofstream& file_to_write) {
//    if (!file_to_write.is_open()) {
//        cerr << "Error: file not open for writing\n";
//        return false;
//    }
//
//    for (const auto& it : list) {
//        file_to_write << it << endl;
//        if (!file_to_write) {
//            cerr << "Error: write failed\n";
//            return false;
//        }
//    }
//
//    return true;
//}

//DoublyLinkedList<Triangle>& read_from_file(ifstream& file){
//    DoublyLinkedList<Triangle> *db;
//    while (!file.eof()){
//        int x,y,x2,y2,x3,y3;
//        file >> x;
//        file >> y;
//        file >> x2;
//        file >> y2;
//        file >> x3;
//        file >> y3;
//
//        auto triangle= *new Triangle;
//        triangle.setPoint(x,y);
//        triangle.setPoint(x2,y2);
//        triangle.setPoint(x3,y3);
//
//        db->insert(triangle);
//    }
//    file.close();
//    return *db;
//}
TEST_CASE("Main") {

//    DoublyLinkedList<Triangle> db;
//    DoublyLinkedList<Triangle> db2;
//
//
//    Triangle triangles[3];
//
//    ifstream file("/home/dmytro/CLionProjects/untitled1/triangles_coords");
//    ofstream file_to_write("/home/dmytro/CLionProjects/untitled1/text_written");
//    if (!file.is_open()) {
//        cout << "File for read cannot be open";
//    }
//    if (!file_to_write.is_open()) {
//        cout << "File for read cannot be open";
//    }
/// read data from file
//    int i = 0;
//    while (!file.eof()){
//        int x,y,x2,y2,x3,y3;
//        file >> x;
//        file >> y;
//        file >> x2;
//        file >> y2;
//        file >> x3;
//        file >> y3;
//        triangles[i] = *new Triangle;
//        triangles[i].setPoint(x,y);
//        triangles[i].setPoint(x2,y2);
//        triangles[i].setPoint(x3,y3);
//        db.insert(triangles[i]);
//        i++;
//    }
//    file.close();


    /// function find
//   auto founded = db.find(triangles[1]);
//    cout << *founded;
    /// sort
//    db.sort();
/// erase
//    db.erase(founded);
/// write to file but unfortunately doesn't work
// write_to_file(db, file_to_write);
//
/// cout  all triangles and theirs points
//    cout << db << endl;

    /// тут спрацьовує оператор  DoublyLinkedList& operator=(const DoublyLinkedList& other)
//    DoublyLinkedList<Triangle> db3 = db.filterByArea(1, db);
//    cout << db3;
/// base ranged  loop
//    for(auto el : db3){
//        cout << el << endl;
//    }
}

TEST_CASE("Check found and erase functions"){
    DoublyLinkedList<Triangle> db;
    Triangle *tr = new Triangle;

    db.insert(*tr);
    auto found = db.find(*tr);
    cout << *found << endl;
    db.erase(found);

    cout << "After deleting  >>>>" << db << endl;

}

TEST_CASE("Check read data from file and filter by area"){
    DoublyLinkedList<Triangle> db;

    ifstream file("/home/dmytro/CLionProjects/untitled1/triangles_coords");

    if (!file.is_open()) {
        throw MyException("Cannnot open file");
    }
    while (!file.eof()){
        int x,y,x2,y2,x3,y3;
        file >> x;
        file >> y;
        file >> x2;
        file >> y2;
        file >> x3;
        file >> y3;

        auto triangle= *new Triangle;
        triangle.setPoint(x,y);
        triangle.setPoint(x2,y2);
        triangle.setPoint(x3,y3);

        db.insert(triangle);
    }
    file.close();

    for (auto el : db){
        cout << "Test 2 >>>>>" << el << endl;
    }

    DoublyLinkedList<Triangle> db3 = db.filterByArea(1, db);
    for (auto el : db3){
        cout << "Test 3 >>>>>" << el << endl;
    }

    // сортую за спаданням площ , потім помітив що за зростанням але вже не перероблював бо там майже аналогічно
    db3.sort();
    for (auto el : db3){
        cout << "Test 4 >>>>>" << el << endl;
    }

}
int main(int argc, char** argv) {
    doctest::Context context;


    context.addFilter("test-case-exclude", "*math*"); // exclude test cases with "math" in their name
    context.setOption("abort-after", 5);              // stop test execution after 5 failed assertions
    context.setOption("order-by", "name");            // sort the test cases by their name

    context.applyCommandLine(argc, argv);

    // overrides
    context.setOption("no-breaks", true);             // don't break in the debugger when assertions fail

    int res = context.run(); // run

    if(context.shouldExit()) // important - query flags (and --exit) rely on the user doing this
        return res;          // propagate the result of the tests

    int client_stuff_return_code = 0;



    return res + client_stuff_return_code; // the result from doctest is propagated here as well

}
