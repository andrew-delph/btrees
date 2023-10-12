#include <iostream>
using namespace std;
#include "bst.h"

void BST::put(string key, string value)
{
    if (root == NULL)
    {
        root = new Node(key, value);
        return;
    }

    Node *temp = find(key);
    temp->value = value;
}

string BST::get(string key)
{
    Node *node = find(key);
    if (node == nullptr)

        return "";
    return node->value;
}

Node *BST::find(string key)
{

    Node *temp = root;
    while (temp != NULL)
    {
        if (temp->key == key)
        {
            break;
        }
        else if (temp->key < key)
        {
            if (temp->left == NULL)
            {
                Node *next = new Node(key, "");
                temp->left = next;
                return next;
            }
            temp = temp->left;
        }
        else if (temp->key > key)
        {
            if (temp->right == NULL)
            {
                Node *next = new Node(key, "");
                temp->right = next;
                return next;
            }
            temp = temp->right;
        }
    }
    return temp;
}
