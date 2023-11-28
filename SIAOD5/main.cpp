#include <bits/stdc++.h>
using namespace std;

struct Node {
    char key;
    struct Node *left, *right;
    int height;
};

int max(int a, int b);

int height(Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b)? a : b;
}

Node* newNode(char key) {
    Node* node = new Node();
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return(node);
}

Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(Node *Node) {
    if (Node == NULL)
        return 0;
    return height(Node->left) - height(Node->right);
}

Node* insert(Node* node, char key) {
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node *search(Node* root, char key) {
    if (root == NULL || root->key == key)
        return root;

    if (root->key < key)
        return search(root->right, key);

    return search(root->left, key);
}

void symBreadthFirstSearch(Node* root) {
    if (root == NULL)
        return;

    std::queue<Node*> q;
    q.push(root);
    q.push(NULL);

    while (!q.empty()) {
        Node* node = q.front();
        q.pop();

        if (node == NULL) {
            if (!q.empty()) {
                q.push(NULL);
            }
        } else {
            std::cout << node->key << " ";

            if (node->left != NULL)
                q.push(node->left);

            if (node->right != NULL)
                q.push(node->right);
        }
    }
}

void breadthFirstSearch(Node* root) {
    if (root == NULL)
        return;

    std::queue<Node*> queue;
    queue.push(root);

    while (!queue.empty()) {
        Node* node = queue.front();
        queue.pop();
        std::cout << node->key << " ";

        if (node->left != NULL)
            queue.push(node->left);

        if (node->right != NULL)
            queue.push(node->right);
    }
}

int sumLeaves(Node* root) {
    if (root == NULL)
        return 0;

    if (root->left == NULL && root->right == NULL)
        return root->key;

    return sumLeaves(root->left) + sumLeaves(root->right);
}

int heightFound(Node* root) {
    if (root == NULL)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

void printTree(Node* root, int space) {
    if (root == NULL)
        return;

    space += 10;

    printTree(root->right, space);

    std::cout << std::endl;
    for (int i = 10; i < space; i++)
        std::cout << " ";
    std::cout << root->key << "\n";

    printTree(root->left, space);
}

int main() {
    Node *root = NULL;
    root = insert(root, 's');
    root = insert(root, 't');
    root = insert(root, 'u');
    root = insert(root, 'v');
    root = insert(root, 'w');
    root = insert(root, 'x');
    root = insert(root, 'y');
    root = insert(root, 'z');
    printTree(root,1);

    if (search(root, 't') != NULL)
        cout << "Found t" << endl;
    else
        cout << "Not Found t" << endl;

    if (search(root, 'a') != NULL)
        cout << "Found a" << endl;
    else
        cout << "Not Found a" << endl;
    breadthFirstSearch(root);
    cout << endl;
    symBreadthFirstSearch(root);
    cout << endl;
    cout << sumLeaves(root) << endl;
    cout << heightFound(root);
    return 0;
}