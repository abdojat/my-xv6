#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  if(argc > 1)
    helloYou(argv[1]);
  else
    helloYou("");
  exit();
}
