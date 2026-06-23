#include "types.h"
#include "stat.h"
#include "user.h"

static void
check_state(int pid, char *expected)
{
  char buf[16];

  if(get_proc_state(pid, buf, sizeof(buf)) != 1){
    printf(1, "test_state: pid %d should exist\n", pid);
    exit();
  }
  if(strcmp(buf, expected) != 0){
    printf(1, "test_state: pid %d expected %s got %s\n", pid, expected, buf);
    exit();
  }
}

int
main(int argc, char *argv[])
{
  int pid;
  char buf[4];

  pid = getpid();
  check_state(pid, "RUNNING");

  if(get_proc_state(99999, buf, sizeof(buf)) != 0){
    printf(1, "test_state: missing pid should return 0\n");
    exit();
  }

  if(get_proc_state(pid, buf, 0) != -1){
    printf(1, "test_state: zero-sized buffer should fail\n");
    exit();
  }

  printf(1, "test_state passed\n");
  exit();
}
