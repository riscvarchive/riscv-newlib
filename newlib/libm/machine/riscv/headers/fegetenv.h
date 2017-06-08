
#ifndef _FEGETENV_H_
#define _FEGETENV_H_

#include <fenv.h>

/* This implementation is intended to comply with the following
 * specification:
 *
 * http://pubs.opengroup.org/onlinepubs/009695399/functions/fegetenv.html
 * Referred to as 'fegetenv.html below.
 *
 * "The fegetenv() function shall attempt to store the current
 * floating-point environment in the object pointed to by envp."
 *
 */

static __inline int _fegetenv(fenv_t *envp)
{
  /* Get the current environment (FCSR) */

  fenv_t fcsr;
  asm volatile("frcsr %0" : "=r"(fcsr));

  /* Store FCSR in envp */

  *envp = fcsr;

  /* Per 'fegetenv.html:
   *
   * "If the representation was successfully stored, fegetenv() shall
   * return zero. Otherwise, it shall return a non-zero value.
   */

  return 0;
}

#endif /* _FEGETENV_H_ */
