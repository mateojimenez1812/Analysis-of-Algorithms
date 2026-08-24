#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int val) {
        value = val;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree {
private:
    Node* root;

    Node* insertHelper(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->value) {
            node->left = insertHelper(node->left, value);
        } else {
            node->right = insertHelper(node->right, value);
        }
        return node;
    }

    void inorderHelper(Node* node) {
        if (node == nullptr) return;
        inorderHelper(node->left);
        cout << node->value << " ";
        inorderHelper(node->right);
    }

public:
    BinaryTree() {
        root = nullptr;
    }

    void insert(int value) {
        root = insertHelper(root, value);
    }

    void printInorder() {
        inorderHelper(root);
        cout << endl;
    }
};

int main() {
    BinaryTree tree;
    int values[] = { 50, 30, 70, 20, 40, 60, 80 };

    for (int v : values) {
        tree.insert(v);
    }

    cout << "Inorder traversal: ";
    tree.printInorder();

    return 0;
}
