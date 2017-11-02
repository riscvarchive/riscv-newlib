#include <machine/syscall.h>

//------------------------------------------------------------------------
// _exit
//------------------------------------------------------------------------
// Exit a program without cleaning up files.

void
_exit(int exit_status)
{
  syscall_errno (SYS_exit, exit_status, 0, 0, 0, 0, 0);
  while (1);
}

