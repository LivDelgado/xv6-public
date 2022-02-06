#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
  int priority;
  int pid;

  if (argc < 3)
  {
    printf(2, "Comando: nice <pid> <priority>\n");
    exit();
  }

  pid = atoi(argv[1]);
  priority = atoi(argv[2]);

  if (priority < 1 || priority > 10)
  {
    printf(2, "Prioridade deve ser entre 1 e 10\n");
    exit();
  }

  setprio(pid, priority);

  exit();
}
