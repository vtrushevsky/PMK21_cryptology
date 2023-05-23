#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct Book {
    string name;
    double price;
};

struct Bookstore {
    string name;
    vector<Book> books;
};

// Функція для пошуку магазину за назвою
bool searchBookstoreByName(const Bookstore& store, const string& name) {
    return store.name == name;
}

// Функція для обчислення загальної вартості книжок у магазині
double calculateTotalPrice(const Bookstore& store) {
    double total = 0.0;
    for (const auto& book : store.books) {
        total += book.price;
    }
    return total;
}

// Функція для перевірки, чи кількість книжок у магазині більше за задане число
bool hasMoreBooksThan(const Bookstore& store, int quantity) {
    return store.books.size() > quantity;
}

// Функція перевірки наявності книги у двох магазинах і перевірка різниці в ціні
bool hasBookWithLowerPrice(const Bookstore& store1, const Bookstore& store2) {
    for (const auto& book1 : store1.books) {
        for (const auto& book2 : store2.books) {
            if (book1.name == book2.name && book1.price < book2.price) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    ifstream file("../bookstores.txt");
    string line;
    vector<Bookstore> stores;

    while (getline(file, line)) {
        Bookstore store;
        store.name = line;
        while (getline(file, line) && line != "") {
            Book book;
            size_t pos = line.find(", ");
            book.name = line.substr(0, pos);
            book.price = stod(line.substr(pos + 2));
            store.books.push_back(book);
        }
        stores.push_back(store);
    }

    // Пошук магазину за назвою
    string searchName = "Bookstore 2";
    auto it = find_if(stores.begin(), stores.end(), bind(searchBookstoreByName, placeholders::_1, searchName));
    if (it != stores.end()) {
        cout << "Bookstore found: " << it->name << endl;
    } else {
        cout << "Bookstore not found." << endl;
    }

    // Обчислення загальної вартості книжок для знайденого магазину
    if (it != stores.end()) {
        double totalPrice = calculateTotalPrice(*it);
        cout << "Total price of books in " << it->name << ": " << totalPrice << endl;
    }

    // Знаходження магазину, кількість книжок якого більше за задане число
    int quantityThreshold = 5;
    auto foundStore = find_if(stores.begin(), stores.end(), bind(hasMoreBooksThan, placeholders::_1, quantityThreshold));

    if (foundStore != stores.end()) {
        cout << "Store with more than " << quantityThreshold << " books found: " << foundStore->name << endl;
    } else {
        cout << "No store found with more than " << quantityThreshold << " books." << endl;
    }

    // Перевірка для першого і другого магазинів
    int storeIndex1 = 0;
    int storeIndex2 = 1;

    if (hasBookWithLowerPrice(stores[storeIndex1], stores[storeIndex2])) {
        cout << "In store '" << stores[storeIndex1].name << "' there is a book with a lower price compared to store '"
             << stores[storeIndex2].name << "'." << endl;
    } else {
        cout << "There is no book in store '" << stores[storeIndex1].name << "' with a lower price compared to store '"
             << stores[storeIndex2].name << "'." << endl;
    }
    return 0;
}