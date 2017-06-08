#include "headers/feupdateenv.h"

int feupdateenv(const fenv_t *envp)
{
    return _feupdateenv(envp);
}
