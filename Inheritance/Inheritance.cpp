#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Product {
protected:
    string countryOfOrigin;
    double price;

public:
    Product(const string& countryOfOrigin, double price)
        : countryOfOrigin(countryOfOrigin), price(price) {
    }

    string getCountryOfOrigin() const {
        return countryOfOrigin;
    }

    double getPrice() const {
        return price;
    }
};

class Toy : public Product {
private:
    string toyName;
    int minAge;
    int maxAge;

public:
    Toy(const string& countryOfOrigin, double price, const string& toyName, int minAge, int maxAge)
        : Product(countryOfOrigin, price), toyName(toyName), minAge(minAge), maxAge(maxAge) {
    }

    string getToyName() const {
        return toyName;
    }

    int getMinAge() const {
        return minAge;
    }

    int getMaxAge() const {
        return maxAge;
    }
};

vector<Toy> filterToysByAgeAndPrice(const vector<Toy>& toys, int minAge, int maxAge, double minPrice, double maxPrice) {
    vector<Toy> filteredToys;

    for (const auto& toy : toys) {
        if (toy.getMinAge() <= maxAge && toy.getMaxAge() >= minAge && toy.getPrice() >= minPrice && toy.getPrice() <= maxPrice) {
            filteredToys.push_back(toy);
        }
    }

    return filteredToys;
}

int main() {
    vector<Toy> toys;

    toys.push_back(Toy("US", 10.0, "Teddy Bear", 1, 3));
    toys.push_back(Toy("China", 15.0, "Building Blocks", 3, 6));
    toys.push_back(Toy("Germany", 20.0, "Puzzle", 5, 10));
    toys.push_back(Toy("US", 12.0, "Doll", 2, 4));
    toys.push_back(Toy("China", 18.0, "Remote Control Car", 6, 12));
    toys.push_back(Toy("Germany", 25.0, "Board Game", 8, 14));

    int minAge = 3;
    int maxAge = 10;
    double minPrice = 10.0;
    double maxPrice = 20.0;

    vector<Toy> filteredToys = filterToysByAgeAndPrice(toys, minAge, maxAge, minPrice, maxPrice);

    for (const auto& toy : filteredToys) {
        cout << "Toy Name: " << toy.getToyName() << endl;
        cout << "Country of Origin: " << toy.getCountryOfOrigin() << endl;
        cout << "Price: $" << toy.getPrice() << endl;
        cout << endl;
    }

    return 0;
}
