#include <iostream>
using namespace std;
#include "bst.h"

int main()
{
    cout << "starting.\n";

    BST tree;

    tree.put("test1", "1");
    tree.put("test2", "2");
    tree.put("test0", "0");
    tree.put("test4", "4");

    cout << "1 " << tree.get("test1") << std::endl;
    cout << "2 " << tree.get("test2") << std::endl;
    cout << "0 " << tree.get("test0") << std::endl;

    cout << "blank: " << tree.get("???") << std::endl;

    cout << "4 " << tree.get("test4") << std::endl;

    // string str1 = "b";
    // string str2 = "c";

    // if (str1 == str2)
    // {
    //     cout << "str1 and str2 are equal." << std::endl;
    // }
    // else if (str1 > str2)
    // {
    //     cout << "str1 is greater than str2." << std::endl;
    // }
    // else
    // {
    //     cout << "str1 is less than str2." << std::endl;
    // }
}