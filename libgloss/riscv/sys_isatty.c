#include <machine/syscall.h>

int _fstat(int file, struct stat *st);

//------------------------------------------------------------------------
// isatty
//------------------------------------------------------------------------
// Query whether output stream is a terminal. For consistency with the
// other minimal implementations, which only support output to stdout,
// this minimal implementation is suggested by the newlib docs.

int
_isatty(int file)
{
  struct stat s;
  int ret = _fstat (file, &s);
  return ret == -1 ? -1 : !!(s.st_mode & S_IFCHR);
}

