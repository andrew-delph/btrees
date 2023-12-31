#include <stdio.h>
#include <string.h>
#include <assert.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

struct Node
{
    struct Node *left;
    struct Node *right;
    char *key;
    char *value;
    int height;
};

struct Avl
{
    struct Node *root;
};

struct Node *create_node()
{

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        // Handle memory allocation failure
        printf("HERE!\n");
        exit(1);
    }

    newNode->left = NULL;
    newNode->right = NULL;
    newNode->key = NULL;
    newNode->value = NULL;
    return newNode;
}

struct Avl *create_tree()
{
    struct Avl *newTree = (struct Avl *)malloc(sizeof(struct Avl));
    if (newTree == NULL)
    {
        // Handle memory allocation failure
        exit(1);
    }

    newTree->root = NULL;
    return newTree;
}

int size_helper(struct Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return 1 + size_helper(node->left) + size_helper(node->right);
}

int size(struct Avl *tree)
{
    printf("size: %d\n", size_helper(tree->root));
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

void in_order(struct Avl *tree)
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

void pre_order(struct Avl *tree)
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
    struct Node *right = node->right;
    struct Node *temp = right->left;
    // struct Node *right = (node->right != NULL) ? node->right : create_node(node);
    // struct Node *temp = (right->left != NULL) ? right->left : create_node(right);
    right->left = node;
    node->right = temp;
    // TODO update height
    node->height = 1 + max(get_height(node->left), get_height(node->right));
    right->height = 1 + max(get_height(right->left), get_height(right->right));

    return right;
}

struct Node *right_rotate(struct Node *node)
{
    struct Node *left = node->left;
    struct Node *temp = left->right;
    // struct Node *left = (node->left != NULL) ? node->left : create_node(node);
    // struct Node *temp = (left->right != NULL) ? left->right : create_node(left);
    left->right = node;
    node->left = temp;
    // TODO update height
    node->height = 1 + max(get_height(node->left), get_height(node->right));
    left->height = 1 + max(get_height(left->left), get_height(left->right));

    return left;
}

struct Node *insert(struct Node *node, char key[], char value[])
{
    if (node == NULL || node->key == NULL)
    {
        node = create_node();
        node->key = key;
        node->value = value;
        return node;
    }
    int comp = strcmp(key, node->key);
    if (comp > 0)
    {
        node->right = insert(node->right, key, value);
    }
    else if (comp < 0)
    {
        node->left = insert(node->left, key, value);
    }
    else
    {
        node->key = key;
        node->value = value;
        return node;
    }

    node->height = 1 + max(get_height(node->left), get_height(node->right));

    int balance = get_balance(node);
    if (balance > 1)
    {
        if (strcmp(key, node->left->key) < 0)
        {

            return right_rotate(node);
        }
        else
        {
            node->left = left_rotate(node->left);
            return right_rotate(node);
        }
    }
    if (balance < -1)
    {
        if (strcmp(key, node->right->key) > 0)
        {

            return left_rotate(node);
        }
        else
        {
            node->right = right_rotate(node->right);
            return left_rotate(node);
        }
    }

    return node;
}

struct Node *insert(struct Avl *tree, char key[], char value[])
{
    tree->root = insert(tree->root, key, value);
    return tree->root;
}

char *get_node(struct Node *node, char *key)
{
    if (node == NULL)
    {
        return NULL;
    }
    int comp = strcmp(key, node->key);

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

char *get_value(struct Avl *tree, char *key)
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

int dataNum = 3000;
void insert_data(struct Avl *tree, char c)
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

void fisherYatesShuffle(char *arr[], int n)
{
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        // Swap arr[i] and arr[j]
        char *temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void insert_data_ints(struct Avl *tree)
{

    char *keys[dataNum];

    // Initialize keys array with string values "0" to "100"
    for (int i = 0; i < dataNum; i++)
    {
        keys[i] = malloc(10);           // Allocate memory for the string
        snprintf(keys[i], 10, "%d", i); // Convert integer to string
    }

    fisherYatesShuffle(keys, dataNum);

    for (int i = 0; i < dataNum; i++)
    {
        insert(tree, keys[i], "x");
    }
}

void assert_data(struct Avl *tree, char c)
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

    struct Avl *tree = create_tree();

    assert(get_value(tree, "test") == NULL);

    // insert(tree, "2", "X");
    // insert(tree, "3", "X");
    // insert(tree, "4", "X");
    // insert(tree, "1", "X");
    // insert(tree, "aa", "X");
    // insert(tree, "a", "X");

    insert_data_ints(tree);

    // insert_data(tree, 'c');

    insert_data(tree, 'c');
    insert_data(tree, 'y');
    insert_data(tree, 'z');

    // insert_item(tree, "b", "x");
    // printf("--------\n");
    // insert_item(tree, "b", "x");
    // insert_data(tree, 'x');

    // in_order(tree);
    // pre_order(tree);

    printf("height: %d\n", get_height(tree->root));
    size(tree);

    printf("tget_test: %s\n", get_value(tree, "2"));

    assert_data(tree, 'c');
    assert_data(tree, 'y');
    assert_data(tree, 'z');

    // printf("--------\n");

    printf("DONE.\n");

    return 0;
}
