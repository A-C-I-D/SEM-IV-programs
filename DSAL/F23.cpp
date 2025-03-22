//Department maintains a student information. The file contains roll number, name, division, and address. Allow user to add delete information of student. Display information of particular student. If record of student does not exist an appropriate message is displayed. If it is, then the system displays the student details. Use sequential file to maintain the data.


#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Student {
    int roll;
    string name, division, address;
};

void addStudent() {
    ofstream file("students.txt", ios::app);
    Student s;
    cout << "Enter Roll No: "; cin >> s.roll;
    cout << "Enter Name: "; cin.ignore(); getline(cin, s.name);
    cout << "Enter Division: "; getline(cin, s.division);
    cout << "Enter Address: "; getline(cin, s.address);
    file << s.roll << " " << s.name << " " << s.division << " " << s.address << "\n";
    file.close();
    cout << "Student added successfully.\n";
}

void displayStudent(int roll) {
    ifstream file("students.txt");
    Student s;
    bool found = false;
    while (file >> s.roll) {
        file.ignore();
        getline(file, s.name, ' ');
        getline(file, s.division, ' ');
        getline(file, s.address);
        if (s.roll == roll) {
            cout << "\nStudent Details:\n";
            cout << "Roll No: " << s.roll << "\nName: " << s.name << "\nDivision: " << s.division << "\nAddress: " << s.address << "\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "Record not found.\n";
    file.close();
}

void deleteStudent(int roll) {
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    Student s;
    bool found = false;
    while (file >> s.roll) {
        file.ignore();
        getline(file, s.name, ' ');
        getline(file, s.division, ' ');
        getline(file, s.address);
        if (s.roll == roll) found = true;
        else temp << s.roll << " " << s.name << " " << s.division << " " << s.address << "\n";
    }
    file.close();
    temp.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    if (found) cout << "Record deleted successfully.\n";
    else cout << "Record not found.\n";
}

int main() {
    int choice, roll;
    do {
        cout << "\n1. Add Student\n2. Display Student\n3. Delete Student\n4. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addStudent(); break;
            case 2: cout << "Enter Roll No: "; cin >> roll; displayStudent(roll); break;
            case 3: cout << "Enter Roll No: "; cin >> roll; deleteStudent(roll); break;
        }
    } while (choice != 4);
    return 0;
}
