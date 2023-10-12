#include <iostream>
using namespace std;
#include "bst.h"

void BST::put(string key, string value)
{
    root = new Node(key, value);
    cout
        << "key: " << key << " value: " << value << "\n";
}

string BST::get(string key)
{

    if (root == nullptr)
        return "";
    return root->value;
}
