/**
  ******************************************************************************************
  * \file hyp_types_gcc.h
  * \brief P60 types header file for GCC simulation
  *
  ******************************************************************************************
  * \attention
  *
  *  ST makes no warranty express or implied including but not limited to, any warranty of
  *  (i) merchantability or fitness for a particular purpose and/or (ii) requirements, for
  *  a particular purpose in relation to the LICENSED MATERIALS, which is provided <93>AS IS<94>,
  *  WITH ALL FAULTS. ST does not represent or warrant that the LICENSED MATERIALS provided
  *  hereunder is free of infringement of any third party patents, copyrights, trade secrets
  *  or other intellectual property rights. ALL WARRANTIES, CONDITIONS OR OTHER TERMS
  *  IMPLIED BY LAW ARE EXCLUDED TO THE FULLEST EXTENT PERMITTED BY LAW.
  *
  * <h2><center>&copy; COPYRIGHT 2020 STMicroelectronics - All Rights Reserved</center></h2>
  *
  ******************************************************************************************
  */

/*------------------------------------------------------------------------------
 * Includes
 *----------------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#ifndef __HYP_TYPES_GCC_H__
#define __HYP_TYPES_GCC_H__

/*------------------------------------------------------------------------------
 * Defines
 *----------------------------------------------------------------------------*/
/// Assert define
#ifdef __HYPERION_NOASSERT__
#define ASSERT(a)
#else // __HYPERION_NOASSERT__
#define ASSERT(a) assert(a)
#endif // __HYPERION_NOASSERT__

#define chess_unroll_loop_preamble
#define chess_loop_range(a,...)
#define chess_prepare_for_pipelining
#define chess_require_pipelining(a)
#define chess_no_warn_unroll
#define chess_unroll_loop(a)
#define chess_storage(a)
#define chess_flatten_loop
#define nop()
#define property(disable_instruction_class_do_loop_r)
#define chess_require_postamble
#define adds adds32
#define subs subs32
#define lmul lmul32
#define sat sat16
#define clrcc()

#define GET_CYCLE_DIFF 1

#ifdef ARM_COMPILE
#define HYPSA_TEST_SHA_SIZE 0x8000
#else // FPGA_COMPILE
#define HYPSA_TEST_SHA_SIZE 0
#endif // FPGA_COMPILE
#define HYPSA_TEST_FFT_SHA_SIZE 0

#define NB_ITER 24

#define f32_add(a, b) (a) + (b)
#define f32_sub(a,b) (a) - (b)

#define NB_COEF_HORNER   14

#define store_swap s_store_swap
#define vmac_swap s_vmac_swap

#define butterfly_m0 BUTTERFLY_M
#define cmulm0       CMULM
#define cmulm1       CMULMBIS
#define butterfly_m1 BUTTERFLY_MBIS


// TBD
#define sw_q15
#define lw_q15
#define set_int32_on()
#define load4x8
#define set_int32_off()
#define dvadd
#define hsp_sti_hp0_buff
#define dvmac



//bflym
//mdata.l = y.l - x.l
//mdata.h = y.h + x.h
//q.l = x.l + y.l
//q.h = x.h - y.h
#define BUTTERFLY_M(inx, iny, mdata, c)\
{\
	float32_t tmpmdata[2];\
	float32_t tmpc[2];\
	ufd64_t *resmdata = (ufd64_t *)tmpmdata;\
	ufd64_t *resc = (ufd64_t *)tmpc;\
	tmpmdata[0] = extract_low(iny) - extract_low(inx);\
	tmpmdata[1] = extract_high(iny) + extract_high(inx);\
	tmpc[0] = extract_low(inx) + extract_low(iny);\
	tmpc[1] = extract_high(inx) - extract_high(iny);\
	mdata = *resmdata;\
	c = *resc;\
}

//bflym
//mdata.l = x.l - y.l
//mdata.h = x.h + y.h
//q.l = x.l + y.l
//q.h = x.h - y.h
#define BUTTERFLY_MBIS(inx, iny, mdata, c)\
{\
	float32_t tmpmdata[2];\
	float32_t tmpc[2];\
	ufd64_t *resmdata = (ufd64_t *)tmpmdata;\
	ufd64_t *resc = (ufd64_t *)tmpc;\
	tmpmdata[0] = extract_low(inx) - extract_low(iny);\
	tmpmdata[1] = extract_high(inx) + extract_high(iny);\
	tmpc[0] = extract_low(inx) + extract_low(iny);\
	tmpc[1] = extract_high(inx) - extract_high(iny);\
	mdata = *resmdata;\
	c = *resc;\
}

#define getfpsta() 0


#ifndef HSP_HYP_BRAMAB_ADDR
#define HSP_HYP_BRAMAB_ADDR 0
#endif // HSP_HYP_BRAMAB_ADDR
#ifndef HSP_HYP_BRAMA_ADDR
#define HSP_HYP_BRAMA_ADDR 0
#endif // HSP_HYP_BRAMA_ADDR
#ifndef HSP_HYP_BRAMB_ADDR
#define HSP_HYP_BRAMB_ADDR 0
#endif // HSP_HYP_BRAMB_ADDR

/*------------------------------------------------------------------------------
 * Types
 *----------------------------------------------------------------------------*/
typedef uint32_t uloop_t;
typedef int32_t sloop_t;
typedef int8_t q7_t;
typedef int16_t q15_t;
typedef int32_t q31_t;
typedef int64_t q63_t;
typedef float float32_t;
typedef int32_t cycleu_t;
typedef uint64_t ufd64_t;
typedef int32_t mod_t;
typedef union
{
	float f;
	int   i;
	float32_t  f32;
} ufi;

/*------------------------------------------------------------------------------
 * Variables
 *----------------------------------------------------------------------------*/
extern int iter_inc; // For CORDIC
#if 0
static uint32_t reverse_coef_horner[NB_COEF_HORNER] =
{
	0x3f800000,/*  0 1  */
	0x3f317218,/*  1 log(2)  */
	0x3e75fdf0,/*  2 log(2) * 0.346573590300977230072021484375  */
	0x3d635847,/*  3 log(2) * 8.00755023374222218990325927734375e-2  */
	0x3c1d955b,/*  4 log(2) * 1.38760268673649989068508148193359375e-2  */
	0x3aaec3fe,/*  5 log(2) * 1.923625581184751354157924652099609375e-3  */
	0x392184cb,/*  6 log(2) * 2.2222735145760452724061906337738037109375e-4  */
	0x377fe935,/*  7 log(2) * 2.20061236149149408447556197643280029296875e-5  */
	0x35b11da0,/*  8 log(2) * 1.903801916114389314316213130950927734375e-6  */
	0x33d763d8,/*  9 log(2) * 1.4470056519666485428388114087283611297607421875e-7  */
	0x32179eac,/*  10 log(2) * 1.2732410258065041119834859273396432399749755859375e-8  */
	0x30f50329,/*  11 log(2) * 2.571891568638184910611244049505330622196197509765625e-9  */
	0xb01e9826,/*  12 log(2) * (-8.323813786674516546071345146629028022289276123046875e-10)  */
	0xaff70a46,/*  13 log(2) * (-6.482943214376757357086944466573186218738555908203125e-10)  */
};
#endif
/*------------------------------------------------------------------------------
 * Functions
 *----------------------------------------------------------------------------*/
/**
 * Normalize float for Hyperion restriction
 */
inline static void norm_float(float32_t *val)
{
  int32_t max_norm = 0x00800000;
  int32_t min_norm = 0x80800000;
  int32_t moinszero = 0x80000000;
  if ((*val > 0) && (*val < *((float32_t *) &max_norm))) {
    *val = 0;
  } else if ((*val < 0) && (*val > *((float32_t *) &min_norm))) {
    *val = *(float32_t *) &moinszero;
  }
}

/**
 * Get cycle counter
 */
inline static cycleu_t chess_cycle_count()
{
  return 0;
}

/***
lmul64(a,b)
***/
inline static int64_t lmul64(int32_t a, int32_t b)
{
	return (int64_t)((int64_t)a * (int64_t)b);
}

/***
sat8(a)
***/
inline static int8_t sat8(int16_t a)
{
	if (a < INT8_MIN)
	{
		return INT8_MIN;
	}
	if (a > INT8_MAX)
	{
		return INT8_MAX;
	}
	return (int8_t)a;
}

/***
sat16(a)
***/
inline static int16_t sat16(int32_t a)
{
	if (a < INT16_MIN)
	{
		return INT16_MIN;
	}
	if (a > INT16_MAX)
	{
		return INT16_MAX;
	}
	return (int16_t)a;
}

/***
sat32(a)
***/
inline static int32_t sat32(int64_t a)
{
	if (a < INT32_MIN)
	{
		return INT32_MIN;
	}
	if (a > INT32_MAX)
	{
		return INT32_MAX;
	}
	return (int32_t)a;
}

/***
addsdiv2(a,b)
***/
inline static int16_t addsdiv2(int16_t a, int16_t b)
{
	int32_t acc = (int32_t)((int32_t)a + (int32_t)b);
	if (acc < INT16_MIN)
	{
		return INT16_MIN;
	}
	if (acc > INT16_MAX)
	{
		return INT16_MAX;
	}
	return (int16_t)acc >> 1;
}

/***
subsdiv2(a,b)
***/
inline static int16_t subsdiv2(int16_t a, int16_t b)
{
	int32_t acc = (int32_t)((int32_t)a - (int32_t)b) ;
	if (acc < INT16_MIN)
	{
		return INT16_MIN;
	}
	if (acc > INT16_MAX)
	{
		return INT16_MAX;
	}
	return (int16_t)acc >> 1;
}

/***
shr1adds(a,b)
***/
inline static int16_t shr1adds(int16_t a, int16_t b)
{
	int32_t acc = (int32_t)(((int32_t)a >> 1) + ((int32_t)b >> 1));

	if (acc < INT16_MIN)
	{
		return INT16_MIN;
	}
	if (acc > INT16_MAX)
	{
		return INT16_MAX;
	}
	return (int16_t)acc;
}

/***
asls8(a,b)
***/
inline static int8_t asls8(int8_t a, int8_t b)
{
	int16_t acc;
	if (b < 0)
	{
		acc = (int16_t)a >> (int16_t)-b;
	}
	else
	{
		acc = (int16_t)a << (int16_t)b;
	}
	return sat8(acc);
}

/***
asls16(a,b)
***/
inline static int16_t asls16(int16_t a, int16_t b)
{
	int32_t acc;
	if (b < 0)
	{
		acc = (int32_t)a >> (int32_t)-b;
	}
	else
	{
		acc = (int32_t)a << (int32_t)b;
	}
	return sat16(acc);
}

/***
asls32(a,b)
***/
inline static int32_t asls32(int32_t a, int32_t b)
{
	int64_t acc;
	if (b < 0)
	{
		acc = (int64_t)a >> (int64_t)-b;
	}
	else
	{
		acc = (int64_t)a << (int64_t)b;
	}
	return sat32(acc);
}

/***
abss8(a)
***/
inline static int8_t abss8(int8_t a)
{
	int8_t b = a;
	if (b < 0)
	{
		if (b == (int8_t)0x80)
			return 0x7f;
		else
			return -b;
	}
	else return b;
}

/***
abss16(a)
***/
inline static int16_t abss16(int16_t a)
{
	int16_t b = a;
	if (b < 0)
	{
		if (b == (int16_t)0x8000)
			return 0x7fff;
		else
			return -b;
	}
	else return b;
}

/***
abss32(a)
***/
inline static int32_t abss32(int32_t a)
{
	int32_t b = a;
	if (b < 0)
	{
		if (b == (int32_t)0x80000000)
			return 0x7fffffff;
		else
			return -b;
	}
	else return b;
}

/***
abss64(a)
***/
inline static int64_t abss64(int64_t a)
{
	int64_t b = a;
	if (b < 0)
	{
		if (b == (int64_t)0x8000000000000000)
			return 0x7fffffffffffffff;
		else
			return -b;
	}
	else return b;
}

/***
adds8(a,b)
***/
inline static int8_t adds8(int8_t a, int8_t b)
{
	int16_t acc = (int16_t)a + (int16_t)b;
	if (acc < INT8_MIN)
	{
		return INT8_MIN;
	}
	if (acc > INT8_MAX)
	{
		return INT8_MAX;
	}
	return (int8_t)acc;
}

/***
adds16(a,b)
***/
inline static int16_t adds16(int16_t a, int16_t b)
{
	int32_t acc = (int32_t)a + (int32_t)b;
	if (acc < INT16_MIN)
	{
		return INT16_MIN;
	}
	if (acc > INT16_MAX)
	{
		return INT16_MAX;
	}
	return (int16_t)acc;
}

/***
adds32(a,b)
***/
inline static int32_t adds32(int32_t a, int32_t b)
{
	int64_t acc = (int64_t)a + (int64_t)b;
	if (acc < INT32_MIN)
	{
		return INT32_MIN;
	}
	if (acc > INT32_MAX)
	{
		return INT32_MAX;
	}
	return (int32_t)acc;
}

/***
subs8(a,b)
***/
inline static int8_t subs8(int8_t a, int8_t b)
{
	int16_t acc = (int16_t)a - (int16_t)b;
	if (acc < INT8_MIN)
	{
		return INT8_MIN;
	}
	if (acc > INT8_MAX)
	{
		return INT8_MAX;
	}
	return (int8_t)acc;
}

/***
subs16(a,b)
***/
inline static int16_t subs16(int16_t a, int16_t b)
{
	int32_t acc = (int32_t)a - (int32_t)b;
	if (acc < INT16_MIN)
	{
		return INT16_MIN;
	}
	if (acc > INT16_MAX)
	{
		return INT16_MAX;
	}
	return (int16_t)acc;
}

/***
subs32(a,b)
***/
inline static int32_t subs32(int32_t a, int32_t b)
{
	int64_t acc = (int64_t)a - (int64_t)b;
	if (acc < INT32_MIN)
	{
		return INT32_MIN;
	}
	if (acc > INT32_MAX)
	{
		return INT32_MAX;
	}
	return (int32_t)acc;
}

/***
abss16(a)
***/
inline static int16_t abss(int16_t a)
{
	int16_t b = a;
	if (b < 0)
	{
		if (b == (int16_t)0x8000)
			return 0x7fff;
		else
			return -b;
	}
	else return b;
}

/***
lmul16(a,b)
***/
inline static int16_t lmul16(int8_t a, int8_t b)
{
	return (int16_t)((int16_t)a * (int16_t)b);
}

/***
lmul32(a,b)
***/
inline static int32_t lmul32(int16_t a, int16_t b)
{
	return (int32_t)((int32_t)a * (int32_t)b);
}

/***
cyclic_add16(ptr, inc, start, size)
***/
inline static int16_t * cyclic_add16(q15_t *p, int offs, q15_t *start, uint32_t len)
{
  q15_t *r = p + offs;
  if (r >= start+len) {
    return r - len;
  } else if (r <  start) {
    return r + len;
  } else {
    return r;
  }
}

/***
cyclic_add32(ptr, inc, start, size)
***/
inline static int32_t *cyclic_add32(int32_t *p, int32_t offs, int32_t *start, int32_t len)
{
  int32_t *r = p + offs;
  if (r >= start+len) {
    return r - len;
  } else if (r <  start) {
    return r + len;
  } else {
    return r;
  }
}

/***
cyclic_addf(ptr, inc, start, size)
***/
inline static uint32_t cyclic_addf(uint32_t p, int32_t offs, uint32_t start, int32_t len)
{
  uint32_t r = p + offs;
  if (r >= (start+len)) {
    return (r - len);
  } else if (r <  start) {
    return (r + len);
  } else {
    return r;
  }
}

/***
cyclic_addf64(ptr, inc, start, size)
***/
inline static ufd64_t *cyclic_addf64(ufd64_t *p, int32_t offs, ufd64_t *start, int32_t len)
{
	ufd64_t *r = p + offs;

	if (r >= start+len)
	{
		return r - len;
	}
	else
	{
		if (r < start)
		{
			return r + len;
		}
		else
		{
			return r;
		}
	}
}

/***
cyclic_addf64_rom(ptr, inc, start, size)
***/
inline static ufd64_t *cyclic_addf64_rom(ufd64_t *p, int32_t offs, ufd64_t *start, int32_t len)
{
	int32_t offset = (int32_t)p - (int32_t)start;
	offset += offs;
	offset = (offset & 0x0fff);
	ufd64_t *r = start + offset;

	return r;
}

/**
 * Gcc implementation for hyperion butterfly_j float
 * X.r = X.r + Y.i
 * X.i = X.i - Y.r
 * Y.r = X.r - Y.i
 * Y.i = X.i + Y.r
 */
inline static void gcc_butterfly_j(ufd64_t inx, ufd64_t iny, ufd64_t *oux, ufd64_t *ouy)
{
  uint32_t a0 = inx & 0xffffffff;
  uint32_t a1 = (inx >> 32) & 0xffffffff;
  uint32_t b0 = iny & 0xffffffff;
  uint32_t b1 = (iny >> 32) & 0xffffffff;
  float32_t *pfa0 = (float32_t *) &a0;
  float32_t *pfa1 = (float32_t *) &a1;
  float32_t *pfb0 = (float32_t *) &b0;
  float32_t *pfb1 = (float32_t *) &b1;
  float32_t fc0 = *pfa0 + *pfb1;
  float32_t fc1 = *pfa1 - *pfb0;
  float32_t fd0 = *pfa0 - *pfb1;
  float32_t fd1 = *pfa1 + *pfb0;
  uint32_t c0 = *((uint32_t *) &fc0);
  uint32_t c1 = *((uint32_t *) &fc1);
  uint32_t d0 = *((uint32_t *) &fd0);
  uint32_t d1 = *((uint32_t *) &fd1);
  *oux = ((ufd64_t) c0) | (((ufd64_t) c1) << 32);
  *ouy = ((ufd64_t) d0) | (((ufd64_t) d1) << 32);
}

/**
 * Gcc implementation for hyperion butterfly float
 * X.r = X.r + Y.r
 * X.i = X.i + Y.i
 * Y.r = X.r - Y.r
 * Y.i = X.i - Y.i
 */
inline static void gcc_butterfly(ufd64_t inx, ufd64_t iny, ufd64_t *oux, ufd64_t *ouy)
{
  uint32_t a0 = inx & 0xffffffff;
  uint32_t a1 = (inx >> 32) & 0xffffffff;
  uint32_t b0 = iny & 0xffffffff;
  uint32_t b1 = (iny >> 32) & 0xffffffff;
  float32_t *pfa0 = (float32_t *) &a0;
  float32_t *pfa1 = (float32_t *) &a1;
  float32_t *pfb0 = (float32_t *) &b0;
  float32_t *pfb1 = (float32_t *) &b1;
  float32_t fc0 = *pfa0 + *pfb0;
  float32_t fc1 = *pfa1 + *pfb1; // a + b
  float32_t fd0 = *pfa0 - *pfb0;
  float32_t fd1 = *pfa1 - *pfb1; // a ? b
  uint32_t c0 = *((uint32_t *) &fc0);
  uint32_t c1 = *((uint32_t *) &fc1);
  uint32_t d0 = *((uint32_t *) &fd0);
  uint32_t d1 = *((uint32_t *) &fd1);
  *oux = ((ufd64_t) c0) | (((ufd64_t) c1) << 32);
  *ouy = ((ufd64_t) d0) | (((ufd64_t) d1) << 32);
}

/*
kx 0x0 kx 0x1 kx 0x2 kx 0x3 kx 0x4 kx 0x5 kx 0x6 kx 0x7 kx 0x8 kx 0x9 kx 0xa kx 0xb kx 0xc kx 0xd kx 0xe kx 0xf kx 0x10 kx 0x11 kx 0x12 kx 0x13 kx 0x14 kx 0x15 kx 0x16 kx 0x17 jump 0x50
kx 0x0 kx 0x1 kx 0x2 kx 0x3 kx 0x4 kx 0x5 kx 0x6 kx 0x7 kx 0x8 kx 0x9 kx 0xa kx 0xb kx 0xc kx 0xd kx 0xe kx 0xf kx 0x10 kx 0x11 kx 0x12 kx 0x13 kx 0x14 kx 0x15 kx 0x16 kx 0x17 jump 0xa0
kx 0x0 kx 0x1 kx 0x2 kx 0x3 kx 0x4 kx 0x5 kx 0x6 kx 0x7 kx 0x8 kx 0x9 kx 0xa kx 0xb kx 0xc kx 0xd kx 0xe kx 0xf kx 0x10 kx 0x11 kx 0x12 kx 0x13 kx 0x14 kx 0x15 kx 0x16 kx 0x17 jump 0x0

kx 0x0 kx 0x1 kx 0x2 kx 0x3 kx 0x4 kx 0x5 kx 0x6 kx 0x7 kx 0x8 kx 0x9 kx 0xa kx 0xb kx 0xc kx 0xd kx 0xe kx 0xf kx 0x10 kx 0x11 kx 0x12 kx 0x13 kx 0x14 kx 0x15 kx 0x16 kx 0x17 jump 0x50
kx 0x0 kx 0x1 kx 0x2 kx 0x3 kx 0x4 kx 0x5 kx 0x6 kx 0x7 kx 0x8 kx 0x9 kx 0xa kx 0xb kx 0xc kx 0xd kx 0xe kx 0xf kx 0x10 kx 0x11 kx 0x12 kx 0x13 kx 0x14 kx 0x15 kx 0x16 kx 0x17 jump 0xa0
kx 0x0 kx 0x1 kx 0x2 kx 0x3 kx 0x4 kx 0x5 kx 0x6 kx 0x7 kx 0x8 kx 0x9 kx 0xa kx 0xb kx 0xc kx 0xd kx 0xe kx 0xf kx 0x10 kx 0x11 kx 0x12 kx 0x13 kx 0x14 kx 0x15 kx 0x16 kx 0x17 jump 0xf0
kx 0x0 kx 0x1 kx 0x2 kx 0x3 kx 0x4 kx 0x5 kx 0x6 kx 0x7 kx 0x8 kx 0x9 kx 0xa kx 0xb kx 0xc kx 0xd kx 0xe kx 0xf kx 0x10 kx 0x11 kx 0x12 kx 0x13 kx 0x14 kx 0x15 kx 0x16 kx 0x17 jump 0x0

kx 0x0 kx 0x1 kx 0x2 kx 0x3 kx 0x4 kx 0x5 kx 0x6 kx 0x7 kx 0x8 kx 0x9 kx 0xa kx 0xb kx 0xc kx 0xd kx 0xe kx 0xf kx 0x10 kx 0x11 kx 0x12 kx 0x13 kx 0x14 kx 0x15 kx 0x16 kx 0x17 jump 0x50
kx 0x0 kx 0x1 kx 0x2 kx 0x3 kx 0x4 kx 0x5 kx 0x6 kx 0x7 kx 0x8 kx 0x9 kx 0xa kx 0xb kx 0xc kx 0xd kx 0xe kx 0xf kx 0x10 kx 0x11 kx 0x12 kx 0x13 kx 0x14 kx 0x15 kx 0x16 kx 0x17 jump 0xa0
kx 0x0 kx 0x1 kx 0x2 kx 0x3 kx 0x4 kx 0x5 kx 0x6 kx 0x7 kx 0x8 kx 0x9 kx 0xa kx 0xb kx 0xc kx 0xd kx 0xe kx 0xf kx 0x10 kx 0x11 kx 0x12 kx 0x13 kx 0x14 kx 0x15 kx 0x16 kx 0x17 jump 0xf0
kx 0x0 kx 0x1 kx 0x2 kx 0x3 kx 0x4 kx 0x5 kx 0x6 kx 0x7 kx 0x8 kx 0x9 kx 0xa kx 0xb kx 0xc kx 0xd kx 0xe kx 0xf kx 0x10 kx 0x11 kx 0x12 kx 0x13 kx 0x14 kx 0x15 kx 0x16 kx 0x17 jump 0x140
kx 0x0 kx 0x1 kx 0x2 kx 0x3 kx 0x4 kx 0x5 kx 0x6 kx 0x7 kx 0x8 kx 0x9 kx 0xa kx 0xb kx 0xc kx 0xd kx 0xe kx 0xf kx 0x10 kx 0x11 kx 0x12 kx 0x13 kx 0x14 kx 0x15 kx 0x16 kx 0x17 jump 0x0

*/

/**
 * Next butterfly
 */
inline static ufd64_t *next_bfly(ufd64_t *p, int32_t mask, ufd64_t *start)
{
#ifdef USE64_PTR
  ufd64_t po = p - start;
  po = (po + 1) & ~mask;
  ufd64_t *res = start + po;
#else // USE64_PTR
  int32_t tmpmask = mask >> 1; // Need shift to be complient with Hyperion archi
  ufd64_t po = p - start;
  po = (po + 1) & ~tmpmask;
  ufd64_t *res = start + po;
#endif // USE64_PTR
  return res;
}

/***
mycirc_addq15
***/
inline static int32_t *circ_add(int32_t *p, int32_t step, int32_t length, int32_t *start)
{
  int32_t po = p - start;
  po = (po + step) & (length - 1);
  int32_t *res = start + po;
  return res;
}

/**
 * circ_add for FFT with ufd64_t rom coeff
 */
inline static ufd64_t *gcc_circ_add4(ufd64_t *p, int32_t step, int32_t length, ufd64_t *start)
{
  int32_t po = p - start;
  po = (po + step) & (length - 1);
  ufd64_t *pres = start + po;
  return pres;
}

/**
 * circ_add for radix 4 FFT with ufd64_t rom coeff
 */
inline static int32_t gcc_circ_add3(int32_t a, int32_t b, int32_t c)
{
  int32_t val = (a & ~(c-1)) | ((a + b) & (c-1));
  return val;
}

/**
 * Complex multiply in float
 * X.r = X.r * Y.r - Xi * Yi
 * X.i = X.r * Y.i + Xi * Yr
 */
inline static ufd64_t cmul(ufd64_t inx, ufd64_t iny)
{
  uint32_t a0 = inx & 0xffffffff;
  uint32_t a1 = (inx >> 32) & 0xffffffff;
  uint32_t b0 = iny & 0xffffffff;
  uint32_t b1 = (iny >> 32) & 0xffffffff;
  float32_t *pfa0 = (float32_t *) &a0;
  float32_t *pfa1 = (float32_t *) &a1;
  float32_t *pfb0 = (float32_t *) &b0;
  float32_t *pfb1 = (float32_t *) &b1;
  float32_t p_re = *pfa0 * *pfb0 - *pfa1 * *pfb1;
  float32_t p_im = *pfa0 * *pfb1 + *pfa1 * *pfb0;
  uint32_t res0 = *((uint32_t *) &p_re);
  uint32_t res1 = *((uint32_t *) &p_im);
  ufd64_t res = ((ufd64_t) res0) | (((ufd64_t) res1) << 32);
  return res;
}

/**
 * Left shift for pointer
 */
inline static int32_t lshift1(int32_t in)
{
  int32_t res = in << 1;
  return res;
}

/**
 * Right shift for pointer
 */
inline static int32_t rshift1(int32_t in)
{
  int32_t res = in >> 1;
  return res;
}

/**
 * Left shift for pointer
 */
inline static int32_t lshift2(int32_t in)
{
  int32_t res = in << 2;
  return res;
}

/**
 * Right shift for pointer
 */
inline static int32_t rshift2(int32_t in)
{
  int32_t res = in >> 2;
  return res;
}

/******* SIMD *******/
inline static float fred(ufd64_t a0)
{
  uint32_t ulsb0 = a0 & 0xffffffff;
  uint32_t umsb0 = a0 >> 32;
  float *pflsb0 = (float *) &ulsb0;
  float *pfmsb0 = (float *) &umsb0;
  // Do SIMD operation
  float res = *pflsb0 + *pfmsb0;
  return res;
}

inline static ufd64_t vsub(ufd64_t a0, ufd64_t a1)
{
  uint32_t ulsb0 = a0 & 0xffffffff;
  uint32_t ulsb1 = a1 & 0xffffffff;
  uint32_t umsb0 = a0 >> 32;
  uint32_t umsb1 = a1 >> 32;
  float *pflsb0 = (float *) &ulsb0;
  float *pflsb1 = (float *) &ulsb1;
  float *pfmsb0 = (float *) &umsb0;
  float *pfmsb1 = (float *) &umsb1;
  // Do SIMD operation
  float rflsb = *pflsb0 - *pflsb1;
  float rfmsb = *pfmsb0 - *pfmsb1;
  uint32_t rulsb = *(uint32_t *) &rflsb;
  uint32_t rumsb = *(uint32_t *) &rfmsb;
  ufd64_t res64 = ((uint64_t) rumsb << 32) | (uint64_t) rulsb;
  return res64;
}

inline static ufd64_t vrmul(ufd64_t a0, float a1)
{
  uint32_t ulsb0 = a0 & 0xffffffff;
  uint32_t umsb0 = a0 >> 32;
  float *pflsb0 = (float *) &ulsb0;
  float *pfmsb0 = (float *) &umsb0;
  // Do SIMD operation
  float rflsb = *pflsb0 * a1;
  float rfmsb = *pfmsb0 * a1;
  uint32_t rulsb = *(uint32_t *) &rflsb;
  uint32_t rumsb = *(uint32_t *) &rfmsb;
  ufd64_t res64 = ((uint64_t) rumsb << 32) | (uint64_t) rulsb;
  return res64;
}

inline static ufd64_t vmac(ufd64_t a0, ufd64_t a1, ufd64_t a2)
{
  uint32_t ulsb0 = a0 & 0xffffffff;
  uint32_t ulsb1 = a1 & 0xffffffff;
  uint32_t ulsb2 = a2 & 0xffffffff;
  uint32_t umsb0 = a0 >> 32;
  uint32_t umsb1 = a1 >> 32;
  uint32_t umsb2 = a2 >> 32;
  float *pflsb0 = (float *) &ulsb0;
  float *pflsb1 = (float *) &ulsb1;
  float *pflsb2 = (float *) &ulsb2;
  float *pfmsb0 = (float *) &umsb0;
  float *pfmsb1 = (float *) &umsb1;
  float *pfmsb2 = (float *) &umsb2;
  // Do SIMD operation
  float rflsb = *pflsb0 + (*pflsb1 * *pflsb2);
  float rfmsb = *pfmsb0 + (*pfmsb1 * *pfmsb2);
  uint32_t rulsb = *(uint32_t *) &rflsb;
  uint32_t rumsb = *(uint32_t *) &rfmsb;
  ufd64_t res64 = ((uint64_t) rumsb << 32) | (uint64_t) rulsb;
  return res64;
}

inline static ufd64_t vadd(ufd64_t a0, ufd64_t a1)
{
  uint32_t ulsb0 = a0 & 0xffffffff;
  uint32_t ulsb1 = a1 & 0xffffffff;
  uint32_t umsb0 = a0 >> 32;
  uint32_t umsb1 = a1 >> 32;
  float *pflsb0 = (float *) &ulsb0;
  float *pflsb1 = (float *) &ulsb1;
  float *pfmsb0 = (float *) &umsb0;
  float *pfmsb1 = (float *) &umsb1;
  // Do SIMD operation
  float rflsb = *pflsb0 + *pflsb1;
  float rfmsb = *pfmsb0 + *pfmsb1;
  uint32_t rulsb = *(uint32_t *) &rflsb;
  uint32_t rumsb = *(uint32_t *) &rfmsb;
  ufd64_t res64 = ((uint64_t) rumsb << 32) | (uint64_t) rulsb;
  return res64;
}

inline static ufd64_t vradd(ufd64_t a0, float a1)
{
  uint32_t ulsb0 = a0 & 0xffffffff;
  uint32_t umsb0 = a0 >> 32;
  float *pflsb0 = (float *) &ulsb0;
  float *pfmsb0 = (float *) &umsb0;
  // Do SIMD operation
  float rflsb = *pflsb0 + a1;
  float rfmsb = *pfmsb0 + a1;
  uint32_t rulsb = *(uint32_t *) &rflsb;
  uint32_t rumsb = *(uint32_t *) &rfmsb;
  ufd64_t res64 = ((uint64_t) rumsb << 32) | (uint64_t) rulsb;
  return res64;
}

inline static ufd64_t vmul(ufd64_t a0, ufd64_t a1)
{
  uint32_t ulsb0 = a0 & 0xffffffff;
  uint32_t ulsb1 = a1 & 0xffffffff;
  uint32_t umsb0 = a0 >> 32;
  uint32_t umsb1 = a1 >> 32;
  float *pflsb0 = (float *) &ulsb0;
  float *pflsb1 = (float *) &ulsb1;
  float *pfmsb0 = (float *) &umsb0;
  float *pfmsb1 = (float *) &umsb1;
  // Do SIMD operation
  float rflsb = *pflsb0 * *pflsb1;
  float rfmsb = *pfmsb0 * *pfmsb1;
  uint32_t rulsb = *(uint32_t *) &rflsb;
  uint32_t rumsb = *(uint32_t *) &rfmsb;
  ufd64_t res64 = ((uint64_t) rumsb << 32) | (uint64_t) rulsb;
  return res64;
}

inline static ufd64_t vi2f(ufd64_t a0)
{
  uint32_t ulsb0 = a0 & 0xffffffff;
  uint32_t umsb0 = a0 >> 32;
  // Do SIMD operation
  float rflsb = (float) ulsb0;
  float rfmsb = (float) umsb0;
  uint32_t rulsb = *(uint32_t *) &rflsb;
  uint32_t rumsb = *(uint32_t *) &rfmsb;
  ufd64_t res64 = ((uint64_t) rumsb << 32) | (uint64_t) rulsb;
  return res64;
}

inline static ufd64_t vf2iz(ufd64_t a0)
{
  uint32_t ulsb0 = a0 & 0xffffffff;
  uint32_t umsb0 = a0 >> 32;
  // Do SIMD operation
  int32_t rilsb = *(int32_t *) &ulsb0;
  int32_t rimsb = *(int32_t *) &umsb0;
  uint32_t rulsb = *(uint32_t *) &rilsb;
  uint32_t rumsb = *(uint32_t *) &rimsb;
  ufd64_t res64 = ((uint64_t) rumsb << 32) | (uint64_t) rulsb;
  return res64;
}

inline static ufd64_t vu2f(ufd64_t a0)
{
  uint32_t ulsb0 = a0 & 0xffffffff;
  uint32_t umsb0 = a0 >> 32;
  // Do SIMD operation
  float rflsb = (float) ulsb0;
  float rfmsb = (float) umsb0;
  uint32_t rulsb = *(uint32_t *) &rflsb;
  uint32_t rumsb = *(uint32_t *) &rfmsb;
  ufd64_t res64 = ((uint64_t) rumsb << 32) | (uint64_t) rulsb;
  return res64;
}

inline static ufd64_t vf2uz(ufd64_t a0)
{
  uint32_t ulsb0 = a0 & 0xffffffff;
  uint32_t umsb0 = a0 >> 32;
  // Do SIMD operation
  uint32_t rilsb = *(uint32_t *) &ulsb0;
  uint32_t rimsb = *(uint32_t *) &umsb0;
  uint32_t rulsb = *(uint32_t *) &rilsb;
  uint32_t rumsb = *(uint32_t *) &rimsb;
  ufd64_t res64 = ((uint64_t) rumsb << 32) | (uint64_t) rulsb;
  return res64;
}

inline static float_t s24b2f(int32_t a0)
{
  int32_t tmpi = a0 & 0xffffff;
  if (a0 & 0x800000) {
    tmpi |= 0xff000000;
  }
  float resf = (float) tmpi;
  return resf;
}

//res0 = acc0 + a*b res1 = acc1 + a*(b(lo),c(hi))
inline static void vdmac(ufd64_t acc0, ufd64_t a , ufd64_t b,  ufd64_t acc1, ufd64_t c, ufd64_t *res0, ufd64_t *res1)
{
	uint32_t acc0h = acc0 >> 32;
	uint32_t acc0l = acc0 & 0xffffffff;
	uint32_t acc1h = acc1 >> 32;
	uint32_t acc1l = acc1 & 0xffffffff;
	uint32_t ah = a >> 32;
	uint32_t al = a & 0xffffffff;
	uint32_t bh = b >> 32;
	uint32_t bl = b & 0xffffffff;
  	//uint32_t ch = c >> 32;
	uint32_t cl = c & 0xffffffff;

	float * facc0l = (float *)&acc0l;
	float * facc0h = (float *)&acc0h;
	float * facc1l = (float *)&acc1l;
	float * facc1h = (float *)&acc1h;
	float * fal = (float *)&al;
	float * fah = (float *)&ah;
	float * fbl = (float *)&bl;
	float * fbh = (float *)&bh;
  	float * fcl = (float *)&cl;
	//float * fch = (float *)&ch;

	// Do 1st SIMD operation
	float lsb = *facc0l + (*fal * *fbl);
	float hsb = *facc0h + (*fah * *fbh);
	uint32_t rulsb = *(uint32_t *) &lsb;
	uint32_t ruhsb = *(uint32_t *) &hsb;
	*res0 = ((uint64_t) ruhsb << 32) | (uint64_t) rulsb;

	// Do 2nd SIMD operation
	lsb = *facc1l + (*fal * *fbh);
	hsb = *facc1h + (*fah * *fcl);
	uint32_t rulsb1 = *(uint32_t *) &lsb;
	uint32_t ruhsb1 = *(uint32_t *) &hsb;
	*res1 = ((uint64_t) ruhsb1 << 32) | (uint64_t) rulsb1;
}

/**
 * Extract MSB of a 64 bits in a 32 bits
 */
inline static float32_t extract_high(ufd64_t reg)
{
	uint32_t resh = reg >> 32;
	return (*(float *)&resh);
}

/**
 * Extract LSB of a 64 bits in a 32 bits
 */
inline static float32_t extract_low(ufd64_t reg)
{
	uint32_t resl = reg & 0xffffffff;
	return (*(float *)&resl);
}

#ifndef ARM_COMPILE

/**
 * Float max value
 */
inline static float32_t hyp_fmax(float32_t a, float32_t b)
{
  float32_t res = a;
  if (b > a) {
    res = b;
  }
  return res;
}

/**
 * Float min value
 */
inline static float32_t hyp_fmin(float32_t a, float32_t b)
{
  float32_t res = a;
  if (a > b) {
    res = b;
  }
  return res;
}

/**
 * get absolute value
 */
inline static float32_t hyp_fabs(float32_t val)
{
  return fabsf(val);
}

/**
 * get absolute value
 */
inline static ufd64_t hyp_conj(ufd64_t val64)
{
  ufd64_t res64;
  float32_t *val = (float32_t *) &val64;
  float32_t *res = (float32_t *) &res64;
  *res++ = *val++;
  *res = - (*val);
  return res64;
}

/**
 * Float fneg value
 */
inline static float32_t fneg(float32_t a)
{
  float32_t res = -a;
  return res;
}

/**
 * Float min value
 */
inline static float32_t hyp_fsat(float32_t a, float32_t b)
{
  float32_t res = a;
  res = hyp_fmin(res, b);
  res = hyp_fmax(res, fneg(b));
  return res;
}

/**
 * Float min value
 */
inline static float32_t fsat(float32_t a, ufd64_t val64)
{
  float32_t res = a;
  float32_t min = *((float32_t *) &val64);
  float32_t max = *((float32_t *) &val64);
  res = hyp_fmin(res, min);
  res = hyp_fmax(res, max);
  return res;
}

/**
 * greater less than uint valu
 */
inline static int32_t gtltu(uint32_t a, ufd64_t bram_maxmin)
{
  uint32_t *pVal = (uint32_t *) &bram_maxmin;
  uint32_t min = pVal[0]; // Min
  uint32_t max = pVal[1]; // Max

  uint32_t res = 0;
  if (a < min) {
    res++;
  }
  if (a > max) {
    res++;
  }
  return res;
}
#endif // ARM_COMPILE

/**
 * startcc
 */
inline static void startcc()
{
}

/**
 * stopcc
 */
inline static void stopcc()
{
}

/**
 * getcc
 */
inline static uint32_t getcc()
{
	return 0;
}

#define set_fft_inv()
#define clr_fft_attr()

#ifndef ARM_COMPILE
/**
 * Radix4 digit_reverse from Synopsis.
 */
inline static int digit_reverse(int a, int n)
//  2-bit reversal of "n" LSBs of "a"
//  (for odd powers of 2 the LSB is 1-bit reversed).
{
	int mixed = n & 1; // mixed radix 2/4 for odd powers of 2
	int b = 0;
	if (mixed)
	{
		b |= (a & 1) << (n-1);
	}
	int ml = 3 << mixed;
	int mh = 3 << (n-2);
	int sh = n-2;
	for ( ; sh >= 2; sh -= 4, ml <<=2, mh >>=2)
	{
		b |= (a & ml) << (sh - 2*mixed);
		b |= (a & mh) >> sh;
	}
	if (sh < 2)
	{
		// middle digit when (n-mixed)/2 is odd
		if (sh == 1 || sh == 0) // middle digit when (n-mixed)/2 is odd
			b |= (a & ml) >> mixed;
	}
	//printf("Swap [%d]=%d\n", a, b);
	return b;
}

/**
 * Set FFT attribute
 */
inline static void gcc_set_fft_attr(uint32_t fftAttr, uint32_t fftSize, ufd64_t *dataA)
{
  /* fft_attr
     used by the FFT to control the load operations and bit reverse addressing.
     fft_attr has different fields:
     fft_attr[3:0] contains the log2(Size of the FFT), used for bit reverse addressing mode. Ex: 7 for a FFT 128 points, 8 for a FFT 256. It can support FFT up to 32768 points.
     fft_attr[4] used to compute real FFT (ie : imaginary part of data load from AMEM is overwritten by 0) //lla only
     fft_attr[5] used to compute inverse FFT (ie : imaginary part of data load from AMEM is negate) //lla only
     fft_attr[7:6] :reserved.
     fft_attr[19:8]: used for bit reverse addressing mode to store the address of the current element read.
  */
  uint32_t log2Nbp = fftAttr & 0xf;
  if (fftAttr & 0xf) {
    // Bit reverse activated for radix4
    ufd64_t tmp64[fftSize];
    for (uint32_t i = 0; i < fftSize; i++) {
      tmp64[i] = dataA[i];
    }
    // Do radix 4 bit reverse
    for (uint32_t i = 0; i < fftSize; i++) {
      //printf("inRev[%d] = in[%d]\n", digit_reverse(i, log2_nbp), i);
      dataA[digit_reverse(i, log2Nbp)] = tmp64[i]; // Synopsis digit reverse
      assert(digit_reverse(i, log2Nbp) < fftSize);
    }
  }
  fftAttr |= 0xfff0; // Clear log2Nbp
  if (fftAttr == 0x20) {
    // Inverse FFT: imaginary part of data load from AMEM is negate
    float32_t *dIm = (float32_t *) dataA;
    dIm++; // Point on imaginary part
    for (uint32_t i = 0; i < fftSize; i++) {
      *dIm = -*dIm; // Conjugate
      dIm += 2;
    }
  }
  if (fftAttr == 0x10) {
    // Real input: imaginary part of data load from AMEM is overwritten by 0
    ufd64_t tmp64[fftSize];
    uint32_t *dRe = (uint32_t *) dataA;
    for (uint32_t i = 0; i < fftSize; i++) {
      tmp64[i] = (ufd64_t) dRe[i];
    }
    for (uint32_t i = 0; i < fftSize; i++) {
      dataA[i] = tmp64[i];
    }
  }
}

static inline int get_polysize(void)
{
	return -1;
}

static inline float constantK(int n)
{
	float k=1;
	for (int i=0; i<n; i++) {
		k = k * (1 + exp2(-2*i));
	}
	return sqrt(k);

}

static inline void cordic_quad(float *x, float *y, float *a)
{
	float _x=*x;
	float _y=*y;
	*a= 0.;
	iter_inc = 0;
	if (_x < 0) {
		if (_y < 0) {
			*a = -1.57079632679490;
			_x = -*y;
			_y = *x;
		} else {
			*a = 1.57079632679490;
			_x = *y;
			_y = - *x;
		}
	}
	*x = _x;
	*y = _y;
}

static inline float div_pow2(float x, int pow2)
{
	int e;
	ufi _t;
	_t.f = x;
	e = ((_t.i & 0x7F800000) >> 23);
	// printf("e = %d\n", e);
	if (e > pow2) {
		e = e - pow2;
		_t.i = (_t.i & 0x807FFFFF) | (e << 23);

	} else {
		_t.f = 0.;
	}
	return _t.f;
}

static inline  void atan_cordic_iter(float *x, float *y, float angle_lut, float *angle)
{
	float _x = *x;
	float _y = *y;
	float _a = *angle;
	if (_y > 0.) {
		_a = _a + angle_lut;
		_x = *x + div_pow2(*y , iter_inc);
		_y = *y - div_pow2(*x , iter_inc);
	} else {
		_a = _a - angle_lut;
		_x = *x - div_pow2(*y , iter_inc);
		_y = *y + div_pow2(*x , iter_inc);
	}
	*x = _x;
	*y = _y;
	*angle = _a;
	iter_inc ++;
}

static inline void sf_atan_cordic_iter(float *x, float *y, float angle_lut, float *angle)
{
	ufi _x, _y,_a,_a_l,_x_div_p2, _y_div_p2;
	_x.f = *x;
	_y.f = *y;
	_a.f = *angle;
	_x_div_p2.f = div_pow2(_x.f, iter_inc);
	_y_div_p2.f = div_pow2(_y.f, iter_inc);
	_a_l.f = angle_lut;
	if (_y.f > 0.) {
		_a.f32 = f32_add(_a.f32, _a_l.f32);
		_x.f32 = f32_add(_x.f32, _y_div_p2.f32);
		_y.f32 = f32_sub(_y.f32, _x_div_p2.f32);
	} else {
		_a.f32 = f32_sub(_a.f32, _a_l.f32);
		_x.f32 = f32_sub(_x.f32, _y_div_p2.f32);
		_y.f32 = f32_add(_y.f32, _x_div_p2.f32);
	}
	*x = _x.f;
	*y = _y.f;
	*angle = _a.f;
	iter_inc ++;
}

#ifdef GCC_FFT
inline static void gcc_bitreverse(void *vparam)
{
  hyp_fft_param_t *param = (hyp_fft_param_t *) vparam;
  ufd64_t chess_storage(DMwA) *dataA = param->pSrcA;
  uint32_t nbPoints = param->fftSize;
  uint32_t log2Nbp = param->log2Nbp;
  uint32_t bitrev = param->bitrev;
  if (bitrev) {
    ufd64_t tmp64[nbPoints];
    for (uint32_t i = 0; i < nbPoints; i++) {
      tmp64[i] = dataA[i];
    }
    /* Bit reverse as it is not done in hyperion for the moment */
    for (uint32_t i = 0; i < nbPoints; i++) {
      //printf("inRev[%d] = in[%d]\n", digit_reverse(i, log2Nbp), i);
      dataA[digit_reverse(i, log2Nbp)] = tmp64[i];
    }
  }
}
#endif // GCC_FFT

inline static float32_t hyp_powf( uint32_t power, int32_t x )
{
	int32_t a = x;
	uint32_t res = 0;
	uint32_t inf = 0x7F800000;

	if (a > 127)
	{ //+inf
		//return (0x7F800000);
		return ((float32_t)*((float32_t *)&inf));
	}
	else if (a < -128)
	{ //zero
		return (0.0);
	}
	else
	{
		//res[30:23] = a+127;
		a = ((a + 127) & 0xff) << 23;
		float32_t f = (float32_t)*((float32_t *)&a);
		return (f);
	}
}

#if 0
static inline float32_t poly_horner_simd(float32_t x)
{
	ufd64_t *coeff64 = (ufd64_t *)reverse_coef_horner;
	float32_t initx[2];
	initx[0] = 1.0;
	initx[1] = x;
	ufd64_t * restrict px64 = (ufd64_t*)initx;
	ufd64_t acc64 = vmul(*coeff64++,*px64); // c14 c13.x
	float32_t initx2[2];
	initx2[0] = x * x;
	initx2[1] = x * x;
	ufd64_t *pxpow2 = (ufd64_t*)initx2;
	ufd64_t resmul;
	for (int i = 0; i < 6; i++)
	{
		*px64 = vmul(*px64,*pxpow2);
		acc64 = vmac(acc64, *px64, *coeff64++);
	}
	float32_t acc32 = fred(acc64);
	//printf("acc32=%.10f\n",acc32);
	return acc32;
}
#endif

static inline void extract_and_fix_denorm(uint32_t *aSign_out, uint32_t *aExp_out,uint32_t *aSig_out, uint32_t *denorm, uint32_t a)
{
	uint32_t f;
	uint32_t aSign;
	uint32_t aExp;
	uint32_t aSig;

	aSign = (a & 0x80000000) >> 31; // a[31];
	aExp  = (a & 0x7F800000) >> 23; // a[30:23];
	aSig  = (a & 0x007FFFFF); // a[22:0];

	f = ((aExp == 0) && (aSig != 0));

	if (f)
	{ //Denormal -> 0
		*denorm = 1; //float_flag_denormal
		//FLT_DEBUG_PRINT("Denormal !! op=0x%x ",a);
		aExp = 0;
		aSig = 0;
	}
	else
	{
		*denorm = 0;
	}
	*aSign_out = aSign;
	*aExp_out  = aExp;
	*aSig_out  = aSig;
}

static inline float32_t pre_log(float32_t f)
{
	//uint8 float_exception_flags = 0x00;
    float32_t c;
    uint32_t aSign;
    uint32_t aExp;
    uint32_t aSig;
    uint32_t a_NaN, asNaN, a_zero, a_inf; //special case
    uint32_t sig_diff,sig_diff_dec,not_bSig;
    uint32_t denorma;

	uint32_t a = (uint32_t)*((uint32_t *)&f);

    extract_and_fix_denorm( &aSign, &aExp, &aSig, &denorma, a);

    //float_exception_flags[5] = denorma ;
    //uint32_is_signaling_nan(asNaN,a);
    a_NaN = (aExp == 0xFF && aSig != 0 ? 1 : 0);
    a_inf = (aExp == 0xFF && aSig == 0 ? 1 : 0);
    a_zero = (aExp == 0 && aSig == 0 ? 1 : 0);
    c = 0.0;

    if (aSign && !a_zero)
	{ //negative value -> NaN
		if (asNaN)
		{
			//float_exception_flags[4] = 1; //float_flag_invalid;
		}
		uint32_t uint32_default_nan = 0x7FC00000;
		c = (float32_t)*((float32_t *)&uint32_default_nan);
    }
    if (a_zero)
	{//0 -> -inf
		uint32_t tmp = 0xFF800000;
		c = (float32_t)*((float32_t *)&tmp); //0xFF800000;
    }
    if (a_inf)
	{//+inf
		uint32_t tmp = 0x7F800000;
		c = (float32_t)*((float32_t *)&tmp); //0x7F800000;
    }
    //fpsta_out = float_exception_flags;
    return (c);
}

static inline void gcc_norm_log(float32_t f, float32_t *fexp, float32_t *c)
{

	uint32_t a = (uint32_t)*((uint32_t *)&f);

    uint32_t float_exception_flags = 0x00;
    uint32_t aSign;
    uint32_t aExp;
    uint32_t aSig;
    uint32_t a_NaN, asNaN, a_zero, a_inf; //special case
    uint32_t sig_diff,sig_diff_dec,not_bSig;
    uint32_t denorma;

	uint32_t cuint;
	//float32_t expuint;
	int32_t expuint;

    extract_and_fix_denorm( &aSign, &aExp, &aSig, &denorma, a);

	//float_exception_flags[5] = denorma ;

	//c[22:0]= aSig[22:0];
    //c[30:23]= aExp;
    //c[31]= aSign;

	cuint = aSig & 0x007FFFFF;
	cuint = cuint | (aExp << 23);
	cuint = cuint | (aSign << 31);

    //bool greater = aSig[22]; // mantissa greater than 1.5 irrespective of the exponent;
    uint32_t greater = (aSig >> 22)&1; // mantissa greater than 1.5 irrespective of the exponent;
    if (greater)
	{
		//c[30:23] = 126; // force exp to be 126, that is 2^-1, which realises the division by 2
		cuint = (cuint & ~0x7F800000)  | (126 << 23);
		expuint = aExp - 126;
    }
	else
	{ // mantissa is between 1. to 1.5
		//c[30:23] = 127; // force exp to be 127, that us 1
		cuint =  (cuint & ~0x7F800000) | (127 << 23); // force exp to be 127, that us 1
		//float32_t *p = (float32_t *)&aExp;
		expuint = aExp - 127;
	}
	*c = (float32_t)*((float32_t *)&cuint);
	*fexp = (float32_t)expuint;
}
#endif // ARM_COMPILE

static inline ufd64_t s_store_swap(ufd64_t src)
{
	float32_t rhl[2];
	ufd64_t *p = (ufd64_t *)rhl;

 //   printf("xtract_high(src)=0x%08x extract_low(src)=0x%08x\n",extract_high(src),extract_low(src));
	rhl[0] = extract_high(src);
	rhl[1] = extract_low(src);

	return *p;
}

static inline ufd64_t s_vmac_swap(ufd64_t acc, ufd64_t a, ufd64_t b)
{
	float32_t rhl[2];
	ufd64_t *p = (ufd64_t *)rhl;

    float32_t acclo = extract_low(acc);  // acc[31:0];
    float32_t acchi = extract_high(acc); // acc[63:32];
    float32_t alo   = extract_low(a);    // a[31:0];
    float32_t ahi   = extract_high(a);   // a[63:32];
    float32_t blo   = extract_low(b);    // b[31:0];
    float32_t bhi   = extract_high(b);   // b[63:32];
    float32_t mlo   = alo * bhi;         // fmul(alo,bhi);
    float32_t mhi   = ahi * blo;         // fmul(ahi,blo);

    rhl[0]  = acclo + mlo;   // malo = faddsub(_FADD_,acclo,mlo);
    rhl[1]  = acchi + mhi;   // mahi = faddsub(_FADD_,acchi,mhi);
//    return mahi::malo;

	return *p;
}

//CMUL_M:
//Zr = (mcoeffi * Xr) + (mcoeffr * Xi)
//Zi =(mcoeffr * Xr) - (mcoeffi * Xi)
//z.l = x.h * y.l + x.l * y.h
//z.h = x.l * y.l - x.h * y.h
static inline ufd64_t CMULM(ufd64_t coeff, ufd64_t x)
{
	float32_t tmp[2];
	ufd64_t *res = (ufd64_t *)tmp;

	tmp[0] = (extract_high(coeff) * extract_low(x)) + (extract_low(coeff) * extract_high(x));
	tmp[1] = (extract_low(coeff) * extract_low(x)) - (extract_high(coeff) * extract_high(x));
	return(*res);
}

//CMUL_M:
//Zr = (mcoeffi * Xr) + (mcoeffr * Xi)
//Zi =(mcoeffr * Xr) - (mcoeffi * Xi)
//z.l = x.h * y.l + x.l * y.h
//z.h = x.h * y.h - x.l * y.l
static inline ufd64_t CMULMBIS(ufd64_t coeff, ufd64_t x)
{
	float32_t tmp[2];
	ufd64_t *res = (ufd64_t *)tmp;

	tmp[0] = (extract_high(coeff) * extract_low(x)) + (extract_low(coeff) * extract_high(x));
	tmp[1] = (extract_high(coeff) * extract_high(x)) - (extract_low(coeff) * extract_low(x));
	return(*res);
}


#endif // __HYP_TYPES_GCC_H__
