#include "types.h"
#include "stat.h"
#include "user.h"

static void
stay_alive(void)
{
  sleep(20);
}

int
main(int argc, char *argv[])
{
  int pid;
  int gpid;

  pid = fork();
  if(pid < 0){
    printf(1, "fork failed\n");
    exit();
  }

  if(pid == 0){
    gpid = fork();
    if(gpid < 0){
      printf(1, "fork failed\n");
      exit();
    }

    if(gpid == 0){
      stay_alive();
      exit();
    }

    stay_alive();
    wait();
    exit();
  }

  sleep(5);
  pstree();

  wait();
  exit();
}
