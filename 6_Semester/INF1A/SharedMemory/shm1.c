#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <assert.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

#define MAY_READ 0
#define MAY_WRITE 1
#define DATA_DONE -1

int main()
{
	int fd;
	int read = MAY_READ;
	int write = MAY_WRITE;
	int done = DATA_DONE;
	int pid;
	const off_t lenght = 11 * sizeof(int);
	fd = shm_open("/shm", O_RDWR | O_CREAT, 0666);

	if (fd == -1)
	{
		perror("open");
		exit(1);
	}

	assert(0 == ftruncate(fd, lenght));
	int *shm = mmap(NULL, lenght, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	int integers[lenght];
	for (int i = 0; i < lenght / sizeof(int) -1; i++)
	{
		integers[i] = i;
	}

	volatile int* m = shm;
	memcpy(shm, &write, sizeof(int));

	pid = fork();
	if (pid == 0)					//Child
	{
		for (int j = 0; j <= 3; j++)
		{
			while (MAY_WRITE == *m)
			{
				printf("Ich %d darf schreiben\n", getpid());

				for (int i = 0; i <= lenght / sizeof(int); i++)
				{
					memcpy(shm + i + 1, integers + i, sizeof(int));
				}
				memcpy(shm, &read, sizeof(int));

				for (int i = 0; i < lenght / sizeof(int) - 1; i++)
				{
					integers[i] = integers[i] + 10;
				}
			}

			while (MAY_WRITE != *m)	{}		//Warten bis Lesen fertig
		}

		printf("Ich %d darf letztes mal schreiben\n", getpid());

		for (int i = 0; i <= lenght / sizeof(int); i++)
		{
			memcpy(shm + i + 1, integers + i, sizeof(int));
		}
		memcpy(shm, &done, sizeof(int));
	}

	else					//Child
	{
		for (int j = 0; j <= 3 ; j++)
		{
			while (MAY_READ != *m)	{}			//Warten bis schreiben fertig

			while (MAY_READ == *m)
			{
				printf("Ich %d darf lesen\n", getpid());
				for (int i = 1; i < lenght / sizeof(int); i++)
				{
					printf(" %d ", *(int *)(shm + i));
				}
				memcpy(shm, &write, sizeof(int));
				printf("\n");
			}
		}

		while (DATA_DONE != *m) {}				//Warten bis schreiben fertig

		while (DATA_DONE == *m)
		{
			printf("Ich %d darf letztes mal lesen\n", getpid());
			for (int i = 1; i < lenght / sizeof(int); i++)
			{
				printf(" %d ", *(int *)(shm + i));
			}
			memcpy(shm, &write, sizeof(int));
			printf("\n");
		}
		wait(NULL);
		printf("Datentransfer Ende\n");
	}
	close(fd);
	return 0;
}
