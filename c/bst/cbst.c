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

void pre_order(struct Cbst *tree)
{
    printf("pre_order:");
    pre_order_helper(tree->root);
    printf("\n");
}

void pre_order_helper(struct Node *node)
{
    if (node == NULL || node->item == NULL)
    {
        return;
    }
    printf(" %s-[%d]", node->item->key, getBalance(node), getNodeHeight(node));
    pre_order_helper(node->left);
    pre_order_helper(node->right);
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

struct Node *leftRotate(struct Node *node)
{
    printf("left balance %d %d\n", getBalance(node), node->right != NULL);
    struct Node *right = node->right;
    right->left = node;
    right->parent = node->parent;
    node->right = NULL;
    node->parent = right;
    updateHeight(node);
    return right;
}

struct Node *rightRotate(struct Node *node)
{
    printf("right balance %d %d\n", getBalance(node), node->left != NULL);
    struct Node *left = node->left;
    left->right = node;
    left->parent = node->parent;
    node->parent = left;
    node->left = NULL;
    updateHeight(node);
    return left;
}

void balanceNode(struct Cbst *tree, struct Node *node)
{
    if (node == NULL)
    {
        return;
    }

    int isRoot = tree->root == node;
    int balance = getBalance(node);
    if (balance > 1 || balance < -1)
    {
        printf("k = %s b = %d h = %d\n", node->item->key, balance, node->height);
    }
    if (balance > 1)
    {
        struct Node *r = rightRotate(node);

        if (isRoot)
        {
            printf("MOVED ROOT %d\n", r == NULL);
            tree->root = r;
        }
    }
    else if (balance < -1)
    {
        struct Node *l = leftRotate(node);
        if (isRoot)
        {
            printf("MOVED ROOT %d\n", l == NULL);
            tree->root = l;
        }
    }
    balanceNode(tree, node->parent);
    // balanceNode(tree, node->right);
}

struct Node *insert_item(struct Cbst *tree, char key[], char value[])
{
    struct Node *temp = get_node(tree, key);
    temp->item = create_item();
    temp->item->key = key;
    temp->item->value = value;
    updateHeight(temp);
    balanceNode(tree, temp);
    return temp;
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

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void segfault_handler(int signal_num)
{
    printf("Caught segmentation fault! Exiting...\n");
    exit(1);
}

int dataNum = 7;
void insert_data(struct Cbst *tree, char c)
{

    for (int i = 1; i <= dataNum; i++)
    {
        char *str = (char *)malloc(i + 1);
        if (str == NULL)
        {
            printf("Memory allocation failed.\n");
            return;
        }
        memset(str, c, i);
        str[i] = '\0';
        insert_item(tree, str, str);
    }
}

void assert_data(struct Cbst *tree, char c)
{
    for (int i = 1; i <= dataNum; i++)
    {
        char *str = (char *)malloc(i + 1);
        if (str == NULL)
        {
            printf("Memory allocation failed.\n");
            return;
        }
        memset(str, c, i);
        str[i] = '\0';
        char *get = get_item(tree, str);
        assert(get != NULL);
        assert(strcmp(get, str) == 0);
    }
}
int main()
{
    signal(SIGSEGV, segfault_handler);

    struct Cbst *tree = create_tree();

    insert_data(tree, 'c');

    // insert_item(tree, "b", "x");
    // printf("--------\n");
    // insert_item(tree, "b", "x");
    insert_data(tree, 'x');

    assert_data(tree, 'c');

    printf("--------\n");
    in_order(tree);
    pre_order(tree);
    assert_data(tree, 'c');

    printf("DONE.");

    return 0;
}
