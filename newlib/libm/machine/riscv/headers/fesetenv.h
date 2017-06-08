
#ifndef _FESETENV_H_
#define _FESETENV_H_

#include <fenv.h>

/* This implementation is intended to comply with the following
 * specification:
 *
 * http://pubs.opengroup.org/onlinepubs/009695399/functions/fegetenv.html
 * Referred to as 'fegetenv.html below.
 *
 * "The fegetenv() function shall attempt to store the current
 * floating-point environment in the object pointed to by envp.
 *
 * The fesetenv() function shall attempt to establish the
 * floating-point environment represented by the object pointed to by
 * envp. The argument envp shall point to an object set by a call to
 * fegetenv() or feholdexcept(), or equal a floating-point environment
 * macro. The fesetenv() function does not raise floating-point
 * exceptions, but only installs the state of the floating-point
 * status flags represented through its argument."
 */

static __inline int _fesetenv(const fenv_t *envp)
{

  /* Set environment (FCSR) */

  fenv_t fcsr = *envp;
  asm volatile("fscsr %0" : : "r"(fcsr));

  /* Per 'fegetenv.html:
   *
   * "If the environment was successfully established, fesetenv()
   * shall return zero. Otherwise, it shall return a non-zero value.
   */

  return 0;
}

#endif /* _FESETENV_H_ */
