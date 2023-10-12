#include <iostream>
using namespace std;
#include "bst.h"
#include <iostream>
#include <string>
#include <random>

#include <iostream>
#include <chrono>

string generateRandomString(int x)
{
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, sizeof(alphanum) - 2);

    string result;
    for (int i = 0; i < x; ++i)
    {
        result += alphanum[dis(gen)];
    }

    return result;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    Item *item = new Item;
    item->key = "zz";
    item->value = "xx";
    cout << item->key << "starting.\n";

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

    for (int i = 0; i < 100000; ++i)
    {
        string key = generateRandomString(5);
        string value = generateRandomString(5);
        tree.put(key, value);
    }

    auto finish = std::chrono::high_resolution_clock::now();

    // Calculate the difference between start and finish
    std::chrono::duration<double> elapsed = finish - start;

    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
}