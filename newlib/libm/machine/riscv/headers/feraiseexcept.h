
#ifndef _FERAISEEXCEPT_H_
#define _FERAISEEXCEPT_H_

#include <fenv.h>

/* This implementation is intended to comply with the following
 * specification:
 *
 * http://pubs.opengroup.org/onlinepubs/009695399/functions/feraiseexcept.html
 * Referred to as 'feraiseexcept.html below.
 *
 * "The feraiseexcept() function shall attempt to raise the supported
 * floating-point exceptions represented by the excepts argument. The
 * order in which these floating-point exceptions are raised is
 * unspecified, except that if the excepts argument represents IEC
 * 60559 valid coincident floating-point exceptions for atomic
 * operations (namely overflow and inexact, or underflow and inexact),
 * then overflow or underflow shall be raised before inexact. Whether
 * the feraiseexcept() function additionally raises the inexact
 * floating-point exception whenever it raises the overflow or
 * underflow floating-point exception is implementation-defined."
 */

static __inline int _feraiseexcept(int excepts)
{
  /* Mask excepts to be sure only supported flag bits are set */

  excepts &= FE_ALL_EXCEPT;

  /* Per "The RISC-V Instruction Set Manual: Volume I: User-Level ISA:
   * Version 2.1":
   *
   * "The fields within the fcsr can also be accessed individually
   * through different CSR addresses, and separate assembler
   * pseudo-ops are defined for these accesses. The FRRM instruction
   * reads the Rounding Mode field frm and copies it into the
   * least-significant three bits of integer register rd, with zero in
   * all other bits. FSRM swaps the value in frm by copying the
   * original value into integer register rd, and then writing a new
   * value obtained from the three least-significant bits of integer
   * register rs1 into frm. FRFLAGS and FSFLAGS are defined
   * analogously for the Accrued Exception Flags field
   * fflags. Additional pseudo-instructions FSRMI and FSFLAGSI swap
   * values using an immediate value instead of register rs1."
   */

  asm volatile("csrrw zero, fflags, %0" : : "r"(excepts));

  /* Per 'feraiseexcept.html:
   * "If the argument is zero or if all the specified exceptions were
   * successfully raised, feraiseexcept() shall return
   * zero. Otherwise, it shall return a non-zero value."
   */

  /* Per "The RISC-V Instruction Set Manual: Volume I: User-Level ISA:
   * Version 2.1":
   *
   * "As allowed by the standard, we do not support traps on
   * floating-point exceptions in the base ISA, but instead require
   * explicit checks of the flags in software."
   *
   */

  return -1;
}

#endif /* _FERAISEEXCEPT_H_ */
