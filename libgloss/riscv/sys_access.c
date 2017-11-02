#include <machine/syscall.h>

//------------------------------------------------------------------------
// access
//------------------------------------------------------------------------
// Permissions of a file (by name).

int
_access(const char *file, int mode)
{
  return syscall_errno (SYS_access, file, mode, 0, 0, 0, 0);
}

