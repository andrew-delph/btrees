#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <assert.h>

#define T 3

void segfault_handler(int signal_num)
{
    printf("Caught segmentation fault! Exiting...\n");
    exit(1);
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

struct Item
{
    char *key;
    char *value;
};

struct Node
{
    int leaf;
    int length;
    struct Node *children;
    struct Item *items;
};

void items_append(struct Node *node, const char *key, const char *value)
{
    int new_length = node->length + 1;
    struct Item *new_items = (struct Item *)realloc(node->items, new_length * sizeof(struct Item));
    if (new_items == NULL)
    {
        // Handle memory allocation failure
        printf("Memory allocation failed!\n");
        exit(1);
    }

    new_items[new_length - 1].key = strdup(key);
    new_items[new_length - 1].value = strdup(value);

    node->items = new_items;
    node->length = new_length;
}

// Function to get the length of the Items structure
int items_length(const struct Node *node)
{
    return node->length;
}

struct Node *create_node(int leaf)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        // Handle memory allocation failure
        printf("HERE!\n");
        exit(1);
    }

    newNode->children = NULL;
    newNode->items = NULL;
    newNode->leaf = leaf;
    return newNode;
}

void print_node(struct Node *node)
{
    for (int i = 0; i < items_length(node->items); i++)
    {
        printf(" %s", node->items[i].key);
    }
}

// void in_order_helper(struct Node *node)
// {
//     if (node == NULL)
//     {
//         return;
//     }

//     in_order_helper(node->left);
//     print_node(node);
//     in_order_helper(node->right);
// }

struct Node *insert_node(struct Node *node, char key[], char value[])
{
    if (node == NULL)
    {
        node = create_node(0);
    }

    // insert to node

    // if node is over size. split

    return node;
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

struct Node *insert_data_ints(struct Node *root, int lower, int upper)
{
    int num = upper - lower;
    char *keys[num];

    // Initialize keys array with string values "0" to "100"
    for (int i = 0; i < num; i++)
    {
        int id = lower + i;
        keys[i] = malloc(10);            // Allocate memory for the string
        snprintf(keys[i], 10, "%d", id); // Convert integer to string
    }

    fisherYatesShuffle(keys, num);

    for (int i = 0; i < num; i++)
    {
        printf("key = %s\n", keys[i]);
        root = insert_node(root, keys[i], "x");
    }
    return root;
}

// int size_helper(struct Node *node)
// {
//     if (node == NULL)
//     {
//         return 0;
//     }
//     // printf("size_helper %d\n", node->items->length);

//     return node->items->length + size_helper(node->left) + size_helper(node->right);
// }

// int height_helper(struct Node *node)
// {
//     if (node == NULL)
//     {
//         return 0;
//     }
//     // printf("size_helper %d\n", node->items->length);

//     return 1 + max(height_helper(node->left), height_helper(node->right));
// }

int main()
{
    signal(SIGSEGV, segfault_handler);
    printf("started btree.\n");

    struct Node *root = create_node(1);

    int num = 10;
    root = insert_data_ints(root, 0, 100);

    // printf("inserted data.\n\n");

    // printf("in_order: ");
    // in_order_helper(root);
    // printf("\n\n");

    // int size = size_helper(root);
    // printf("size: %d\n", size);

    // int height = height_helper(root);
    // printf("height: %d\n", height);

    // assert(num == size);
    printf("\nDONE.\n");

    return 0;
}