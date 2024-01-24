#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	int fd[2];

	int zahlen[50];
	pid_t p;

	for (int i = 1; i <= 50; i++)			//Create array with values
	{
		zahlen[i - 1] = i;
	}

	if (pipe(fd) == -1)
	{
		fprintf(stderr, "Pipe Failed");
		return 1;
	}

	p = fork();

	if (p < 0)
	{
		fprintf(stderr, "fork Failed");
		return 1;
	}

	// Parent process
	else if (p > 0)
	{
		printf("Ich %d darf schreiben\n", getpid());
		close(fd[0]); // Close reading end
		write(fd[1], zahlen, 50 * sizeof(int));			//Write values to pipe
		close(fd[1]); //Close writing end

		// Wait for child to end
		wait(NULL);
	}

	// child process
	else
	{
		int buffer;
		close(fd[1]); // Close writing end of first pipe

		printf("Ich %d darf lesen: \n", getpid());

		while (read(fd[0], &buffer, sizeof(buffer)) > 0)		//Read untill pipe empty
		{
			printf(" %d ", buffer);
		}
		printf("\nLesen fertig\n");

		// Close reading end
		close(fd[0]);
		exit(0);
	}
}