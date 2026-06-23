#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int p[2];
  int pid;
  char token;

  if(pipe(p) < 0){
    printf(1, "pipe failed\n");
    exit();
  }

  pid = fork();
  if(pid < 0){
    printf(1, "fork failed\n");
    exit();
  }
  if(pid == 0){
    close(p[1]);
    read(p[0], &token, 1);
    getSibling();
    exit();
  }

  pid = fork();
  if(pid < 0){
    printf(1, "fork failed\n");
    exit();
  }
  if(pid == 0){
    close(p[1]);
    read(p[0], &token, 1);
    getSibling();
    exit();
  }

  close(p[0]);
  write(p[1], "xx", 2);
  close(p[1]);

  wait();
  wait();
  exit();
}
