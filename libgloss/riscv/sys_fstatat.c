#include <machine/syscall.h>

//------------------------------------------------------------------------
// fstatat
//------------------------------------------------------------------------
// Status of a file (by name) in a given directory.

int
_fstatat(int dirfd, const char *file, struct stat *st, int flags)
{
  struct kernel_stat kst;
  int rv = syscall_errno (SYS_fstatat, dirfd, file, &kst, flags, 0, 0);
  _conv_stat (st, &kst);
  return rv;
}

