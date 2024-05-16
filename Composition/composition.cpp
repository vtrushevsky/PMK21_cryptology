#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Talon {
private:
    string subjectName;
    int points;
    string instructorLastName;

public:
    Talon(const string& subjectName, int points, const string& instructorLastName)
        : subjectName(subjectName), points(points), instructorLastName(instructorLastName) {}

    string getInstructorLastName() const {
        return instructorLastName;
    }

    int getPoints() const {
        return points;
    }

    string getSubjectName() const {
        return subjectName;
    }
};

class Student {
public:  
    string fullName;
    string group;
    vector<Talon> talons;

public:
    Student(const string& fullName, const string& group)
        : fullName(fullName), group(group) {}

    void addTalon(const Talon& talon) {
        talons.push_back(talon);
    }

    bool hasMultipleTalons() const {
        return talons.size() > 1;
    }

    const vector<Talon>& getTalons() const {
        return talons;
    }
};


vector<Student> readStudentsFromFile(const string& filename) {
    vector<Student> students;
    ifstream file(filename);

    if (file.is_open()) {
        string fullName;
        string group;
        string subjectName;
        int points;
        string instructorLastName;

        while (file >> fullName >> group >> subjectName >> points >> instructorLastName) {
            bool studentExists = false;
            for (Student& student : students) {
                if (student.fullName == fullName && student.group == group) {
                    student.addTalon(Talon(subjectName, points, instructorLastName));
                    studentExists = true;
                    break;
                }
            }
            if (!studentExists) {
                Student student(fullName, group);
                student.addTalon(Talon(subjectName, points, instructorLastName));
                students.push_back(student);
            }
        }

        file.close();
    }
    else {
        cout << "Failed to open file " << filename << endl;
    }

    return students;
}

void writeStudentsWithMultipleTalonsToFile(const vector<Student>& students, const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        for (const Student& student : students) {
            if (student.hasMultipleTalons()) {
                file << "Student: " << student.fullName << ", Group: " << student.group << endl;
                for (const Talon& talon : student.getTalons()) {
                    file << "Subject: " << talon.getSubjectName() << ", Points: " << talon.getPoints()
                        << ", Instructor: " << talon.getInstructorLastName() << endl;
                }
                file << endl;
            }
        }

        file.close();
    }
    else {
        cout << "Failed to open file " << filename << endl;
    }
}


string findMostFrequentInstructorLastName(const vector<Student>& students) {
    unordered_map<string, int> instructorCounts;

    for (const Student& student : students) {
        for (const Talon& talon : student.getTalons()) {
            instructorCounts[talon.getInstructorLastName()]++;
        }
    }

    string mostFrequentInstructorLastName;
    int maxCount = 0;

    for (const auto& pair : instructorCounts) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            mostFrequentInstructorLastName = pair.first;
        }
    }

    return mostFrequentInstructorLastName;
}

int main() {
    
    vector<Student> students = readStudentsFromFile("students.txt");

    
    writeStudentsWithMultipleTalonsToFile(students, "students_with_multiple_talons.txt");

    
    string mostFrequentInstructorLastName = findMostFrequentInstructorLastName(students);

    
    ofstream instructorFile("most_frequent_instructor.txt");
    if (instructorFile.is_open()) {
        instructorFile << "Most frequent instructor last name: " << mostFrequentInstructorLastName << endl;
        instructorFile.close();
    }
    else {
        cout << "Failed to open file most_frequent_instructor.txt" << endl;
    }

    return 0;
}
