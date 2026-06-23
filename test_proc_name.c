#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int pid;
  char buf[16];

  pid = getpid();

  if(fill_proc_name(pid, "codex") != 1){
    printf(1, "test_proc_name: self pid %d should be valid\n", pid);
    exit();
  }

  if(get_proc_name(pid, buf, sizeof(buf)) != 1){
    printf(1, "test_proc_name: could not read self name\n");
    exit();
  }
  if(strcmp(buf, "codex") != 0){
    printf(1, "test_proc_name: expected codex got %s\n", buf);
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

  if(get_proc_name(pid, buf, sizeof(buf)) != 1){
    printf(1, "test_proc_name: could not read short name\n");
    exit();
  }
  if(strcmp(buf, "shortname") != 0){
    printf(1, "test_proc_name: expected shortname got %s\n", buf);
    exit();
  }

  if(get_proc_name(99999, buf, sizeof(buf)) != 0){
    printf(1, "test_proc_name: missing pid read should return 0\n");
    exit();
  }

  printf(1, "test_proc_name passed\n");
  exit();
}
