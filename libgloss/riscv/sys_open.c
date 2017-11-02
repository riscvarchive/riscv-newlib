#include <machine/syscall.h>

int
_open(const char *name, int flags, int mode)
{
  return syscall_errno (SYS_open, name, flags, mode, 0, 0, 0);
}
