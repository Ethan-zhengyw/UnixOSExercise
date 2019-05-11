// #include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int pid = 999;
    printf("[%d] pid = %d\n", getpid(), pid);
    execl("copy.out", "copy.out", argv[1], argv[2], (char *)NULL);
    printf("[%d] run done\n", getpid());
}
