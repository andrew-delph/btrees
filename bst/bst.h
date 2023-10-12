// addition.h
#include <iostream>
using namespace std;
#pragma once

struct Item
{
    std::string key;
    std::string value;
};

class Node
{
public:
    Node(Item *item) : item(item), left(nullptr), right(nullptr){};
    Node *left;
    Node *right;
    Item *item;
};

class BST
{
private:
    Node *root;

public:
    BST() : root(nullptr) {}
    void put(string key, string value);
    string get(string key);
    Node *find(string key);
};