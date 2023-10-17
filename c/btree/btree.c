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

struct Node *create_node(int leaf)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        // Handle memory allocation failure
        printf("HERE!\n");
        exit(1);
    }

    newNode->children = (struct Node *)malloc(2 * T * sizeof(struct Node));
    newNode->items = (struct Item *)malloc(2 * T * sizeof(struct Item));
    newNode->leaf = leaf;
    return newNode;
}

void items_insert(struct Item **items, int *length, const char *key, const char *value)
{
    // Increase the length of the array
    (*length)++;

    printf("length %d\n", *length);

    // // Reallocate memory to accommodate the new item
    // *items = (struct Item *)realloc(*items, (*length) * sizeof(struct Item));

    if (*items == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    int i = (*length) - 2;
    while (i >= 0)
    {
        int comp = strcmp(key, (*items)[i].key);
        int found = comp > 0;
        if (found)
        {
            break;
        }
        (*items)[i + 1].key = (*items)[i].key;
        (*items)[i + 1].value = (*items)[i].value;
        i--;
    }

    int index = i + 1;
    (*items)[index].key = key;
    (*items)[index].value = value;
}

// Function to get the length of the Items structure
int items_length(const struct Node *node)
{
    return node->length;
}

void print_items(struct Item *items, int length)
{
    for (int i = 0; i < length; i++)
    {
        printf(" [%s]", items[i].key);
    }
    printf("\n");
}

void test_items()
{
    printf("test_items\n");
    struct Item *items = NULL;
    int length = 0;
    items_insert(&items, &length, "b", "bb");
    print_items(items, 1);

    items_insert(&items, &length, "c", "cc");
    print_items(items, 2);

    items_insert(&items, &length, "d", "dd");
    print_items(items, 3);

    items_insert(&items, &length, "a", "aa");
    print_items(items, 4);
    // items = items_insert(items, 0, 2, "key4", "value4");
    // print_items(items, 3);
}

void split_child(struct Node *node, int index)
{

    // printf("xlen1: %d\n", node->length);
    struct Node *child = &node->children[index];
    printf("split_child index = %d length = %d\n", index, child->length);
    struct Node *parent = create_node(child->leaf);
    // printf("child len: %d\n", child->length);
    node->children[index + 1] = *parent;
    node->items[index] = child->items[0];
    for (int i = 0; i < T; i++)
    {
        parent->items[i] = child->items[T + i];
    }
    parent->length = T;
    for (int i = 0; i < T; i++)
    {
        child->items[i] = child->items[T + i];
    }
    child->length = T;
    if (child->leaf == 1)
    {
        printf("child is a leaf!\n");
        for (int i = 0; i <= T; i++)
        {
            parent->children[i] = child->children[T + i];
        }
        for (int i = 0; i < T; i++)
        {
            child->children[i] = child->children[i];
        }
    }
    // printf("xlen2: %d\n", node->length);
    // printf("child leaf: %d\n", child->leaf);
}

void insert_non_full(struct Node *node, char key[], char value[])
{
    int i = node->length - 1;

    if (node->leaf)
    {
        printf("LEAF!\n");
        items_insert(&node->items, &node->length, key, value);
    }
    else
    {
        printf("NON-LEAF!\n");
        int i = (node->length - 1);
        while (i >= 0 && strcmp(key, node->items[i].key) > 0)
        {
            i--;
        }
        i++;
        if (node->children[i].length >= (2 * T) - 1)
        {
            split_child(node, i);
            if (strcmp(key, node->items[i].key) > 0)
            {
                i++;
            }
        }
        insert_non_full(&node->children[i], key, value);
    }
}

struct Node *insert(struct Node *root, char key[], char value[])
{
    printf("----insert!\n");
    if (root == NULL)
    {
        printf("create root.\n");
        root = create_node(1);
    }

    if (root->length == T)
    {
        printf("root full.\n");
        struct Node *temp = create_node(0);
        temp->children[0] = *root;
        split_child(temp, 0);
        insert_non_full(temp, key, value);
        return temp;
    }
    else
    {
        insert_non_full(root, key, value);
        return root;
    }
}

void fisherYatesShuffle(char **array, int size)
{
    for (int i = size - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        char *temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

char **generate_keys(int lower, int upper)
{
    int num = upper - lower;
    char **keys = (char **)malloc(num * sizeof(char *));

    if (keys == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    // Initialize keys array with string values "0" to "100"
    for (int i = 0; i < num; i++)
    {
        int id = lower + i;
        keys[i] = (char *)malloc(10); // Allocate memory for the string

        if (keys[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(1);
        }

        snprintf(keys[i], 10, "%d", id); // Convert integer to string
    }

    fisherYatesShuffle(keys, num);

    return keys;
}

struct Node *insert_data_ints(struct Node *root, int lower, int upper)
{
    int num = upper - lower;
    char **keys = generate_keys(lower, upper);

    for (int i = 0; i < num; i++)
    {
        printf("\ni=%d", i);
        root = insert(root, keys[i], "x");
    }
    return root;
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

    // test_items();

    struct Node *root = create_node(1);

    root = insert_data_ints(root, 0, 1000);

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