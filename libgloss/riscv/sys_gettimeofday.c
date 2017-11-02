#include <machine/syscall.h>

//----------------------------------------------------------------------
// gettimeofday
//----------------------------------------------------------------------
// Get the current time.  Only relatively correct.

int
_gettimeofday(struct timeval *tp, void *tzp)
{
  return syscall_errno (SYS_gettimeofday, tp, 0, 0, 0, 0, 0);
}

