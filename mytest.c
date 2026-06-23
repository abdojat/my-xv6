#include "types.h"
#include "stat.h"
#include "user.h"

static void
welcome_child(void)
{
  printf(1, "mytest: welcome child entered\n");
  if(welcomeDone() < 0){
    printf(1, "mytest: welcomeDone failed in child\n");
    exit();
  }

  printf(1, "mytest: ERROR returned from welcomeDone\n");
  exit();
}

int
main(int argc, char *argv[])
{
  int pid;

  if(welcomeDone() != -1){
    printf(1, "mytest: welcomeDone should fail before registration\n");
    exit();
  }

  pid = fork();
  if(pid < 0){
    printf(1, "mytest: fork before registration failed\n");
    exit();
  }
  if(pid == 0){
    printf(1, "mytest: first child ran normally\n");
    exit();
  }
  wait();

  if(welcomeFunction((void *)welcome_child) < 0){
    printf(1, "mytest: welcomeFunction registration failed\n");
    exit();
  }

  pid = fork();
  if(pid < 0){
    printf(1, "mytest: fork after registration failed\n");
    exit();
  }
  if(pid == 0){
    printf(1, "mytest: second child resumed after welcomeDone\n");
    exit();
  }
  wait();

  printf(1, "mytest passed\n");
  exit();
}
