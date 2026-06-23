#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int pid;

  pid = getpid();
  if(is_proc_valid(pid) != 1){
    printf(1, "test_valid: self pid %d should be valid\n", pid);
    exit();
  }

  if(is_proc_valid(99999) != 0){
    printf(1, "test_valid: missing pid should be invalid\n");
    exit();
  }

  printf(1, "test_valid passed\n");
  exit();
}
