#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;


void printLogTable() {
    cout << setw(10) << right << "Число" << setw(10) << right << "Натур. лог" << setw(10) << right << "Десят. лог" << endl;
    cout << setprecision(5) << fixed;

    for (int i = 2; i <= 100; i++) {
        cout << setw(10) << right << i << setw(10) << right << log(i) << setw(10) << right << log10(i) << endl;
    }
}


void printCenteredString(const string& str) {
    int screenWidth = 80;  
    int strWidth = str.length();
    int padding = (screenWidth - strWidth) / 2;

    cout << setw(padding + strWidth) << str << endl;
}


ostream& systemTime(ostream& os) {
    time_t currentTime = time(nullptr);
    tm* localTime = localtime(&currentTime);

    os << put_time(localTime, "%X %x");
    return os;
}


istream& skip10(istream& is) {
    char buffer[11];
    is.read(buffer, 10);
    return is;
}

int main() {
    
    printLogTable();

    
    string input;
    cout << "Введіть рядок: ";
    getline(cin, input);
    printCenteredString(input);

    
    cout << "Поточний час та дата: " << systemTime << endl;

    
    cout << "Введіть рядок для пропуску 10 символів: ";
    cin >> skip10;
    cout << "Решта рядка після пропуску 10 символів: " << skip10 << endl;

    return 0;
}
