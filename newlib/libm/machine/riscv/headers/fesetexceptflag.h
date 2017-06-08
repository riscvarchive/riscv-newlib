
#ifndef _FESETEXCEPTFLAG_H_
#define _FESETEXCEPTFLAG_H_

#include <fenv.h>

/* This implementation is intended to comply with the following
 * specification:
 *
 * http://pubs.opengroup.org/onlinepubs/009695399/functions/fesetexceptflag.html
 * Referred to as 'fesetexceptflag.html below.
 *
 * "The fesetexceptflag() function shall attempt to set the
 * floating-point status flags indicated by the argument excepts to
 * the states stored in the object pointed to by flagp. The value
 * pointed to by flagp shall have been set by a previous call to
 * fegetexceptflag() whose second argument represented at least those
 * floating-point exceptions represented by the argument excepts. This
 * function does not raise floating-point exceptions, but only sets
 * the state of the flags."
 *
 */

static __inline int _fesetexceptflag(const fexcept_t *flagp, int excepts)
{
  /* Mask excepts to be sure only supported flag bits are set */

  excepts &= FE_ALL_EXCEPT;

  /* Set the requested flags */

  fexcept_t fflags = (excepts & *flagp);

  /* Set new the flags */

  asm volatile("csrs fflags, %0" : : "r"(fflags));

  /* Per 'fesetexceptflag.html:
   *
   * "If the excepts argument is zero or if all the specified
   * exceptions were successfully set, fesetexceptflag() shall return
   * zero. Otherwise, it shall return a non-zero value."
   */

  return 0;
}

#endif /* _FESETEXCEPTFLAG_H_ */
