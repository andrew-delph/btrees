#include <iostream>
using namespace std;
#include "bst.h"

void BST::put(string key, string value)
{
    Item *item = new Item;
    item->key = key;
    item->value = value;
    if (root == NULL)
    {
        root = new Node(item);
        return;
    }

    Node *temp = find(key);
    temp->item = item;
}

string BST::get(string key)
{
    Node *node = find(key);
    if (node == nullptr)
    {
        return "";
    }

    return node->item->value;
}

Node *BST::find(string key)
{

    Node *temp = root;
    while (temp != NULL)
    {
        if (temp->item->key == key)
        {
            break;
        }
        else if (temp->item->key < key)
        {
            if (temp->left == NULL)
            {
                Item *item = new Item;
                Node *next = new Node(item);
                temp->left = next;
                return next;
            }
            temp = temp->left;
        }
        else if (temp->item->key > key)
        {
            if (temp->right == NULL)
            {
                Item *item = new Item;
                Node *next = new Node(item);
                temp->right = next;
                return next;
            }
            temp = temp->right;
        }
    }
    return temp;
}
