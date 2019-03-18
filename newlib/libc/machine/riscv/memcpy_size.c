/* Copyright (c) 2019  SiFive Inc. All rights reserved.

   This copyrighted material is made available to anyone wishing to use,
   modify, copy, or redistribute it subject to the terms and conditions
   of the FreeBSD License.   This program is distributed in the hope that
   it will be useful, but WITHOUT ANY WARRANTY expressed or implied,
   including the implied warranties of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  A copy of this license is available at
   http://www.opensource.org/licenses.
*/

#include <stdint.h>
#include <string.h>
#include "../../string/local.h"

void *
    __inhibit_loop_to_libcall
    memcpy(void *restrict d, const void *restrict s, size_t count)
{
  uint8_t *des = (uint8_t *)d;
  const uint8_t *src = (const uint8_t *)s;
  const uint8_t *src_end = ((const uint8_t *)s) + count;
  while (src != src_end)
    *(des++) = *(src++);
  return d;
}
