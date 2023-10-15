#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <assert.h>

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
    struct Items *items;
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

    sort_items(items);
}

// Function to get the length of the Items structure
int items_length(const struct Items *items)
{
    return items->length;
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

void print_node(struct Node *node)
{
    for (int i = 0; i < items_length(node->items); i++)
    {
        printf(" %s", node->items->items[i].key);
    }
}

void in_order_helper(struct Node *node)
{
    if (node == NULL)
    {
        return;
    }

    in_order_helper(node->left);
    print_node(node);
    in_order_helper(node->right);
}

void in_order(struct Btree *tree)
{
    printf("in_order:");
    in_order_helper(tree->root);
    printf("\n");
}

struct Node *insert_node(struct Node *node, int n, char key[], char value[])
{
    if (node == NULL)
    {
        node = create_node(n);
    }

    if (items_length(node->items) < n)
    {
        items_append(node->items, key, value);
    }
    else
    {
        if (strcmp(key, node->items->items[0].key) < 0)
        {
            node->left = insert_node(node->left, n, key, value);
        }
        // else if (strcmp(key, node->items->items[n - 1].key) > 0)
        else
        {
            node->right = insert_node(node->right, n, key, value);
        }
    }

    return node;
}

struct Node *insert(struct Btree *tree, char key[], char value[])
{
    tree->root = insert_node(tree->root, tree->n, key, value);
    return tree->root;
}

// int dataNum = 3000;
// void insert_data(struct Btree *tree, char c)
// {

//     for (int i = 1; i <= dataNum; i++)
//     {
//         char *str = (char *)malloc(i + 1);
//         if (str == NULL)
//         {
//             printf("Memory allocation failed.\n");
//             return;
//         }
//         memset(str, c, i);
//         str[i] = '\0';
//         insert(tree, str, str);
//     }
// }

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

void insert_data_ints(struct Btree *tree, int num)
{

    char *keys[num];

    // Initialize keys array with string values "0" to "100"
    for (int i = 0; i < num; i++)
    {
        keys[i] = malloc(10);           // Allocate memory for the string
        snprintf(keys[i], 10, "%d", i); // Convert integer to string
    }

    fisherYatesShuffle(keys, num);

    for (int i = 0; i < num; i++)
    {
        insert(tree, keys[i], "x");
    }
}

int size_helper(struct Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    // printf("size_helper %d\n", node->items->length);

    return node->items->length + size_helper(node->left) + size_helper(node->right);
}

int size(struct Btree *tree)
{
    return size_helper(tree->root);
}

int main()
{
    signal(SIGSEGV, segfault_handler);
    printf("started btree.\n");

    struct Btree *tree = create_tree(10);

    int num = 55;
    insert_data_ints(tree, num);

    printf("inserted data.\n");

    in_order(tree);

    int count = size(tree);
    printf("count: %d\n", count);
    assert(num == count);
    printf("\nDONE.\n");

    return 0;
}