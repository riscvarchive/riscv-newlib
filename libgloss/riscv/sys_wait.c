#include <machine/syscall.h>

//------------------------------------------------------------------------
// wait
//------------------------------------------------------------------------
// Wait for a child process. Minimal implementation for a system without
// processes just causes an error.

int _wait(int *status)
{
  errno = ECHILD;
  return -1;
}

