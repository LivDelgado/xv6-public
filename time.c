#include "time.h"

int stdout = 1;
int stderror = 2;

void calculateTimeAndPrint(int start, int end, char *type) {
  int difference = end - start;
  int seconds = difference / 100;
  int seconds_rest = difference % 100;

  // print time result
  printf(stdout, "%s: \t", type);
  printf(stdout, "%d.", seconds);
  if (seconds_rest < 10)
    printf(stdout, "0");
  printf(stdout, "%d\n", seconds_rest);
}

int main(int argc, char *argv[])
{
  int rt_start = uptime();

  int pid = fork();

  if (pid == 0) // child process
  {
    if (exec(argv[1], argv + 1) < 0)
    {
      printf(stderror, "time: Failed to execute command\n");
      exit();
    }
  }
  else if (pid > 0) // parent process - wait for child execution
  {
    wait();
  }
  else
  {
    printf(stderror, "time: Fork error\n");
    exit();
  }

  int rt_end = uptime();

  printf(stdout, "time spent in %s command\n", argv[1]);
  calculateTimeAndPrint(rt_start, rt_end, "real");

  exit();
}