
#ifndef _FESETROUND_H_
#define _FESETROUND_H_

#include <fenv.h>

/* This implementation is intended to comply with the following
 * specification:
 *
 * http://pubs.opengroup.org/onlinepubs/009695399/functions/fesetround.html
 * Referred to as 'fegetenv.html below.
 *
 * "The fesetround() function shall establish the rounding direction
 * represented by its argument round. If the argument is not equal to
 * the value of a rounding direction macro, the rounding direction is
 * not changed."
 */

static __inline int _fesetround(int round)
{
  /* Mask round to be sure only valid rounding bits are set */

  round &= FE_RMODE_MASK;

  /* Set the rounding mode */

  asm volatile("fsrm %0" : : "r"(round));

  /* Per 'fesetround.html:
   *
   * "The fesetround() function shall return a zero value if and only
   * if the requested rounding direction was established."
   */

  return 0;
}
#endif /* _FESETROUND_H_ */
