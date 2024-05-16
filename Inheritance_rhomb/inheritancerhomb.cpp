#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Car {
protected:
    string name;
    string brand;
    double engineVolume;

public:
    Car(const string& name, const string& brand, double engineVolume)
        : name(name), brand(brand), engineVolume(engineVolume) {
    }

    virtual ~Car() {}

    virtual void printDetails(ostream& os) const {
        os << "Name: " << name << endl;
        os << "Brand: " << brand << endl;
        os << "Engine Volume: " << engineVolume << "L" << endl;
    }

    virtual void saveToFile(ostream& os) const {
        os << "Car" << endl;
        os << name << endl;
        os << brand << endl;
        os << engineVolume << endl;
    }

    double getEngineVolume() const {
        return engineVolume;
    }

    string getBrand() const {
        return brand;
    }
};

class GasolineCar : public virtual Car {
protected:
    double fuelTankCapacity;

public:
    GasolineCar(const string& name, const string& brand, double engineVolume, double fuelTankCapacity)
        : Car(name, brand, engineVolume), fuelTankCapacity(fuelTankCapacity) {
    }

    virtual ~GasolineCar() {}

    void printDetails(ostream& os) const override {
        Car::printDetails(os);
        os << "Fuel Tank Capacity: " << fuelTankCapacity << "L" << endl;
    }

    void saveToFile(ostream& os) const override {
        Car::saveToFile(os);
        os << "GasolineCar" << endl;
        os << fuelTankCapacity << endl;
    }
};

class ElectricCar : public virtual Car {
protected:
    int maxRange;
    int chargingTime;

public:
    ElectricCar(const string& name, const string& brand, double engineVolume, int maxRange, int chargingTime)
        : Car(name, brand, engineVolume), maxRange(maxRange), chargingTime(chargingTime) {
    }

    virtual ~ElectricCar() {}

    void printDetails(ostream& os) const override {
        Car::printDetails(os);
        os << "Max Range: " << maxRange << "km" << endl;
        os << "Charging Time: " << chargingTime << " hours" << endl;
    }

    void saveToFile(ostream& os) const override {
        Car::saveToFile(os);
        os << "ElectricCar" << endl;
        os << maxRange << endl;
        os << chargingTime << endl;
    }
};

class HybridCar : public GasolineCar, public ElectricCar {
public:
    HybridCar(const string& name, const string& brand, double engineVolume, double fuelTankCapacity, int maxRange, int chargingTime)
        : Car(name, brand, engineVolume), GasolineCar(name, brand, engineVolume, fuelTankCapacity), ElectricCar(name, brand, engineVolume, maxRange, chargingTime) {
    }

    ~HybridCar() {}

    void printDetails(ostream& os) const override {
        Car::printDetails(os);
        os << "Fuel Tank Capacity: " << fuelTankCapacity << "L" << endl;
        os << "Max Range: " << maxRange << "km" << endl;
        os << "Charging Time: " << chargingTime << " hours" << endl;
    }

    void saveToFile(ostream& os) const override {
        Car::saveToFile(os);
        os << "HybridCar" << endl;
        os << fuelTankCapacity << endl;
        os << maxRange << endl;
        os << chargingTime << endl;
    }
};

bool compareByEngineVolume(const Car* car1, const Car* car2) {
    return car1->getEngineVolume() < car2->getEngineVolume();
}

bool compareByBrand(const Car* car1, const Car* car2) {
    return car1->getBrand() < car2->getBrand();
}

void printCarsDetails(const vector<Car*>& cars) {
    for (const auto& car : cars) {
        car->printDetails(cout);
        cout << endl;
    }
}

void saveCarsToFile(const string& filename, const vector<Car*>& cars) {
    ofstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Failed to open the file: " + filename);
    }

    for (const auto& car : cars) {
        car->saveToFile(file);
        file << endl;
    }

    file.close();
}

string findBrandWithAllTypes(const vector<Car*>& cars) {
    vector<string> brands;
    for (const auto& car : cars) {
        string brand = car->getBrand();
        if (find(brands.begin(), brands.end(), brand) == brands.end()) {
            brands.push_back(brand);
        }
    }

    for (const auto& brand : brands) {
        bool hasGasolineCar = false;
        bool hasElectricCar = false;
        bool hasHybridCar = false;

        for (const auto& car : cars) {
            if (car->getBrand() == brand) {
                if (dynamic_cast<const GasolineCar*>(car) != nullptr) {
                    hasGasolineCar = true;
                }
                if (dynamic_cast<const ElectricCar*>(car) != nullptr) {
                    hasElectricCar = true;
                }
                if (dynamic_cast<const HybridCar*>(car) != nullptr) {
                    hasHybridCar = true;
                }
            }
        }

        if (hasGasolineCar && hasElectricCar && hasHybridCar) {
            return brand;
        }
    }

    return "";
}

int main() {
    vector<Car*> cars;

    cars.push_back(new GasolineCar("Gas Car 1", "Brand 1", 2.0, 50.0));
    cars.push_back(new ElectricCar("Electric Car 1", "Brand 2", 1.5, 200, 8));
    cars.push_back(new HybridCar("Hybrid Car 1", "Brand 1", 1.8, 40.0, 150, 6));
    cars.push_back(new GasolineCar("Gas Car 2", "Brand 3", 1.6, 45.0));
    cars.push_back(new ElectricCar("Electric Car 2", "Brand 2", 2.0, 250, 10));
    cars.push_back(new HybridCar("Hybrid Car 2", "Brand 3", 2.2, 55.0, 180, 7));

    cout << "Car Details:" << endl;
    printCarsDetails(cars);

    sort(cars.begin(), cars.end(), compareByBrand);
    sort(cars.begin(), cars.end(), compareByEngineVolume);

    cout << endl << "Sorted Car Details:" << endl;
    printCarsDetails(cars);

    string filename = "car_details.txt";
    saveCarsToFile(filename, cars);
    cout << "Car details saved to file: " << filename << endl;

    string brandWithAllTypes = findBrandWithAllTypes(cars);
    if (!brandWithAllTypes.empty()) {
        cout << "Brand with all three types of cars: " << brandWithAllTypes << endl;
    }
    else {
        cout << "No brand found with all three types of cars." << endl;
    }

    for (const auto& car : cars) {
        delete car;
    }

    return 0;
}