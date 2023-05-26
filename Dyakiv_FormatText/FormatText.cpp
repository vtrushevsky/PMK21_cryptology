#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

void printLogTable() {
    cout << setw(10) << "Number" << setw(10) << "Natural Log" << setw(10) << "Decimal Log" << endl;

    for (int i = 2; i <= 100; ++i) {
        double naturalLog = log(i);
        double decimalLog = log10(i);

        cout << fixed << setprecision(5) << setw(10) << i << setw(10) << naturalLog << setw(10) << decimalLog << endl;
    }
}

void printCenteredString(const string& str) {
    int screenWidth = 80; 
    int strWidth = str.length();

    int padding = (screenWidth - strWidth) / 2;

    for (int i = 0; i < padding; ++i) {
        cout << " ";
    }

    cout << str << endl;
}

ostream& systemTimeDate(ostream& os) {
    time_t now = time(0);
    char* dateTime = ctime(&now);
    os << dateTime;
    return os;
}

istream& skipCharacters(istream& is) {
    char skip[11];
    is.read(skip, 10);
    return is;
}

int main() {
    printLogTable();

    string str = "Hello, World!";
    printCenteredString(str);

    cout << systemTimeDate;

    cin >> skipCharacters;

    return 0;
}
