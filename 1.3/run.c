// #include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int pid;
    pid = fork();
    if (pid == 0)
    {
        printf("[%d] pid = %d\n", getpid(), pid);
	execl("copy.out", "copy.out", argv[1], argv[2], (char *)NULL);
    }
    else
    {
        printf("[%d] pid = %d\n", getpid(), pid);
    }
    wait((int *)NULL);
    printf("copy done\n");
}
