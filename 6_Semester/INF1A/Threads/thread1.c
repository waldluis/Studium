#include  <stdio.h>
#include  <stdlib.h>
#include  <unistd.h>
#include  <pthread.h>

#define NUM_THREADS 3

void *printThreadID(void *threadid) {
    long tid;
    tid = (long)threadid;
    for(int i = 0; i < 5; i++)
    {
    	printf("thread %ld, pthread ID: %lu\n", tid, pthread_self());
    	sleep(1);
    }
    pthread_exit(NULL);
}


int main(int argc, char const *argv[]) {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    for (t = 0; t < NUM_THREADS; t++) {
        rc = pthread_create(&threads[t], NULL, printThreadID, (void *)t);
        if (rc) {
            printf("ERORR: %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }
    pthread_exit(NULL);    
}
