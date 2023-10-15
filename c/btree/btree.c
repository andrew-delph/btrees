#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void segfault_handler(int signal_num)
{
    printf("Caught segmentation fault! Exiting...\n");
    exit(1);
}

struct Item
{
    char *key;
    char *value;
};

struct Items
{
    int length;
    struct Item *items;
};

struct Node
{
    struct Node *left;
    struct Node *right;
    struct Item *items;
};

struct Btree
{
    struct Node *root;
    int n;
};

struct Items *create_items()
{
    struct Items *items = (struct Items *)malloc(sizeof(struct Items));
    if (items == NULL)
    {
        // Handle memory allocation failure
        printf("Memory allocation failed!\n");
        exit(1);
    }
    items->length = 0;
    items->items = NULL;
    return items;
}

void items_append(struct Items *items, const char *key, const char *value)
{
    int new_length = items->length + 1;
    struct Item *new_items = (struct Item *)realloc(items->items, new_length * sizeof(struct Item));
    if (new_items == NULL)
    {
        // Handle memory allocation failure
        printf("Memory allocation failed!\n");
        exit(1);
    }

    new_items[new_length - 1].key = strdup(key);
    new_items[new_length - 1].value = strdup(value);

    items->items = new_items;
    items->length = new_length;
}

// Function to get the length of the Items structure
int items_length(const struct Items *items)
{
    return items->length;
}

int compare_items(const void *a, const void *b)
{
    const struct Item *itemA = (const struct Item *)a;
    const struct Item *itemB = (const struct Item *)b;

    return strcmp(itemA->key, itemB->key);
}

// Function to sort the items by the 'value' key
void sort_items(struct Items *items)
{
    qsort(items->items, items->length, sizeof(struct Item), compare_items);
}

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
    newNode->items = create_items();
    return newNode;
}

struct Btree *create_tree(int n)
{
    struct Btree *newTree = (struct Avl *)malloc(sizeof(struct Btree));
    if (newTree == NULL)
    {
        // Handle memory allocation failure
        exit(1);
    }

    newTree->root = NULL;
    newTree->n = n;
    return newTree;
}

struct Node *insert_node(struct Node *node, int n, char key[], char value[])
{
    if (node == NULL)
    {
        node = create_node(n);
    }

    return node;
}

struct Node *insert(struct Btree *tree, char key[], char value[])
{
    tree->root = insert_node(tree->root, tree->n, key, value);
    return tree->root;
}

int main()
{
    signal(SIGSEGV, segfault_handler);
    printf("started btree.\n");

    struct Btree *tree = create_tree(4);

    struct Items *items = create_items();

    printf("len %d\n", items_length(items));

    items_append(items, "key1", "value1");

    items_append(items, "key2", "value2");

    items_append(items, "a", "value2");

    items_append(items, "c", "value2");

    items_append(items, "b", "value2");

    printf("len %d\n", items_length(items));

    for (int i = 0; i < items_length(items); i++)
    {
        printf("Item %d: key = %s\n", i, items->items[i].key);
    }

    sort_items(items);

    printf("\nsorted.\n\n");

    for (int i = 0; i < items_length(items); i++)
    {
        printf("Item %d: key = %s\n", i, items->items[i].key);
    }

    printf("\nDONE.\n");

    return 0;
}