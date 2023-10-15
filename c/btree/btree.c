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
    printf("started btree.\n");

    printf("DONE.\n");

    return 0;
}