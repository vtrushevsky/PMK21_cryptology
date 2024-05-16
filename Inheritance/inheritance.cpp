#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

class Product {
protected:
    string countryCode;
    double price;

public:
    Product(const string& countryCode, double price) : countryCode(countryCode), price(price) {}

    string getCountryCode() const {
        return countryCode;
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
    Toy(const string& countryCode, double price, const string& toyName, int minAge, int maxAge)
        : Product(countryCode, price), toyName(toyName), minAge(minAge), maxAge(maxAge) {}

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

int main() {
    SetConsoleOutputCP(1251);
    
    vector<Toy> toys;
    toys.push_back(Toy("US", 10.99, "LEGO Set", 6, 12));
    toys.push_back(Toy("CN", 5.99, "Stuffed Animal", 3, 6));
    toys.push_back(Toy("JP", 19.99, "Action Figure", 8, 14));
    toys.push_back(Toy("UK", 14.99, "Board Game", 10, 99));
    toys.push_back(Toy("US", 9.99, "Puzzle", 4, 99));

    
    int minAge, maxAge;
    double minPrice, maxPrice;

    cout << "������ ������ ������� ��� ������ ������� (��������� �� ������������ ��): ";
    cin >> minAge >> maxAge;

    cout << "������ ��� ���� ��� ������ ������� (�������� �� ����������� ����): ";
    cin >> minPrice >> maxPrice;

    
    cout << "������ �������������� �������:" << endl;
    for (const Toy& toy : toys) {
        if (toy.getMinAge() >= minAge && toy.getMaxAge() <= maxAge &&
            toy.getPrice() >= minPrice && toy.getPrice() <= maxPrice) {
            cout << "�����: " << toy.getToyName() << endl;
            cout << "³��� ���: " << toy.getMinAge() << " - " << toy.getMaxAge() << endl;
            cout << "ֳ��: " << toy.getPrice() << endl;
            cout << "��� �����-���������: " << toy.getCountryCode() << endl;
            cout << "-----------------------" << endl;
        }
    }

    return 0;
}
