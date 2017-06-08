#ifndef _FEUPDATEENV_H_
#define _FEUPDATEENV_H_

#include <fenv.h>

/* This implementation is intended to comply with the following
 * specification:
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/functions/feupdateenv.html
 *
 * "The feupdateenv() function shall attempt to save the currently
 * raised floating-point exceptions in its automatic storage, attempt
 * to install the floating-point environment represented by the object
 * pointed to by envp, and then attempt to raise the saved
 * floating-point exceptions. The argument envp shall point to an
 * object set by a call to feholdexcept() or fegetenv(), or equal a
 * floating-point environment macro."
 */

static __inline int _feupdateenv(const fenv_t *envp)
{
    fenv_t saved_env = *envp; /* Save currently raised exceptions */
    fenv_t fcsr = *envp; /* Environment to install */
    asm volatile("fscsr %0" : : "r"(fcsr)); /* Install environment */

    /* "The feupdateenv() function shall return a zero value if and only
     * if all the required actions were successfully carried out."
     */

    return 0;
}

#endif /* _FEUPDATEENV_H_ */
