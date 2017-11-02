#include <machine/syscall.h>

//----------------------------------------------------------------------
// read
//----------------------------------------------------------------------
// Read from a file.

ssize_t _read(int file, void *ptr, size_t len)
{
  return syscall_errno (SYS_read, file, ptr, len, 0, 0, 0);
}

