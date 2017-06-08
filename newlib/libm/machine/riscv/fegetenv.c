#include "headers/fegetenv.h"

int fegetenv(fenv_t *envp)
{
    return _fegetenv(envp);
}
