
#ifndef _FEHOLDEXCEPT_H_
#define _FEHOLDEXCEPT_H_

#include <fenv.h>

/* This implementation is intended to comply with the following
 * specification:
 *
 * http://pubs.opengroup.org/onlinepubs/009695399/functions/feholdexcept.html
 * Referred to as 'feholdexcept.html below.
 *
 * "The feholdexcept() function shall save the current floating-point
 * environment in the object pointed to by envp, clear the
 * floating-point status flags, and then install a non-stop (continue
 * on floating-point exceptions) mode, if available, for all
 * floating-point exceptions."
 */

static __inline int _feholdexcept(fenv_t *envp)
{
  /* Store the current FP environment in envp*/

  fenv_t fcsr;
  asm volatile("frcsr %0" : : "r"(fcsr));
  *envp = fcsr;

  /* Clear the FP flags */

  asm volatile("csrrwi zero, fflags, %0" : : "i"(0));

  /* RISC-V does not raise FP traps so it is always in a "non-stop" mode */

  /* Per 'feholdexcept.html:
   *
   * "The feholdexcept() function shall return zero if and only if
   * non-stop floating-point exception handling was successfully
   * installed."
   */

  return 0;
}

#endif /* _FEHOLDEXCEPT_H_ */
