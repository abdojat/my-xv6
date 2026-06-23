#include "types.h"
#include "stat.h"
#include "user.h"

#define WORK 8000000

static void
burn_cpu(void)
{
  volatile unsigned int x = 0;
  unsigned int i;

  for(i = 0; i < WORK; i++)
    x = x * 1664525u + 1013904223u;
}

static void
run_group(char *label, int prios[], int n)
{
  int i;
  int pid;

  printf(1, "%s\n", label);
  for(i = 0; i < n; i++){
    pid = fork();
    if(pid < 0){
      printf(1, "schedtest: fork failed\n");
      exit();
    }
    if(pid == 0){
      if(setprio(prios[i]) < 0){
        printf(1, "schedtest: setprio(%d) failed\n", prios[i]);
        exit();
      }
      if(getprio() != prios[i]){
        printf(1, "schedtest: getprio mismatch for %d\n", prios[i]);
        exit();
      }
      burn_cpu();
      printf(1, "schedtest: child pid %d prio %d done\n", getpid(), prios[i]);
      exit();
    }
  }

  for(i = 0; i < n; i++)
    wait();
}

int
main(int argc, char *argv[])
{
  int weighted[] = { 1, 3, 6 };
  int starvation[] = { 1, 8 };
  int equal[] = { 4, 4, 4 };

  run_group("schedtest: weighted priorities 1, 3, 6", weighted, 3);
  run_group("schedtest: starvation sanity 1, 8", starvation, 2);
  run_group("schedtest: equal priorities 4, 4, 4", equal, 3);

  printf(1, "schedtest: passed\n");
  exit();
}
