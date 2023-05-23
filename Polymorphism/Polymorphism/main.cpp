#include <iostream>
#include "string"
#include <fstream>
#include <vector>
#include <sstream>


using namespace std;



class Telefon{
protected:
    string nazva;
    string firma;
    int cina;
public:
    virtual void SetNazva(string a) = 0;
    virtual void SetFirma(string a) = 0;
    virtual void print() = 0;
};

class Mobile: public Telefon {
protected:
    string colir;
    int memory;
public:
    Mobile(string n, string f, int c, string co, int m){
        nazva = n;
        firma = f;
        cina = c;
        colir = co;
        memory = m;
    }

    void print() override{
        cout << nazva << " " << firma << " " << cina << " " << memory << endl;
    }

    void SetNazva(string a) override{
        nazva = a;
    }
    void SetFirma(string a) override{
        firma = a;
    }
    void SetColir(string a) {
        colir = a;
    }
    void SetMemory(int a){
        memory = a;
    }
};

class Radiotelefon: public Telefon{
protected:
    int radius;
    bool avtoprikol;
public:
    Radiotelefon(string n, string f, int c, int r, bool a){
        nazva = n;
        firma = f;
        cina = c;
        radius = r;
        avtoprikol = a;
    }

    void SetNazva(string a) override{
        nazva = a;
    }
    void SetFirma(string a) override{
        firma = a;
    }
    void SetRadius(int a) {
        radius = a;
    }
    void SetAvto(bool a) {
        avtoprikol = a;
    }

    void print() override{
        cout << nazva << " " << firma << " " << radius << " " << avtoprikol << endl;
    }
};

//void printing(const vector<Telefon*>& telefony) {
//    for (const auto& telefon : telefony) {
//        telefon->print();
//    }
//}

int main() {
    vector<Telefon*> telefony; // create a vector of pointers to the base class Telefon

    // read data from the MobilnyTelefon.txt file
    ifstream mobilnyFile("C:\\Users\\user\\CLionProjects\\Mobilochki\\nokia.txt");
    if (mobilnyFile.is_open()) {
        string line;
        while (getline(mobilnyFile, line)) {
            // parse the line and create a MobilnyTelefon object
            // assuming the format is "nazva,firma,cina,colir,memory"
            string nazva, firma, colir;
            int cina, memory;
            istringstream iss(line);
            getline(iss, nazva, ',');
            getline(iss, firma, ',');
            iss >> cina;
            getline(iss, colir, ',');
            iss >> memory;
            telefony.push_back(new Mobile(nazva, firma, cina, colir, memory));
        }
        mobilnyFile.close();
    } else {
        cout << "Unable to open MobilnyTelefon.txt file" << endl;
        return 1;
    }

    ifstream radioFile("C:\\Users\\user\\CLionProjects\\Mobilochki\\sigma.txt");
    if (radioFile.is_open()) {
        string line;
        while (getline(radioFile, line)) {
            // parse the line and create a Radiotelefon object
            // assuming the format is "nazwa,firma,cena,radius,av"
            string nazwa, firma;
            bool av;
            int cena, radius;
            istringstream iss(line);
            getline(iss, nazwa, ',');
            getline(iss, firma, ',');
            iss >> cena;
            iss >> radius;
            iss >> av;
            telefony.push_back(new Radiotelefon(nazwa, firma, cena, radius, av));
        }
        radioFile.close();
    } else {
        cout << "Unable to open Radiotelefon.txt file" << endl;
        return 1;
    }

    return 0;
}
