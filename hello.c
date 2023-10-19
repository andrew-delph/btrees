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

// int main()
// {
//     printf("starting\n");
//     register int total = 0;
//     // int total = 0;
//     int num = 100000000;
//     for (int j = 0; j < 5; j++)
//     {
//         for (int i = 0; i < num; i++)
//         {
//             total++;
//         }
//         for (int i = 0; i < num; i++)
//         {
//             total--;
//         }
//         for (int i = 0; i < num; i++)
//         {
//             total++;
//         }
//     }

//     printf("total = %d\n", total);
//     return 0;
// }
void test(int i)
{
    if (i > 10)
    {
        return;
    }
    test(i + 1);
}
#define max(A, B) ((A) > (B) ? (A) : (B))
int main()
{
    printf("starting test().z\n");
    test(0);
    printf("max= %d\n", max('a', 2));
    return 0;
}