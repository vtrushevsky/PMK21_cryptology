
#include <iostream>
#include <fstream>
using namespace std;

// Розробити ієрархію класів для ромбовидного наслідування:
// автомобіль (об’єм двигуна, назва, марка)
class Car {
protected:
    double VolumeEngine;
    string Name;
    string Brand;

public:
    Car() : VolumeEngine(0), Name(""), Brand("") {}

    Car(double volumeengine, const string& name, const string& brand)
        : VolumeEngine(volumeengine), Name(name), Brand(brand) {}

    double GetVolumeEngine() const {
        return this->VolumeEngine;
    }
    string GetName() const {
        return this->Name;
    }
    string GetBrand() const {
        return this->Brand;
    }

    virtual void print(ostream& os) const {
        os << "Volume of engine: " << this->GetVolumeEngine()
           << " Name: " << this->GetName()
           << " Brand: " << this->Brand;
        cout << endl;
    }
};

ostream& operator<<(ostream& os, const Car& c) {
    c.print(os);
    return os;
}

// 1) бензиновий автомобіль (об”єм баку)
class petrolCar : virtual public Car {
protected:
    double VolumeTank;

public:
    petrolCar() : VolumeTank(0) {}

    petrolCar(double volumetank, double volumeengine, const string& name, const string& brand)
        : Car(volumeengine, name, brand), VolumeTank(volumetank) {}

    void printPetrolParam(ostream& os) const {
        os << "  Volume of tank: " << this->VolumeTank;
    }

    void print(ostream& os) const override {
        Car::print(os);
        printPetrolParam(os);
        cout << endl;
    }

    friend istream& operator>>(istream& is, petrolCar& pc) {
        is >> pc.VolumeTank;
        return is;
    }
};

// 2) електромобіль (max час пробігу, час зарядки)
class electroCar : virtual public Car {
protected:
    double maxTimeMileage;
    int chargeHours;

public:
    electroCar() : Car(), maxTimeMileage(0), chargeHours(0) {}

    electroCar(double maxtimemileage, int chargehours, double volumeengine, const string& name, const string& brand)
        : Car(volumeengine, name, brand), maxTimeMileage(maxtimemileage), chargeHours(chargehours) {}

    void printElectroParam(ostream& os) const {
        os << "  Max time of mileage: " << this->maxTimeMileage << " Charge hours: " << this->chargeHours;
    }

    void print(ostream& os) const override {
        Car::print(os);
        printElectroParam(os);
        cout << endl;
    }

    friend istream& operator>>(istream& is, electroCar& ec) {
        is >> ec.maxTimeMileage >> ec.chargeHours;
        return is;
    }
};

class combination: public petrolCar, public electroCar {
protected:
    int petrolMileage;
    int electroMileage;

public:
    combination(): petrolCar(), electroCar(), petrolMileage(0), electroMileage(0) {}

    combination(int petrolmileage, int electromileage, double maxtimemileage, int chargehours, double volumetank, double volumeengine, const string& name, const string& brand): Car(volumeengine, name, brand), petrolCar(volumetank, volumeengine, name, brand), electroCar(maxtimemileage, chargehours, volumeengine, name, brand), petrolMileage(petrolmileage), electroMileage(electromileage) {}

    void print(ostream& os) const override {
        Car::print(os);
        printParam(os);
        printPetrolParam(os);
        printElectroParam(os);
        os << endl;
    }

    void printParam (ostream& os) const {
        os << "  Petrol car mileage: " << this->petrolMileage << " Electrocar mileage: " << this->electroMileage;
    }

    friend istream& operator>>(istream& is, combination& cc) {
        is >> cc.petrolMileage >> cc.electroMileage;
        return is;
    }
};
int main () {
    //Ввести дані про різні автомобілі різних марок в один масив, видрукувати дані про них у файл.
    Car** car = new Car* [3];

    petrolCar pc(60, 120, "Porsche Taikan", "Porsche");
    electroCar ec(120, 24, 80, "Tesla x5", "Tesla");
    combination cc(200, 120, 100.3, 24, 80, 75, "BMW XM", "BMW");

    car[0] = &pc;
    car[1] = &ec;
    car[2] = &cc;

    for (size_t i = 0; i < 3; ++i) {
    cout << *car[i] << endl;
}
    ofstream outFile("cars.txt");
    if (outFile.is_open()) {
        for (size_t i = 0; i < 3; ++i) {
            car[i]->print(outFile);
        }
        outFile.close();
    } else {
        cout << "Error: could not open file";
    }

// Посортувати їх за об’ємом двигуна, далі за маркою. Знайти марку, яка містить авто всіх трьох типів.


    delete[] car;

return 0; 

    
}