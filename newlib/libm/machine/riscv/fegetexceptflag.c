#include "headers/fegetexceptflag.h"

int fegetexceptflag(fexcept_t *flagp, int excepts)
{
    return _fegetexceptflag(flagp, excepts);
}
