#include <stdio.h>

void comp(char *a, char *b)
{
    int comp = strcmp(a, b);
    printf("comp %3d \ta: %4s \t b: %4s\n", comp, a, b);
}
int main()
{
    printf("starting\n");

    comp("7", "16");

    comp("13", "2");

    printf("\n");
    printf("\n");
    return 0;
}
