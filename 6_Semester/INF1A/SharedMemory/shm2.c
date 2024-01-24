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
	int fd_pipe1[2];
	int fd_pipe2[2];
	int pid;
	int buffer, buffer1;;
	int reading = MAY_READ;
	int writing = MAY_WRITE;
	int done = DATA_DONE;
	int zaehler = 0;
	const off_t lenght = 10 * sizeof(int);

	//Create SHM
	fd = shm_open("/shm", O_RDWR | O_CREAT, 0666);
	if (fd == -1)
	{
		perror("open");
	}
	assert(0 == ftruncate(fd, lenght));
	int *shm = mmap(NULL, lenght, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	//Create Data
	int integers[lenght];
	for (int i = 1; i < lenght / sizeof(int) +1; i++)
	{
		integers[i-1] = i;
	}

	//Create Pipe
	if (pipe(fd_pipe1) == -1)						//writing pipe
	{
		fprintf(stderr, "Pipe1 Failed");
		return 1;
	}
	fcntl(fd_pipe1[0], F_SETFL, O_NONBLOCK);		//pipe non blocking
	write(fd_pipe1[1], &writing, sizeof(int));		//Block for first write

	if (pipe(fd_pipe2) == -1)						//reading pipe
	{
		fprintf(stderr, "Pipe2 Failed");
		return 1;
	}
	fcntl(fd_pipe2[0], F_SETFL, O_NONBLOCK);		//pipe non blocking
	write(fd_pipe2[1], &writing, sizeof(int));		//Block for first write


	pid = fork();
	if (pid == 0)				//Child
	{
		while (1)
		{
			read(fd_pipe1[0], &buffer1, sizeof(buffer1));

			if (buffer1 == 0)			//Read allowed
			{}
			else if (buffer1 == 1)		//Write allowed
			{
				if (zaehler == 4)
				{
					printf("Ich %d darf letztes mal schreiben\n", getpid());

					for (int i = 0; i <= lenght / sizeof(int); i++)
					{
						memcpy(shm + i + 1, integers + i, sizeof(int));
					}
					write(fd_pipe1[1], &done, sizeof(int));		//Writing done
					write(fd_pipe2[1], &done, sizeof(int));		//Writing done
					//close Pipe
					close(fd_pipe1[0]);
					close(fd_pipe1[1]);
					close(fd_pipe2[0]);
					close(fd_pipe2[1]);
					return 0;
				}
				else
				{
					printf("Ich %d darf schreiben\n", getpid());

					for (int i = 0; i <= lenght / sizeof(int); i++)
					{
						memcpy(shm + i + 1, integers + i, sizeof(int));
					}

					//count up values
					for (int i = 0; i < lenght / sizeof(int); i++)
					{
						integers[i] = integers[i] + 10;
					}
					zaehler++;
					write(fd_pipe1[1], &reading, sizeof(int));	//Writing done
					write(fd_pipe2[1], &reading, sizeof(int));	//Writing done
				}
			}
			else
			{sleep(1);}
		}
	}

	else					//Parent
	{
		sleep(1);
		while (1)
		{
			read(fd_pipe2[0], &buffer, sizeof(buffer));

			if (buffer == 0)			//Read allowed
			{
				printf("Ich %d darf lesen\n", getpid());
				for (int i = 1; i <= lenght / sizeof(int); i++)
				{
					printf(" %d ", *(int *)(shm + i));
				}
				printf("\n");
				write(fd_pipe2[1], &writing, sizeof(int));		//Reading done
				write(fd_pipe1[1], &writing, sizeof(int));		//Reading done
			}
			else if (buffer == 1)		//Writing allowed
			{sleep(1);}

			else if (buffer == -1)		//Tranfser end
			{
				printf("Ich %d darf letztes mal lesen\n", getpid());
				for (int i = 1; i <= lenght / sizeof(int); i++)
				{
					printf(" %d ", *(int *)(shm + i));
				}
				printf("\n");
				write(fd_pipe1[1], &writing, sizeof(int));		//Reading done
				printf("Datentransfer Ende\n");
				//close pipe and shm
				close(fd_pipe1[0]);
				close(fd_pipe1[1]);
				close(fd_pipe2[0]);
				close(fd_pipe2[1]);
				close(fd);
				wait(NULL);
				return 0;
			}
		}
	}
}