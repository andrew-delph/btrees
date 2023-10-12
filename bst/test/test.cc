// test.cc
#include <cassert>

#include <iostream>
using namespace std;
#include "../bst.h"

void test_add()
{

    BST tree;

    tree.put("test1", "1");
    tree.put("test2", "2");
    tree.put("test0", "0");
    tree.put("test4", "4");

    assert(tree.get("test1") == "1");
    assert(tree.get("test2") == "2");
    assert(tree.get("test0") == "0");
    assert(tree.get("blank") == "");
    assert(tree.get("test4") == "4");
}

int main()
{
    test_add();
    return 0;
}
