/* copyright (c) 1997, 1998, 2002, 2003, 2004, 2005
   Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ralf Baechle <ralf@gnu.org>.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#ifndef _SYS_ASM_H
#define _SYS_ASM_H

/* 
 * Macros to handle different pointer/register sizes for 32/64-bit code
 */
#if __riscv_xlen == 64
# define PTRLOG 3
# define SZREG	8
# define REG_S sd
# define REG_L ld
#elif __riscv_xlen == 32
# define PTRLOG 2
# define SZREG	4
# define REG_S sw
# define REG_L lw
#else
# error __riscv_xlen must equal 32 or 64
#endif

#ifndef __riscv_float_abi_soft
/* For ABI uniformity, reserve 8 bytes for floats, even if double-precision
   floating-point is not supported in hardware.  */
# define SZFREG 8
# ifdef __riscv_float_abi_single
#  define FREG_L flw
#  define FREG_S fsw
# elif defined(__riscv_float_abi_double)
#  define FREG_L fld
#  define FREG_S fsd
# elif defined(__riscv_float_abi_quad)
#  define FREG_L flq
#  define FREG_S fsq
# else
#  error unsupported FLEN
# endif
#endif

#endif /* sys/asm.h */
