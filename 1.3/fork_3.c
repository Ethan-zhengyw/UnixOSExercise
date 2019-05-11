#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
main ()

{
	printf("[%d] enter main func 7\n", getpid());
	pid_t pid; 
	pid=fork(); 
	do_something();
        printf("[%d] enter main func 10\n", getpid());
	if (pid < 0) 
	{
		printf("error in fork!"); 
	} 
	else if (pid == 0) 
	{
		// pid = fork() is not executed in child process
		// therefore pid is uninitialized, equals to 0(default value)
                printf("[%d] enter main func 17\n", getpid());
		printf("i am the child process, my process id is %d\n", getpid()); 
	}
	else 
	{
		printf("i am the parent process, my process id is %d\n", getpid()); 
		printf("i am the parent process, my child process id is %d\n", pid); 
	}
} 

do_something()
{
	int i;
	for (i = 0; i < 5; i++)
	{
		sleep(1);
		printf("[%d] looping, count: %d, %d\n", getpid(), getppid(), i);
	}
}
