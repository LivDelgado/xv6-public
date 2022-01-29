#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int stdout = 1;
int stderror = 2;



int calculateTimeDifference(int start, int end) {
  return end - start;
}

void printTimeDifference(int difference) {
  char signal = ' ';
  if (difference < 0) {
    signal = '-';
    difference *= -1;
  }

  int seconds = difference / 100;
  int seconds_rest = difference % 100;

  // print time result
  printf(stdout, "%c%d.", signal, seconds);
  if (seconds_rest < 100 && seconds_rest > 10)
    printf(stdout, "0%ds\n", seconds_rest);
  else if (seconds_rest < 10)
    printf (stdout, "00%ds\n", seconds_rest);
}

void calculateTimeAndPrint(int start, int end) {
  printTimeDifference(calculateTimeDifference(start, end));
}

int main(int argc, char *argv[]) {
  // create a new process to execute the command
  int pid = fork();

  // get current number of ticks as a real time start
  int rt_start = uptime();

  printProcesses();

  if (pid == 0) // child process
  {
    char *command = argv[1];
    char **arguments = argv + 1;

    // execute the command
    if (exec(command, arguments) < 0)
    {
      printf(stderror, "scheduler test: Failed to execute command\n");
      exit();
    }
  }
  else if (pid > 0) // parent process - wait for child execution
  {
    wait();
  }
  else
  {
    printf(stderror, "scheduler test: Fork error\n");
    exit();
  }
  printProcesses();

  // get current ticks number as real time end
  int rt_end = uptime();

  calculateTimeAndPrint(rt_start, rt_end);
  
  exit();
  printProcesses();
}