#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

using namespace std;

class Owner {
public:
    string name;
    string address;

    Owner(const string& ownerName, const string& ownerAddress) : name(ownerName), address(ownerAddress) {}
};

class Phone {
public:
    string brand;
    int price;

    Phone(const string& phoneBrand, int phonePrice) : brand(phoneBrand), price(phonePrice) {}
};

void saveDatabase(const map<Owner, Phone>& database, const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        for (const auto& entry : database) {
            file << "Owner: " << entry.first.name << ", Address: " << entry.first.address << ", Brand: " << entry.second.brand << ", Price: " << entry.second.price << endl;
        }

        file.close();
        cout << "Database saved to " << filename << endl;
    }
    else {
        cout << "Error: Unable to open file for writing." << endl;
    }
}

void loadDatabase(map<Owner, Phone>& database, const string& filename) {
    ifstream file(filename);

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            string ownerName;
            string ownerAddress;
            string phoneBrand;
            int phonePrice;

            size_t ownerNameStart = line.find("Owner: ") + 7;
            size_t ownerNameEnd = line.find(", Address: ");
            ownerName = line.substr(ownerNameStart, ownerNameEnd - ownerNameStart);

            size_t ownerAddressStart = line.find("Address: ") + 10;
            size_t ownerAddressEnd = line.find(", Brand: ");
            ownerAddress = line.substr(ownerAddressStart, ownerAddressEnd - ownerAddressStart);

            size_t phoneBrandStart = line.find("Brand: ") + 7;
            size_t phoneBrandEnd = line.find(", Price: ");
            phoneBrand = line.substr(phoneBrandStart, phoneBrandEnd - phoneBrandStart);

            size_t phonePriceStart = line.find("Price: ") + 7;
            phonePrice = stoi(line.substr(phonePriceStart));

            database[Owner(ownerName, ownerAddress)] = Phone(phoneBrand, phonePrice);
        }

        file.close();
        cout << "Database loaded from " << filename << endl;
    }
    else {
        cout << "Error: Unable to open file for reading. A new database will be created." << endl;
    }
}

void addEntryFromInput(map<Owner, Phone>& database) {
    string ownerName;
    string ownerAddress;
    string brand;
    int price;

    cout << "Enter owner's name: ";
    getline(cin, ownerName);

    cout << "Enter owner's address: ";
    getline(cin, ownerAddress);

    cout << "Enter phone brand: ";
    getline(cin, brand);

    cout << "Enter phone price: ";
    cin >> price;
    cin.ignore();

    database[Owner(ownerName, ownerAddress)] = Phone(brand, price);

    cout << "Entry added to the database." << endl;
}

vector<Phone> findPhonesByOwner(const map<Owner, Phone>& database, const string& ownerName) {
    vector<Phone> phones;

    for (const auto& entry : database) {
        if (entry.first.name == ownerName) {
            phones.push_back(entry.second);
        }
    }

    return phones;
}

void movePhonesToContainer(vector<Phone>& phones, vector<Phone>& targetContainer) {
    for (const auto& phone : phones) {
        targetContainer.push_back(phone);
    }
}

Owner findOwnerByPhone(const map<Owner, Phone>& database, const string& phoneNumber) {
    for (const auto& entry : database) {
        if (entry.second.phoneNumber == phoneNumber) {
            return entry.first;
        }
    }

    return Owner("", "");
}

vector<Owner> findOwnersByAddress(const map<Owner, Phone>& database, const string& address) {
    vector<Owner> owners;

    for (const auto& entry : database) {
        if (entry.first.address == address) {
            owners.push_back(entry.first);
        }
    }

    return owners;
}

vector<Owner> findOwnersByBrandAndPrice(const map<Owner, Phone>& database, const string& brand, int minPrice) {
    vector<Owner> owners;

    for (const auto& entry : database) {
        if (entry.second.brand == brand && entry.second.price > minPrice) {
            owners.push_back(entry.first);
        }
    }

    return owners;
}

void changePhoneNumber(map<Owner, Phone>& database, const string& ownerName, const string& newPhoneNumber) {
    for (auto& entry : database) {
        if (entry.first.name == ownerName) {
            entry.second.phoneNumber = newPhoneNumber;
            break;
        }
    }
}

void calculateStatistics(const map<Owner, Phone>& database, const string& filename) {
    map<string, int> streetOwnersCount;
    map<string, int> streetPhonesValue;

    for (const auto& entry : database) {
        string street = entry.first.address.substr(entry.first.address.find_last_of(',') + 2);
        streetOwnersCount[street]++;
        streetPhonesValue[street] += entry.second.price;
    }

    ofstream file(filename);

    if (file.is_open()) {
        file << "Street\t\tOwners Count\tPhones Value" << endl;
        for (const auto& entry : streetOwnersCount) {
            file << entry.first << "\t\t" << entry.second << "\t\t" << streetPhonesValue[entry.first] << endl;
        }

        file.close();
        cout << "Statistics saved to " << filename << endl;
    }
    else {
        cout << "Error: Unable to open file for writing." << endl;
    }
}

int main() {
    map<Owner, Phone> database;
    string filename = "database.txt";

    loadDatabase(database, filename);

    int choice;

    do {
        cout << "Menu:" << endl;
        cout << "1. Add entry" << endl;
        cout << "2. Find phones by owner" << endl;
        cout << "3. Move phones to another container" << endl;
        cout << "4. Find owner by phone number" << endl;
        cout << "5. Find owners by address" << endl;
        cout << "6. Find owners by brand and price" << endl;
        cout << "7. Change phone number" << endl;
        cout << "8. Calculate statistics" << endl;
        cout << "9. Save database" << endl;
        cout << "0. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            addEntryFromInput(database);
            break;
        case 2:
        {
            string ownerName;
            cout << "Enter owner's name: ";
            getline(cin, ownerName);

            vector<Phone> phones = findPhonesByOwner(database, ownerName);
            cout << "Phones owned by " << ownerName << ":" << endl;
            for (const auto& phone : phones) {
                cout << "Brand: " << phone.brand << ", Price: " << phone.price << endl;
            }
        }
        break;
        case 3:
        {
            string ownerName;
            cout << "Enter owner's name: ";
            getline(cin, ownerName);

            vector<Phone> phones = findPhonesByOwner(database, ownerName);
            vector<Phone> targetContainer;

            movePhonesToContainer(phones, targetContainer);

            cout << "Phones owned by " << ownerName << " moved to the target container." << endl;
        }
        break;
        case 4:
        {
            string phoneNumber;
            cout << "Enter phone number: ";
            getline(cin, phoneNumber);

            Owner owner = findOwnerByPhone(database, phoneNumber);

            if (owner.name != "") {
                cout << "Phone number " << phoneNumber << " belongs to " << owner.name << "." << endl;
            }
            else {
                cout << "Phone number " << phoneNumber << " not found." << endl;
            }
        }
        break;
        case 5:
        {
            string address;
            cout << "Enter address: ";
            getline(cin, address);

            vector<Owner> owners = findOwnersByAddress(database, address);

            cout << "Owners at address " << address << ":" << endl;
            for (const auto& owner : owners) {
                cout << "Name: " << owner.name << ", Address: " << owner.address << endl;
            }
        }
        break;
        case 6:
        {
            string brand;
            int minPrice;

            cout << "Enter phone brand: ";
            getline(cin, brand);

            cout << "Enter minimum price: ";
            cin >> minPrice;
            cin.ignore();

            vector<Owner> owners = findOwnersByBrandAndPrice(database, brand, minPrice);

            cout << "Owners of phones with brand " << brand << " and price greater than " << minPrice << ":" << endl;
            for (const auto& owner : owners) {
                cout << "Name: " << owner.name << ", Address: " << owner.address << endl;
            }
        }
        break;
        case 7:
        {
            string ownerName;
            string newPhoneNumber;
            cout << "Enter owner's name: ";
            getline(cin, ownerName);

            cout << "Enter new phone number: ";
            getline(cin, newPhoneNumber);

            changePhoneNumber(database, ownerName, newPhoneNumber);
            cout << "Phone number changed for owner " << ownerName << "." << endl;
        }
        break;
        case 8:
        {
            string statisticsFilename;
            cout << "Enter statistics filename: ";
            getline(cin, statisticsFilename);

            calculateStatistics(database, statisticsFilename);
        }
        break;
        case 9:
            saveDatabase(database, filename);
            break;
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
            break;
        }

        cout << endl;

    } while (choice != 0);

    return 0;
}
