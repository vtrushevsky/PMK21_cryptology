#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Telefon {
protected:
    string nazva;
    string firma;
    double tsina;

public:
    Telefon(const string& _nazva, const string& _firma, double _tsina)
        : nazva(_nazva), firma(_firma), tsina(_tsina) {}

    virtual ~Telefon() {}

    virtual void printDetails() const = 0; 

    double getTsina() const {
        return tsina;
    }
};

class MobilnyiTelefon : public Telefon {
private:
    string kolir;
    int obiemPamiat;

public:
    MobilnyiTelefon(const string& _nazva, const string& _firma, double _tsina,
        const string& _kolir, int _obiemPamiat)
        : Telefon(_nazva, _firma, _tsina), kolir(_kolir), obiemPamiat(_obiemPamiat) {}

    void printDetails() const override {
        cout << "Назва: " << nazva << endl;
        cout << "Фірма: " << firma << endl;
        cout << "Ціна: " << tsina << endl;
        cout << "Колір: " << kolir << endl;
        cout << "Об'єм пам'яті: " << obiemPamiat << " GB" << endl;
        cout << "-------------------------" << endl;
    }
};

class Radiotelefon : public Telefon {
private:
    double radiusDii;
    bool avtovidpovidach;

public:
    Radiotelefon(const string& _nazva, const string& _firma, double _tsina,
        double _radiusDii, bool _avtovidpovidach)
        : Telefon(_nazva, _firma, _tsina), radiusDii(_radiusDii), avtovidpovidach(_avtovidpovidach) {}

    void printDetails() const override {
        cout << "Назва: " << nazva << endl;
        cout << "Фірма: " << firma << endl;
        cout << "Ціна: " << tsina << endl;
        cout << "Радіус дії: " << radiusDii << " м" << endl;
        cout << "Автовідповідач: " << (avtovidpovidach ? "Є" : "Немає") << endl;
        cout << "-------------------------" << endl;
    }

    bool hasAvtovidpovidach() const {
        return avtovidpovidach;
    }
};

bool compareByTsina(const Telefon* t1, const Telefon* t2) {
    return t1->getTsina() < t2->getTsina();
}

int main() {
    vector<Telefon*> telefoni;
    ifstream file1("file1.txt");
    string line;

    while (getline(file1, line)) {
        string nazva, firma, kolir;
        double tsina;
        int obiemPamiat;

        size_t pos = 0;
        pos = line.find(",");
        nazva = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(",");
        firma = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(",");
        tsina = stod(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find(",");
        kolir = line.substr(0, pos);
        line.erase(0, pos + 1);

        obiemPamiat = stoi(line);

        telefoni.push_back(new MobilnyiTelefon(nazva, firma, tsina, kolir, obiemPamiat));
    }

    file1.close();

    ifstream file2("file2.txt");

    while (getline(file2, line)) {
        string nazva, firma;
        double tsina;
        double radiusDii;
        bool avtovidpovidach;

        size_t pos = 0;
        pos = line.find(",");
        nazva = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(",");
        firma = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(",");
        tsina = stod(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find(",");
        radiusDii = stod(line.substr(0, pos));
        line.erase(0, pos + 1);

        avtovidpovidach = line == "1";

        telefoni.push_back(new Radiotelefon(nazva, firma, tsina, radiusDii, avtovidpovidach));
    }

    file2.close();

    sort(telefoni.begin(), telefoni.end(), compareByTsina);

    ofstream outputFile("sorted_phones.txt");
    double totalSum = 0.0;

    for (const auto& telefon : telefoni) {
        telefon->printDetails();
        totalSum += telefon->getTsina();
    }
    outputFile << "Загальна сума: " << totalSum << endl;
    outputFile.close();

    ofstream radioOutputFile("radio_phones_with_answering_machine.txt");

    for (const auto& telefon : telefoni) {
        Radiotelefon* radioTelefon = dynamic_cast<Radiotelefon*>(telefon);
        if (radioTelefon && radioTelefon->hasAvtovidpovidach()) {
            radioTelefon->printDetails();
        }
    }

    radioOutputFile.close();

    for (const auto& telefon : telefoni) {
        delete telefon;
    }

    return 0;
}