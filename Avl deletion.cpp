
#include <iostream>
using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;
    int height;
};

// Returns the height of a node
int height(Node* node) {
    if (node == NULL)
        return 0;

    return node->height;
}

// Returns the larger of two values
int maxValue(int a, int b) {
    if (a > b)
        return a;

    return b;
}

// Creates a new node
Node* newNode(int key) {
    Node* node = new Node();

    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

// Calculates the balance factor
int getBalance(Node* node) {
    if (node == NULL)
        return 0;

    return height(node->left) - height(node->right);
}

// Performs a right rotation
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + maxValue(height(y->left), height(y->right));
    x->height = 1 + maxValue(height(x->left), height(x->right));

    return x;
}

// Performs a left rotation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + maxValue(height(x->left), height(x->right));
    y->height = 1 + maxValue(height(y->left), height(y->right));

    return y;
}

// Inserts a new key into the AVL tree
Node* insert(Node* node, int key) {
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    // Update height
    node->height = 1 + maxValue(height(node->left), height(node->right));

    // Calculate balance factor
    int balance = getBalance(node);

    // LL Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // RR Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // LR Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Finds the node with the smallest key
Node* minValueNode(Node* node) {
    Node* current = node;

    // Keep moving left to find the smallest value
    while (current->left != NULL)
        current = current->left;

    return current;
}

// Deletes a key from the AVL tree
Node* deleteNode(Node* root, int key) {

    // Step 1: Perform normal BST deletion
    if (root == NULL)
        return root;

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    }
    else {

        // Case 1: Node has no child
        if (root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        }

        // Case 2: Node has only a right child
        else if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }

        // Case 3: Node has only a left child
        else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Case 4: Node has two children
        else {
            // Find inorder successor
            Node* temp = minValueNode(root->right);

            // Copy successor's value
            root->key = temp->key;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree became empty, return NULL
    if (root == NULL)
        return root;

    // Step 2: Update height
    root->height = 1 + maxValue(height(root->left), height(root->right));

    // Step 3: Calculate balance factor
    int balance = getBalance(root);

    // Step 4: Perform rotations if unbalanced

    // LL Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // LR Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // RL Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Displays the tree in inorder
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

int main() {
    Node* root = NULL;

    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 10);
    root = insert(root, 25);
    root = insert(root, 50);

    cout << "Before deletion: ";
    inorder(root);

    root = deleteNode(root, 20);

    cout << "\nAfter deletion: ";
    inorder(root);

    return 0;
}

