#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
main ()

{
	printf("[%d] enter main func 7\n", getpid());
	pid_t pid; 
	pid=fork(); 
	pid=fork(); 
        printf("[%d] enter main func 10\n", getpid());
	if (pid < 0) 
	{
		printf("error in fork!"); 
	} 
	else 
	{
		printf("[%d] my child process id is %d\n", getpid(), pid); 
		printf("[%d] my parent process id is %d\n", getpid(), getppid()); 
		do_something();
		printf("[%d] waiting child process %d\n", getpid(), pid); 
		wait((int *) 0);
		printf("[%d] waiting child process %d done\n", getpid(), pid); 
	}
} 

do_something()
{
	printf("[%d] my parent process id is %d, start looping\n", getpid(), getppid());
	int i;
	for (i = 0; i < 5; i++)
	{
		sleep(1);
		printf("[%d] my parent process id is %d, count: %d\n", getpid(), getppid(), i);
	}
}
