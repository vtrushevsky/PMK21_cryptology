#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <windows.h>

using namespace std;


class Book {
public:
    string title;
    string author;
    double price;

    Book(const string& _title, const string& _author, double _price)
        : title(_title), author(_author), price(_price) {}
};


class Bookstore {
public:
    string name;
    vector<Book> books;

    Bookstore(const string& _name) : name(_name) {}

    
    bool findByName(const string& storeName) const {
        return name == storeName;
    }

    
    double calculateTotalPrice() const {
        double totalPrice = 0.0;
        for (const Book& book : books) {
            totalPrice += book.price;
        }
        return totalPrice;
    }

    
    void findBooksByAuthor(const string& author, const string& filename) const {
        ofstream outputFile(filename);
        if (!outputFile.is_open()) {
            cout << "�� ������� ������� ���� " << filename << endl;
            return;
        }

        for (const Book& book : books) {
            if (book.author == author) {
                outputFile << book.title << ", " << book.price << endl;
            }
        }

        outputFile.close();
    }

    
    int countBooksByAuthorInPriceRange(const string& author, double minPrice, double maxPrice) const {
        int count = 0;
        for (const Book& book : books) {
            if (book.author == author && book.price >= minPrice && book.price <= maxPrice) {
                count++;
            }
        }
        return count;
    }

    
    void printMinMaxPriceBooks() const {
        auto minPriceBook = min_element(books.begin(), books.end(), [](const Book& b1, const Book& b2) {
            return b1.price < b2.price;
            });

        auto maxPriceBook = max_element(books.begin(), books.end(), [](const Book& b1, const Book& b2) {
            return b1.price < b2.price;
            });

        cout << "����� � ��������� �������: " << minPriceBook->title << ", " << minPriceBook->author << ", " << minPriceBook->price << endl;
        cout << "����� � ������������ �������: " << maxPriceBook->title << ", " << maxPriceBook->author << ", " << maxPriceBook->price << endl;
    }

    
    bool findStoreWithBookCountGreaterThan(int count) const {
        return books.size() > count;
    }

    
    bool hasNeighborBooksWithDoublePrice(const string& storeName) const {
        for (size_t i = 0; i < books.size() - 1; i++) {
            if (books[i].price * 2 == books[i + 1].price) {
                return true;
            }
        }
        return false;
    }

    
    bool hasBookWithLowerPriceInOtherStore(const Bookstore& otherStore) const {
        for (const Book& book : books) {
            auto it = find_if(otherStore.books.begin(), otherStore.books.end(), [&](const Book& otherBook) {
                return otherBook.title == book.title && otherBook.price < book.price;
                });

            if (it != otherStore.books.end()) {
                return true;
            }
        }
        return false;
    }

    
    pair<Book, Book> findFirstPairWithDoublePrice() const {
        for (size_t i = 0; i < books.size() - 1; i++) {
            if (books[i].price * 2 == books[i + 1].price) {
                return make_pair(books[i], books[i + 1]);
            }
        }
        return make_pair(Book("", "", 0.0), Book("", "", 0.0)); 
    }

    
    bool isFirstThreeBooksSubsequenceOfOtherStore(const Bookstore& otherStore) const {
        if (books.size() < 3 || otherStore.books.size() < 3) {
            return false;
        }

        return std::equal(books.begin(), books.begin() + 3, otherStore.books.begin());

    }
};

int main() {
    SetConsoleOutputCP(1251);

    Bookstore store1("������� 1");
    store1.books.push_back(Book("����� 1", "����� 1", 10.0));
    store1.books.push_back(Book("����� 2", "����� 2", 15.0));
    store1.books.push_back(Book("����� 3", "����� 1", 20.0));

    Bookstore store2("������� 2");
    store2.books.push_back(Book("����� 4", "����� 3", 12.0));
    store2.books.push_back(Book("����� 5", "����� 1", 18.0));
    store2.books.push_back(Book("����� 6", "����� 2", 25.0));

    
    string searchStoreName = "������� 2";
    if (store1.findByName(searchStoreName)) {
        cout << "������� ��������: " << searchStoreName << endl;

        
        double totalPrice = store1.calculateTotalPrice();
        cout << "�������� ������� ������ � �������: " << totalPrice << endl;

        
        string author = "����� 1";
        string filename = "books_by_author.txt";
        store1.findBooksByAuthor(author, filename);
        cout << "����� ������ " << author << " �������� �� �������� � ���� " << filename << endl;

        
        double minPrice = 10.0;
        double maxPrice = 20.0;
        int count = store1.countBooksByAuthorInPriceRange(author, minPrice, maxPrice);
        cout << "ʳ������ ������ ������ " << author << " � ������� ��� [" << minPrice << ", " << maxPrice << "]: " << count << endl;

        
        store1.printMinMaxPriceBooks();

        
        int bookCount = 2;
        if (store1.findStoreWithBookCountGreaterThan(bookCount)) {
            cout << "ʳ������ ������ � ������� " << store1.name << " ����� �� " << bookCount << endl;
        }

       
        if (store1.hasNeighborBooksWithDoublePrice(store1.name)) {
            cout << "� ������� " << store1.name << " � ���� ������ ������ � ������� ����������" << endl;
        }

        
        if (store1.hasBookWithLowerPriceInOtherStore(store2)) {
            cout << "� ������� " << store1.name << " � ����� � ������ �����, �� � ������� " << store2.name << endl;
        }

        
        pair<Book, Book> doublePricePair = store1.findFirstPairWithDoublePrice();
        if (doublePricePair.first.title != "" && doublePricePair.second.title != "") {
            cout << "�������� ���� ������: " << doublePricePair.first.title << ", " << doublePricePair.second.title << endl;
        }

        
        if (store1.isFirstThreeBooksSubsequenceOfOtherStore(store2)) {
            cout << "����� ��� ����� ��������� ������������� � ������� " << store2.name << endl;
        }
    }
    else {
        cout << "������� �� ��������: " << searchStoreName << endl;
    }

    return 0;
}
