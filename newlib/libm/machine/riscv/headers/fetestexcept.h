
#ifndef _FETESTEXCEPT_H_
#define _FETESTEXCEPT_H_

#include <fenv.h>

/* This implementation is intended to comply with the following
 * specification:
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/functions/fetestexcept.html
 *
 * "The fetestexcept() function shall determine which of a specified
 * subset of the floating-point exception flags are currently set. The
 * excepts argument specifies the floating-point status flags to be
 * queried."
 */

static __inline int _fetestexcept(int excepts)
{
  fenv_t fcsr;
  asm volatile("frcsr %0" : "=r"(fcsr));

  excepts &= FE_ALL_EXCEPT;

  /* "The fetestexcept() function shall return the value of the
   * bitwise-inclusive OR of the floating-point exception macros
   * corresponding to the currently set floating-point exceptions
   * included in excepts."
   */

  return (fcsr & excepts);
}

#endif /* _FETESTEXCEPT_H_ */
