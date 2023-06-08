#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>
#include <cassert>
#include <utility>
#include <string>

using namespace std;

class Book {
public:
    string title;
    string author;
    double price;

    Book(const string& title, const string& author, double price) {
        this->title = title;
        this->author = author;
        this->price = price;
    }
};

class Bookstore {
public:
    string name;
    vector<Book> books;

    Bookstore(const string& name) {
        this->name = name;
    }

    void addBook(const Book& book) {
        books.push_back(book);
    }

    double calculateTotalPrice() const {
        return accumulate(books.begin(), books.end(), 0.0, [](double sum, const Book& book) {
            return sum + book.price;
            });
    }

    vector<Book> findBooksByAuthor(const string& author) const {
        vector<Book> result;
        copy_if(books.begin(), books.end(), back_inserter(result), [&](const Book& book) {
            return book.author == author;
            });
        return result;
    }

    int countBooksByAuthorInPriceRange(const string& author, double minPrice, double maxPrice) const {
        return count_if(books.begin(), books.end(), [&](const Book& book) {
            return book.author == author && book.price >= minPrice && book.price <= maxPrice;
            });
    }

    pair<Book, Book> findMinMaxPricedBooks() const {
        assert(!books.empty());

        auto minMaxPair = minmax_element(books.begin(), books.end(), [](const Book& book1, const Book& book2) {
            return book1.price < book2.price;
            });

        return make_pair(*minMaxPair.first, *minMaxPair.second);
    }

    bool hasMoreBooksThan(int count) const {
        return books.size() > count;
    }

    bool hasAdjacentBooksWithDoublePrice() const {
        if (books.size() < 2) {
            return false;
        }

        for (size_t i = 0; i < books.size() - 1; i++) {
            if (books[i].price * 2 == books[i + 1].price) {
                return true;
            }
        }

        return false;
    }

    bool hasSameBookWithLowerPrice(const Bookstore& otherStore) const {
        for (const Book& book : books) {
            auto it = find_if(otherStore.books.begin(), otherStore.books.end(), [&](const Book& otherBook) {
                return book.title == otherBook.title && book.price < otherBook.price;
                });

            if (it != otherStore.books.end()) {
                return true;
            }
        }

        return false;
    }

    pair<Book, Book> findFirstBooksPairWithDoublePrice(const Bookstore& otherStore) const {
        for (const Book& book : books) {
            auto it = find_if(otherStore.books.begin(), otherStore.books.end(), [&](const Book& otherBook) {
                return book.price * 2 == otherBook.price;
                });

            if (it != otherStore.books.end()) {
                return make_pair(book, *it);
            }
        }

        return make_pair(Book("", "", 0.0), Book("", "", 0.0));
    }

    bool areFirstThreeBooksSubsequenceOf(const Bookstore& otherStore) const {
        if (books.size() < 3 || otherStore.books.size() < 3) {
            return false;
        }

        return equal(books.begin(), books.begin() + 3, otherStore.books.begin(), [](const Book& book1, const Book& book2) {
            return book1.title == book2.title;
            });
    }
};

Bookstore findBookstoreByName(const vector<Bookstore>& bookstores, const string& name) {
    auto it = find_if(bookstores.begin(), bookstores.end(), [&](const Bookstore& bookstore) {
        return bookstore.name == name;
        });

    if (it != bookstores.end()) {
        return *it;
    }

    return Bookstore("");
}

void writeBooksToFile(const vector<Book>& books, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        copy(books.begin(), books.end(), ostream_iterator<Book>(file, "\n"));
        file.close();
    }
}

int main() {
    vector<Bookstore> bookstores;
    string filename = "bookstores.txt";

    ifstream file(filename);
    if (file.is_open()) {
        string line;

        while (getline(file, line)) {
            if (line.empty()) {
                continue;
            }

            Bookstore bookstore(line);

            while (getline(file, line)) {
                if (line.empty()) {
                    break;
                }

                string title, author;
                double price;

                istringstream iss(line);
                iss >> title >> author >> price;

                Book book(title, author, price);
                bookstore.addBook(book);
            }

            bookstores.push_back(bookstore);
        }

        file.close();
    }

    string searchStoreName = "Bookstore A";
    Bookstore foundStore = findBookstoreByName(bookstores, searchStoreName);

    double totalPrice = foundStore.calculateTotalPrice();

    string searchAuthor = "John Smith";
    vector<Book> booksByAuthor = foundStore.findBooksByAuthor(searchAuthor);
    writeBooksToFile(booksByAuthor, "books_by_author.txt");

    double minPrice = 10.0;
    double maxPrice = 50.0;
    int bookCountInPriceRange = foundStore.countBooksByAuthorInPriceRange(searchAuthor, minPrice, maxPrice);

    pair<Book, Book> minMaxPricedBooks = foundStore.findMinMaxPricedBooks();

    int minBookCount = 10;
    auto it = find_if(bookstores.begin(), bookstores.end(), [&](const Bookstore& bookstore) {
        return bookstore.hasMoreBooksThan(minBookCount);
        });

    Bookstore storeWithMoreBooks = *it;

    bool hasAdjacentBooksWithDoublePrice = foundStore.hasAdjacentBooksWithDoublePrice();

    Bookstore otherStore = bookstores[1];
    bool hasSameBookWithLowerPrice = foundStore.hasSameBookWithLowerPrice(otherStore);

    pair<Book, Book> firstBooksPairWithDoublePrice = foundStore.findFirstBooksPairWithDoublePrice(otherStore);

    bool areFirstThreeBooksSubsequence = foundStore.areFirstThreeBooksSubsequenceOf(otherStore);

    return 0;
}
