#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>

#define T 2
#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)

void segfault_handler(int signal_num)
{
    debug("Caught segmentation fault! Exiting...\n");
    exit(1);
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int debug_flag = 0;
void debug(const char *format, ...)
{
    if (debug_flag)
    {
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }
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
        debug("HERE!\n");
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
        debug("HERE!\n");
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
    // debug("len=(%d) >>", length);
    // for (int i = 0; i < 2 * T; i++)
    // {
    //     if (items[i] != NULL)
    //     {
    //         debug("[%s] ", items[i]->key);
    //     }
    //     else
    //     {
    //         debug("[%s]", "N");
    //     }
    // }

    for (int i = 0; i < length; i++)
    {
        debug("[%s] ", items[i]->key);
    }
    // debug("\n");
}

int traverse(struct Node *node, int level, int index)
{
    debug("\n");
    for (int i = 0; i < level; i++)
    {
        debug("\t");
    }
    debug("t(%d,%d)", level, index);
    if (node == NULL)
    {
        debug(" [NULL]");
        return 0;
    }
    debug("(%d)| ", node->length);
    int count = node->length;
    print_items(node->items, node->length);
    if (node->leaf)
    {
        return count;
    }
    for (int i = 0; i < node->length + 1; i++)
    {
        if (node->length)
        {
            count += traverse(node->children[i], level + 1, i);
        }
        else
        {
            traverse(node->children[i], level + 1, i);
        }
    }

    return count;
}

void items_insert(struct Item **items, int *length, struct Item *item)
{
    if (item == NULL)
    {
        debug("items_insert item is NULL\n");
        return;
    }

    // Increase the length of the array

    // debug("length %d\n", *length);

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
    debug("\n");
    debug(">>>>>>>>>>>>>>> leaf %d\n", node->leaf);
    debug(">>>>>>>>>>>>>>> length %d\n", node->length);
    debug(">>>>>>>>>>>>>>> index %d\n", index);
    debug("---------------SPLIT-TRAVERSE-1---------------\n");
    debug("traverse node:\n");
    traverse(node, 0, 0);

    debug("\n\ntraverse split:\n");
    traverse(split, 0, 0);

    debug("\n");
    debug("\n 1 split items: leaf=%d len=%d\n", split->leaf, split->length);
    print_items(split->items, split->length);
    debug("\n");
    debug("\n 1 node items: leaf=%d len=%d\n", node->leaf, node->length);
    print_items(node->items, node->length);
    debug("\n");
    debug("\n");

    debug("split_child index = %d length = %d key = %s\n", index, split->length, split->items[T - 1]->key);
    struct Node *neighbor = create_node(split->leaf);

    // for (int i = index + 1; i < 2 * T - 1; i++)
    for (int i = 2 * T - 2; i > index; i--)
    {
        // printf("shift: %d->%d\n", i, i + 1);
        node->children[i + 1] = node->children[i];
    }

    node->children[index + 1] = neighbor;
    items_insert(node->items, &node->length, split->items[T - 1]);

    // for (int i = 0; i < T - 1; i++)
    for (int i = T - 2; i >= 0; i--)
    {
        neighbor->items[i] = split->items[T + i];
        if (neighbor->items[i] != NULL)
        {
            debug("neighbor key: %s\n", neighbor->items[i]->key);
        }
        // items_insert(neighbor->items, &neighbor->length, split->items[T + i]);
    }
    debug("split_length: %d...%d\n", split_length, MAX(split_length - T, 0));
    neighbor->length = MAX(split_length - T, 0);
    //  neighbor->length = MIN(split_length, T - 1);
    for (int i = 0; i < T - 1; i++)
    {
        split->items[i] = split->items[i];
        // items_insert(split->items, &split->length, split->items[T + i]);
    }
    split->length = MIN(split_length, T - 1);
    // node->length++;
    if (split->leaf == 0)
    {
        debug("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!child is leaf: %d\n", split->leaf);
        for (int i = 0; i < T; i++)
        {
            neighbor->children[i] = split->children[T + i];
        }
        for (int i = 0; i < T; i++)
        {
            split->children[i] = split->children[i];
        }
    }

    debug("\n 2 split items: leaf=%d len=%d\n", split->leaf, split->length);
    print_items(split->items, split->length);
    debug("\n");
    debug("\n 2 neighbor items: leaf=%d len=%d\n", neighbor->leaf, neighbor->length);
    print_items(neighbor->items, neighbor->length);
    debug("\n");
    debug("\n 2 node items: leaf=%d len=%d\n", node->leaf, node->length);
    print_items(node->items, node->length);

    debug("\n\n---------------SPLIT-TRAVERSE-2---------------\n");
    printf("node\n");
    traverse(node, 0, 0);
    printf("\nsplit\n");
    traverse(split, 0, 0);
    printf("\n neighbor\n");
    traverse(neighbor, 0, 0);
    // debug("don.\n");
    debug("\n<<<<<<<<<<<<<<<<\n");
    debug("<<<<<<<<<<<<<<<<\n");
    debug("\n");
}

char *get(struct Node *node, char key[])
{
    if (node == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < node->length; i++)
    {

        int comp = strcmp(key, node->items[i]->key);
        if (comp == 0)
        {
            return node->items[i]->value;
        }
        else if (comp < 0)
        {
            debug("get %d\n", i);
            return get(node->children[i], key);
        }
    }
    debug("get %d\n", node->length);
    return get(node->children[node->length], key);
}

void insert_non_full(struct Node *node, char key[], char value[])
{

    if (node->leaf)
    {
        debug("LEAF! len: %d key=%s\n", node->length, key);
        items_insert_kv(node->items, &node->length, key, value);
    }
    else
    {
        debug("NON-LEAF!\n");
        int i = (node->length - 1);
        while (i >= 0 && strcmp(key, node->items[0]->key) < 0)
        {
            i--;
        }
        i++;
        if (node->children[i]->length == (2 * T) - 1)
        {
            debug("insert_non_full split\n");
            split_child(node, i);
            int comp = strcmp(key, node->items[i]->key);
            // printf("CHECKING %s comp %d\n", node->items[i]->key, comp);
            if (strcmp(key, node->items[i]->key) > 0)
            {
                i++;
            }
        }
        debug("insert child: %d\n", i);
        insert_non_full(node->children[i], key, value);
    }
}

struct Node *insert(struct Node *root, char key[], char value[])
{
    debug("----insert! %s\n", key);
    if (root == NULL)
    {
        debug("create root.\n");
        root = create_node(1);
    }

    if (root->length == T)
    {
        debug("root full.\n");
        traverse(root, 0, 0);
        struct Node *temp = create_node(0);
        temp->children[0] = root;
        split_child(temp, 0);
        // temp->length = 1;
        // debug("LENGTH AFTER: %d\n", temp->length);
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
        // snprintf(keys[i], 10, "%c", 'A' + id); // Convert integer to string
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
        printf("\n \n i=%d\n", i);
        int prev = debug_flag;
        debug_flag = 1;
        root = insert(root, keys[i], keys[i]);
        traverse(root, 0, 0);
        debug_flag = prev;
        printf("\n");
        // char *got = get(root, keys[i]);
        // printf("\n[after insert]keys[i]: %s got : %s\n", keys[i], got);
        // assert(got == keys[i]);
        printf("\n");
        for (int j = 0; j <= i; j++)
        {
            char *check_key = keys[j];
            char *got_value = get(root, check_key);
            if (got_value != check_key)
            {
                printf("\n[full check] keys[j]: %s got: %s j=%d i=%d\n", check_key, got_value, j, i);
                debug_flag = 1;
                get(root, check_key);
                debug_flag = prev;
            }
            assert(got_value == check_key);
        }
    }

    return root;
}

void test_tree(int num)
{
    struct Node *root = NULL;
    root = insert_data_ints(root, 0, num, 0);
    int count = traverse(root, 0, 0);
    printf("\ntest count: %d num: %d\n", count, num);
    assert(count == num);

    return;
}
void tests()
{
    for (int i = 0; i < 40; i++)
    {
        test_tree(i);
    }
    printf("\nDONE TESTS.\n");
    return;
}

int main()
{
    signal(SIGSEGV, segfault_handler);
    printf("started btree.\n");

    debug("max=%d min=%d\n", MAX(2, 3), MIN(2, 3));

    tests();
    // debug_flag = 1;
    // test_tree(6);
    return 0;
    printf("\n\n\n\n\n\n\n\n\n");

    int count;
    struct Node *root = NULL;

    int num = 6;
    root = insert_data_ints(root, 0, num, 0);

    printf("\n\n---------------TRAVERSE---------------\n");
    count = traverse(root, 0, 0);
    printf("\ncount: %d", count);
    printf("\nFIRST\n");

    assert(count == num);
    return 0;

    printf("---BAD-INSERT------------------------------------------------------------------------------------\n");

    root = insert(root, "36", "x");
    printf("\n\n---------------TRAVERSE---------------\n");
    count = traverse(root, 0, 0);
    printf("\nSECOND. count: %d\n", count);

    assert(count == ++num);

    // assert(num == size);
    printf("\nDONE.\n");

    return 0;
}