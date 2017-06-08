#include "headers/fesetexceptflag.h"

int fesetexceptflag(const fexcept_t *flagp, int excepts)
{
    return _fesetexceptflag(flagp, excepts);
}
