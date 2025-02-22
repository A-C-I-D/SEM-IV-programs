#include <iostream>
#include <stack>
using namespace std;

struct Node {
    char data;
    Node *left, *right;
    Node(char val) : data(val), left(nullptr), right(nullptr) {}
};

Node* constructTree(const string& prefix) {
    stack<Node*> st;
    for (int i = prefix.size() - 1; i >= 0; i--) {
        Node* node = new Node(prefix[i]);
        if (isalpha(prefix[i])) st.push(node);
        else {
            node->left = st.top(); st.pop();
            node->right = st.top(); st.pop();
            st.push(node);
        }
    }
    return st.top();
}

void postorderTraversal(Node* root) {
    stack<Node*> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        Node* node = s1.top(); s1.pop();
        s2.push(node);
        if (node->left) s1.push(node->left);
        if (node->right) s1.push(node->right);
    }
    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
}

void deleteTree(Node* root) {
    stack<Node*> st;
    st.push(root);
    while (!st.empty()) {
        Node* node = st.top(); st.pop();
        if (node->left) st.push(node->left);
        if (node->right) st.push(node->right);
        delete node;
    }
}

int main() {
    string prefix;
    cout << "Enter prefix expression: ";
    cin >> prefix;
    Node* root = constructTree(prefix);
    postorderTraversal(root);
    cout << endl;
    deleteTree(root);
    return 0;
}
