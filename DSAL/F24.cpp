//Company maintains employee information as employee ID, name, designation, and salary. Allow user to add delete information of particular employee. If employee does not exist an appropriate message is displayed. If it is, then system displays the employee details. Use index sequential file to maintain the data

#include <iostream>
#include <fstream>
#include <map>
using namespace std;

struct Employee {
    int id;
    string name, designation;
    double salary;
};

map<int, Employee> employeeIndex;

void loadIndex() {
    ifstream file("employees.txt");
    Employee e;
    while (file >> e.id) {
        file.ignore();
        getline(file, e.name, ' ');
        getline(file, e.designation, ' ');
        file >> e.salary;
        employeeIndex[e.id] = e;
    }
    file.close();
}

void saveData() {
    ofstream file("employees.txt");
    for (const auto &entry : employeeIndex) {
        file << entry.second.id << " " << entry.second.name << " " << entry.second.designation << " " << entry.second.salary << "\n";
    }
    file.close();
}

void addEmployee() {
    Employee e;
    cout << "Enter Employee ID: "; cin >> e.id;
    if (employeeIndex.count(e.id)) {
        cout << "Employee ID already exists.\n";
        return;
    }
    cout << "Enter Name: "; cin.ignore(); getline(cin, e.name);
    cout << "Enter Designation: "; getline(cin, e.designation);
    cout << "Enter Salary: "; cin >> e.salary;
    employeeIndex[e.id] = e;
    saveData();
    cout << "Employee added successfully.\n";
}

void displayEmployee(int id) {
    if (employeeIndex.count(id)) {
        Employee e = employeeIndex[id];
        cout << "\nEmployee Details:\n";
        cout << "ID: " << e.id << "\nName: " << e.name << "\nDesignation: " << e.designation << "\nSalary: " << e.salary << "\n";
    } else {
        cout << "Employee not found.\n";
    }
}

void deleteEmployee(int id) {
    if (employeeIndex.erase(id)) {
        saveData();
        cout << "Employee deleted successfully.\n";
    } else {
        cout << "Employee not found.\n";
    }
}

int main() {
    loadIndex();
    int choice, id;
    do {
        cout << "\n1. Add Employee\n2. Display Employee\n3. Delete Employee\n4. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addEmployee(); break;
            case 2: cout << "Enter Employee ID: "; cin >> id; displayEmployee(id); break;
            case 3: cout << "Enter Employee ID: "; cin >> id; deleteEmployee(id); break;
        }
    } while (choice != 4);
    return 0;
}
