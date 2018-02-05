#include "weak_alias.h"

/* This weak alias is needed because _POSIX_THREADS triggers 
   _STDIO_WITH_THREAD_CANCELLATION_SUPPORT in libc/stdio/local.h which adds 
   thread cancelation support. If running without pthreads, there is no need to 
   worry about this. However, libpthread can override this weak alias if linked 
   against. */
int __pthread_setcancelstate(int state, int * oldstate)
{
  return 0;
}

weak_alias (__pthread_setcancelstate, pthread_setcancelstate)
