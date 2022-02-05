#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
  int max_int = 2147483647;

  int pid;
  int k, n;
  int x, j, z;

  if (argc < 2)
    n = 1; //Default
  else
    n = atoi(argv[1]);
  if (n < 0 || n > 20)
    n = 2;
  x = 0;
  pid = 0;

  for (k = 0; k < n; k++)
  {
    pid = fork();
    printProcesses();
    if (pid < 0)
    {
      printf(1, "%d failed in fork!\n", getpid());
    }
    else if (pid > 0)
    {
      // parent
      wait();
    }
    else
    {
      for (j = 0; j < max_int; j++)
      {
        printf(1, "j, %d\n", j);
        for (z = 0; z < max_int; z++)
        {
          //printf(1, "z, %d\n", z);
          x = x + 3.14 * 89.64; //Useless calculation to consume CPU Time
        }
      }
    }
  }

  exit();
}
