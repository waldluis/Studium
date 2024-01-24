#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
  for (int i = 0; i < 10; i++) // loop will run n times (n=10)
  {
    if (fork() == 0)
    {
      printf("Child: started. PID=%d\n", getpid());
      printf("Child: exiting. PID=%d\n", getpid());
      exit(0);
    }
  }

  system("pstree -p | grep -C2 fork2.o");
  for (int i = 0; i < 10; i++) // loop will run n times (n=10)
    wait(NULL);
}