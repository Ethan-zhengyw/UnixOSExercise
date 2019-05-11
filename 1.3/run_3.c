// #include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int pid = 999;
    char *env[] = {NULL};
    printf("[%d] pid = %d\n", getpid(), pid);
    execve("copy.out", argv, env);

    // This code will not be executed if execve execute successfully.
    printf("[%d] run done\n", getpid());
}
