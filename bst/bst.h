// addition.h
#include <iostream>
using namespace std;
#pragma once

class Node
{
public:
    Node(string key, string value) : key(key), value(value), left(nullptr), right(nullptr){};
    Node *left;
    Node *right;
    string key;
    string value;
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