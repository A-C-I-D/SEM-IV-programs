//Consider a scenario for hospital to cater services to different kind of patients as Serious (top priority), non-serious (Medium Priority), and General checkup (Least Priority). Implement priority queue to cater services to the patients

#include <iostream>
#include <queue>
using namespace std;

struct Patient {
    string name;
    int priority; // Higher number = Higher priority

    bool operator<(const Patient& p) const {
        return priority < p.priority; // Max-Heap (Higher priority comes first)
    }
};

class HospitalQueue {
    priority_queue<Patient> pq;

public:
    void addPatient(string name, int priority) {
        pq.push({name, priority});
        cout << name << " added with priority " << priority << ".\n";
    }

    void servePatient() {
        if (pq.empty()) {
            cout << "No patients in queue.\n";
            return;
        }
        cout << "Serving " << pq.top().name << " (Priority: " << pq.top().priority << ")\n";
        pq.pop();
    }

    void displayQueue() {
        if (pq.empty()) {
            cout << "No patients in queue.\n";
            return;
        }

        priority_queue<Patient> temp = pq;
        cout << "Current Queue:\n";
        while (!temp.empty()) {
            cout << temp.top().name << " (Priority: " << temp.top().priority << ")\n";
            temp.pop();
        }
    }
};

int main() {
    HospitalQueue hq;
    int choice, priority;
    string name;

    while (true) {
        cout << "\nHospital Queue Menu:\n";
        cout << "1. Add Patient\n2. Serve Patient\n3. Display Queue\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter Patient Name: ";
                getline(cin, name);
                cout << "Enter Priority (3-Serious, 2-Non-Serious, 1-General): ";
                cin >> priority;
                hq.addPatient(name, priority);
                break;
            case 2:
                hq.servePatient();
                break;
            case 3:
                hq.displayQueue();
                break;
            case 4:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}
