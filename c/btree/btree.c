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
    struct Node *children[2 * T];
    struct Item *items[2 * T];
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

    // newNode->children = (struct Node *)malloc(2 * T * sizeof(struct Node));
    // newNode->items = (struct Item *)malloc(2 * T * sizeof(struct Item));
    newNode->leaf = leaf;
    return newNode;
}

struct Item *create_item(char *key, char *value)
{
    struct Item *newItem = (struct Item *)malloc(sizeof(struct Item));
    if (newItem == NULL)
    {
        // Handle memory allocation failure
        printf("HERE!\n");
        exit(1);
    }

    // newNode->children = (struct Node *)malloc(2 * T * sizeof(struct Node));
    // newNode->items = (struct Item *)malloc(2 * T * sizeof(struct Item));
    // newNode->leaf = leaf;
    newItem->key = key;
    newItem->value = value;
    return newItem;
}

void print_items(struct Item **items, int length)
{
    for (int i = 0; i < length; i++)
    {
        printf(" [%s]", (*items[i]).key);
    }
    printf("\n");
}

int traverse(struct Node *node, int level)
{
    if (node == NULL || node->length == 0)
    {
        return 0;
    }
    int count = node->length;
    printf("t(%d)|  ", level);
    print_items(node->items, node->length);
    for (int i = 0; i < node->length + 1; i++)
    {
        count += traverse(&node->children[i], level + 1);
    }
    return count;
}

void items_insert(struct Item **items, int *length, char *key, char *value)
{
    // Increase the length of the array
    (*length)++;

    printf("length %d\n", *length);
    items[(*length) - 1] = create_item(key, value);

    return;

    if (items == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    int i = (*length) - 2;
    while (i >= 0)
    {
        int comp = strcmp(key, (*items[i]).key);
        int found = comp > 0;
        if (found)
        {
            break;
        }
        (*items[i + 1]).key = (*items[i]).key;
        (*items[i + 1]).value = (*items[i]).value;
        i--;
    }

    int index = i + 1;

    items[index] = create_item(key, value);
}

// Function to get the length of the Items structure
int items_length(const struct Node *node)
{
    return node->length;
}

void test_items()
{
    printf("test_items\n");
    struct Item *items[20];

    // struct Item insert;
    // insert.key = "INSERT";
    // insert.value = "VVV";
    // items[1] = &insert;

    // printf(">> %s\n", items[1]->key);

    // insert.key = "??";
    // printf(">> %s\n", items[1]->key);

    int length = 0;

    items_insert(items, &length, "b", "bb");
    print_items(items, length);

    items_insert(items, &length, "c", "cc");
    print_items(items, length);

    items_insert(items, &length, "d", "dd");
    print_items(items, length);

    items_insert(items, &length, "a", "aa");
    print_items(items, length);

    items_insert(items, &length, "z", "zz");
    print_items(items, length);

    for (int i = 0; i < 10; i++)
    {
        items_insert(items, &length, "z", "zz");
        print_items(items, length);
    }

    // struct Item insert;
    // insert.key = "INSERT";
    // insert.value = "VVV";
    // items[1] = insert;
    // print_items(items, length);

    // // insert.key = "changed!";

    // items[2].key = "TESTzz";

    // // (*items[1]).key = "TY";
    // print_items(items, length);

    // items[3] = items[2];

    // print_items(items, length);

    // items[2].key = "sdsds";

    // print_items(items, length);

    // items = items_insert(items, 0, 2, "key4", "value4");
    // print_items(items, 3);
    printf("!!!\n");
    return;
}

void split_child(struct Node *node, int index)
{

    // struct Node *child = &node->children[index];
    // // printf("\n>>node items: %d\n", node->leaf);
    // // print_items(node->items, node->length);
    // // printf("\n");

    // // printf("\n>>child items: %d\n", child->leaf);
    // // print_items(child->items, child->length);
    // // printf("\n");

    // printf("split_child index = %d length = %d key = %s\n", index, child->length, child->items[T - 1].key);
    // struct Node *parent = create_node(child->leaf);
    // node->children[index + 1] = *parent;
    // node->items[index] = child->items[T - 1];
    // for (int i = 0; i < T - 1; i++)
    // {
    //     parent->items[i] = child->items[T + i];
    // }
    // parent->length = T - 1;
    // for (int i = 0; i < T - 1; i++)
    // {
    //     child->items[i] = child->items[i];
    // }
    // child->length = T - 1;
    // node->length++;
    // printf("child is leaf: %d\n", child->leaf);
    // if (child->leaf == 0)
    // {
    //     for (int i = 0; i < T; i++)
    //     {
    //         parent->children[i] = child->children[T + i];
    //     }
    //     for (int i = 0; i < T; i++)
    //     {
    //         child->children[i] = child->children[i];
    //     }
    // }

    // printf("\nchild items: child=%d len=%d\n", child->leaf, child->length);
    // print_items(child->items, child->length);

    // printf("\nparent items: child=%d len=%d\n", parent->leaf, parent->length);
    // print_items(parent->items, parent->length);

    // printf("\nnode items: child=%d len=%d\n", node->leaf, node->length);
    // print_items(node->items, node->length);

    // printf("\n\n---------------SPLIT-TRAVERSE---------------\n");
    // traverse(node, 0);

    // printf("\n");
}

void insert_non_full(struct Node *node, char key[], char value[])
{

    // if (node->leaf)
    // {
    //     printf("LEAF! len: %d key=%s\n", node->length, key);
    //     items_insert(&node->items, &node->length, key, value);
    // }
    // else
    // {
    //     printf("NON-LEAF!\n");
    //     int i = (node->length - 1);
    //     while (i >= 0 && strcmp(key, node->items[i].key) < 0)
    //     {
    //         i--;
    //     }
    //     i++;
    //     if (node->children[i].length == (2 * T) - 1)
    //     {
    //         printf("insert_non_full split\n");
    //         split_child(node, i);
    //         if (strcmp(key, node->items[i].key) > 0)
    //         {
    //             i++;
    //         }
    //     }
    //     printf("insert child: %d\n", i);
    //     insert_non_full(&node->children[i], key, value);
    // }
    // printf("inf done.\n");
}

struct Node *insert(struct Node *root, char key[], char value[])
{
    // printf("----insert!\n");
    // if (root == NULL)
    // {
    //     printf("create root.\n");
    //     root = create_node(1);
    // }

    // if (root->length == T)
    // {
    //     printf("root full.\n");
    //     struct Node *temp = create_node(0);
    //     temp->children[0] = *root;
    //     split_child(temp, 0);
    //     // temp->length = 1;

    //     insert_non_full(temp, key, value);
    //     return temp;
    // }
    // else
    // {
    //     insert_non_full(root, key, value);
    //     return root;
    // }
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

char **generate_keys(int lower, int upper, int shuffle)
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

    if (shuffle)
    {
        fisherYatesShuffle(keys, num);
    }

    return keys;
}

struct Node *insert_data_ints(struct Node *root, int lower, int upper, int shuffle)
{
    int num = upper - lower;
    char **keys = generate_keys(lower, upper, shuffle);

    for (int i = 0; i < num; i++)
    {
        printf("\ni=%d", i);
        root = insert(root, keys[i], "x");
    }
    return root;
}

int main()
{
    signal(SIGSEGV, segfault_handler);
    printf("started btree.\n");

    test_items();

    return 0;
    int count;
    struct Node *root = NULL;

    root = insert_data_ints(root, 0, 8, 0);

    printf("\n\n---------------TRAVERSE---------------\n");
    count = traverse(root, 0);
    printf("\ncount: %d", count);
    printf("\n\n");

    root = insert(root, "8", "x");
    printf("\n\n---------------TRAVERSE---------------\n");
    count = traverse(root, 0);
    printf("\ncount: %d", count);

    // assert(num == size);
    printf("\nDONE.\n");

    return 0;
}