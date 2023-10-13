#include <stdio.h>
#include <string.h>

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
    newNode->item = NULL; // Create a new Item for the node
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

    newTree->root = create_node();
    return newTree;
}

void insert_item(struct Cbst *tree, char key[], char value[])
{
    struct Node *temp = tree->root;

    int count = 0;
    while (temp->item != NULL)
    {
        count++;

        int comp = strcmp(temp->item->key, key);
        if (comp > 0)
        {
            if (temp->right == NULL)
            {
                temp->right = create_node();
                break;
            }
            temp = temp->right;
        }
        else if (comp < 0)
        {
            if (temp->left == NULL)
            {
                temp->left = create_node();
                break;
            }
            temp = temp->left;
        }
        else
        {
            break;
        }
    }
    temp->item = create_item();
    temp->item->key = key;
    temp->item->value = value;
    printf("count = %d\n", count);
}

char *get_item(struct Cbst *tree, char key[])
{
    if (tree != NULL && tree->root != NULL && tree->root->item != NULL)
    {
        return tree->root->item->value;
    }
    return NULL;
}

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void segfault_handler(int signal_num)
{
    printf("Caught segmentation fault! Exiting...\n");
    exit(1);
}

int main()
{
    signal(SIGSEGV, segfault_handler);

    struct Cbst *tree = create_tree();

    printf("get_item = %s\n", get_item(&tree, "test"));

    insert_item(tree, "b", "aaa");

    printf("get_item = %s\n", get_item(tree, "test"));

    insert_item(tree, "b", "xxx");
    insert_item(tree, "c", "nnn");
    insert_item(tree, "a", "nnn");
    insert_item(tree, "a", "nnn");
    insert_item(tree, "aa", "nnn");
    insert_item(tree, "aaa", "nnn");
    insert_item(tree, "aaaa", "nnn");
    insert_item(tree, "aaaaa", "nnn");
    insert_item(tree, "aaaaaa", "nnn");
    insert_item(tree, "aaaaaaa", "nnn");

    printf("get_item = %s\n", get_item(tree, "test"));

    printf("DONE.");

    return 0;
}
