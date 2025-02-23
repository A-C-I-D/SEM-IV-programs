#include <iostream>
#include <list>
#include <vector>
using namespace std;

const int TABLE_SIZE = 10;

struct Client {
    string name;
    string phone;
};

class HashTableLinearProbing {
    vector<Client*> table;
public:
    HashTableLinearProbing() : table(TABLE_SIZE, nullptr) {}
    int hash(string key) {
        int sum = 0;
        for (char c : key) sum += c;
        return sum % TABLE_SIZE;
    }
    void insert(string name, string phone) {
        int index = hash(name);
        int i = index;
        while (table[i] != nullptr) {
            i = (i + 1) % TABLE_SIZE;
            if (i == index) return;
        }
        table[i] = new Client{name, phone};
    }
    string search(string name, int &comparisons) {
        int index = hash(name);
        int i = index;
        while (table[i] != nullptr) {
            comparisons++;
            if (table[i]->name == name) return table[i]->phone;
            i = (i + 1) % TABLE_SIZE;
            if (i == index) break;
        }
        return "Not found";
    }
};

class HashTableChaining {
    vector<list<Client>> table;
public:
    HashTableChaining() : table(TABLE_SIZE) {}
    int hash(string key) {
        int sum = 0;
        for (char c : key) sum += c;
        return sum % TABLE_SIZE;
    }
    void insert(string name, string phone) {
        int index = hash(name);
        table[index].push_back({name, phone});
    }
    string search(string name, int &comparisons) {
        int index = hash(name);
        for (auto &client : table[index]) {
            comparisons++;
            if (client.name == name) return client.phone;
        }
        return "Not found";
    }
};

int main() {
    HashTableLinearProbing linear;
    HashTableChaining chaining;
    
    int n;
    cout << "Enter number of clients: ";
    cin >> n;
    cin.ignore();
    
    for (int i = 0; i < n; i++) {
        string name, phone;
        cout << "Enter client name: ";
        getline(cin, name);
        cout << "Enter phone number: ";
        getline(cin, phone);
        linear.insert(name, phone);
        chaining.insert(name, phone);
    }
    
    string name;
    cout << "Enter name to search: ";
    getline(cin, name);
    int compLinear = 0, compChaining = 0;
    
    cout << "Linear Probing Search Result: " << linear.search(name, compLinear) << " (Comparisons: " << compLinear << ")\n";
    cout << "Chaining Search Result: " << chaining.search(name, compChaining) << " (Comparisons: " << compChaining << ")\n";
    
    return 0;
}
