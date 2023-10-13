#include <stdio.h>

struct Item
{
    char *key;
    char *value;
};

struct Node
{
    struct Node *left;
    struct Node *right;
    struct Item *item;
};

struct Cbst
{
    struct Node *root;
};

struct Item *create_item()
{
    struct Item *newItem = (struct Item *)malloc(sizeof(struct Item));
    if (newItem == NULL)
    {
        // Handle memory allocation failure
        exit(1);
    }

    newItem->key = NULL;
    newItem->value = NULL;
    return newItem;
}

struct Node *create_node()
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        // Handle memory allocation failure
        exit(1);
    }

    newNode->left = NULL;
    newNode->right = NULL;
    newNode->item = create_item(); // Create a new Item for the node
    return newNode;
}

struct Cbst *create_tree()
{
    struct Cbst *newTree = (struct Cbst *)malloc(sizeof(struct Cbst));
    if (newTree == NULL)
    {
        // Handle memory allocation failure
        exit(1);
    }

    newTree->root = NULL;
    return newTree;
}

void insert_item(struct Cbst *tree, char key[], char value[])
{

    struct Node *node = create_node();
    tree->root = node;
    tree->root->item->key = key;
    tree->root->item->value = value;
}

char *get_item(struct Cbst *tree, char key[])
{
    if (tree != NULL && tree->root != NULL && tree->root->item != NULL)
    {
        return tree->root->item->value;
    }
    return NULL;
}

int main()
{

    struct Cbst *tree = create_tree();

    printf("get_item = %s\n", get_item(&tree, "test"));

    insert_item(tree, "insert_key", "insert_value");
    printf("inserted %s\n", tree->root->item->value);

    printf("manual %s\n", tree->root->item->value);

    printf("get_item = %s\n", get_item(&tree, "test"));

    insert_item(&tree, "zzzz", "xxx");

    printf("get_item = %s\n", get_item(&tree, "test"));

    printf("DONE.%d", "a" < "b");

    return 0;
}
