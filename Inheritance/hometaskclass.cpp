#include <iostream>
#include <vector>


class Product {
private:
    std::string countryCode; // код країни-виробника
    double price; // ціна товару
public:
    Product(std::string countryCode, double price) : countryCode(countryCode), price(price) {}
    std::string getCountryCode() { return countryCode; }
    double getPrice() { return price; }
};

class Toy : public Product {
private:
    std::string name; // назва іграшки
    int minAge; // мінімальний вік для використання
    int maxAge; // максимальний вік для використання
public:
    Toy(std::string countryCode, double price, std::string name, int minAge, int maxAge)
        : Product(countryCode, price), name(name), minAge(minAge), maxAge(maxAge) {}
    std::string getName() { return name; }
    int getMinAge() { return minAge; }
    int getMaxAge() { return maxAge; }
};


int main() {
    std::vector<Toy> toys{
        Toy("US", 10.99, "Teddy Bear", 2, 6),
        Toy("CN", 15.99, "Lego Set", 5, 12),
        Toy("JP", 24.99, "Remote Control Car", 8, 14),
        Toy("FR", 8.99, "Puzzle", 4, 8),
        Toy("US", 29.99, "Video Game", 10, 18),
        Toy("CN", 19.99, "Doll", 3, 7)
    };

    // Межі для віку та ціни
    int minAge = 5;
    int maxAge = 7;
    double minPrice = 10.00;
    double maxPrice = 20.00;

    // Виводимо іграшки, які задовольняють критерії
    for (Toy& toy : toys) {
        if (toy.getMinAge() <= minAge && toy.getMaxAge() >= maxAge
            && toy.getPrice() >= minPrice && toy.getPrice() <= maxPrice) {
            std::cout << "- " << toy.getName() << ", made in " << toy.getCountryCode() << std::endl;
        }
    }

    std::cout << std::endl;

    // Перевірка коду країни-виробника
    std::string countryCodeToCheck = "US";
    std::cout << "country code : " << countryCodeToCheck << std::endl;
    for (Toy& toy : toys) {
        if (toy.getCountryCode() == countryCodeToCheck) {
            std::cout << toy.getName() << " is made in " << countryCodeToCheck << std::endl;
        }
    }

    return 0;
}