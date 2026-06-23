#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int pid;

  pid = getpid();

  if(fill_proc_name(pid, "codex") != 1){
    printf(1, "test_proc_name: self pid %d should be valid\n", pid);
    exit();
  }

  if(fill_proc_name(99999, "missing") != 0){
    printf(1, "test_proc_name: missing pid should return 0\n");
    exit();
  }

  if(fill_proc_name(pid, "shortname") != 1){
    printf(1, "test_proc_name: short name should succeed\n");
    exit();
  }

  printf(1, "test_proc_name passed\n");
  exit();
}
