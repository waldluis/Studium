#include  <stdio.h>
#include  <stdlib.h>
#include  <unistd.h>
#include  <pthread.h>
#include  "condition.h"

int zahlen[3];
Condition input;					//Class for signals
Condition output;
pthread_t thread;
pthread_t thread2;

void *addThread(void *var) {

	while (1)
	{
		input.wait();
		//Read in the two values to add in threads
		printf("First number to add:\n");
		int result = scanf("%d", &zahlen[0]);
		if (result == EOF)
		{
			pthread_cancel(thread2);
			printf("Input Error\nExiting\n");
			pthread_exit(NULL);
		}

		if (zahlen[0] == 0)			//End when input is zero
		{
			pthread_cancel(thread2);		//End other thread
			printf("Exiting\n");
			pthread_exit(NULL);
		}

		printf("Second number to add:\n");
		result = scanf("%d", &zahlen[1]);

		if (result == EOF)
		{
			pthread_cancel(thread2);
			printf("Input Error\nExiting\n");
			pthread_exit(NULL);
		}

		zahlen[2] = zahlen[0] + zahlen[1];

		output.signal();
	}

	pthread_exit(NULL);
}

void *printThread(void *var) {

	while (1)
	{
		output.wait();
		printf("Calculation: %d + %d = %d\n", zahlen[0], zahlen[1], zahlen[2]);
		input.signal();
	}
	pthread_exit(NULL);
}


int main()
{
	int rc;
	long t = 1;

	printf("Calculator to add two numbers\n");
	printf("To terminate put 0 as first value to add\n\n");

	//Start thread for reading and adding numbers
	rc = pthread_create(&thread, NULL, addThread, (void *)t);
	if (rc) {
		printf("ERORR: %d\n", rc);
		exit(EXIT_FAILURE);
	}

	//Start thread for printing numbers
	rc = pthread_create(&thread2, NULL, printThread, (void *)t);
	if (rc) {
		printf("ERORR: %d\n", rc);
		exit(EXIT_FAILURE);
	}

	input.signal();						//Start calculator

	pthread_join(thread2, NULL);		//Wait until thread is done
	pthread_join(thread, NULL);			//Wait until thread is done

	return 0;
}