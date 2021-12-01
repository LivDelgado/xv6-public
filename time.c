#include "types.h"
#include "user.h"
#include "date.h"
#include "time.h"

int stdout = 1;
int stderror = 2;

int calculateTimeDifference(int start, int end) {
  return end - start;
}

void printTimeDifference(int difference, char *type) {
  char signal = ' ';
  if (difference < 0) {
    signal = '-';
    difference *= -1;
  }

  int seconds = difference / 100;
  int seconds_rest = difference % 100;

  // print time result
  printf(stdout, "%s: \t", type);
  printf(stdout, "%c%d.", signal, seconds);
  if (seconds_rest < 100 && seconds_rest > 10)
    printf(stdout, "0%d\n", seconds_rest);
  else if (seconds_rest < 10)
    printf (stdout, "00%d\n", seconds_rest);
}

void calculateTimeAndPrint(int start, int end, char *type) {
  int difference = calculateTimeDifference(start, end);
  printTimeDifference(difference, type);
}

int main(int argc, char *argv[])
{
  int pid = fork();

  int rt_start = uptime();
  time();

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

  int st_difference = time();
  int rt_end = uptime();

  printf(stdout, "time spent in %s command\n", argv[1]);
  calculateTimeAndPrint(rt_start, rt_end, "real");

  int rt_difference = calculateTimeDifference(rt_start, rt_end);
  printTimeDifference(st_difference, "system");

  int ut_total = rt_difference - st_difference;
  printTimeDifference(ut_total, "user");

  exit();
}
