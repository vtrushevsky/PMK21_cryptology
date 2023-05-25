#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Talon {
    string subject_name;
    int score;
    string teacher_surname;
};

struct Student {
    string name;
    string group;
    vector<Talon> talons;
};

// Function to read data from a file and populate an array of students
void readDataFromFile(string filename, vector<Student>& students) {
    ifstream infile(filename);
    string line;

    while (getline(infile, line)) {
        Student s;
        s.name = line;
        getline(infile, s.group);

        int num_talons;
        infile >> num_talons;

        for (int i = 0; i < num_talons; i++) {
            Talon t;
            infile >> t.subject_name >> t.score >> t.teacher_surname;
            s.talons.push_back(t);
        }

        students.push_back(s);
    }

    infile.close();
}

// Function to write list of students with more than one talon to a file
void writeStudentsWithMultipleTalonsToFile(vector<Student>& students, string filename) {
    ofstream outfile(filename);

    for (auto s : students) {
        if (s.talons.size() > 1) {
            outfile << s.name << endl;
            outfile << s.group << endl;
            outfile << s.talons.size() << endl;

            for (auto t : s.talons) {
                outfile << t.subject_name << " " << t.score << " " << t.teacher_surname << endl;
            }

            outfile << endl;
        }
    }

    outfile.close();
}

// Function to write surname of the teacher with most talons to a file
void writeTeacherWithMostTalonsToFile(vector<Student>& students, string filename) {
    ofstream outfile(filename);

    // Create a map to count occurrences of each teacher surname
    map<string, int> teacher_counts;
    for (auto s : students) {
        for (auto t : s.talons) {
            teacher_counts[t.teacher_surname]++;
        }
    }

    // Find the surname with the most talons
    string most_common_surname;
    int max_count = 0;
    for (auto p : teacher_counts) {
        if (p.second > max_count) {
            most_common_surname = p.first;
            max_count = p.second;
        }
    }

    outfile << most_common_surname << endl;

    outfile.close();
}

int main() {
    vector<Student> students;
    readDataFromFile("input.txt", students);

    writeStudentsWithMultipleTalonsToFile(students, "output1.txt");

    writeTeacherWithMostTalonsToFile(students, "output2.txt");

    return 0;
}
