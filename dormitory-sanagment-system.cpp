#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Student {
    int id;
    string name;
    int roomNumber;

    void inputStudent() {
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Room Number: ";
        cin >> roomNumber;
    }

    void displayStudent() const {
        cout << "ID: " << id << ", Name: " << name << ", Room: " << roomNumber << endl;
    }
};

struct Dormitory {
    vector<Student> students;
    string filename = "students.txt";

    Dormitory() {
        loadFromFile();
    }

    void addStudent() {
        Student s;
        s.inputStudent();
        students.push_back(s);
        saveToFile();
        cout << "Student added successfully!\n";
    }

    void removeStudent(int id) {
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].id == id) {
                students.erase(students.begin() + i);
                saveToFile();
                cout << "Student removed successfully!\n";
                return;
            }
        }
        cout << "Student not found!\n";
    }

    void searchStudent(int id) const {
        for (const auto& s : students) {
            if (s.id == id) {
                s.displayStudent();
                return;
            }
        }
        cout << "Student not found!\n";
    }

    void displayStudents() const {
        if (students.empty()) {
            cout << "No students registered.\n";
            return;
        }
        for (const auto& s : students) {
            s.displayStudent();
        }
    }

    void saveToFile() const {
        ofstream file(filename);
        for (const auto& s : students) {
            file << s.id << " " << s.name << " " << s.roomNumber << endl;
        }
        file.close();
    }

    void loadFromFile() {
        students.clear();
        ifstream file(filename);
        Student s;
        while (file >> s.id) {
            file.ignore();
            getline(file, s.name, ' ');
            file >> s.roomNumber;
            students.push_back(s);
        }
        file.close();
    }
};

int main() {
    Dormitory dorm;
    int choice, id;
    
    while (true) {
        cout << "\nDormitory Management System\n";
        cout << "1. Add Student\n2. Remove Student\n3. Search Student\n4. Display Students\n5. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                dorm.addStudent();
                break;
            case 2:
                cout << "Enter student ID to remove: ";
                cin >> id;
                dorm.removeStudent(id);
                break;
            case 3:
                cout << "Enter student ID to search: ";
                cin >> id;
                dorm.searchStudent(id);
                break;
            case 4:
                dorm.displayStudents();
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}
