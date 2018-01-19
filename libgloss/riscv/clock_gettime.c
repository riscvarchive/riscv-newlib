#include <errno.h>
//#include <stdint.h>
#include <time.h>
#include <sys/time.h>
//#include <libc-internal.h>


/* Get current value of CLOCK and store it in tp.  */
int
clock_gettime (clockid_t clock_id, struct timespec *tp)
{
  struct timeval tv;
  int retval = -1;

  switch (clock_id)
    {
    case CLOCK_REALTIME:
      retval = gettimeofday (&tv, NULL);
      if (retval == 0)
	/* Convert into `timespec'.  */
	TIMEVAL_TO_TIMESPEC (&tv, tp);
      break;
    default:
      errno = (EINVAL);
      break;
    }

  return retval;
}
