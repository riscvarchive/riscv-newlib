#include "headers/fesetenv.h"

int fesetenv(const fenv_t *envp)
{
    return _fesetenv(envp);
}
