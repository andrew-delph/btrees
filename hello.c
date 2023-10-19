#include <stdio.h>
#include "test.h"
#include "addition.h"

struct Person
{
    char *name;
};

void change_name(struct Person *p)
{
    p->name = "Andrew";
}

void change_str(char str[])
{
    printf("c %c\n", str[2]);
    // str[3] = 'X';
    // char c = 'X';
    // str[2] = &c;
}
// int main()
// {
//     struct Person p0;
//     struct Person *p1 = &p0;
//     p1->name = "andrew";
//     change_name(p1);
//     printf("p1 = %s\n", p1->name);

//     char *str = "ANDREW";

//     change_str(str);

//     printf("str %s\n", str);
//     void test();
//     test();
//     return 0;
// }

struct Node
{
    char *name;
};

void test(struct Node n)
{
    // printf("name = %s\n", n->name);
}

void testp(struct Node *n)
{
    // printf("name = %s\n", n->name);
}

int main()
{
    printf("starting\n");

    struct Node n;
    n.name = "andrew";
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            // test(n);
            testp(&n);
        }
    }

    return 0;
}
