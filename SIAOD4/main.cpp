#include <bits/stdc++.h>
using namespace std;

// Node of Binary Tree
struct Node
{
    int data;
    Node* left, * right;
};

// Function to create a new node
Node* newNode(int data)
{
    Node* temp = new Node;
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to replace Binary Tree with another
Node* replaceTreeWithSubtree(Node* root, int key, Node* subtree)
{
    if (root == NULL)
        return NULL;

    // if root key itself is the key
    if (root->data == key)
    {
        root = subtree;
        return root;
    }

    // search for the key in the left and right subtree
    root->left = replaceTreeWithSubtree(root->left, key, subtree);
    root->right = replaceTreeWithSubtree(root->right, key, subtree);

    return root;
}

void printTree(Node* root, string indent, bool last)
{
    if (root != NULL)
    {
        cout << indent;
        if (last)
        {
            cout << "R----";
            indent += "     ";
        }
        else
        {
            cout << "L----";
            indent += "|    ";
        }
        cout << root->data << endl;

        printTree(root->left, indent, false);
        printTree(root->right, indent, true);
    }
}

int main()
{
    Node* root = newNode(10);
    root->left = newNode(5);
    root->right = newNode(15);
    root->left->left = newNode(2);
    root->left->right = newNode(8);

    printTree(root, "",true);
    // Subtree to replace with
    Node* subtree = newNode(20);
    subtree->left = newNode(25);
    subtree->right = newNode(22);
    printTree(subtree, "",true);
    // Find node to be replaced and replace it with subtree
    root = replaceTreeWithSubtree(root, 8, subtree);
    printTree(root, "",true);
    return 0;
}