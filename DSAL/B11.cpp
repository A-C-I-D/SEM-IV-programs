#include <iostream>
#include <string>
using namespace std;

struct Node {
    string keyword, meaning;
    Node *left, *right;
    Node(string k, string m) : keyword(k), meaning(m), left(nullptr), right(nullptr) {}
};

class BST {
    Node* root;
    Node* insert(Node* node, string k, string m) {
        if (!node) return new Node(k, m);
        if (k < node->keyword) node->left = insert(node->left, k, m);
        else if (k > node->keyword) node->right = insert(node->right, k, m);
        return node;
    }
    Node* findMin(Node* node) {
        while (node->left) node = node->left;
        return node;
    }
    Node* remove(Node* node, string k) {
        if (!node) return node;
        if (k < node->keyword) node->left = remove(node->left, k);
        else if (k > node->keyword) node->right = remove(node->right, k);
        else {
            if (!node->left) return node->right;
            if (!node->right) return node->left;
            Node* temp = findMin(node->right);
            node->keyword = temp->keyword;
            node->meaning = temp->meaning;
            node->right = remove(node->right, temp->keyword);
        }
        return node;
    }
    Node* search(Node* node, string k) {
        while (node) {
            if (k == node->keyword) return node;
            node = (k < node->keyword) ? node->left : node->right;
        }
        return nullptr;
    }
    void inorder(Node* node) {
        if (node) {
            inorder(node->left);
            cout << node->keyword << " : " << node->meaning << endl;
            inorder(node->right);
        }
    }
    void reverseInorder(Node* node) {
        if (node) {
            reverseInorder(node->right);
            cout << node->keyword << " : " << node->meaning << endl;
            reverseInorder(node->left);
        }
    }
public:
    BST() : root(nullptr) {}
    void add(string k, string m) { root = insert(root, k, m); }
    void remove(string k) { root = remove(root, k); }
    void update(string k, string m) {
        Node* node = search(root, k);
        if (node) node->meaning = m;
        else cout << "Keyword not found!" << endl;
    }
    void displayAscending() { inorder(root); }
    void displayDescending() { reverseInorder(root); }
    void maxComparisons(string k) {
        int comparisons = 0;
        Node* node = root;
        while (node) {
            comparisons++;
            if (k == node->keyword) break;
            node = (k < node->keyword) ? node->left : node->right;
        }
        cout << "Max comparisons: " << comparisons << endl;
    }
};

int main() {
    BST dict;
    int choice;
    string keyword, meaning;
    do {
        cout << "\n1. Add Keyword\n2. Delete Keyword\n3. Update Meaning\n4. Display Ascending\n5. Display Descending\n6. Find Max Comparisons\n7. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter keyword: "; cin >> keyword;
                cout << "Enter meaning: "; cin.ignore(); getline(cin, meaning);
                dict.add(keyword, meaning);
                break;
            case 2:
                cout << "Enter keyword to delete: "; cin >> keyword;
                dict.remove(keyword);
                break;
            case 3:
                cout << "Enter keyword to update: "; cin >> keyword;
                cout << "Enter new meaning: "; cin.ignore(); getline(cin, meaning);
                dict.update(keyword, meaning);
                break;
            case 4:
                dict.displayAscending();
                break;
            case 5:
                dict.displayDescending();
                break;
            case 6:
                cout << "Enter keyword to search: "; cin >> keyword;
                dict.maxComparisons(keyword);
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 7);
    return 0;
}