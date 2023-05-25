#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;


class Transport {
protected:
    double MotorVolume;
    string Name;
    string Marka;

public:
    Transport() : MotorVolume(0), Name(""), Marka("") {}

    Transport(double motor, const string& name, const string& marka) : MotorVolume(motor), Name(name), Marka(marka) {}

    double GetMotor() const {
        return this->MotorVolume;
    }

    string GetName() const {
        return this->Name;
    }

    string GetMarka() const {
        return this->Marka;
    }

    virtual void print(ostream& os) const {
        os << "\nMotor: " << this->GetMotor() << "\nName: " << this->GetName() << "\nMarka: " << this->GetMarka();
        cout << endl;
    }

    
};

ostream& operator<< (ostream& os, const Transport& t) {
    t.print(os);
    cout << endl;
    return os;
}



class PetrolTransport : virtual public Transport {

protected:
    double TankVolume;


public:
    PetrolTransport() : TankVolume(0) {}

    PetrolTransport(double motor, const string& name, const string& marka, double tank) : Transport(motor, name, marka), TankVolume(tank) {}

    void printPetrolTransport(ostream& os) const {
        os << "\nTank volume: " << this->TankVolume;
    }

    void print(ostream& os) const override {
        Transport::print(os);
        printPetrolTransport(os);
        cout << endl;
    }



    /*friend istream& operator>>(istream& is, PetrolTransport& pt) {
        is >> pt.MotorVolume >> pt.Name >> pt.Marka >> pt.TankVolume;

        return is;
    }*/
};


class ElectricTransport : virtual public Transport {

protected:
    double TimeToCharge;
    double TimeToDrive;


public:
    ElectricTransport() : TimeToDrive(0), TimeToCharge(0) {}

    ElectricTransport(double motor, const string& name, const string& marka, double charge, double drive) : Transport(motor, name, marka), TimeToCharge(charge), TimeToDrive(drive) {}
    
    void printElectricTransport(ostream& os) const {
          os << "\nTime to charge: " << this->TimeToCharge << "\nTime to drive:  " << this->TimeToDrive;
        }

    void print(ostream& os) const override {
        Transport::print(os);
        printElectricTransport(os);
        cout << endl;
    }

    /*friend istream& operator>>(istream& is, ElectricTransport& et) {
        is >> et.MotorVolume >> et.Name >> et.Marka >> et.TimeToCharge >> et.TimeToDrive;

        return is;
    }*/
};


class CombinedTransport : public PetrolTransport, public ElectricTransport {
protected:

    int LongOnPetrol;
    int LongOnElectricity;

public:

    CombinedTransport() : LongOnPetrol(0), LongOnElectricity(0) {}

    CombinedTransport(double motor, const string& name, const string& marka, double tank, double charge, double drive, int petrol, int electricity) : Transport(motor, name, marka), 
        PetrolTransport(motor, name, marka, tank), 
        ElectricTransport(motor, name, marka, charge, drive), 
        LongOnPetrol(petrol), LongOnElectricity(electricity) {}

    void print(ostream& os) const override {
        Transport::print(os);
        os << "\nHave driven on petrol: " << this->LongOnPetrol << "\nHave driven on electricity: " << this->LongOnElectricity;
        cout << endl;
        printPetrolTransport(os);
        cout << endl;
        printElectricTransport(os);
        cout << endl;
    }

    /*friend istream& operator>>(istream& is, CombinedTransport& ct) {
        is >> ct.MotorVolume >> ct.Name >> ct.Marka >> ct.TankVolume >> ct.TimeToCharge >> ct.TimeToDrive >> ct.LongOnPetrol >> ct.LongOnElectricity;
        return is;
    }*/
};



int main() {
    Transport* autos[5] = {
        new ElectricTransport(0, "Model - X", "Tesla", 10, 50),
        new ElectricTransport(0, "Q56", "Nissan", 14, 45),
        new PetrolTransport(6, "GTR 34", "Nissan", 40),
        new CombinedTransport(5, "Model - Alpha", "FutureStar", 40, 10, 50, 12340, 5555),
        new CombinedTransport(6, "Model - F", "Nissan", 30, 11, 40, 1234, 556)
    };

    
    sort(autos, autos + 5, [](Transport* a, Transport* b) {
        return a->GetMotor() < b->GetMotor();
        });
    

    ofstream outputFile("automobiles.txt");
    for (int i = 0; i < 5; i++) {
        autos[i]->print(outputFile);
        outputFile << endl;
    }
    outputFile.close();

    

    return 0;
}
