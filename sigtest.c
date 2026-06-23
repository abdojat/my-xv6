#include "types.h"
#include "stat.h"
#include "user.h"

#define WORK 8000000

volatile int handler_hits = 0;
volatile int handler_value = 0;

void
signal_handler(void)
{
  handler_hits++;
  handler_value = 1234;
  sigreturn();
}

static void
fail(char *msg)
{
  printf(1, "sigtest: %s\n", msg);
  exit();
}

static void
burn_cpu(void)
{
  volatile unsigned int x = 0;
  unsigned int i;

  for(i = 0; i < WORK && handler_hits == 0; i++)
    x = x * 1664525u + 1013904223u;
}

int
main(void)
{
  int pid;
  int child;
  int baseline;

  pid = getpid();

  if(sigsend(pid) < 0)
    fail("sigsend without handler failed");
  sleep(1);
  if(handler_hits != 0)
    fail("handler ran without registration");

  if(signal(signal_handler) < 0)
    fail("signal registration failed");

  baseline = handler_hits;
  getpid();
  if(handler_hits != baseline)
    fail("handler ran without a pending signal");

  if(sigsend(pid) < 0)
    fail("single sigsend failed");
  getpid();
  if(handler_hits != baseline + 1 || handler_value != 1234)
    fail("syscall delivery failed");

  if(sigsend(9999) != -1)
    fail("nonexistent pid should fail");

  handler_hits = 0;
  handler_value = 0;
  child = fork();
  if(child < 0)
    fail("fork for queueing test failed");
  if(child == 0){
    sleep(20);
    if(handler_hits != 1 || handler_value != 1234)
      fail("pending signal queued more than once");
    exit();
  }
  if(sigsend(child) < 0 || sigsend(child) < 0)
    fail("double sigsend to child failed");
  wait();

  handler_hits = 0;
  handler_value = 0;
  child = fork();
  if(child < 0)
    fail("fork for pending-state test failed");
  if(child == 0){
    sleep(1);
    if(handler_hits != 0)
      fail("fork inherited a pending signal");
    exit();
  }
  wait();

  handler_hits = 0;
  handler_value = 0;
  child = fork();
  if(child < 0)
    fail("fork for inherited-handler test failed");
  if(child == 0){
    burn_cpu();
    if(handler_hits != 1 || handler_value != 1234)
      fail("child did not run inherited handler");
    exit();
  }

  if(sigsend(child) < 0)
    fail("sigsend to child failed");
  wait();

  if(sigsend(pid) < 0)
    fail("timer delivery setup failed");
  burn_cpu();
  if(handler_hits != 1 || handler_value != 1234)
    fail("timer delivery failed");

  printf(1, "sigtest: passed\n");
  exit();
}
