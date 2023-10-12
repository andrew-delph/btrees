#include <iostream>
using namespace std;
#include "bst.h"

int main()
{
    cout << "starting.\n";

    BST tree;

    tree.put("helloz", "Test");

    cout << "get: " << tree.get("helloz");
}