#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

char buffer[2];
int version = 1;

int main(int argc, char *argv[])
{
    int fdold, fdnew;

    if (argc != 3)
    {
	printf("need 2 arguments for copy program\n");
	exit(1);
    }
    fdold = open(argv[1], O_RDONLY);  /* open source file read onlu */
    if (fdold == -1)
    {
	printf("cannot open file %s\n", argv[1]);
	exit(1);
    }
    fdnew = creat(argv[2], 0666);  /* create target file rw for all */
    if (fdnew == -1)
    {
	printf("cannot create file %s\n", argv[2]);
	exit(1);
    }
    copy(fdold, fdnew);
    printf("[%d] copy program copy done.\n", getpid());
    exit(0);
}

copy(int fdold, int fdnew)
{
    int count;

    while ((count = read(fdold, buffer, sizeof(buffer))) > 0)
    {
	// printf("read %d char from fdold to buffer.\n", count);
	// printf("%s\n", buffer);
	write(fdnew, buffer, count);
    }
}
