#ifndef _FENV_H_
#define _FENV_H_

/* Per "The RISC-V Instruction Set Manual: Volume I: User-Level ISA:
 * Version 2.1", Section 8.2, "Floating-Point Control and Status
 * Register":
 *
 * Flag Mnemonic Flag Meaning
 * ------------- -----------------
 * NV            Invalid Operation
 * DZ            Divide by Zero
 * OF            Overflow
 * UF            Underflow
 * NX            Inexact
 */

#define FE_INVALID   0x00000010
#define FE_DIVBYZERO 0x00000008
#define FE_OVERFLOW  0x00000004
#define FE_UNDERFLOW 0x00000002
#define FE_INEXACT   0x00000001

#define FE_ALL_EXCEPT (FE_INVALID|FE_DIVBYZERO|FE_OVERFLOW|FE_UNDERFLOW|FE_INEXACT)

/* Per "The RISC-V Instruction Set Manual: Volume I: User-Level ISA:
 * Version 2.1", Section 8.2, "Floating-Point Control and Status
 * Register":
 *
 * Rounding Mode  Mnemonic Meaning  Meaning
 * -------------  ----------------  -------
 * 000            RNE               Round to Nearest, ties to Even
 * 001            RTZ               Round towards Zero
 * 010            RDN               Round Down (towards −∞)
 * 011            RUP               Round Up (towards +∞)
 * 100            RMM               Round to Nearest, ties to Max Magnitude
 * 101                              Invalid. Reserved for future use.
 * 110                              Invalid. Reserved for future use.
 * 111                              In instruction’s rm field, selects dynamic rounding mode;
 *                                  In Rounding Mode register, Invalid
 */

#define FE_TONEAREST_MM 0x00000004
#define FE_UPWARD     	0x00000003
#define FE_DOWNWARD   	0x00000002
#define FE_TOWARDZERO 	0x00000001
#define FE_TONEAREST  	0x00000000

#define FE_RMODE_MASK   0x7

/* Per "The RISC-V Instruction Set Manual: Volume I: User-Level ISA:
 * Version 2.1":
 *
 * "The F extension adds 32 floating-point registers, f0–f31, each 32
 * bits wide, and a floating-point control and status register fcsr,
 * which contains the operating mode and exception status of the
 * floating-point unit."
 */

typedef unsigned int fenv_t;

typedef unsigned int fexcept_t;

extern const fenv_t __fe_dfl_env;
#define FE_DFL_ENV (&__fe_dfl_env)

#endif /* _FENV_H_ */
