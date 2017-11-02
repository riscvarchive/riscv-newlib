#include <machine/syscall.h>

//------------------------------------------------------------------------
// lseek
//------------------------------------------------------------------------
// Set position in a file.

off_t
_lseek(int file, off_t ptr, int dir)
{
  return syscall_errno (SYS_lseek, file, ptr, dir, 0, 0, 0);
}

