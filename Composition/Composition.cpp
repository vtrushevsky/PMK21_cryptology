#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

class Talon {
public:
    string subjectName;
    int score;
    string professorLastName;

    Talon(const string& name, int score, const string& professor) {
        subjectName = name;
        this->score = score;
        professorLastName = professor;
    }
};

class Student {
public:
    string fullName;
    string group;
    vector<Talon> talons;

    Student(const string& name, const string& group) {
        fullName = name;
        this->group = group;
    }

    void addTalon(const Talon& talon) {
        talons.push_back(talon);
    }

    int getTalonCount() const {
        return talons.size();
    }
};

vector<Student> readStudentsFromFile(const string& filename) {
    vector<Student> students;
    ifstream file(filename);

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            string fullName, group, subjectName, professorLastName;
            int score;

            size_t pos = line.find(",");
            fullName = line.substr(0, pos);
            line = line.substr(pos + 1);

            pos = line.find(",");
            group = line.substr(0, pos);
            line = line.substr(pos + 1);

            pos = line.find(",");
            subjectName = line.substr(0, pos);
            line = line.substr(pos + 1);

            pos = line.find(",");
            score = stoi(line.substr(0, pos));
            professorLastName = line.substr(pos + 1);

            auto it = find_if(students.begin(), students.end(), [&](const Student& student) {
                return student.fullName == fullName && student.group == group;
                });

            if (it != students.end()) {
                Talon talon(subjectName, score, professorLastName);
                it->addTalon(talon);
            }
            else {
                Student student(fullName, group);
                Talon talon(subjectName, score, professorLastName);
                student.addTalon(talon);
                students.push_back(student);
            }
        }

        file.close();
    }

    return students;
}

void writeStudentsToFile(const vector<Student>& students, const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        for (const Student& student : students) {
            if (student.getTalonCount() > 1) {
                file << student.fullName << ", " << student.group << endl;
            }
        }

        file.close();
    }
}

string findMostFrequentProfessor(const vector<Student>& students) {
    map<string, int> professorCounts;

    for (const Student& student : students) {
        for (const Talon& talon : student.talons) {
            professorCounts[talon.professorLastName]++;
        }
    }

    string mostFrequentProfessor;
    int maxCount = 0;

    for (const auto& pair : professorCounts) {
        if (pair.second > maxCount) {
            mostFrequentProfessor = pair.first;
            maxCount = pair.second;
        }
    }

    return mostFrequentProfessor;
}

int main() {
    vector<Student> students = readStudentsFromFile("students.txt");

    writeStudentsToFile(students, "File1.txt");

    string mostFrequentProfessor = findMostFrequentProfessor(students);

    ofstream file("File2.txt");
    if (file.is_open()) {
        file << mostFrequentProfessor << endl;
        file.close();
    }

    return 0;
}
