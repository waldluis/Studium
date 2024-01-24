#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
  if (fork() == 0)
  {
    printf("Child_1: started. PID=%d\n", getpid());
    printf("Child_1 exiting. PID=%d\n", getpid());

    if (fork() == 0)
    {
      printf("Child_2: started. PID=%d\n", getpid());
      printf("Child_2: exiting. PID=%d\n", getpid());

      if (fork() == 0)
      {
        printf("Child_3: started. PID=%d\n", getpid());
        printf("Child_3: exiting. PID=%d\n", getpid());

        if (fork() == 0)
        {
          printf("Child_4: started. PID=%d\n", getpid());
          printf("Child_4: exiting. PID=%d\n", getpid());

          if (fork() == 0)
          {
            printf("Child_5: started. PID=%d\n", getpid());
            printf("Child_5: exiting. PID=%d\n", getpid());

            if (fork() == 0)
            {
              printf("Child_6: started. PID=%d\n", getpid());
              printf("Child_6: exiting. PID=%d\n", getpid());


              if (fork() == 0)
              {
                printf("Child_7: started. PID=%d\n", getpid());
                printf("Child_7: exiting. PID=%d\n", getpid());


                if (fork() == 0)
                {
                  printf("Child_8: started. PID=%d\n", getpid());
                  printf("Child_8: exiting. PID=%d\n", getpid());

                  if (fork() == 0)
                  {
                    printf("Child_9: started. PID=%d\n", getpid());
                    printf("Child_9: exiting. PID=%d\n", getpid());

                    if (fork() == 0)
                    {
                      printf("Child_10: started. PID=%d\n", getpid());
                      printf("Child_10: exiting. PID=%d\n", getpid());
                      system("pstree -l | grep -C2 a.out");
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  while (wait(NULL) > 0);
}