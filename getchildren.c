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
  int i;
  int pid;

  for(i = 0; i < 2; i++){
    pid = fork();
    if(pid < 0){
      printf(1, "fork failed\n");
      exit();
    }
    if(pid == 0){
      if(i == 0)
        getChildren();
      stay_alive();
      exit();
    }
  }

  getChildren();

  for(i = 0; i < 2; i++)
    wait();

  getChildren();
  exit();
}
