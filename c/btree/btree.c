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

struct Node *insert_node(struct Node *node, char key[], char value[])
{
    if (node == NULL)
    {
        node = create_node();
    }

    if (items_length(node->items) < T)
    {
        items_append(node->items, key, value);
    }
    else
    {
        if (strcmp(key, node->items->items[0].key) < 0)
        {
            node->left = insert_node(node->left, key, value);
        }
        // else if (strcmp(key, node->items->items[n - 1].key) > 0)
        else
        {
            node->right = insert_node(node->right, key, value);
        }
    }

    return node;
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

struct Node *insert_data_ints(struct Node *root, int num)
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
        root = insert_node(root, keys[i], "x");
    }
    return root;
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

int height_helper(struct Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    // printf("size_helper %d\n", node->items->length);

    return 1 + max(height_helper(node->left), height_helper(node->right));
}

int main()
{
    signal(SIGSEGV, segfault_handler);
    printf("started btree.\n");

    struct Node *root = NULL;

    int num = 10;
    root = insert_data_ints(root, num);

    printf("inserted data.\n\n");

    printf("in_order: ");
    in_order_helper(root);
    printf("\n\n");

    int size = size_helper(root);
    printf("size: %d\n", size);

    int height = height_helper(root);
    printf("height: %d\n", height);

    // assert(num == size);
    printf("\nDONE.\n");

    return 0;
}