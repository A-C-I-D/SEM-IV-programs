//A Dictionary stores keywords & its meanings. Provide facility for adding new keywords, deleting keywords, updating values of any entry. Provide facility to display whole data sorted in ascending/ Descending order. Also find how many maximum comparisons may require for finding any keyword. Use Height balance tree and find the complexity for finding a keyword

#include <iostream>
#include <string>
using namespace std;

struct Node {
    string keyword, meaning;
    Node *left, *right;
    int height;
    Node(string k, string m) : keyword(k), meaning(m), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
    Node* root;

    int height(Node* n) { return n ? n->height : 0; }

    int balanceFactor(Node* n) { return n ? height(n->left) - height(n->right) : 0; }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T = x->right;
        x->right = y;
        y->left = T;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T = y->left;
        y->left = x;
        x->right = T;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    Node* insert(Node* node, string key, string meaning) {
        if (!node) return new Node(key, meaning);
        if (key < node->keyword) node->left = insert(node->left, key, meaning);
        else if (key > node->keyword) node->right = insert(node->right, key, meaning);
        else node->meaning = meaning;

        node->height = max(height(node->left), height(node->right)) + 1;
        int balance = balanceFactor(node);

        if (balance > 1 && key < node->left->keyword) return rotateRight(node);
        if (balance < -1 && key > node->right->keyword) return rotateLeft(node);
        if (balance > 1 && key > node->left->keyword) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && key < node->right->keyword) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    Node* minValueNode(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

    Node* deleteNode(Node* root, string key) {
        if (!root) return root;
        if (key < root->keyword) root->left = deleteNode(root->left, key);
        else if (key > root->keyword) root->right = deleteNode(root->right, key);
        else {
            if (!root->left || !root->right) return root->left ? root->left : root->right;
            Node* temp = minValueNode(root->right);
            root->keyword = temp->keyword;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->keyword);
        }

        root->height = max(height(root->left), height(root->right)) + 1;
        int balance = balanceFactor(root);

        if (balance > 1 && balanceFactor(root->left) >= 0) return rotateRight(root);
        if (balance > 1 && balanceFactor(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        if (balance < -1 && balanceFactor(root->right) <= 0) return rotateLeft(root);
        if (balance < -1 && balanceFactor(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
        return root;
    }

    void inOrder(Node* node) {
        if (node) {
            inOrder(node->left);
            cout << node->keyword << ": " << node->meaning << endl;
            inOrder(node->right);
        }
    }

    void reverseInOrder(Node* node) {
        if (node) {
            reverseInOrder(node->right);
            cout << node->keyword << ": " << node->meaning << endl;
            reverseInOrder(node->left);
        }
    }

    int search(Node* node, string key, int comparisons = 0) {
        if (!node) return comparisons;
        comparisons++;
        if (key == node->keyword) return comparisons;
        if (key < node->keyword) return search(node->left, key, comparisons);
        return search(node->right, key, comparisons);
    }

public:
    AVLTree() : root(nullptr) {}

    void addKeyword(string key, string meaning) {
        root = insert(root, key, meaning);
    }

    void deleteKeyword(string key) {
        root = deleteNode(root, key);
    }

    void updateKeyword(string key, string newMeaning) {
        root = insert(root, key, newMeaning);
    }

    void displayAscending() {
        cout << "Dictionary (Ascending Order):\n";
        inOrder(root);
    }

    void displayDescending() {
        cout << "Dictionary (Descending Order):\n";
        reverseInOrder(root);
    }

    void findKeyword(string key) {
        int comparisons = search(root, key);
        if (comparisons > 0)
            cout << "Keyword found in " << comparisons << " comparisons.\n";
        else
            cout << "Keyword not found.\n";
    }

    int maxComparisons() {
        return height(root);
    }
};

int main() {
    AVLTree dict;
    int choice;
    string key, meaning;

    while (true) {
        cout << "\nDictionary Menu:\n";
        cout << "1. Add Keyword\n";
        cout << "2. Delete Keyword\n";
        cout << "3. Update Keyword Meaning\n";
        cout << "4. Search for Keyword\n";
        cout << "5. Display in Ascending Order\n";
        cout << "6. Display in Descending Order\n";
        cout << "7. Max Comparisons for Search\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                getline(cin, key);
                cout << "Enter meaning: ";
                getline(cin, meaning);
                dict.addKeyword(key, meaning);
                cout << "Keyword added.\n";
                break;
            case 2:
                cout << "Enter keyword to delete: ";
                getline(cin, key);
                dict.deleteKeyword(key);
                cout << "Keyword deleted.\n";
                break;
            case 3:
                cout << "Enter keyword to update: ";
                getline(cin, key);
                cout << "Enter new meaning: ";
                getline(cin, meaning);
                dict.updateKeyword(key, meaning);
                cout << "Keyword updated.\n";
                break;
            case 4:
                cout << "Enter keyword to search: ";
                getline(cin, key);
                dict.findKeyword(key);
                break;
            case 5:
                dict.displayAscending();
                break;
            case 6:
                dict.displayDescending();
                break;
            case 7:
                cout << "Max comparisons for search: " << dict.maxComparisons() << endl;
                break;
            case 8:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}
