#include <iostream>
#include <set>

using namespace std;

class SetADT {
private:
    set<int> elements;

public:
    void add(int element) {
        elements.insert(element);
    }

    void remove(int element) {
        elements.erase(element);
    }

    bool contains(int element) const {
        return elements.find(element) != elements.end();
    }

    int size() const {
        return elements.size();
    }

    void display() const {
        cout << "Set Elements: ";
        for (int element : elements) {
            cout << element << " ";
        }
        cout << endl;
    }

    static SetADT intersection(const SetADT& set1, const SetADT& set2) {
        SetADT result;
        for (int element : set1.elements) {
            if (set2.contains(element)) {
                result.add(element);
            }
        }
        return result;
    }

    static SetADT unionSet(const SetADT& set1, const SetADT& set2) {
        SetADT result = set1;
        for (int element : set2.elements) {
            result.add(element);
        }
        return result;
    }

    static SetADT difference(const SetADT& set1, const SetADT& set2) {
        SetADT result;
        for (int element : set1.elements) {
            if (!set2.contains(element)) {
                result.add(element);
            }
        }
        return result;
    }

    bool subset(const SetADT& otherSet) const {
        for (int element : elements) {
            if (!otherSet.contains(element)) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    SetADT set1, set2;
    int choice, element;
    cout << "\nMenu:\n";
    cout << "1. Add to Set1\n";
    cout << "2. Add to Set2\n";
    cout << "3. Remove from Set1\n";
    cout << "4. Check in Set1\n";
    cout << "5. Size of Set1\n";
    cout << "6. Display Set1\n";
    cout << "7. Display Set2\n";
    cout << "8. Intersection\n";
    cout << "9. Union\n";
    cout << "10. Difference\n";
    cout << "11. Subset Check\n";
    cout << "12. Exit\n";

    do {
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter element: ";
                cin >> element;
                set1.add(element);
                break;

            case 2:
                cout << "Enter element: ";
                cin >> element;
                set2.add(element);
                break;

            case 3:
                cout << "Enter element: ";
                cin >> element;
                set1.remove(element);
                break;

            case 4:
                cout << "Enter element: ";
                cin >> element;
                cout << (set1.contains(element) ? "Yes" : "No") << endl;
                break;

            case 5:
                cout << "Size: " << set1.size() << endl;
                break;

            case 6:
                set1.display();
                break;

            case 7:
                set2.display();
                break;

            case 8:
                SetADT::intersection(set1, set2).display();
                break;

            case 9:
                SetADT::unionSet(set1, set2).display();
                break;

            case 10:
                SetADT::difference(set1, set2).display();
                break;

            case 11:
                cout << (set1.subset(set2) ? "Set1 is a subset of Set2" : "Set1 is not a subset of Set2") << endl;
                break;

            case 12:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 12);
    return 0;
}