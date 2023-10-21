// Searching a key on a B-tree in C
// THIS IS THE EXAMPLE B TREE FROM https://www.programiz.com/dsa/b-tree
// COMPARING RUN TIMES WITH IT.
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define T 1000

struct BTreeNode
{
    int val[T * 2 + 1], count;
    struct BTreeNode *link[T * 2 + 1];
};

struct BTreeNode *root;

// Create a node
struct BTreeNode *createNode(int val, struct BTreeNode *child)
{
    struct BTreeNode *newNode;
    newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    newNode->val[1] = val;
    newNode->count = 1;
    newNode->link[0] = root;
    newNode->link[1] = child;
    return newNode;
}

// Insert node
void insertNode(int val, int pos, struct BTreeNode *node,
                struct BTreeNode *child)
{
    int j = node->count;
    while (j > pos)
    {
        node->val[j + 1] = node->val[j];
        node->link[j + 1] = node->link[j];
        j--;
    }
    node->val[j + 1] = val;
    node->link[j + 1] = child;
    node->count++;
}

// Split node
void splitNode(int val, int *pval, int pos, struct BTreeNode *node,
               struct BTreeNode *child, struct BTreeNode **newNode)
{
    int median, j;

    if (pos > T)
        median = T + 1;
    else
        median = T;

    *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    j = median + 1;
    while (j <= T * 2)
    {
        (*newNode)->val[j - median] = node->val[j];
        (*newNode)->link[j - median] = node->link[j];
        j++;
    }
    node->count = median;
    (*newNode)->count = T * 2 - median;

    if (pos <= T)
    {
        insertNode(val, pos, node, child);
    }
    else
    {
        insertNode(val, pos - median, *newNode, child);
    }
    *pval = node->val[node->count];
    (*newNode)->link[0] = node->link[node->count];
    node->count--;
}

// Set the value
int setValue(int val, int *pval,
             struct BTreeNode *node, struct BTreeNode **child)
{
    int pos;
    if (!node)
    {
        *pval = val;
        *child = NULL;
        return 1;
    }

    if (val < node->val[1])
    {
        pos = 0;
    }
    else
    {
        for (pos = node->count;
             (val < node->val[pos] && pos > 1); pos--)
            ;
        if (val == node->val[pos])
        {
            printf("Duplicates are not permitted\n");
            return 0;
        }
    }
    if (setValue(val, pval, node->link[pos], child))
    {
        if (node->count < T * 2)
        {
            insertNode(*pval, pos, node, *child);
        }
        else
        {
            splitNode(*pval, pval, pos, node, *child, child);
            return 1;
        }
    }
    return 0;
}

// Insert the value
void insert(int val)
{
    int flag, i;
    struct BTreeNode *child;

    flag = setValue(val, &i, root, &child);
    if (flag)
        root = createNode(i, child);
}

// Search node
int search(int val, int *pos, struct BTreeNode *myNode)
{
    if (!myNode)
    {
        return 0;
    }

    if (val < myNode->val[1])
    {
        *pos = 0;
    }
    else
    {
        for (*pos = myNode->count;
             (val < myNode->val[*pos] && *pos > 1); (*pos)--)
            ;
        if (val == myNode->val[*pos])
        {
            // printf("%d is found", val);
            return 1;
        }
    }
    return search(val, pos, myNode->link[*pos]);
}

// Traverse then nodes
void traversal(struct BTreeNode *myNode)
{
    printf("\nt:");
    int i;
    if (myNode)
    {
        for (i = 0; i < myNode->count; i++)
        {
            traversal(myNode->link[i]);
            printf("%d ", myNode->val[i + 1]);
        }
        traversal(myNode->link[i]);
    }
}

int main()
{

    int val, ch;

    clock_t start_time, end_time;
    double elapsed_time;

    // Record the start time
    start_time = clock();

    int num = 10000000;
    for (int i = 0; i < num; i++)
    {
        insert(i);
    }

    end_time = clock();
    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("INSERT time: %.2f seconds\n", elapsed_time);
    start_time = clock();

    for (int i = 0; i < num; i++)
    {
        assert(search(i, &ch, root));
    }

    end_time = clock();

    // Calculate the elapsed time in seconds
    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Get time: %.2f seconds\n", elapsed_time);

    printf("done.");
}