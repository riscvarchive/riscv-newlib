#include <machine/syscall.h>

//----------------------------------------------------------------------
// utime
//----------------------------------------------------------------------
// Stub.

int
_utime(const char *path, const struct utimbuf *times)
{
  return -1;
}

