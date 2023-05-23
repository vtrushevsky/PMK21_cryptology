#include <string>
#include <iostream>

using namespace std;

class Tovar {
protected:
    int code;
    int price;
public:
    Tovar(){
        code = 0;
        price = 0;
    }
};
class Toy: public Tovar {
protected:
    string name;
    int age;
public:
    Toy(): Tovar() {
        code = 0;
        price = 0;
        name = "#";
        age = 0;
    }
    Toy(int c, int p, string n, int a) {
        code = c;
        price = p;
        name = n;
        age = a;
    }
    void GetCode(){
        cout << code << endl;
    }
    int GetPrice(){
        return price;
    }
    int GetAge(){
        return age;
    }
    void Print(){
        cout << name << endl;
    }
};

Toy arr[] = {{0201, 100, "Bear", 0}, {1111, 10, "Car", 3}, {1212, 50, "Helicopter", 10}, {2001, 150, "Plane", 3}, {9955, 1000, "Doll", 15}, {1001, 250, "Bicycle", 10}, {5432, 100, "Monopoly", 8}, {9442, 200, "Puzzle", 9}, {9191, 130, "Fox", 0}};

int main() {
    int age1, age2, pr;
    string yn;
    cout << "Input age from __ to __" << endl;
    cout << "age1: ";
    cin >> age1;
    cout << "age2: ";
    cin >> age2;
    cout << "Input price: ";
    cin >> pr;
    for(int i = 0; i < 8; i++){
        if((arr[i].GetAge() > age1 && arr[i].GetAge() <= age2) && arr[i].GetPrice() < pr){
            arr[i].Print();
        }
    }
    cout << "Print country code? Y/N" << endl;
    cin >> yn;
    if(yn == "Y" || "y"){
        for(int i = 0; i < 8; i++){
            if((arr[i].GetAge() > age1 && arr[i].GetAge() <= age2) && arr[i].GetPrice() < pr){
                arr[i].GetCode();
            }
        }
    }
    return 0;
}
