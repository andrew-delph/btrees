#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <assert.h>

#define T 4
#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)

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
    newNode->length = 0;
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
    printf("len=(%d) >>", length);
    for (int i = 0; i < length; i++)
    {
        printf(" [%s]", items[i]->key);
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
        if (node->children[i] != NULL)
        {
            printf("<%d>", i);
        }
        count += traverse(node->children[i], level + 1);
    }
    return count;
}

void items_insert(struct Item **items, int *length, struct Item *item)
{
    if (item == NULL)
    {
        printf("items_insert item is NULL\n");
        return;
    }

    // Increase the length of the array

    // printf("length %d\n", *length);

    // items[(*length) - 1] = create_item(key, value);
    // return;

    if (items == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    int i = (*length) - 1;
    while (i >= 0)
    {
        int comp = strcmp(item->key, items[i]->key);
        int found = comp > 0;
        if (found)
        {
            break;
        }
        items[i + 1] = items[i];
        // (*items[i + 1]).value = (*items[i]).value;
        i--;
    }

    int index = i + 1;

    if (items[index] == NULL || items[index]->key != item->key)
    {
        (*length)++;
    }

    items[index] = item;
}

void items_insert_kv(struct Item **items, int *length, char *key, char *value)
{
    items_insert(items, length, create_item(key, value));
}

// Function to get the length of the Items structure
int items_length(const struct Node *node)
{
    return node->length;
}

void split_child(struct Node *node, int index)
{

    struct Node *split = node->children[index];
    int split_length = split->length;
    printf(">>>>>>>>>>>>>>>\n");
    printf(">>>>>>>>>>>>>>>\n");
    printf(">>>>>>>>>>>>>>> node is leaf %d\n", node->leaf);
    print_items(node->items, node->length);
    printf("\n");

    printf("\n>>split items: %d\n", split->leaf);
    print_items(split->items, split->length);
    printf("\n");
    traverse(node, 0);

    char *nodeD = node->items[index] != NULL ? node->items[index]->key : "NULLLLLLLLLL";
    char *splitD = split->items[T - 1] != NULL ? split->items[T - 1]->key : "NULLLLLLLLLL";
    printf("~~~~~~~~~~:  nodeD %s splitD %s\n", nodeD, splitD);

    printf("split_child index = %d length = %d key = %s\n", index, split->length, split->items[T - 1]->key);
    struct Node *parent = create_node(split->leaf);

    for (int i = index + 1; i < 2 * T - 1; i++)
    {
        node->children[i + 1] = node->children[i];
    }

    node->children[index + 1] = parent;
    items_insert(node->items, &node->length, split->items[T - 1]);

    for (int i = 0; i < T - 1; i++)
    {
        parent->items[i] = split->items[T + i];
        // items_insert(parent->items, &parent->length, split->items[T + i]);
    }
    parent->length = MAX(split_length - T, 0);
    for (int i = 0; i < T - 1; i++)
    {
        split->items[i] = split->items[i];
        // items_insert(split->items, &split->length, split->items[T + i]);
    }
    split->length = MIN(split_length, T - 1);
    // node->length++;
    if (split->leaf == 0)
    {
        printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!child is leaf: %d\n", split->leaf);
        for (int i = 0; i < T; i++)
        {
            parent->children[i] = split->children[T + i];
        }
        for (int i = 0; i < T; i++)
        {
            split->children[i] = split->children[i];
        }
    }

    printf("\nchild items: leaf=%d len=%d\n", split->leaf, split->length);
    print_items(split->items, split->length);

    printf("\nparent items: leaf=%d len=%d\n", parent->leaf, parent->length);
    print_items(parent->items, parent->length);

    printf("\nnode items: leaf=%d len=%d\n", node->leaf, node->length);
    print_items(node->items, node->length);

    // printf("\n\n---------------SPLIT-TRAVERSE---------------\n");
    // traverse(node, 0);
    // printf("don.\n");

    printf("\n");
}

void insert_non_full(struct Node *node, char key[], char value[])
{

    if (node->leaf)
    {
        printf("LEAF! len: %d key=%s\n", node->length, key);
        items_insert_kv(node->items, &node->length, key, value);
    }
    else
    {
        printf("NON-LEAF!\n");
        int i = (node->length - 1);
        while (i >= 0 && strcmp(key, node->items[0]->key) < 0)
        {
            i--;
        }
        i++;
        if (node->children[i]->length == (2 * T) - 1)
        {
            printf("insert_non_full split\n");
            split_child(node, i);
            if (strcmp(key, node->items[i]->key) > 0)
            {
                i++;
            }
        }
        printf("insert child: %d\n", i);
        insert_non_full(node->children[i], key, value);
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
        temp->children[0] = root;
        split_child(temp, 0);
        // temp->length = 1;
        // printf("LENGTH AFTER: %d\n", temp->length);
        // exit(1);

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

    // int length = 0;

    // items_insert(items, &length, "b", "bb");
    // print_items(items, length);

    // items_insert(items, &length, "c", "cc");
    // print_items(items, length);

    printf("!!!\n");
    return;
}

int main()
{
    signal(SIGSEGV, segfault_handler);
    printf("started btree.\n");

    printf("max=%d min=%d\n", MAX(2, 3), MIN(2, 3));

    // test_items();
    // return 0;

    int count;
    struct Node *root = NULL;

    root = insert_data_ints(root, 0, 22, 0);

    printf("\n\n---------------TRAVERSE---------------\n");
    count = traverse(root, 0);
    printf("\ncount: %d", count);
    printf("\n\n");

    printf("-------------------------------------------------------------------------------------\n");

    root = insert(root, "-1", "x");
    printf("\n\n---------------TRAVERSE---------------\n");
    count = traverse(root, 0);
    printf("\ncount: %d", count);

    // assert(num == size);
    printf("\nDONE.\n");

    return 0;
}