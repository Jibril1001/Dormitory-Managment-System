#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct Student_F {
    string name;
    int id;
    int year;
};

struct Student_M {
    string name;
    int id;
    int year;
};

const int x = 30;
const int y = 6;

Student_F fstudents[x][y];
Student_M mstudents[x][y];

void main_menu_F();
void display_students_F();
void add_student_F();
void del_F();
void main_menu_M();
void save_students_F();
void load_students_F();
void save_students_M();
void load_students_M();
void display_students_M();
void add_student_M();
void del_M();
void main_menu();

char choice;

int main()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 11); // change text color to bright cyan

    cout << "                                          WELCOME TO ADDIS ABABA UNIVERSITY                   \n";
    cout << "                                          =================================                 \n";
    cout << "                                                            \n";
    cout << "                                          CNCS CAMPUS DORMITORY MANAGEMENT SYSTEM\n";
    cout << "                                          =======================================\n";
    cout << "                                                            \n";
    cout << "                             PLEASE MAXIMIZE FOR THE BEST VISIBILITY\n";

    load_students_M();
    load_students_F();

    main_menu();

    return 0;
}

void main_menu()
{
    const string correct_password = "1234";
    cout << "\nPlease Enter The Password: ";
    string input;
    cin >> input;

    if (input == correct_password) {
        char option;
        cout << "\nPlease Enter 'F' or 'f' For Female students\nPlease Enter 'M' or 'm' For Male Students: ";
        cin >> option;

        if (option == 'F' || option == 'f') {
            main_menu_F();
        }
        else if (option == 'M' || option == 'm') {
            main_menu_M();
        }
        else {
            cout << "INVALID INPUT\n";
        }
    }
    else {
        cout << "INVALID PASSWORD\n";
    }
    
    cout << "\nDo you want to try again? (press 'y' to continue / any other key to exit): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        main_menu();
    }
}

void main_menu_M()
{
    int option;
    bool validInput = true;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 11); // bright cyan

    cout << "\nMenu For Male Students:\n";
    cout << "1. Display students\n";
    cout << "2. Add student\n";
    cout << "3. Delete student\n";
    cout << "4. Switch to Female Students Menu\n";
    cout << "Enter your option: ";
    cin >> option;

    if(cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error: You entered a letter instead of an integer.\n";
        validInput = false;
    }

    if (validInput) {
        switch (option) {
            case 1:
                system("CLS");
                cout << "                                              MALE STUDENTS INFORMATION\n";
                cout << "                             PLEASE MAXIMIZE AND ZOOM IN FOR THE BEST VISIBILITY\n";
                display_students_M();
                break;
            case 2:
                system("CLS");
                cout << "                                             ADD STUDENT INFORMATION\n";
                add_student_M();
                break;
            case 3:
                system("CLS");
                cout << "                                             DELETE STUDENT INFORMATION\n";
                del_M();
                break;
            case 4:
                system("CLS");
                main_menu_F();
                return;
            default:
                cout << "INVALID INPUT\n";
                break;
        }
    }

    cout << "\nDo you want to return to the Male Students Menu? (press 'y' to continue / any other key to exit): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        system("CLS");
        main_menu_M();
    }

    save_students_M();
}

void display_students_M() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 2); // green

    for (int i = 0; i < x; i++) {
        cout << "Dorm Number " << i + 1 << "\t";
        for (int j = 0; j < y; j++) {
            // If no student is stored, display an indicator (using "0" here)
            if (mstudents[i][j].name.empty() && mstudents[i][j].id == 0 && mstudents[i][j].year == 0) {
                cout << setw(5) << "0" << " (ID: " << 0 << ") (" << 0 << " EC)\t";
            }
            else {
                cout << setw(5) << mstudents[i][j].name << " (ID: " << mstudents[i][j].id << ") (" << mstudents[i][j].year << " EC)\t";
            }
        }
        cout << endl;
    }
}

void add_student_M() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 9); // bright blue

    string name;
    int id, year;
    int count = 0;

    cout << "\nPLEASE ENTER THE APPROPRIATE ANSWER FOR THE FOLLOWING\n";
    cout << "Enter first name of the new student: ";
    cin >> name;
    cout << "Enter the year of entry (above 2010): ";
    cin >> year;
    cout << "Enter the ID of the new student (4 digits): ";
    cin >> id;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nError: You entered a letter instead of an integer.\n";
        return;
    }

    if (!name.empty() && id >= 1000 && id <= 9999 && year > 2010) {
        cout << "\nTHE FOLLOWING DORMS ARE FREE\n";
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                if (mstudents[i][j].id == 0) {
                    count++;
                    cout << "Dorm number " << i + 1 << ", place " << j + 1 << endl;
                }
            }
        }
        cout << "\nThere are " << count << " free spaces. Where do you want to add this student?\n";
        
        int dorm, place;
        cout << "Please enter the dorm number: ";
        cin >> dorm;
        cout << "Please enter the place in the dorm: ";
        cin >> place;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nError: Invalid input for dorm or place number.\n";
            return;
        }

        if (dorm < 1 || dorm > x || place < 1 || place > y) {
            cout << "Error: Dorm or place number out of range.\n";
            return;
        }

        if (mstudents[dorm - 1][place - 1].id == 0) {
            mstudents[dorm - 1][place - 1].name = name;
            mstudents[dorm - 1][place - 1].id = id;
            mstudents[dorm - 1][place - 1].year = year;
            cout << "New student added successfully.\n";
        }
        else {
            cout << "Error: No vacant space available at that location.\n";
        }
    }
    else {
        cout << "\nError: Invalid name, ID, or year.\n";
    }
}

void del_M() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 12); // bright red

    int id, year;
    cout << "\nEnter the year of entry (above 2010): ";
    cin >> year;
    cout << "Enter the ID of the student to delete (4 digits): ";
    cin >> id;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nError: You entered a letter instead of an integer.\n";
        return;
    }

    bool foundStudent = false;
    for (int i = 0; i < x && !foundStudent; i++) {
        for (int j = 0; j < y; j++) {
            if (mstudents[i][j].id == id && mstudents[i][j].year == year) {
                // Reset student record to indicate a vacant space
                mstudents[i][j].name = "";
                mstudents[i][j].id = 0;
                mstudents[i][j].year = 0;
                foundStudent = true;
                break;
            }
        }
    }

    if (foundStudent) {
        cout << "A student with ID " << id << " and year of entry " << year << " deleted successfully.\n";
    }
    else {
        cout << "Student with ID " << id << " not found.\n";
    }
}

void main_menu_F()
{
    int option;
    bool validInput = true;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 11); // bright cyan

    cout << "\nMenu For Female Students:\n";
    cout << "1. Display students\n";
    cout << "2. Add student\n";
    cout << "3. Delete student\n";
    cout << "4. Switch to Male Students Menu\n";
    cout << "Enter your option: ";
    cin >> option;

    if(cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error: You entered a letter instead of an integer.\n";
        validInput = false;
    }

    if (validInput) {
        switch (option) {
            case 1:
                system("CLS");
                cout << "                                              FEMALE STUDENTS INFORMATION\n";
                cout << "                             PLEASE MAXIMIZE AND ZOOM IN FOR THE BEST VISIBILITY\n";
                display_students_F();
                break;
            case 2:
                system("CLS");
                cout << "                                             ADD STUDENT INFORMATION\n";
                add_student_F();
                break;
            case 3:
                system("CLS");
                cout << "                                             DELETE STUDENT INFORMATION\n";
                del_F();
                break;
            case 4:
                system("CLS");
                main_menu_M();
                return;
            default:
                cout << "INVALID INPUT\n";
                break;
        }
    }

    cout << "\nDo you want to return to the Female Students Menu? (press 'y' to continue / any other key to exit): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        system("CLS");
        main_menu_F();
    }

    save_students_F();
}

void display_students_F() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 2); // green

    for (int i = 0; i < x; i++) {
        cout << "Dorm Number " << i + 1 << "\t";
        for (int j = 0; j < y; j++) {
            if (fstudents[i][j].name.empty() && fstudents[i][j].id == 0 && fstudents[i][j].year == 0) {
                cout << setw(5) << "0" << " (ID: " << 0 << ") (" << 0 << " EC)\t";
            }
            else {
                cout << setw(5) << fstudents[i][j].name << " (ID: " << fstudents[i][j].id << ") (" << fstudents[i][j].year << " EC)\t";
            }
        }
        cout << endl;
    }
}

void add_student_F() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 9); // bright blue

    string name;
    int id, year;
    int count = 0;

    cout << "\nPLEASE ENTER THE APPROPRIATE ANSWER FOR THE FOLLOWING\n";
    cout << "Enter name of new student: ";
    cin >> name;
    cout << "Enter the year of entry (above 2010): ";
    cin >> year;
    cout << "Enter the ID of new student (4 digits): ";
    cin >> id;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nError: You entered an invalid input.\n";
        return;
    }

    if (!name.empty() && id >= 1000 && id <= 9999 && year > 2010) {
        cout << "\nTHE FOLLOWING DORMS ARE FREE\n";
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                if (fstudents[i][j].id == 0) {
                    count++;
                    cout << "Dorm number " << i + 1 << ", place " << j + 1 << endl;
                }
            }
        }
        cout << "\nThere are " << count << " free spaces. Where do you want to add this student?\n";

        int dorm, place;
        cout << "Please enter the dorm number: ";
        cin >> dorm;
        cout << "Please enter the place in the dorm: ";
        cin >> place;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nError: Invalid input for dorm or place number.\n";
            return;
        }

        if (dorm < 1 || dorm > x || place < 1 || place > y) {
            cout << "Error: Dorm or place number out of range.\n";
            return;
        }

        if (fstudents[dorm - 1][place - 1].id == 0) {
            fstudents[dorm - 1][place - 1].name = name;
            fstudents[dorm - 1][place - 1].id = id;
            fstudents[dorm - 1][place - 1].year = year;
            cout << "New student added successfully.\n";
        }
        else {
            cout << "Error: No vacant space available at that location.\n";
        }
    }
    else {
        cout << "\nError: Invalid name, ID, or year.\n";
    }
}

void del_F() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 12); // bright red

    int id, year;
    cout << "\nEnter the year of entry (above 2010): ";
    cin >> year;
    cout << "Enter the ID of the student to delete (4 digits): ";
    cin >> id;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nError: You entered an invalid input.\n";
        return;
    }

    bool foundStudent = false;
    for (int i = 0; i < x && !foundStudent; i++) {
        for (int j = 0; j < y; j++) {
            if (fstudents[i][j].id == id && fstudents[i][j].year == year) {
                fstudents[i][j].name = "";
                fstudents[i][j].id = 0;
                fstudents[i][j].year = 0;
                foundStudent = true;
                break;
            }
        }
    }

    if (foundStudent) {
        cout << "A student with ID " << id << " and year of entry " << year << " deleted successfully.\n";
    }
    else {
        cout << "Student with ID " << id << " not found.\n";
    }
}

void save_students_M() {
    ofstream malefilee("mstudents.txt");
    if (malefilee.is_open()) {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                malefilee << mstudents[i][j].name << " " 
                          << mstudents[i][j].id << " " 
                          << mstudents[i][j].year << "\n";
            }
        }
        malefilee.close();
        cout << "\nMale students saved to file successfully.\n";
    }
    else {
        cout << "\nError: Cannot open file for writing male students.\n";
    }
}

void load_students_M() {
    ifstream malefile("mstudents.txt");
    if (malefile.is_open()) {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                malefile >> mstudents[i][j].name 
                         >> mstudents[i][j].id 
                         >> mstudents[i][j].year;
            }
        }
        malefile.close();
        cout << "\nMale students loaded from file successfully.\n";
    }
    else {
        cout << "\nError: Cannot open file for reading male students.\n";
    }
}

void save_students_F() {
    ofstream femalefilee("fstudents.txt");
    if (femalefilee.is_open()) {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                femalefilee << fstudents[i][j].name << " " 
                            << fstudents[i][j].id << " " 
                            << fstudents[i][j].year << "\n";
            }
        }
        femalefilee.close();
        cout << "\nFemale students saved to file successfully.\n";
    }
    else {
        cout << "\nError: Cannot open file for writing female students.\n";
    }
}

void load_students_F() {
    ifstream femalefile("fstudents.txt");
    if (femalefile.is_open()) {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                femalefile >> fstudents[i][j].name 
                           >> fstudents[i][j].id 
                           >> fstudents[i][j].year;
            }
        }
        femalefile.close();
        cout << "\nFemale students loaded from file successfully.\n";
    }
    else {
        cout << "\nError: Cannot open file for reading female students.\n";
    }
}
