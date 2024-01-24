#include  <stdio.h>
#include  <stdlib.h>
#include  <unistd.h>
#include  <pthread.h>

int zahlen[3];

void *addThread(void *var) {

	zahlen[2] = zahlen[0] + zahlen[1];
	pthread_exit(NULL);
}

void *printThread(void *var) {

	printf("Calculation: %d + %d = %d\n", zahlen[0], zahlen[1], zahlen[2]);
	pthread_exit(NULL);
}


int main()
{
	int rc;
	pthread_t thread;
	pthread_t thread2;
	long t = 1;
	printf("Calculator to add two numbers\n");
	printf("To terminate put 0 as first value to add\n\n");

	while (1)
	{
		//Read in the two values to add in threads
		printf("First number to add:\n");
		int result1 = scanf("%d", &zahlen[0]);

		if (result1 == EOF)
		{
			printf("Exiting\n");
			return 0;
		}

		if (zahlen[0] == 0)			//End when input is zero
		{
			printf("Exiting\n");
			return 0;
		}

		printf("Second number to add:\n");
		int result2 = scanf("%d", &zahlen[1]);

		if (result2 == EOF)
		{
			printf("Exiting\n");
			return 0;
		}

		//Start thread for adding numbers
		rc = pthread_create(&thread, NULL, addThread, (void *)t);
		if (rc) {
			printf("ERORR: %d\n", rc);
			exit(EXIT_FAILURE);
		}
		pthread_join(thread, NULL);			//Wait until thread is done

		//Start thread for printing numbers
		rc = pthread_create(&thread2, NULL, printThread, (void *)t);
		if (rc) {
			printf("ERORR: %d\n", rc);
			exit(EXIT_FAILURE);
		}
		pthread_join(thread2, NULL);		//Wait until thread is done
	}
	return 0;
}