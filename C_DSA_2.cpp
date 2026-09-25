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

/* AVL Tree Insertion */
Node *insert(Node *root, int key) {
    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root;

    root->height = 1 + max(height(root->left),
                           height(root->right));

    int balance = getBalance(root);

    /* LL Case */
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    /* RR Case */
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    /* LR Case */
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    /* RL Case */
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

/* AVL Tree Search */
Node *search(Node *root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return search(root->left, key);

    return search(root->right, key);
}

int main() {
    Node *root = NULL;
    int key, k;

    /* Insert keys until -1 */
    while (1) {
        scanf("%d", &key);

        if (key == -1)
            break;

        root = insert(root, key);
    }

    /* Key to search */
    scanf("%d", &k);

    /* Search in AVL Tree */
    if (search(root, k) != NULL)
        printf("Key %d found in the AVL tree.\n", k);
    else
        printf("Key %d not found in the AVL tree.\n", k);

    return 0;
}
