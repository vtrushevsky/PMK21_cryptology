#include <iostream>
#include <fstream>

using namespace std;


class Car {
protected:
	double engineVolume;
	string name;
	string brand;

public:
	Car(): engineVolume(0), name(""), brand("") {}

	Car(double EngiveVolume, const string& Name, const string& Brand) {
		this->engineVolume = EngiveVolume;
		this->name = Name;
		this->brand = Brand;
	}

	double GetEngineVolume() const {
		return this->engineVolume;
	}

	string GetName() const {
		return this->name;
	}

	string GetBrand() const {
		return this->brand;
	}

	virtual void print(ostream& os) const {
		os << "Engine volume: " << this->GetEngineVolume() << "     Name: " << this->GetName() << "     Brand: " << this->GetBrand();

	}
};

ostream& operator<< (ostream& os, const Car& t) {
	t.print(os);
	cout << endl;
	return os;
}

class FuelCar: virtual public Car {
protected:
	double tankVolume;

public:
	FuelCar(): Car(), tankVolume(0) {}
	FuelCar(double EngiveVolume, const string& Name, const string& Brand, double TankVolume): Car(EngiveVolume, Name, Brand), tankVolume(TankVolume) {}
	
	void printFuelCarParam(ostream& os) const {
		os << "  Tank volume: " << this->tankVolume;
	}
	void print(ostream& os) const override {
		Car::print(os);
		cout << "  ";
		printFuelCarParam(os);

	}
};

class ElectroCar : virtual public Car {
protected:
	double maxDistance;
	double chargeTime;

public:
	ElectroCar() : Car(), maxDistance(0), chargeTime(0) {}
	ElectroCar(double EngiveVolume, const string& Name, const string& Brand, double MaxDistance, double ChargeTime) : Car(EngiveVolume, Name, Brand), maxDistance(MaxDistance), chargeTime(ChargeTime) {}

	void printElectroCarParam(ostream& os) const {
		os << "  Max distance: " << this->maxDistance << "    Charge time: " << this->chargeTime;
	}
	void print(ostream& os) const override {
		Car::print(os);
		cout << "  ";
		printElectroCarParam(os);

	}
};

class HybridCar: public  FuelCar, ElectroCar {
 protected:
	double maxFuelDistance;
	double maxElectroDistance;

public:
	HybridCar(): FuelCar(), ElectroCar(), maxFuelDistance(0), maxElectroDistance(0){}

	HybridCar(double EngiveVolume, const string& Name, const string& Brand, double TankVolume, double MaxDistance, double ChargeTime, double MaxFuelDistance, double MaxElectroDistance): Car(EngiveVolume, Name, Brand), FuelCar(EngiveVolume, Name, Brand, TankVolume), ElectroCar(EngiveVolume, Name, Brand, MaxDistance, ChargeTime), maxFuelDistance(MaxFuelDistance), maxElectroDistance(MaxElectroDistance){}

	void print(ostream& os) const override {
		Car::print(os); cout << "  ";;
		os << "Max fuel distance: " << this->maxFuelDistance << "     Max electro distance: " << this->maxElectroDistance;
		cout << "  ";
		printFuelCarParam(os);
		cout << "  ";
		printElectroCarParam(os);

	}
};

int main(){

	Car** car = new Car * [9];

	FuelCar fc(3, "X5", "BMW", 4);

	FuelCar fc2(7, "X3", "BMW", 3);

	FuelCar fc3(6, "X1", "BMW", 8);

	ElectroCar ec(5, "iX", "Audi", 200, 2);

	ElectroCar ec2(4, "iX", "BMW", 600, 6);

	ElectroCar ec3(8, "760", "Kia", 100, 3);

	HybridCar hc(4, "GLE", "Mercedes", 5, 250, 5, 400, 600);

	HybridCar hc2(5, "LE", "Mercedes Benz", 5, 250, 5, 400, 600);

	HybridCar hc3(3, "GE", "Renault", 5, 250, 5, 400, 600);

	car[0] = &fc;
	car[1] = &fc2;
	car[2] = &fc3;
	car[3] = &ec;
	car[4] = &ec2;
	car[5] = &ec3;
	car[6] = &hc;
	car[7] = &hc2;
	car[8] = &hc3;

	

	

	ofstream fout;

	fout.open("myFile.txt");

	if (!fout.is_open()) {
		cout << "Error" << endl;
	}
	else {

		for (size_t i = 0; i < 9; ++i) {
			fout << *car[i] << endl;
		}

		delete[] car;
	}

	fout.close();
	

	return 0;
}