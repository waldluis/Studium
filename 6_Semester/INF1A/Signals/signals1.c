#include  <stdio.h>
#include  <signal.h>
#include  <stdlib.h>
#include  <unistd.h>

void     INThandler(int);

int  main(void)
{
     struct sigaction sa;
     sa.sa_handler = INThandler;
     sa.sa_flags = 0;

     sigaction(SIGINT, &sa, NULL);

     printf("Burning CDs till the end of time...\n");

     while (1)
          pause();
     return 0;
}

void  INThandler(int sig)
{
     static int counter = 0;

     if(counter == 0)              //First ctrl-c
     {
          printf("\nOUCH, did you hit Ctrl-C?\nPress ctrl-c again to exit\n");
          fflush(stdout);
          counter++;
     }
     else if(counter == 1)         //Second ctrl-c
     {
          printf("\nExiting now\n");
          fflush(stdout);
          exit(0);
     }
}
