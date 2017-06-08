
#ifndef _FECLEAREXCEPT_H_
#define _FECLEAREXCEPT_H_

#include <fenv.h>

/* This implementation is intended to comply with the following
 * specification:
 *
 * http://pubs.opengroup.org/onlinepubs/009695399/functions/feclearexcept.html
 * Referred to as 'feclearexcept.html below.
 *
 * "The feclearexcept() function shall attempt to clear the supported
 * floating-point exceptions represented by excepts."
 */

static __inline int _feclearexcept(int excepts)
{
  /* Mask excepts to be sure only supported flag bits are set */

  excepts &= FE_ALL_EXCEPT;

  /* Per "The RISC-V Instruction Set Manual: Volume I: User-Level ISA:
   * Version 2.1":
   *
   * "The CSRRC (Atomic Read and Clear Bits in CSR) instruction reads
   * the value of the CSR, zeroextends the value to XLEN bits, and
   * writes it to integer register rd. The initial value in integer
   * register rs1 is treated as a bit mask that specifies bit
   * positions to be cleared in the CSR. Any bit that is high in rs1
   * will cause the corresponding bit to be cleared in the CSR, if
   * that CSR bit is writable. Other bits in the CSR are unaffected."
   */

  /* Clear the requested flags */

  asm volatile("csrrc zero, fflags, %0" : : "r"(excepts));

  /* Per 'feclearexcept.html
   * "If the argument is zero or if all the specified exceptions were
   * successfully cleared, feclearexcept() shall return zero. Otherwise,
   * it shall return a non-zero value."
   */

  return 0;
}

#endif /* _FECLEAREXCEPT_H_ */
