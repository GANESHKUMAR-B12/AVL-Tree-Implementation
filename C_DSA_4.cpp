#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

int height(Node *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node *createNode(int key) {
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->key = key;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

int getBalance(Node *node) {
    if (node == NULL)
        return 0;

    return height(node->left) - height(node->right);
}

Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

Node *insert(Node *root, int key) {
    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root;   // Ignore duplicate values

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // LL case
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    // RR case
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    // LR case
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL case
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int countGreater(Node *root, int x) {
    if (root == NULL)
        return 0;

    if (root->key > x) {
        return 1 + countGreater(root->left, x)
                 + countGreater(root->right, x);
    }

    return countGreater(root->right, x);
}

int main() {
    Node *root = NULL;
    int n, value, x;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        root = insert(root, value);
    }

    scanf("%d", &x);

    int count = countGreater(root, x);

    printf("Number of elements greater than %d are %d", x, count);

    return 0;
}
