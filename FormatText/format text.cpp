#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;


void printLogTable() {
    cout << setw(10) << right << "�����" << setw(10) << right << "�����. ���" << setw(10) << right << "�����. ���" << endl;
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
    cout << "������ �����: ";
    getline(cin, input);
    printCenteredString(input);

    
    cout << "�������� ��� �� ����: " << systemTime << endl;

    
    cout << "������ ����� ��� �������� 10 �������: ";
    cin >> skip10;
    cout << "����� ����� ���� �������� 10 �������: " << skip10 << endl;

    return 0;
}
