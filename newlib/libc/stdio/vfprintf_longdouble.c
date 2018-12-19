/*
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <newlib.h>

#include <_ansi.h>
#include <reent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <wchar.h>
#include <sys/lock.h>
#include <stdarg.h>
#include "local.h"
#include "../stdlib/local.h"
#include "fvwrite.h"
#include "vfieeefp.h"
#include "nano-vfprintf_local.h"



#define _NO_LONGDBL
#if defined _WANT_IO_LONG_DOUBLE && (LDBL_MANT_DIG > DBL_MANT_DIG)
#undef _NO_LONGDBL
#endif

extern char *_ldtoa_r (struct _reent *, _LONG_DOUBLE, int,
			      int, int *, int *, char **);

extern int _ldcheck (_LONG_DOUBLE *);

/* FIXME - frexpl is not yet supported; and cvt infloops if (double)f
   converts a finite value into infinity.  */
/* #  define FREXP frexpl */

static char *__cvt (struct _reent *data, _PRINTF_FLOAT_TYPE value, int ndigits,
	     int flags, char *sign, int *decpt, int ch, int *length,
	     char *buf);

int __exponent (char *p0, int exp, int fmtch);

#ifdef FLOATING_POINT

static char *
__cvt (struct _reent *data, _PRINTF_FLOAT_TYPE value, int ndigits, int flags,
       char *sign, int *decpt, int ch, int *length, char *buf)
{
  int mode, dsgn;
  char *digits, *bp, *rve;

	union
	{
	  struct ldieee ieee;
	  _LONG_DOUBLE val;
	} ld;
	ld.val = value;
	if (ld.ieee.sign) { /* this will check for < 0 and -0.0 */
		value = -value;
		*sign = '-';
	} else
		*sign = '\000';

  if (ch == 'f' || ch == 'F')
    {
      /* Ndigits after the decimal point.  */
      mode = 3;
    }
  else
    {
      /* To obtain ndigits after the decimal point for the 'e'
	 and 'E' formats, round to ndigits + 1 significant figures.  */
      if (ch == 'e' || ch == 'E')
	{
	  ndigits++;
	}
      /* Ndigits significant digits.  */
      mode = 2; 
    }

  digits = _DTOA_R (data, value, mode, ndigits, decpt, &dsgn, &rve);

  /* Print trailing zeros.  */
  if ((ch != 'g' && ch != 'G') || flags & ALT)
    {
      bp = digits + ndigits;
      if (ch == 'f' || ch == 'F')
	{
	  if (*digits == '0' && value)
	    *decpt = -ndigits + 1;
	  bp += *decpt;
	}
      /* Kludge for __dtoa irregularity.  */
      if (value == 0)
	rve = bp;
      while (rve < bp)
	*rve++ = '0';
    }
  *length = rve - digits;
  return (digits);
}



/* Decode and print floating point number specified by "eEfgG".  */
int
_printf_longdouble (struct _reent *data,
	       struct _prt_data_t *pdata,
	       FILE * fp,
	       int (*pfunc) (struct _reent *, FILE *, const char *,
			     size_t len), va_list * ap)
{
long double _fpvalue;
   
  char *decimal_point = _localeconv_r (data)->decimal_point;
  size_t decp_len = strlen (decimal_point);
  /* Temporary negative sign for floats.  */
  char softsign;
  /* Integer value of exponent.  */
  int expt;
  /* Character count for expstr.  */
  int expsize = 0;
  /* Actual number of digits returned by cvt.  */
  int ndig = 0;
  char *cp;
  int n;
  /* Field size expanded by dprec(not for _printf_float).  */
  int realsz;
  char code = pdata->code;
  
   if (pdata->flags & LONGDBL) {

	_fpvalue = GET_ARG (N, *ap, _LONG_DOUBLE);
  } else {
	_fpvalue = (_LONG_DOUBLE)GET_ARG (N, *ap, double);
  }

/* do this before tricky precision changes */
 expt = _ldcheck (&_fpvalue);
	if (expt == 2) {
	
				if (_fpvalue < 0)
					pdata->l_buf[0] = '-';
				if (code <= 'G') /* 'A', 'E', 'F', or 'G' */
					cp = "INF";
				else
					cp = "inf";
				pdata->size = 3;
				pdata->flags &= ~ZEROPAD;
			    goto print_longdouble;
			}
			if (expt == 1) {
			
				
				if (code <= 'G') /* 'A', 'E', 'F', or 'G' */
					cp = "NAN";
				else
					cp = "nan";
				pdata->size = 3;
				pdata->flags &= ~ZEROPAD;
				goto print_longdouble;
				
			}

  

  if (pdata->prec == -1)
    {
      pdata->prec = DEFPREC;
    }
  else if ((code == 'g' || code == 'G') && pdata->prec == 0)
    {
      pdata->prec = 1;
    }

  pdata->flags |= FPT;

  cp = __cvt (data, _fpvalue, pdata->prec, pdata->flags, &softsign,
	      &expt, code, &ndig, cp);

  if (code == 'g' || code == 'G')
    {
      if (expt <= -4 || expt > pdata->prec)
	/* 'e' or 'E'.  */
	code -= 2;
      else
	code = 'g';
    }
  if (code <= 'e')
    {
      /* 'a', 'A', 'e', or 'E' fmt.  */
      --expt;
      expsize = __exponent (pdata->expstr, expt, code);
      pdata->size = expsize + ndig;
      if (ndig > 1 || pdata->flags & ALT)
	++pdata->size;
    }
  else
    {
      if (code == 'f')
	{
	  /* 'f' fmt.  */
	  if (expt > 0)
	    {
	      pdata->size = expt;
	      if (pdata->prec || pdata->flags & ALT)
		pdata->size += pdata->prec + 1;
	    }
	  else
	    /* "0.X".  */
	    pdata->size = (pdata->prec || pdata->flags & ALT)
	      ? pdata->prec + 2 : 1;
	}
      else if (expt >= ndig)
	{
	  /* Fixed g fmt.  */
	  pdata->size = expt;
	  if (pdata->flags & ALT)
	    ++pdata->size;
	}
      else
	pdata->size = ndig + (expt > 0 ? 1 : 2 - expt);
      pdata->lead = expt;
    }

  if (softsign)
    pdata->l_buf[0] = '-';
print_longdouble:
  if (_printf_common (data, pdata, &realsz, fp, pfunc) == -1)
    goto error;

  if ((pdata->flags & FPT) == 0)
    {
      PRINT (cp, pdata->size);
    }
  else
    {
      /* Glue together f_p fragments.  */
      if (code >= 'f')
	{
	  /* 'f' or 'g'.  */
	  if (_fpvalue == 0)
	    {
	      /* Kludge for __dtoa irregularity.  */
	      PRINT ("0", 1);
	      if (expt < ndig || pdata->flags & ALT)
		{
		  PRINT (decimal_point, decp_len);
		  PAD (ndig - 1, pdata->zero);
		}
	    }
	  else if (expt <= 0)
	    {
	      PRINT ("0", 1);
	      if (expt || ndig || pdata->flags & ALT)
		{
		  PRINT (decimal_point, decp_len);
		  PAD (-expt, pdata->zero);
		  PRINT (cp, ndig);
		}
	    }
	  else
	    {
	      char *convbuf = cp;
	      PRINTANDPAD (cp, convbuf + ndig, pdata->lead, pdata->zero);
	      cp += pdata->lead;
	      if (expt < ndig || pdata->flags & ALT)
		PRINT (decimal_point, decp_len);
	      PRINTANDPAD (cp, convbuf + ndig, ndig - expt, pdata->zero);
	    }
	}
      else
	{
	  /* 'a', 'A', 'e', or 'E'.  */
	  if (ndig > 1 || pdata->flags & ALT)
	    {
	      PRINT (cp, 1);
	      cp++;
	      PRINT (decimal_point, decp_len);
	      if (_fpvalue)
		{
		  PRINT (cp, ndig - 1);
		}
	      /* "0.[0..]".  */
	      else
		/* __dtoa irregularity.  */
		PAD (ndig - 1, pdata->zero);
	    }
	  else			/* "XeYYY".  */
	    PRINT (cp, 1);
	  PRINT (pdata->expstr, expsize);
	}
    }

  /* Left-adjusting padding (always blank).  */
  if (pdata->flags & LADJUST)
    PAD (pdata->width - realsz, pdata->blank);

  return (pdata->width > realsz ? pdata->width : realsz);
error:
  return -1;

#undef _fpvalue
}

#endif
