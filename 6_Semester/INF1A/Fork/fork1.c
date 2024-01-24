#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	pid_t p;
	p = fork();

	if (p == 0)
	{
		printf("Child: start.\n");
		printf("Child: my PID=%d, parent PID=%d\n", getpid(), getppid());
#ifdef ORPHAN
		sleep(3);
		printf("I am so ronry!\n");
#endif
		printf("Child: my PID=%d, parent PID=%d\n", getpid(), getppid());
		printf("Child: exiting\n");
#ifdef ZOMBIE
		return 0;
#endif
	}
	else
	{
		printf("Parent: start.\n");
		printf("Parent: my PID=%d, child PID=%d\n", getpid(), p);
#ifdef ZOMBIE
		sleep(3);
		printf("Zombie Nation!\n");
#endif
		printf("Parent: exiting\n");
	}
	return 0;
}
