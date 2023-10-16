#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Item
{
    char *key;
    char *value;
};

void items_insert(struct Item **items, int *length, const char *key, const char *value)
{
    // Increase the length of the array
    (*length)++;

    // Reallocate memory to accommodate the new item
    *items = (struct Item *)realloc(*items, (*length) * sizeof(struct Item));

    if (*items == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    // Allocate memory for the new item's key and value
    (*items)[(*length) - 1].key = strdup(key);
    (*items)[(*length) - 1].value = strdup(value);

    if ((*items)[(*length) - 1].key == NULL || (*items)[(*length) - 1].value == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
}

int main()
{
    struct Item *items = NULL;
    int length = 0;

    // Insert an item at the end of the list
    items_insert(&items, &length, "key1", "value1");

    items_insert(&items, &length, "key2", "value2");

    // Don't forget to free memory when you're done with the items
    for (int i = 0; i < length; i++)
    {
        printf("Inserted item: key=%s, value=%s\n", items[i].key, items[i].value);
        free(items[i].key);
        free(items[i].value);
    }

    free(items);

    return 0;
}
