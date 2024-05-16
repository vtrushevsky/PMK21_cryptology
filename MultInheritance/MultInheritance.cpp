#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


class Figura {
public:
    virtual ~Figura() {}

    virtual double obchyslitPloshchu() const = 0; 
    virtual double obchyslitVysotu() const = 0; 

    virtual void printDetails() const = 0; 
};


class FiguraPloska : public Figura {
protected:
    double ploshcha;

public:
    FiguraPloska(double _ploshcha) : ploshcha(_ploshcha) {}

    double obchyslitPloshchu() const override {
        return ploshcha;
    }

    double obchyslitVysotu() const override {
        return 0.0; 
    }
};


class FiguraObiemna : public Figura {
protected:
    double vysota;

public:
    FiguraObiemna(double _vysota) : vysota(_vysota) {}

    double obchyslitPloshchu() const override {
        return 0.0; 
    }

    double obchyslitVysotu() const override {
        return vysota;
    }
};


class Bagatokutnyk : public FiguraPloska {
private:
    int kilkistStoron;

public:
    Bagatokutnyk(double _ploshcha, int _kilkistStoron) : FiguraPloska(_ploshcha), kilkistStoron(_kilkistStoron) {}

    void printDetails() const override {
        cout << "������������" << endl;
        cout << "�����: " << ploshcha << endl;
        cout << "ʳ������ �����: " << kilkistStoron << endl;
        cout << "-------------------------" << endl;
    }
};


class Kolo : public FiguraPloska {
private:
    double radius;

public:
    Kolo(double _ploshcha, double _radius) : FiguraPloska(_ploshcha), radius(_radius) {}

    void printDetails() const override {
        cout << "����" << endl;
        cout << "�����: " << ploshcha << endl;
        cout << "�����: " << radius << endl;
        cout << "-------------------------" << endl;
    }
};


class Paralelepiped : public FiguraObiemna {
private:
    double dovzhyna;
    double shyrina;

public:
    Paralelepiped(double _vysota, double _dovzhyna, double _shyrina) : FiguraObiemna(_vysota), dovzhyna(_dovzhyna), shyrina(_shyrina) {}

    void printDetails() const override {
        cout << "������������" << endl;
        cout << "������: " << vysota << endl;
        cout << "�������: " << dovzhyna << endl;
        cout << "������: " << shyrina << endl;
        cout << "-------------------------" << endl;
    }
};


class Konus : public FiguraObiemna {
private:
    double radius;

public:
    Konus(double _vysota, double _radius) : FiguraObiemna(_vysota), radius(_radius) {}

    void printDetails() const override {
        cout << "�����" << endl;
        cout << "������: " << vysota << endl;
        cout << "�����: " << radius << endl;
        cout << "-------------------------" << endl;
    }
};

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    vector<Figura*> figury;

    
    for (int i = 0; i < 10; i++) {
        double ploshcha, vysota;
        cout << "Գ���� #" << (i + 1) << endl;
        cout << "������ �����: ";
        cin >> ploshcha;
        cout << "������ ������: ";
        cin >> vysota;

        if (i % 2 == 0) {
            figury.push_back(new Bagatokutnyk(ploshcha, i + 3));
        }
        else {
            figury.push_back(new Kolo(ploshcha, i + 1));
        }

        figury.push_back(new Paralelepiped(vysota, i + 2, i + 4));
        figury.push_back(new Konus(vysota, i + 1.5));
    }

    
    sort(figury.begin(), figury.end(), [](Figura* f1, Figura* f2) {
        return f1->obchyslitPloshchu() > f2->obchyslitPloshchu();
        });
    cout << "����� ������ (� ������� �������� �����):" << endl;
    for (const auto& figura : figury) {
        if (dynamic_cast<FiguraPloska*>(figura)) {
            figura->printDetails();
        }
    }

    
    sort(figury.begin(), figury.end(), [](Figura* f1, Figura* f2) {
        return f1->obchyslitVysotu() < f2->obchyslitVysotu();
        });

    cout << "��'��� ������ (� ������� ��������� ������):" << endl;
    for (const auto& figura : figury) {
        if (dynamic_cast<FiguraObiemna*>(figura)) {
            figura->printDetails();
        }
    }

    
    double rozmir;
    cout << "������ ������������ �����: ";
    cin >> rozmir;

    for (const auto& figura : figury) {
        if (dynamic_cast<FiguraPloska*>(figura) && figura->obchyslitPloshchu() == rozmir) {
            cout << "�������� ������ ������ � ����������� ������������ �������:" << endl;
            figura->printDetails();
            break;
        }
        else if (dynamic_cast<FiguraObiemna*>(figura) && figura->obchyslitVysotu() == rozmir) {
            cout << "�������� ��'���� ������ � ����������� ������������ �������:" << endl;
            figura->printDetails();
            break;
        }
    }

    
    for (const auto& figura : figury) {
        delete figura;
    }

    return 0;
}