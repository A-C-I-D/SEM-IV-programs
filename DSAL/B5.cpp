#include <iostream>
#include <vector>
using namespace std;

struct Node {
    string name;
    vector<Node*> children;
    Node(string n) : name(n) {}
};

class BookTree {
    Node* root;
public:
    BookTree(string bookName) { root = new Node(bookName); }
    Node* addNode(Node* parent, string name) {
        Node* newNode = new Node(name);
        parent->children.push_back(newNode);
        return newNode;
    }
    void printTree(Node* node, int depth = 0) {
        if (!node) return;
        for (int i = 0; i < depth; i++) cout << "  ";
        cout << node->name << endl;
        for (auto child : node->children) printTree(child, depth + 1);
    }
    void display() { printTree(root); }
    Node* getRoot() { return root; }
};

int main() {
    string bookName, chapterName, sectionName, subsectionName;
    int choice;
    cout << "Enter book title: ";
    getline(cin, bookName);
    BookTree book(bookName);
    
    do {
        cout << "\nMenu:\n1. Add Elements (Chapter, Section, Subsection)\n2. Display\n3. Exit\nEnter choice: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1: {
                cout << "Enter chapter name: ";
                getline(cin, chapterName);
                Node* ch = book.addNode(book.getRoot(), chapterName);
                
                cout << "Enter number of sections in " << chapterName << ": ";
                int sections;
                cin >> sections;
                cin.ignore();
                for (int j = 0; j < sections; j++) {
                    cout << "Enter section name: ";
                    getline(cin, sectionName);
                    Node* sec = book.addNode(ch, sectionName);
                    
                    cout << "Enter number of subsections in " << sectionName << ": ";
                    int subsections;
                    cin >> subsections;
                    cin.ignore();
                    for (int k = 0; k < subsections; k++) {
                        cout << "Enter subsection name: ";
                        getline(cin, subsectionName);
                        book.addNode(sec, subsectionName);
                    }
                }
                break;
            }
            case 2:
                cout << "\nBook Structure:\n";
                book.display();
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 3);
    
    return 0;
}
