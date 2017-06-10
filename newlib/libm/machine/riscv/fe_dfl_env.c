#include <fenv.h>

/* This implementation is intended to comply with the following
 * specification:
 *
 * http://pubs.opengroup.org/onlinepubs/009695399
 *
 * "The <fenv.h> header shall define the following macro, which
 * represents the default floating-point environment (that is, the one
 * installed at program startup) and has type pointer to
 * const-qualified fenv_t. It can be used as an argument to the
 * functions within the <fenv.h> header that manage the floating-point
 * environment.
 *
 * FE_DFL_ENV"
 */

const fenv_t fe_dfl_env = { 0 };
const fenv_t *fe_dfl_env_p = &fe_dfl_env;
