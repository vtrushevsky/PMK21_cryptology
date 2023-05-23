#include <iostream>
#include "string"

using namespace std;

class Avto {
protected:
    int engineObiem;
    string nazva;
    string marka;
public:
    void SetEngineObiem(int a){
        engineObiem = a;
    }
    void SetNazva(string a){
        nazva = a;
    }
    void SetMarka(string a){
        marka = a;
    }
    string GetNazva(){
        return nazva;
    }
    string GetMarka(){
        return marka;
    }
    int GetEngineObiem() {
        return engineObiem;
    }
};

class BenzinCar: public Avto {
private:
    int bakObiem;
public:
    void SetBak(int a) {
        bakObiem = a;
    }
    int GetBak() {
        return bakObiem;
    }

};

class ElectroCar: public Avto {
private:
    int timeProbigu;
    int chargeTime;
public:
    void SetTimeProbigu(int a) {
        timeProbigu = a;
    }
    void SetChargeTime(int a) {
        chargeTime = a;
    }
};

class Hybrid: public BenzinCar, public ElectroCar {
protected:
    int differentProbig;
public:
    void SetDif(int a) {
        differentProbig = a;
    }
};

//C:\Users\user\CLionProjects\rhomb\cars.txt
int main() {
    const int n = 2;

    Avto car;

    BenzinCar a;

//    a.SetEngineObiem(5);
    a.SetEngineObiem(10);
    a.SetBak(20);
    a.SetMarka("Toyota");
    a.SetNazva("TurboMashina");

    ElectroCar b;
    b.SetEngineObiem(20000);
    b.SetChargeTime(5);
    b.SetTimeProbigu(15);
    b.SetMarka("Tesla");
    b.SetNazva("TeslaCar");

    Hybrid c;
    c.BenzinCar::SetNazva("HybridCar");
    c.BenzinCar::SetMarka("Hybrid");
    c.BenzinCar::SetEngineObiem(5);
    c.ElectroCar::SetTimeProbigu(3);
    c.ElectroCar::SetChargeTime(1);
    c.SetDif(10);
//    ElectroCar hcar1 = static_cast<ElectroCar>(c);
//    BenzinCar bcar = static_cast<BenzinCar>(a);
//    ElectroCar ecar = static_cast<ElectroCar>(b);



    Hybrid cars[n];
    cars[0] = a;
    cars[1] = b;
    cars[2] = c;

    cout << cars[0].GetNazva() << " " << cars[0]->GetMarka() << " " << cars[0]->GetEngineObiem() << " " << cars[0].GetBak() << endl;

    return 0;
}
