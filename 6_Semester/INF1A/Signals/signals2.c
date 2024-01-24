#define _DEFAULT_SOURCEq

#include  <stdio.h>
#include  <signal.h>
#include  <stdlib.h>
#include  <unistd.h>

volatile sig_atomic_t keep_going = 1;
static int ct = 0;

void     SIGALRMhandler(int);

/* Do one chunk of highly scientific computations: */
void do_stuff(void)
{

    ct++;
    printf("Starting chunk number (%d) ...\n", ct);

    for (int i = 0; i < 200; ++i)  usleep(1000);

    printf("Finished chunk number (%d).\n", ct);

}

int main()
{
    /* Check the flag once in a while to see when to quit: */
    struct sigaction sa;
    sa.sa_handler = SIGALRMhandler;
    sa.sa_flags = 0;

    sigaction(SIGALRM, &sa, NULL);

    alarm(3);                   //Alarm after 3 seconds to end program

    while ( keep_going )  // volatile
    {
        do_stuff();
    }
    return 0;
}

void  SIGALRMhandler(int sig)
{
    printf("Runtime expired\nFinish action and shut down\n");
    fflush(stdout);
    keep_going = 0;
}