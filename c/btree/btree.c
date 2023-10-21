#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <time.h>

#define T 1000
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

int debug_flag = 1;
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
    for (int i = 0; i < length; i++)
    {
        debug("[%s] ", items[i]->key);
    }
    // debug("\n");
}

int traverse(struct Node *node, int level, int index)
{
    // debug("\n");
    // for (int i = 0; i < level; i++)
    // {
    //     debug("\t");
    // }
    // debug("t(%d,%d)", level, index);
    if (node == NULL)
    {
        // debug(" [NULL]");
        return 0;
    }
    // debug("(%d)| ", node->length);
    int count = node->length;
    // print_items(node->items, node->length);
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

int items_search(struct Item **items, int length, char *key)
{
    int left = 0;
    int right = length - 1;

    // debug("left: %d right: %d\n", left, right);

    while (left <= right)
    {

        int mid = left + (right - left) / 2;
        int comp = strcmp(key, items[mid]->key);
        // debug("mid %d comp %d k1 %s k2 %s\n", mid, comp, key, items[mid]->key);
        if (comp == 0)
        {
            return mid;
        }
        else if (comp > 0)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
}

void items_insert(struct Item **items, int *length, struct Item *item)
{

    if (items == NULL)
    {
        fprintf(stderr, "items is NULL.\n");
        exit(1);
    }

    int index = items_search(items, *length, item->key);

    if ((*length) < index && items[index] != NULL && items[index]->key != NULL && strcmp(item->key, items[index]->key) == 0)
    {
        items[index] = item;
    }
    else
    {
        for (int i = 2 * T - 2; i >= index; i--)
        {
            items[i + 1] = items[i];
        }
        items[index] = item;
        (*length)++;
    }

    return;
}

void items_insert_kv(struct Item **items, int *length, char *key, char *value)
{
    items_insert(items, length, create_item(key, value));
}

// Function to get_value the length of the Items structure
int items_length(const struct Node *node)
{
    return node->length;
}

void split_child(struct Node *node, int index)
{

    struct Node *split = node->children[index];

    struct Node *neighbor = create_node(split->leaf);

    // for (int i = index + 1; i < 2 * T - 1; i++)
    for (int i = 2 * T - 2; i > index; i--)
    {
        node->children[i + 1] = node->children[i];
    }

    node->children[index + 1] = neighbor;
    items_insert(node->items, &node->length, split->items[T - 1]);

    for (int i = T - 1; i >= 0; i--)
    {
        neighbor->items[i] = split->items[T + i];
    }

    int neighbor_length = MAX(split->length - T, 0);
    int split_length = MIN(split->length, T - 1);
    neighbor->length = neighbor_length;
    split->length = split_length;

    for (int i = T - 1; i >= 0; i--)
    {
        split->items[i] = split->items[i];
    }
    if (split->leaf == 0)
    {
        for (int i = 0; i < T; i++)
        {
            neighbor->children[i] = split->children[T + i];
        }
        for (int i = 0; i < T; i++)
        {
            split->children[i] = split->children[i];
        }
    }
}

char *get_value(struct Node *node, char key[])
{
    if (node == NULL)
    {
        return NULL;
    }

    int index = items_search(node->items, node->length, key);
    if (index >= node->length)
    {
        return get_value(node->children[node->length], key);
    }
    else if (
        strcmp(key, node->items[index]->key) == 0)
    {
        return node->items[index]->value;
    }
    return get_value(node->children[index], key);
}

void insert_non_full(struct Node *node, char key[], char value[])
{

    if (node->leaf)
    {
        items_insert_kv(node->items, &node->length, key, value);
    }
    else
    {
        int i = (node->length - 1);
        while (i >= 0 && strcmp(key, node->items[i]->key) < 0)
        {
            i--;
        }
        i++;
        if (node->children[i]->length == (2 * T) - 1)
        {
            split_child(node, i);
            int comp = strcmp(key, node->items[i]->key);
            if (strcmp(key, node->items[i]->key) > 0)
            {
                i++;
            }
        }
        insert_non_full(node->children[i], key, value);
    }
}

struct Node *insert(struct Node *root, char key[], char value[])
{
    if (root == NULL)
    {
        root = create_node(1);
    }

    if (root->length == 2 * T - 1)
    {
        struct Node *temp = create_node(0);
        temp->children[0] = root;
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

    clock_t start_time, end_time;
    double elapsed_time;

    // Record the start time
    start_time = clock();

    for (int i = 0; i < num; i++)
    {
        root = insert(root, keys[i], keys[i]);
    }

    for (int i = 0; i < num; i++)
    {
        char *check_key = keys[i];
        char *got_value = get_value(root, check_key);

        assert(got_value == check_key);
    }

    end_time = clock();

    // Calculate the elapsed time in seconds
    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Elapsed time: %.2f seconds\n", elapsed_time);

    return root;
}

void test_tree(int num)
{
    struct Node *root = NULL;
    root = insert_data_ints(root, 0, num, 0);
    // int count = traverse(root, 0, 0);
    // printf("\ntest count: %d num: %d", count, num);
    // assert(count == num);

    return;
}
void test_trees()
{
    for (int i = 1000; i < 1100; i++)
    {
        test_tree(i);
    }

    return;
}

void test_items()
{
    printf("test_items.\n");
    struct Item *items[2 * T];
    int length = 0;
    items_insert_kv(items, &length, "1", "x");
    items_insert_kv(items, &length, "2", "x");
    items_insert_kv(items, &length, "3", "x");

    debug_flag = 1;
    print_items(items, length);
    debug_flag = 0;

    printf("\n");

    printf("A: %d\n", items_search(items, length, "1"));
    printf("b: %d\n", items_search(items, length, "2"));
    printf("c: %d\n", items_search(items, length, "3"));
    printf("0: %d\n", items_search(items, length, "0"));
    printf("4: %d\n", items_search(items, length, "4"));
    printf("length %d\n", length);
}

void test()
{
    // debug_flag = 1;
    test_items();
    test_trees();
    printf("\nDONE TESTS.\n");
}

int main()
{
    signal(SIGSEGV, segfault_handler);
    printf("started btree.\n");

    debug("max=%d min=%d\n", MAX(2, 3), MIN(2, 3));

    // test();

    test_tree(10000000);
    printf("done\n");
    return 0;
}