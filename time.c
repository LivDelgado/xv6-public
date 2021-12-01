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
  printf(stdout, "%s:\t", type);
  printf(stdout, "%c%d.", signal, seconds);
  if (seconds_rest < 100 && seconds_rest > 10)
    printf(stdout, "0%ds\n", seconds_rest);
  else if (seconds_rest < 10)
    printf (stdout, "00%ds\n", seconds_rest);
}

void calculateTimeAndPrint(int start, int end, char *type) {
  int difference = calculateTimeDifference(start, end);
  printTimeDifference(difference, type);
}

int main(int argc, char *argv[])
{
  // check if the number of arguments for time is less than needed
  // if so, prints only zeros
  if (argc < 2) {
    printTimeDifference(0, "real");
    printTimeDifference(0, "user");
    printTimeDifference(0, "sys");

    exit();
  }

  // create a new process to execute the command
  int pid = fork();

  // get current number of ticks as a real time start
  int rt_start = uptime();

  // calls time function to reset configurations
  time();

  if (pid == 0) // child process
  {
    char *command = argv[1];
    char **arguments = argv + 1;

    // execute the command
    if (exec(command, arguments) < 0)
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

  // gets the system time calculation from time function
  int st_difference = time();

  // get current ticks number as real time end
  int rt_end = uptime();

  // start printing the output
  printf(stdout, "time spent in %s command\n", argv[1]);

  // print real time
  calculateTimeAndPrint(rt_start, rt_end, "real");

  // print system time
  printTimeDifference(st_difference, "system");

  // calculates user time (real - system)
  int rt_difference = calculateTimeDifference(rt_start, rt_end);
  int ut_total = rt_difference - st_difference;

  // print user time
  printTimeDifference(ut_total, "user");

  exit();
}
