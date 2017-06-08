
#ifndef _FEGETROUND_H_
#define _FEGETROUND_H_

#include <fenv.h>

/* This implementation is intended to comply with the following
 * specification:
 *
 * http://pubs.opengroup.org/onlinepubs/009695399/functions/fegetround.html
 * Referred to as 'fegetround.html below.
 *
 * "The fegetround() function shall get the current rounding direction."
 */

static __inline int _fegetround()
{
  /* Get current rounding mode */

  fenv_t frm;
  asm volatile("frrm %0" : "=r"(frm));

  /* Per 'fegetround.html:
   *
   * "The fegetround() function shall return the value of the rounding
   * direction macro representing the current rounding direction or a
   * negative value if there is no such rounding direction macro or
   * the current rounding direction is not determinable."
   */

  /* Return the rounding mode */

  return frm;
}

#endif /* _FEGETROUND_H_ */
