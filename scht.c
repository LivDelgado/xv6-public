#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int stdout = 1;
int stderror = 2;


void executeProcess(int pid, char *command, char **arguments)
{
  if (pid == 0) // child process
  {
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
}

int main(int argc, char *argv[])
{
  char *command = argv[1];
  char **arguments = argv + 1;

  for (int i = 1; i < 11; i+=2) {
    // create a new process to execute the command
    int process = fork();
    //setprio(i); // when should we call this method?
    printProcesses();
    executeProcess(process, command, arguments);
  }

  printProcesses();

  exit();
}
