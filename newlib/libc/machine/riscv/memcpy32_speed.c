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

#define ALIGNOF(addr) (((uintptr_t)(addr)) & (sizeof(void *) - 1))

// load: aligned load
// loadu: unaligned load
// loaduX: unaligned load with offset X
// u32: unsigned 32 bit integer
// u64: unsigned 64 bit integer
// u128: unsigned 128 bit integer

static void load_u32(uint8_t *des, const uint8_t *src)
{
  ((uint32_t *)des)[0] = ((const uint32_t *)src)[0];
}

#define loadu0_u32 load_u32

static void loadu1_u32(uint8_t *des, const uint8_t *src)
{
  uint32_t temp2 = ((const uint32_t *)(src - 1))[0];
  uint32_t temp3 = src[3];
  temp2 >>= 8;
  temp3 <<= 24;
  temp2 |= temp3;
  ((uint32_t *)des)[0] = temp2;
}

static void loadu2_u32(uint8_t *des, const uint8_t *src)
{
#if 1
  uint16_t temp2 = ((const uint16_t *)src)[0];
  uint16_t temp3 = ((const uint16_t *)src)[1];
  ((uint16_t *)des)[0] = temp2;
  ((uint16_t *)des)[1] = temp3;
#else
  uint32_t temp2 = ((const uint16_t *)src)[0];
  uint32_t temp3 = ((const uint16_t *)src)[1];
  temp3 <<= 16;
  temp2 |= temp3;
  ((uint32_t *)des)[0] = temp2;
#endif
}

static void loadu3_u32(uint8_t *des, const uint8_t *src)
{
  uint32_t temp2 = src[0];
  uint32_t temp3 = ((const uint32_t *)(src + 1))[0];
  temp3 <<= 8;
  temp2 |= temp3;
  ((uint32_t *)des)[0] = temp2;
}

static void load_u64(uint8_t *des, const uint8_t *src)
{
  uint32_t temp2 = ((const uint32_t *)src)[0];
  uint32_t temp3 = ((const uint32_t *)src)[1];
  ((uint32_t *)des)[0] = temp2;
  ((uint32_t *)des)[1] = temp3;
}

#define loadu0_u64 load_u64

static void loadu1_u64(uint8_t *des, const uint8_t *src)
{
  uint32_t temp2 = ((const uint32_t *)(src - 1))[0];
  uint32_t temp3 = ((const uint32_t *)(src + 3))[0];
  temp2 >>= 8;
  uint32_t temp4 = temp3 << 24;
  uint32_t temp5 = src[7];
  temp2 |= temp4;
  temp3 >>= 8;
  temp5 <<= 24;
  ((uint32_t *)des)[0] = temp2;
  temp3 |= temp5;
  ((uint32_t *)des)[1] = temp3;
}

static void loadu2_u64(uint8_t *des, const uint8_t *src)
{
  uint16_t temp2 = ((const uint16_t *)src)[0];
  uint16_t temp3 = ((const uint16_t *)src)[1];
  uint16_t temp4 = ((const uint16_t *)src)[2];
  uint16_t temp5 = ((const uint16_t *)src)[3];
  ((uint16_t *)des)[0] = temp2;
  ((uint16_t *)des)[1] = temp3;
  ((uint16_t *)des)[2] = temp4;
  ((uint16_t *)des)[3] = temp5;
}

static void loadu3_u64(uint8_t *des, const uint8_t *src)
{
  uint32_t temp2 = src[0];
  uint32_t temp3 = ((const uint32_t *)(src + 1))[0];
  uint32_t temp4 = ((const uint32_t *)(src + 5))[0];
  uint32_t temp5 = temp3 << 8;
  temp4 <<= 8;
  temp2 |= temp5;
  temp3 >>= 24;
  ((uint32_t *)des)[0] = temp2;
  temp3 |= temp4;
  ((uint32_t *)des)[1] = temp3;
}

static void load_u128(uint8_t *des, const uint8_t *src)
{
  uint32_t temp2 = ((const uint32_t *)src)[0];
  uint32_t temp3 = ((const uint32_t *)src)[1];
  uint32_t temp4 = ((const uint32_t *)src)[2];
  uint32_t temp5 = ((const uint32_t *)src)[3];
  ((uint32_t *)des)[0] = temp2;
  ((uint32_t *)des)[1] = temp3;
  ((uint32_t *)des)[2] = temp4;
  ((uint32_t *)des)[3] = temp5;
}

#define loadu0_u128 load_u128

static void loadu1_u128(uint8_t *des, const uint8_t *src)
{
  uint32_t temp2 = ((const uint32_t *)(src - 1))[0];
  uint32_t temp3 = ((const uint32_t *)(src + 3))[0];
  temp2 >>= 8;
  uint32_t temp4 = temp3 << 24;
  uint32_t temp5 = ((const uint32_t *)(src + 7))[0];
  temp2 |= temp4;
  temp3 >>= 8;
  temp4 = temp5 << 24;
  ((uint32_t *)des)[0] = temp2;
  temp3 |= temp4;
  temp2 = ((const uint32_t *)(src + 11))[0];
  temp5 >>= 8;
  temp4 = temp2 << 24;
  ((uint32_t *)des)[1] = temp3;
  temp5 |= temp4;
  temp3 = src[15];
  temp2 >>= 8;
  temp3 <<= 24;
  ((uint32_t *)des)[2] = temp5;
  temp2 |= temp3;
  ((uint32_t *)des)[3] = temp2;
}

static void loadu2_u128(uint8_t *des, const uint8_t *src)
{
  uint16_t temp2 = ((const uint16_t *)src)[0];
  uint16_t temp3 = ((const uint16_t *)src)[1];
  uint16_t temp4 = ((const uint16_t *)src)[2];
  uint16_t temp5 = ((const uint16_t *)src)[3];
  ((uint16_t *)des)[0] = temp2;
  ((uint16_t *)des)[1] = temp3;
  ((uint16_t *)des)[2] = temp4;
  ((uint16_t *)des)[3] = temp5;
  temp2 = ((const uint16_t *)src)[4];
  temp3 = ((const uint16_t *)src)[5];
  temp4 = ((const uint16_t *)src)[6];
  temp5 = ((const uint16_t *)src)[7];
  ((uint16_t *)des)[4] = temp2;
  ((uint16_t *)des)[5] = temp3;
  ((uint16_t *)des)[6] = temp4;
  ((uint16_t *)des)[7] = temp5;
}

static void loadu3_u128(uint8_t *des, const uint8_t *src)
{
  uint32_t temp2 = src[0];
  uint32_t temp3 = ((const uint32_t *)(src + 1))[0];
  uint32_t temp4 = temp3 << 8;
  uint32_t temp5 = ((const uint32_t *)(src + 5))[0];
  temp2 |= temp4;
  temp3 >>= 24;
  temp4 = temp5 << 8;
  ((uint32_t *)des)[0] = temp2;
  temp3 |= temp4;
  temp2 = ((const uint32_t *)(src + 9))[0];
  temp5 >>= 24;
  temp4 = temp2 << 8;
  ((uint32_t *)des)[1] = temp3;
  temp5 |= temp4;
  temp3 = ((const uint32_t *)(src + 13))[0];
  temp2 >>= 24;
  temp3 <<= 8;
  ((uint32_t *)des)[2] = temp5;
  temp2 |= temp3;
  ((uint32_t *)des)[3] = temp2;
}

#define MEMCPY_OFFSET(align_num)                \
  {                                             \
    while (src != src_end)                      \
    {                                           \
      loadu##align_num##_u128(des, src);        \
      src += 16;                                \
      des += 16;                                \
    }                                           \
    switch (residual)                           \
    {                                           \
    case 15:                                    \
      des[14] = src[14];                        \
    case 14:                                    \
      des[13] = src[13];                        \
    case 13:                                    \
      des[12] = src[12];                        \
    case 12:                                    \
      loadu##align_num##_u64(des, src);         \
      loadu##align_num##_u32(des + 8, src + 8); \
      break;                                    \
    case 11:                                    \
      des[10] = src[10];                        \
    case 10:                                    \
      des[9] = src[9];                          \
    case 9:                                     \
      des[8] = src[8];                          \
    case 8:                                     \
      loadu##align_num##_u64(des, src);         \
      break;                                    \
    case 7:                                     \
      des[6] = src[6];                          \
    case 6:                                     \
      des[5] = src[5];                          \
    case 5:                                     \
      des[4] = src[4];                          \
    case 4:                                     \
      loadu##align_num##_u32(des, src);         \
      break;                                    \
    case 3:                                     \
      des[2] = src[2];                          \
    case 2:                                     \
      des[1] = src[1];                          \
    case 1:                                     \
      des[0] = src[0];                          \
      break;                                    \
    }                                           \
  }

void *
    __inhibit_loop_to_libcall
    memcpy(void *restrict d, const void *restrict s, size_t count)
{
  uint8_t *des = (uint8_t *)d;
  const uint8_t *src = (const uint8_t *)s;
  if (3 < count)
  {
    uintptr_t alignof_des = (4 - ALIGNOF(des));
    switch (alignof_des)
    {
    case 3:
      des[2] = src[2];
    case 2:
      des[1] = src[1];
    case 1:
      des[0] = src[0];
      count -= alignof_des;
      des += alignof_des;
      src += alignof_des;
      break;
    }
    size_t residual = count & 15;
    count &= 0xFFFFFFF0;
    const uint8_t *src_end = src + count;
    switch (ALIGNOF(src))
    {
    case 0:
      MEMCPY_OFFSET(0);
      break;
    case 1:
      MEMCPY_OFFSET(1);
      break;
    case 2:
      MEMCPY_OFFSET(2);
      break;
    case 3:
      MEMCPY_OFFSET(3);
      break;
    }
  }
  else
    switch (count)
    {
    case 3:
      des[2] = src[2];
    case 2:
      des[1] = src[1];
    case 1:
      des[0] = src[0];
    }
  return d;
}
