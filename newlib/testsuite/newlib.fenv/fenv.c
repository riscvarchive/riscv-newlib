
#include <stdio.h>

/* This test has only be validated on RISC-V. */

#ifdef __riscv

#include <stdint.h>
#include <math.h>
#include <float.h>
#include <fenv.h>

#define ERR_CHECK(x)				\
    {						\
	int e = 0;				\
	e += x;					\
	err += e;				\
	if (e) {				\
	    printf("%s FAILED\n", #x);		\
	}					\
    }

/* Test */

int test(float fs1, float fs2, uint32_t rm, uint32_t xres, uint32_t xflags)
{
  int err = 0; // error count
  fenv_t env;  // FP environment
  fenv_t temp = -1;
  fexcept_t flags; // FP exceptions flags
  float f;
  uint32_t u;  // hex result

  const char *modes[4] = { "nearest", "zero", "down", "up" };

  /* Clear the flags */

  feclearexcept(FE_ALL_EXCEPT);
  ERR_CHECK(fegetenv(&env));
  ERR_CHECK((env & FE_ALL_EXCEPT) != 0);

  /* Set the rounding mode and perform the op */

  fesetround(rm);
  f = fs1 / fs2;
  u = *(uint32_t*)&f;

  /* Check the result */

  ERR_CHECK((u != xres));
  ERR_CHECK(fegetenv(&env));
  ERR_CHECK((env & FE_ALL_EXCEPT) != xflags);

  /* Get the flags individually via fegetexceptflag() */

  ERR_CHECK(fegetexceptflag(&flags, FE_INVALID));
  ERR_CHECK((flags & FE_INVALID) != (xflags & FE_INVALID));
  ERR_CHECK(fegetexceptflag(&flags, FE_DIVBYZERO));
  ERR_CHECK((flags & FE_DIVBYZERO) != (xflags & FE_DIVBYZERO));
  ERR_CHECK(fegetexceptflag(&flags, FE_OVERFLOW));
  ERR_CHECK((flags & FE_OVERFLOW) != (xflags & FE_OVERFLOW));
  ERR_CHECK(fegetexceptflag(&flags, FE_UNDERFLOW));
  ERR_CHECK((flags & FE_UNDERFLOW) != (xflags & FE_UNDERFLOW));
  ERR_CHECK(fegetexceptflag(&flags, FE_INEXACT));
  ERR_CHECK((flags & FE_INEXACT) != (xflags & FE_INEXACT));

  /* Test the flags individually via fetestexcept() */

  ERR_CHECK((fetestexcept(FE_INVALID) != (xflags & FE_INVALID)));
  ERR_CHECK((fetestexcept(FE_DIVBYZERO) != (xflags & FE_DIVBYZERO)));
  ERR_CHECK((fetestexcept(FE_OVERFLOW) != (xflags & FE_OVERFLOW)));
  ERR_CHECK((fetestexcept(FE_UNDERFLOW) != (xflags & FE_UNDERFLOW)));
  ERR_CHECK((fetestexcept(FE_INEXACT) != (xflags & FE_INEXACT)));

  /* Test that rounding mode can be read successfully */

  temp = fegetround();

  ERR_CHECK((temp != rm));

  return err;
}

/* Check for various flags */

int test_flags()
{
#define N_FTESTS 5 // Number of tests
  int err = 0; // error count

  float fs1[N_FTESTS] = { 2.0, 2.0, 0.0, 1.0, FLT_MAX };
  float fs2[N_FTESTS] = { 1.0, 3.0, 0.0, 0.0, FLT_MIN };

  uint32_t xres[N_FTESTS] = { 0x40000000, 0x3f2aaaab, 0x7fc00000, 0x7f800000, 0x7f800000 };
  uint32_t xflags[N_FTESTS] = { 0, FE_INEXACT, FE_INVALID, FE_DIVBYZERO, FE_OVERFLOW|FE_INEXACT };

  for (size_t i = 0; i < N_FTESTS; i++)
    {
      err += test(fs1[i], fs2[i], FE_TONEAREST, xres[i], xflags[i]);
    }

  return err;
}

/* Test rounding modes */

int test_rounding()
{
#define N_RTESTS 4 // Number of tests
  int err = 0; // error count

  const uint32_t xres[N_RTESTS] = { 0x3f2aaaab, 0x3f2aaaaa, 0x3f2aaaaa, 0x3f2aaaab };
  const uint32_t xflags[N_RTESTS] = { FE_INEXACT, FE_INEXACT, FE_INEXACT, FE_INEXACT };

  for (size_t i = 0 ; i < N_RTESTS; i++)
    {
      err += test(2.0, 3.0, i, xres[i], xflags[i]);
    }

  return err;
}

/* Test feupdateenv() */

int test_updateandhold()
{
  int err = 0;
  fenv_t env, tempenv;
  fexcept_t flags;

  /* Get current env */

  err += fegetenv(&env);

  /* Set all unset flags and check that the resulting flags are all one */

  env = ~env & FE_ALL_EXCEPT;

  ERR_CHECK(feupdateenv(&env));
  ERR_CHECK(fegetenv(&tempenv));
  ERR_CHECK(tempenv != FE_ALL_EXCEPT);

  /* Make sure that feholdexept() returns the correct env and clears flags */

  ERR_CHECK(feholdexcept(&flags));
  ERR_CHECK(flags != FE_ALL_EXCEPT);

  ERR_CHECK(fegetexceptflag(&flags, FE_ALL_EXCEPT));
  ERR_CHECK(flags != 0);

  return err;
}

#endif

/* Call individual tests */

int main(int argc, char **argv)
{
#ifdef __riscv
#ifdef __riscv_flen
  int err = 0;
  fenv_t env = 0;

  /* Clear environment (no exceptions, rounding mode 0) */

  fesetenv(&env);
  ERR_CHECK((env & FE_ALL_EXCEPT) != 0);

  /* Run tests */

  ERR_CHECK(test_rounding());
  ERR_CHECK(test_flags());
  ERR_CHECK(test_updateandhold());

  return err;
#else
  /* Return pass status for soft float*/
  return 0;
#endif
#else
  printf("testsuite/newlib.fenv is currently only supported for RISC-V.\n");
  return 0;
#endif
}
