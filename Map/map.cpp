#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

class Owner {
private:
    string name;
    string address;

public:
    Owner(const string& name, const string& address)
        : name(name), address(address) {}

    string getName() const { return name; }
    string getAddress() const { return address; }
};

class Phone {
private:
    string number;
    string manufacturer;
    double price;

public:
    Phone(const string& number, const string& manufacturer, double price)
        : number(number), manufacturer(manufacturer), price(price) {}

    string getNumber() const { return number; }
    string getManufacturer() const { return manufacturer; }
    double getPrice() const { return price; }
    void setNumber(const string& newNumber) { number = newNumber; }
};

void populateDatabaseFromInput(map<Owner, Phone>& database) {
    
}

void writeDatabaseToFile(const map<Owner, Phone>& database, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Failed to open file.");
    }

    for (const auto& entry : database) {
        const Owner& owner = entry.first;
        const Phone& phone = entry.second;
        file << owner.getName() << "," << owner.getAddress() << ","
            << phone.getNumber() << "," << phone.getManufacturer() << ","
            << phone.getPrice() << "\n";
    }

    file.close();
}

vector<Phone> findAndMovePhones(map<Owner, Phone>& database, const string& ownerName) {
    vector<Phone> foundPhones;

    auto it = database.begin();
    while (it != database.end()) {
        if (it->first.getName() == ownerName) {
            foundPhones.push_back(it->second);
            it = database.erase(it);
        }
        else {
            ++it;
        }
    }

    return foundPhones;
}

Owner findOwnerByPhoneNumber(const map<Owner, Phone>& database, const string& phoneNumber) {
    for (const auto& entry : database) {
        if (entry.second.getNumber() == phoneNumber) {
            return entry.first;
        }
    }

    throw runtime_error("Owner not found.");
}

vector<Owner> findOwnersByManufacturerAndPrice(const map<Owner, Phone>& database, const string& manufacturer, double price) {
    vector<Owner> foundOwners;

    for (const auto& entry : database) {
        const Phone& phone = entry.second;
        if (phone.getManufacturer() == manufacturer && phone.getPrice() > price) {
            foundOwners.push_back(entry.first);
        }
    }

    return foundOwners;
}

void changePhoneNumber(map<Owner, Phone>& database, const string& ownerName, const string& newPhoneNumber) {
    for (auto& entry : database) {
        Owner& owner = const_cast<Owner&>(entry.first);
        Phone& phone = entry.second;
        if (owner.getName() == ownerName) {
            phone.setNumber(newPhoneNumber);
            return;
        }
    }

    throw runtime_error("Owner not found.");
}

void calculateStatistics(const map<Owner, Phone>& database, const string& filename) {
    
}

int main() {
    try {
        map<Owner, Phone> database;

        populateDatabaseFromInput(database);

        
        writeDatabaseToFile(database, "database.txt");

        
        vector<Phone> foundPhones = findAndMovePhones(database, "John Smith");

        
        Owner owner = findOwnerByPhoneNumber(database, "123456789");

        
        vector<Owner> foundOwners = findOwnersByManufacturerAndPrice(database, "Apple", 1000.0);

        
        changePhoneNumber(database, "John Smith", "987654321");

        
        calculateStatistics(database, "statistics.txt");

    }
    catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
    }

    return 0;
}
