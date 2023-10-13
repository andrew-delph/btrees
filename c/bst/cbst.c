#include <stdio.h>
#include <string.h>
#include "utils.h"
#include <assert.h>

struct Item
{
    char *key;
    char *value;
};

struct Node
{
    struct Node *left;
    struct Node *right;
    struct Item *item;
    struct Node *parent;
    int height;
};

struct Cbst
{
    struct Node *root;
};

struct Item *create_item()
{
    struct Item *newItem = (struct Item *)malloc(sizeof(struct Item));
    if (newItem == NULL)
    {
        // Handle memory allocation failure
        exit(1);
    }

    newItem->key = NULL;
    newItem->value = NULL;
    return newItem;
}

struct Node *create_node(struct Node *parent)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        // Handle memory allocation failure
        exit(1);
    }

    newNode->left = NULL;
    newNode->right = NULL;
    newNode->item = NULL; // Create a new Item for the node
    newNode->parent = parent;
    return newNode;
}

struct Cbst *create_tree()
{
    struct Cbst *newTree = (struct Cbst *)malloc(sizeof(struct Cbst));
    if (newTree == NULL)
    {
        // Handle memory allocation failure
        exit(1);
    }

    newTree->root = create_node(NULL);
    return newTree;
}

struct Node *get_node(struct Cbst *tree, char key[])
{
    struct Node *temp = tree->root;
    int count = 0;
    while (temp->item != NULL)
    {
        count++;
        // printf("height: %d\n", temp->height);

        int comp = strcmp(key, temp->item->key);
        if (comp > 0)
        {
            if (temp->right == NULL)
            {
                temp->right = create_node(temp);
                temp = temp->right;
                break;
            }
            temp = temp->right;
        }
        else if (comp < 0)
        {
            if (temp->left == NULL)
            {
                temp->left = create_node(temp);
                temp = temp->left;
                break;
            }
            temp = temp->left;
        }
        else
        {
            break;
        }
    }
    // printf("count = %d\n", count);
    return temp;
}

void insert_item(struct Cbst *tree, char key[], char value[])
{
    struct Node *temp = get_node(tree, key);
    temp->item = create_item();
    temp->item->key = key;
    temp->item->value = value;
    updateHeight(temp);
    balanceNode(temp);
}

char *get_item(struct Cbst *tree, char key[])
{
    struct Node *temp = get_node(tree, key);

    if (temp->item == NULL)
    {
        return NULL;
    }

    return temp->item->value;
}

void in_order(struct Cbst *tree)
{
    printf("in_order:");
    in_order_helper(tree->root);
    printf("\n");
}

void in_order_helper(struct Node *node)
{
    if (node == NULL || node->item == NULL)
    {
        return;
    }
    in_order_helper(node->left);
    printf(" %s", node->item->key);
    in_order_helper(node->right);
}

void updateHeight(struct Node *node)

{
    if (node == NULL)
    {
        return;
    }
    int leftHeight = 0;
    int rightHeight = 0;
    if (node->left != NULL)
    {
        leftHeight = node->left->height + 1;
    }
    if (node->right != NULL)
    {
        rightHeight = node->right->height + 1;
    }
    node->height = max(leftHeight, rightHeight);
    updateHeight(node->parent);
}

int getNodeHeight(struct Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->height;
}

int getTreeHeight(struct Cbst *tree)

{
    return getNodeHeight(tree->root);
}

int getBalance(struct Node *node)
{
    return getNodeHeight(node->left) - getNodeHeight(node->right);
}

int balanceNode(struct Node *node)
{
    int balance = getBalance(node);
    if (balance > 1)
    {
        printf("balance %d\n", balance);
    }
    else if (balance < -1)
    {
        printf("balance %d\n", balance);
    }
    return 1;
}

int rightRotate(struct Node *node)
{
    return 1;
}

int leftRotate(struct Node *node)
{
    return 1;
}

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void segfault_handler(int signal_num)
{
    printf("Caught segmentation fault! Exiting...\n");
    exit(1);
}

int main()
{
    signal(SIGSEGV, segfault_handler);

    struct Cbst *tree = create_tree();

    insert_item(tree, "b", "its b");

    assert(get_item(tree, "b") == "its b");
    assert(get_item(tree, "b") == "its b");

    insert_item(tree, "c", "its c");
    assert(get_item(tree, "b") == "its b");
    assert(get_item(tree, "b") == "its b");

    insert_item(tree, "a", "its a");

    insert_item(tree, "aa", "its a2");
    assert(get_item(tree, "b") == "its b");
    insert_item(tree, "aaa", "its a3");
    insert_item(tree, "aaaa", "its a4");
    insert_item(tree, "aaaaa", "its a5");

    assert(get_item(tree, "a") == "its a");
    assert(get_item(tree, "aa") == "its a2");
    assert(get_item(tree, "aaa") == "its a3");
    assert(get_item(tree, "aaaa") == "its a4");
    assert(get_item(tree, "aaaaa") == "its a5");
    assert(get_item(tree, "b") == "its b");

    insert_item(tree, "bb", "its b2");
    insert_item(tree, "ccc", "its c3");
    insert_item(tree, "aaaaaaa", "its a7");

    in_order(tree);

    printf("balance: %d\n", getBalance(tree->root));
    for (int i = 1; i <= 10; i++)
    {
        char *str = (char *)malloc(i + 1);
        if (str == NULL)
        {
            printf("Memory allocation failed.\n");
            return 1;
        }
        memset(str, 'c', i);
        str[i] = '\0';
        insert_item(tree, str, "extrac");
    }
    printf("balance: %d\n", getBalance(tree->root));

    assert(5 == 5);
    printf("DONE.");

    printf("min: %d, min %d\n", max(2, 5), max(2, 5));

    return 0;
}
