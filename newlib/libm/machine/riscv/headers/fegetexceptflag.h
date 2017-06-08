
#ifndef _FEGETEXCEPTFLAG_H_
#define _FEGETEXCEPTFLAG_H_

#include <fenv.h>

/* This implementation is intended to comply with the following
 * specification:
 *
 * http://pubs.opengroup.org/onlinepubs/009695399/functions/fegetexceptflag.html
 * Referred to as 'fegetexceptflag.html below.
 *
 * "The fegetexceptflag() function shall attempt to store an
 * implementation-defined representation of the states of the
 * floating-point status flags indicated by the argument excepts in
 * the object pointed to by the argument flagp."
 */

static __inline int _fegetexceptflag(fexcept_t *flagp, int excepts)
{
  /* Mask excepts to be sure only supported flag bits are set */

  excepts &= FE_ALL_EXCEPT;

  /* Get current exception flags */

  fexcept_t fflags;
  asm volatile("frflags %0" : "=r"(fflags));

  /* Return the requested flags in flagp */

  *flagp = fflags & excepts;

  /* Per 'fegetexceptflag.html:
   *
   * "If the representation was successfully stored, fegetexceptflag()
   * shall return zero. Otherwise, it shall return a non-zero
   * value."
   */

  return 0;

}

#endif /* _FEGETEXCEPTFLAG_H_ */
