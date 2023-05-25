#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Holder {
private:
    string fullName;
    string address;
    int number;

public:
    Holder(const string& fullName, const string& address, int number)
        : fullName(fullName), address(address), number(number) {}

    string getFullName() const { return fullName; }
    string getAddress() const { return address; }
    int getNumber() const { return number; }
    void setNumber(int newNumber) { number = newNumber; }

    bool operator<(const Holder& other) const {
        return number < other.number;
    }

    bool operator>(const Holder& other) const {
        return number > other.number;
    }
};

class Phone {
private:
    double price;
    string model;

public:
    Phone() : price(0.0), model("") {}
    Phone(double price, const string& model) : price(price), model(model) {}

    double getPrice() const { return price; }
    string getModel() const { return model; }
};

// Search for an owner by number
Holder searchByNumber(const map<Holder, Phone>& database, int number) {
    for (const auto& entry : database) {
        const Holder& holder = entry.first;
        if (holder.getNumber() == number) {
            return holder;
        }
    }
    // Return a default-constructed Holder object if not found
    return Holder("", "", 0);
}

// Search for an owner by address
Holder searchByAddress(const map<Holder, Phone>& database, const string& address) {
    for (const auto& entry : database) {
        const Holder& holder = entry.first;
        if (holder.getAddress() == address) {
            return holder;
        }
    }
    // Return a default-constructed Holder object if not found
    return Holder("", "", 0);
}

// Function to populate the database from a file
void populateDatabaseFromFile(map<Holder, Phone>& database, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            // Parse each line and extract the relevant information
            stringstream ss(line);
            string fullName, address, model;
            int number;
            double price;

            if (ss >> fullName >> address >> number >> price >> model) {
                // Create Holder and Phone objects and add them to the database
                database[Holder(fullName, address, number)] = Phone(price, model);
            }
        }
        file.close();
        cout << "Database populated from file: " << filename << endl;
    } else {
        cout << "Error: Unable to open file for reading: " << filename << endl;
    }
}

// Function to populate the database from keyboard input
void populateDatabaseFromKeyboard(map<Holder, Phone>& database) {
    cout << "Enter the number of entries to add: ";
    int numEntries;
    cin >> numEntries;
    cin.ignore();  // Ignore the newline character after reading an integer

    for (int i = 0; i < numEntries; i++) {
        string fullName, address, model;
        int number;
        double price;

        cout << "Enter full name: ";
        getline(cin, fullName);
        cout << "Enter address: ";
        getline(cin, address);
        cout << "Enter number: ";
        cin >> number;
        cout << "Enter price: ";
        cin >> price;
        cin.ignore();  // Ignore the newline character after reading a double
        cout << "Enter model: ";
        getline(cin, model);

        // Create Holder and Phone objects and add them to the database
        database[Holder(fullName, address, number)] = Phone(price, model);
    }

    cout << "Database populated from keyboard input." << endl;
}



void changePhoneNumber(map<Holder, Phone>& database, const string& fullName, int newNumber) {
    for (auto& entry : database) {
        Holder& holder = const_cast<Holder&>(entry.first);
        if (holder.getFullName() == fullName) {
            holder.setNumber(newNumber);
            cout << "The phone number for holder " << holder.getFullName() << " has been changed to " << newNumber << endl;
            return;
        }
    }
    cout << "Phone number for holder " << fullName << " not found in the database." << endl;
}

void computeStatistics(const map<Holder, Phone>& database, const string& filename) {
    map<string, int> streetOwnersCount;
    map<string, double> streetTotalPrice;

    for (const auto& entry : database) {
        const Holder& holder = entry.first;
        const Phone& phone = entry.second;

        string street = holder.getAddress();
        size_t commaIndex = street.find(',');
        if (commaIndex != string::npos) {
            street = street.substr(commaIndex + 1);
        }

        streetOwnersCount[street]++;
        streetTotalPrice[street] += phone.getPrice();
    }

    ofstream file(filename);
    if (file.is_open()) {
        file << "Street\t\tOwners\t\tTotal Price" << endl;
        for (const auto& entry : streetOwnersCount) {
            const string& street = entry.first;
            int ownersCount = entry.second;
            double totalPrice = streetTotalPrice[street];

            file << street << "\t\t" << ownersCount << "\t\t" << totalPrice << endl;
        }
        file.close();
        cout << "Calculation results have been successfully saved to file: " << filename << endl;
    } else {
        cout << "Error: Unable to open file for writing: " << filename << endl;
    }
}

int main() {
    map<Holder, Phone> database;
    
    populateDatabaseFromFile(database, "database.txt");
    populateDatabaseFromKeyboard(database);

    int searchNumber;
    cout << "Enter a number to search for an owner: ";
    cin >> searchNumber;

    Holder foundByNumber = searchByNumber(database, searchNumber);
    if (foundByNumber.getFullName() != "") {
        cout << "Owner found by number: " << foundByNumber.getFullName() << endl;
    } else {
        cout << "Owner not found by number: " << searchNumber << endl;
    }

    string searchAddress;
    cout << "Enter an address to search for an owner: ";
    getline(cin, searchAddress);

    Holder foundByAddress = searchByAddress(database, searchAddress);
    if (foundByAddress.getFullName() != "") {
        cout << "Owner found by address: " << foundByAddress.getFullName() << endl;
    } else {
        cout << "Owner not found by address: " << searchAddress << endl;
    }

    string fullNameToChange;
    int newNumber;
    cout << "Enter the full name of the owner to change their phone number: ";
    getline(cin, fullNameToChange);
    cout << "Enter the new phone number: ";
    cin >> newNumber;

    changePhoneNumber(database, fullNameToChange, newNumber);

    computeStatistics(database, "statistics.txt");

    return 0;
}


