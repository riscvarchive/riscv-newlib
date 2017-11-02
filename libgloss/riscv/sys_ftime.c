#include <machine/syscall.h>

//----------------------------------------------------------------------
// ftime
//----------------------------------------------------------------------
// Get the current time.  Only relatively correct.

int
_ftime(struct timeb *tp)
{
  tp->time = tp->millitm = 0;
  return 0;
}

