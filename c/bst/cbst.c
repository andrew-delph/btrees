#include <stdio.h>
#include <string.h>
#include "utils.h"
#include <assert.h>

struct Node
{
    struct Node *left;
    struct Node *right;
    char *key;
    char *value;
    int height;
};

struct Cbst
{
    struct Node *root;
};

struct Node *create_node()
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        // Handle memory allocation failure
        exit(1);
    }

    newNode->left = NULL;
    newNode->right = NULL;
    newNode->key = NULL;
    newNode->value = NULL;
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

    newTree->root = NULL;
    return newTree;
}

void in_order_helper(struct Node *node)
{
    if (node == NULL)
    {
        return;
    }
    in_order_helper(node->left);
    printf(" %s", node->key);
    in_order_helper(node->right);
}

void in_order(struct Cbst *tree)
{
    printf("in_order:");
    in_order_helper(tree->root);
    printf("\n");
}

void pre_order_helper(struct Node *node)
{
    if (node == NULL)
    {
        return;
    }
    printf(" %s", node->key);
    pre_order_helper(node->left);
    pre_order_helper(node->right);
}

void pre_order(struct Cbst *tree)
{
    printf("pre_order:");
    pre_order_helper(tree->root);
    printf("\n");
}

int get_height(struct Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->height;
}

int get_balance(struct Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return get_height(node->left) - get_height(node->right);
}

struct Node *left_rotate(struct Node *node)
{
    printf("left balance %d %d\n", get_balance(node), node->right != NULL);
    struct Node *right = (node->right != NULL) ? node->right : create_node(node);
    struct Node *temp = (right->left != NULL) ? right->left : create_node(right);
    temp->left = node;
    node->right = temp;
    // TODO update height
    return right;
}

struct Node *right_rotate(struct Node *node)
{
    printf("left balance %d %d\n", get_balance(node), node->right != NULL);
    struct Node *left = (node->left != NULL) ? node->left : create_node(node);
    struct Node *temp = (left->right != NULL) ? left->right : create_node(left);
    temp->right = node;
    node->left = temp;
    // TODO update height
    return left;
}

struct Node *insert_node(struct Node *node, char key[], char value[])
{
    if (node == NULL)
    {
        node = create_node();
        node->key = key;
        node->value = value;
        return node;
    }
    int comp = strcmp(node->key, key);
    if (comp > 0)
    {
        node->right = insert_node(node->right, key, value);
    }
    else if (comp < 0)
    {
        node->left = insert_node(node->left, key, value);
    }
    else
    {
        node->key = key;
        node->value = value;
    }

    return node;
}

struct Node *insert(struct Cbst *tree, char key[], char value[])
{
    if (tree->root == NULL)
    {
        tree->root = create_node();
        tree->root->key = key;
        tree->root->value = value;
        return tree->root;
    }

    return insert_node(tree->root, key, value);
}

char *get_node(struct Node *node, char *key)
{
    if (node == NULL)
    {
        return NULL;
    }
    int comp = strcmp(node->key, key);
    if (comp > 0)
    {
        return get_node(node->right, key);
    }
    else if (comp < 0)
    {
        return get_node(node->left, key);
    }
    else
    {
        return node->value;
    }
}

char *get_value(struct Cbst *tree, char *key)
{
    return get_node(tree->root, key);
}

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void segfault_handler(int signal_num)
{
    printf("Caught segmentation fault! Exiting...\n");
    exit(1);
}

int dataNum = 100;
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
        insert(tree, str, str);
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
        char *get = get_value(tree, str);
        assert(get != NULL);
        assert(strcmp(get, str) == 0);
    }
}
int main()
{
    signal(SIGSEGV, segfault_handler);
    printf("started.\n");

    struct Cbst *tree = create_tree();

    assert(get_value(tree, "test") == NULL);

    insert_data(tree, 'c');
    insert_data(tree, 'y');
    insert_data(tree, 'z');

    // insert_item(tree, "b", "x");
    // printf("--------\n");
    // insert_item(tree, "b", "x");
    // insert_data(tree, 'x');

    assert_data(tree, 'c');
    assert_data(tree, 'y');
    assert_data(tree, 'z');

    // printf("--------\n");
    // in_order(tree);
    // pre_order(tree);

    printf("DONE.\n");

    return 0;
}
