/**
  ******************************************************************************************
  * \file hsp_test_common.c
  * \brief Common functions for unitary tests
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
  * <h2><center>&copy; COPYRIGHT 2019 STMicroelectronics - All Rights Reserved</center></h2>
  *
  ******************************************************************************************
  */

#ifndef __HSP_TEST_COMMON_C__
#define __HSP_TEST_COMMON_C__

/*------------------------------------------------------------------------------
 * Includes
 *----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#ifndef ARM_COMPILE
#ifndef __GNUC__
#include "hyp_malloc.h"
#else // __GNUC__
#include "malloc.h"
#endif // __GNUC__
#endif // ARM_COMPILE
#include "hsp_test_common.h"
#ifndef HYP_UNITARY_TEST
#ifndef GCC_COMPILE
#include "hsp_reg_map.h"
#endif // GCC_COMPILE
#endif // HYP_UNITARY_TEST

//#define LOAD_BY_TEST_COMMON
#ifdef LOAD_BY_TEST_COMMON
#ifdef ARM_COMPILE
#include "generated_hsp_CRAM.c"
#include "generated_hsp_DRAM.c"
#ifdef ARM_LOAD_BRAM
#include "generated_hsp_BRAM.c"
#endif // ARM_LOAD_BRAM
#endif // ARM_COMPILE
#endif

#ifndef ARM_COMPILE
#include "hsp_fw_def.h"
#else
#include "hsp_fw_def_generic.h"
#endif
#ifndef HYP_UNITARY_TEST
// #include "hsp_ll.h"
#endif // HYP_UNITARY_TEST

#ifdef HYPSA_SIMU
#include "hyp_cnn.h"
#endif // HYPSA_SIMU

/*------------------------------------------------------------------------------
 * Defines
 *----------------------------------------------------------------------------*/
#ifdef __GNUC__
#define hyp_malloc malloc
#define hyp_free free
#endif // __GNUC__

// To save output in compare_float
//#define WRITE_OUTPUT

#ifdef ARM_COMPILE
/* Systick Start */
#define cTimerCount_Start() do {                             \
	SysTick->LOAD = 0xFFFFFF ;  /* Set reload register */   \
	SysTick->VAL = 0 ;          /* Clear Counter */         \
	SysTick->CTRL = 0x5 ;       /* Enable Counting*/        \
	} while(0)

/* Systick Stop and retrieve CPU Clocks count */
#define cTimerCount_Stop(Value) do {                                     \
	SysTick->CTRL = 0;           /* Disable Counting */                              \
	Value = SysTick->VAL;       /* Load the SysTick Counter Value */    \
	Value = 0xFFFFFF - Value;   /* Capture Counts in CPU Cycles*/       \
} while(0)

#endif
/*------------------------------------------------------------------------------
 * Types
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 * Variables
 *----------------------------------------------------------------------------*/

/// Destination buffer used by all tests
#ifdef ARM_COMPILE

// Need to define chess_storage
#define chess_storage(a)

// Here describe HSP memory map for ARM access in FPGA
#define HSP_BRAM_AB_BASE_ADDR (HYPSA_SHARED_MEM_BASE_ADDR)

#ifdef STM32U3C5xx
#define HSP_CRAM_BASE_ADDR  (HSP_ARM_MEMORY_BASE_ADDR)
#define HSP_DRAM_BASE_ADDR ((HSP_ARM_MEMORY_BASE_ADDR) + (HSP_MEM_CRAM_SIZE<<10))
#define HSP_CYCLE_COUNT_ADDR (HSP_BASE_DRAM_MEM + HSP_DRAM_CC_ADDR) ///< Temporary HSP internal CC address
#endif
#ifdef STM32U575xx
#define HSP_CRAM_BASE_ADDR ((HSP1_BASE_NS) + (HSP_ARM_MEMORY_BASE_ADDR))
#define HSP_DRAM_BASE_ADDR ((HSP1_BASE_NS) + (HSP_ARM_MEMORY_BASE_ADDR) + (HSP_MEM_CRAM_SIZE<<10))
#define HSP_CYCLE_COUNT_ADDR (HSP1_BASE_NS + HSP_BASE_DRAM_MEM + HSP_DRAM_CC_ADDR) ///< Temporary HSP internal CC address
#endif
#ifdef STM32H7P5xx
#define HSP_CRAM_BASE_ADDR  (HSP_ARM_MEMORY_BASE_ADDR)
#define HSP_DRAM_BASE_ADDR ((HSP_ARM_MEMORY_BASE_ADDR) + (HSP_MEM_CRAM_SIZE<<10))
#define HSP_CYCLE_COUNT_ADDR (HSP_BASE_DRAM_MEM + HSP_DRAM_CC_ADDR) ///< Temporary HSP internal CC address
#endif

//#pragma location = HYPSA_TEST_DST_ADDR
float32_t hspTestDst4096[8192];
float32_t hspTestDstExt4096[4096];
// Used for end of test synchronization
extern volatile uint32_t hsp_it_evt;
extern volatile uint32_t hsp_it_gbl;

#else // ARM_COMPILE
#define HSP_DRAM_BASE_ADDR 0
#define HSP_BRAM_AB_BASE_ADDR 0x40000
float32_t chess_storage(hypDM:HYPSA_TEST_DST_ADDR) hspTestDst4096[8192];
// Used for calling scheduler in hypsa platform
void hypsa_extra_fct();
void hypsa_send_evt(uint32_t evt);
#endif // ARM_COMPILE
void hsp_startcc(void);
uint32_t hyp_get_cc(void);
/// Use to test error counter report
uint32_t _errorReportCount = 0;

/// Return internal measure from last lib function called
#ifdef ARM_COMPILE
#pragma location = HSP_CYCLE_COUNT_ADDR
volatile cycleu_t hspInternalMeasure; // = 0: removed for beta4
cycleu_t _armMeasure = 0;
#else // ARM_COMPILE
volatile cycleu_t chess_storage(hypDM:HYP_CYCLE_COUNT_ADDR) hypInternalMeasure = 0;
cycleu_t _armMeasure = 0;
#endif // ARM_COMPILE

/// Start cycle for perf
cycleu_t _startCycles;

/// Print internal measure in lib function
int32_t _doPrint = 1;

/// Mailbox status for test return value
#ifndef GCC_COMPILE
#ifdef ARM_COMPILE
// A revoir avec Val, comment on fait pour la HAL? peut on partager le handler en FPGA et en hypsa qui sera definit tantot comme hsp_reg tantot comme le handler HSP HAL?
uint32_t *_mbStatus = ((uint32_t *) HSP_H2CMSGDR_ADDR);
#else // ARM_COMPILE

//#define _mbStatus = hsp_reg.SPE_H2CMSGDR;

#ifdef HYP_UNITARY_TEST
uint32_t blablambStatus;
uint32_t *_mbStatus = &blablambStatus;
#else // HYP_UNITARY_TEST
uint32_t *_mbStatus = (uint32_t *) (&hsp_reg.SPE_H2CMSGDR);
#endif// HYP_UNITARY_TEST

#endif // ARM_COMPILE
#endif // GCC_COMPILE

#ifdef __GNUC__
ufd64_t chess_storage(hypDMB) fftDataB[4096];
#endif // __GNUC__


/*------------------------------------------------------------------------------
 * Functions
 *----------------------------------------------------------------------------*/

/**
 * Compare data table with ref and print maximun difference
 * data Input vector
 * ref Reference vector to compare
 * size Number of elements to compare
 * noPrintPassed Flag to not print when PASSED
 * return number of check failed
 */
uint32_t compare_max_diff_float(const char *testName, float32_t *data, float32_t *ref, uint32_t size,
                                uint16_t noPrintPassed)
{
    if (_errorReportCount) {
      // Error detected, do not compare but return error status
      TEST_INFO_REPORT(testName, "ERROR: compare_max_diff_float _errorReportCount (=HSP status) 0x%x\n",
                       _errorReportCount);
      return _errorReportCount;
    }
	float32_t maxDiff = 0.0;
	assert(data);
	assert(ref);
	//  assert(size);
	uint32_t nbCheckFailed = _errorReportCount;
	uint32_t nbErr1 = 0;
	uint32_t nbErrN = 0; // Res nan != Exp -nan
	uint32_t nbErrZ = 0; // Res nan != Exp -nan
	int imaxdiff = -1;

	for (uint32_t idx = 0; idx < size; idx++)
	{
		uint32_t *pdata = (uint32_t *) &data[idx];
		uint32_t *pref = (uint32_t *) &ref[idx];
		if (*pdata != *pref)
		{
			if ((*pdata == (*pref + 0x1)) || (*pref == (*pdata + 0x1)))
			{
				nbErr1++;
			}
			else
			{
				if ((*pdata == 0x7fc00000) && (*pref == 0xffc00000))
				{
					nbErrN++;
				}
				else
				{
					if ((*pdata == 0x00000000) && (*pref == 0x80000000))
					{
						nbErrZ++;
					}
					else
					{
						float32_t diff = 0.0;
						//if (ref[idx] > data[idx])
						if (*pref > *pdata)
						{
							//diff = ref[idx] - data[idx];
							diff = ref[idx] - data[idx];
						}
						else
						{
							diff = data[idx] - ref[idx];
						}

						if (diff < 0)
						{
							diff = -diff;
						}
						if (diff > maxDiff)
						{
							maxDiff = diff;
							imaxdiff = idx;
						}
                        if (nbCheckFailed < 10) {
                          printf("ERROR at[%3d]: Res %.52f != Exp %.52f (0x%08x 0x%08x)\n",
                                 idx, data[idx], ref[idx],	*pdata, *pref);
                        }
						nbCheckFailed++;
					}
				}
			}
		}
	}
	if (nbErr1)
	{
		TEST_INFO_REPORT(testName, "ERROR: nb check1: %d\n", nbErr1);
	}
	if (nbErrN)
	{
		TEST_INFO_REPORT(testName, "ERROR: nb check Res nan != Exp -nan: %d\n", nbErrN);
	}
	if (nbErrZ)
	{
		TEST_INFO_REPORT(testName, "ERROR: nb check Res 0 != Exp -0: %d\n", nbErrZ);
	}
	if (nbCheckFailed == 0)
	{
      if (noPrintPassed == 0) {
        TEST_INFO_REPORT(testName, "\tPASSED\n");
      }
	}
	else
	{
		uint32_t *pmax = (uint32_t *) &maxDiff;
		TEST_INFO_REPORT(testName, "Max difference %.8f (0x%08x) @[%d]=%.10f\n", maxDiff, *pmax,imaxdiff,data[imaxdiff]);
		TEST_INFO_REPORT(testName, "ERROR: nb check %d\n", nbCheckFailed);
	}
#ifdef WRITE_OUTPUT
	// generate output file for SNR calculation
	write_file32("output_test_data.fx", size, (uint32_t *)data);
	write_file32("output_test_ref.fx", size, (uint32_t *)ref);
#endif
	return nbCheckFailed;
}

/**
 * Compare data table with ref
 * data Input vector
 * ref Reference vector to compare
 * size Number of elements to compare
 * noPrintPassed Flag to not print when PASSED
 * return number of check failed
 */
uint32_t compare_float(const char *testName, float32_t *data, float32_t *ref, uint32_t size, uint16_t noPrintPassed)
{
  if (_errorReportCount) {
    // Error detected, do not compare but return error status
    TEST_INFO_REPORT(testName, "ERROR: compare_float _errorReportCount (=HSP status) 0x%x\n", _errorReportCount);
    return _errorReportCount;
  }
  if (data == NULL) {
    TEST_INFO_REPORT(testName, "ERROR: compare_float NULL data ptr\n");
    return 1;
  }
  if (ref == NULL) {
    TEST_INFO_REPORT(testName, "ERROR: compare_float NULL ref ptr\n");
    return 1;
  }
  //  assert(size);
  uint32_t nbCheckFailed = _errorReportCount;
  uint32_t nbErr1 = 0;
  uint32_t nbErrN = 0; // Res nan != Exp -nan
  uint32_t nbErrZ = 0; // Res 0 != Exp -0

  for (uint32_t idx = 0; idx < size; idx++) {
    uint32_t *pdata = (uint32_t *) &data[idx];
    uint32_t *pref = (uint32_t *) &ref[idx];
    if (*pdata != *pref) {
      if ((*pdata == (*pref + 0x1)) || (*pref == (*pdata + 0x1))) {
        nbErr1++;
      } else if ((*pdata == 0x7fc00000) && (*pref == 0xffc00000)) {
        nbErrN++;
      } else if ((*pdata == 0x00000000) && (*pref == 0x80000000)) {
        nbErrZ++;
      } else {
        if (nbCheckFailed < 10) {
          printf("ERROR at[%3d]: Res %.52f != Exp %.52f (0x%08x 0x%08x)\n", idx, data[idx], ref[idx],
                 *pdata, *pref);
        }
        nbCheckFailed++;
      }
    }
  }
  if (nbErr1) {
    TEST_INFO_REPORT(testName, "ERROR: nb check1: %d\n", nbErr1);
  }
  if (nbErrZ) {
    TEST_INFO_REPORT(testName, "ERROR: nb check Res 0 != Exp -0: %d\n", nbErrZ);
  }
  if (nbErrN) {
    TEST_INFO_REPORT(testName, "ERROR: nb check Res nan != Exp -nan: %d\n", nbErrN);
  }
  if (nbCheckFailed == 0) {
    if (noPrintPassed == 0) {
      TEST_INFO_REPORT(testName, "\tPASSED\n");
    }
  } else {
    TEST_INFO_REPORT(testName, "ERROR: nb check %d\n", nbCheckFailed);
  }
#ifdef WRITE_OUTPUT
  // generate output file for SNR calculation
  write_file32("output_test_data.fx", size, (uint32_t *) data);
  write_file32("output_test_ref.fx", size, (uint32_t *) ref);
#endif

  return nbCheckFailed;
}

/**
 * Compare data table with ref
 * data Input vector
 * ref Reference vector to compare
 * size Number of elements to compare
 * noCompare Flag to no compare data and ref but check _errorReportCount was set by Hyperion
 * return number of check failed
 */
uint32_t compare_int32(const char *testName, uint32_t *data, uint32_t *ref, uint32_t size, uint16_t error)
{
  if (_errorReportCount) {
    // Error detected, do not compare but return error status
    TEST_INFO_REPORT(testName, "ERROR: compare_int32 _errorReportCount (=HSP status) 0x%x\n", _errorReportCount);
    return _errorReportCount;
  }
  assert(data);
  assert(ref);
  //  assert(size);
  uint32_t nbCheckFailed = _errorReportCount;
  uint32_t maxDiff = 0;
  uint32_t nbErr1 = 0;
  for (uint16_t idx = 0; idx < size; idx++) {
    if (data[idx] != ref[idx]) {
      uint32_t diff = 0;
      if ((data[idx] == (ref[idx] + error)) || (ref[idx] == (data[idx] + error))) {
        nbErr1++;
      } else {
        if (ref[idx] > data[idx]) {
          diff = ref[idx] - data[idx];
        } else {
          diff = data[idx] - ref[idx];
        }
        if (diff > maxDiff) {
          maxDiff = diff;
        }
        printf("ERROR at[%3d]: Res 0x%08x != Exp 0x%08x\n", idx, data[idx], ref[idx]);
        nbCheckFailed++;
      }
    }
  }
  if (nbErr1) {
    TEST_INFO_REPORT(testName, "ERROR: nb check1: %d\n", nbErr1);
  }
  if (nbCheckFailed == 0) {
    TEST_INFO_REPORT(testName, "\tPASSED\n");
  } else {
    TEST_INFO_REPORT(testName, "ERROR: nb check %d\n", nbCheckFailed);
    uint32_t *maxDiff32 = (uint32_t *) &maxDiff;
    TEST_INFO_REPORT(testName, "Max difference %d (0x%08x)\n", *maxDiff32, *maxDiff32);
  }
  return nbCheckFailed;
}

/**
 * Compare data table with ref
 * data Input vector
 * ref Reference vector to compare
 * size Number of elements to compare
 * noCompare Flag to no compare data and ref but check _errorReportCount was set by Hyperion
 * return number of check failed
 */
uint32_t compare_int8(const char *testName, uint8_t *data, uint8_t *ref, uint32_t size, uint16_t noCompare)
{
/*   if (noCompare) { */
/*     TEST_INFO_REPORT(testName, "No compare, rturn _errorReportCount %d\n", */
/*                      _errorReportCount); */
/*     return _errorReportCount; */
/*   } */
  if (_errorReportCount) {
    // Error detected, do not compare but return error status
    TEST_INFO_REPORT(testName, "ERROR: compare_int8 _errorReportCount (=HSP status) 0x%x\n", _errorReportCount);
    return _errorReportCount;
  }
  assert(data);
  assert(ref);
  //  assert(size);
  uint32_t nbCheckFailed = _errorReportCount;
  int8_t maxDiff = 0;
  for (uint16_t idx = 0; idx < size; idx++) {
    if (data[idx] != ref[idx]) {
      int8_t diff = 0;
      if (ref[idx] > data[idx]) {
        diff = ref[idx] - data[idx];
      } else {
        diff = data[idx] - ref[idx];
      }
      if (diff > maxDiff) {
        maxDiff = diff;
      }
     if (noCompare != P60_CHECK_DO_CMP) {
        if (nbCheckFailed < 16) {
          printf("ERROR at[%3d]: Res 0x%02x != Exp 0x%02x\n", idx, data[idx], ref[idx]);
        }
      } else {
        if (nbCheckFailed < 16) {
        //if (nbCheckFailed < 130) {
        printf("ERROR at[%3d]: Res 0x%02x != Exp 0x%02x\n", idx, data[idx], ref[idx]);
      }
      }
      nbCheckFailed++;
    }
  }
  if (nbCheckFailed == 0) {
    TEST_INFO_REPORT(testName, "\tPASSED\n");
  } else {
    TEST_INFO_REPORT(testName, "ERROR: nb check %d\n", nbCheckFailed);
    TEST_INFO_REPORT(testName, "Max difference %d (0x%02x)\n", maxDiff, maxDiff);
  }
  return nbCheckFailed;
}

/**
 * Compare data table with ref
 * eltInFormat Input vector
 * eltOuFormat Output vector
 * data Input vector
 * ref Reference vector to compare
 * size Number of elements to compare
 * return number of check failed
 */
void conv_vect_type(uint8_t eltInFormat, uint8_t dmaI2f, uint32_t *pIn, uint32_t *pOu, uint32_t size)
{
#ifdef __HSP_DMA__	
  uint32_t resIssigned = 0;
  if (eltInFormat == HSP_DMA_ELT_FMT_U16) {
    uint16_t *pSrc = (uint16_t *) pIn;
    uint32_t *pDst = pOu;
    for (uint32_t idx = 0; idx < size; idx++) {
      *pDst++ = (uint32_t) *pSrc++;
    }
  } else if (eltInFormat == HSP_DMA_ELT_FMT_S16) {
    resIssigned = 1;
    int16_t *pSrc = (int16_t *) pIn;
    int32_t *pDst = (int32_t *) pOu;
    for (uint32_t idx = 0; idx < size; idx++) {
      *pDst++ = (int32_t) *pSrc++;
    }
  } else {
    if (eltInFormat == HSP_DMA_ELT_FMT_32B) {
      resIssigned = 1;
    }
    uint32_t *pSrc = (uint32_t *) pIn;
    uint32_t *pDst = (uint32_t *) pOu;
    for (uint32_t idx = 0; idx < size; idx++) {
      *pDst++ = (uint32_t) *pSrc++;
    }
  }
#ifdef DEPRECATED_I2F_CONV
  if (dmaI2f == HSP_DMA_ELT_FMT_I2F) {
    if (resIssigned) {
      // Use signed translation
      int32_t *pSrc32 = (int32_t *) pOu;
      float32_t *pDst = (float32_t *) pOu;
      for (uint32_t idx = 0; idx < size; idx++) {
        float32_t tmpf = (float32_t) pSrc32[idx];
        *pDst++ = tmpf;
      }
    } else {
      float32_t *pDst = (float32_t *) pOu;
      for (uint32_t idx = 0; idx < size; idx++) {
        float32_t tmpf = (float32_t) pOu[idx];
        *pDst++ = tmpf;
      }
    }
  }
#endif // DEPRECATED_I2F_CONV
#endif  // __HSP_DMA__

}

/**
 * Compare data table with ref
 * eltInFormat Input vector
 * eltOuFormat Output vector
 * data Input vector
 * ref Reference vector to compare
 * size Number of elements to compare
 * return number of check failed
 */
void conv_vect_type_jmp(uint8_t eltInFormat, uint8_t dmaI2f, uint8_t *pIn, uint32_t *pOu, uint32_t size,
                        uint8_t iJump, uint8_t oJump)
{
#ifdef __HSP_DMA__
  uint32_t sign = 0;
  iJump++;
/*   if (oJump == 0) { */
/*     oJump++; */
/*   } */
  if (eltInFormat == HSP_DMA_ELT_FMT_U16) {
    uint16_t *pSrc = (uint16_t *) pIn;
    uint32_t *pDst = pOu;
    for (uint32_t idx = 0; idx < size; idx++) {
      *pDst = (uint32_t) *pSrc;
      pSrc += iJump;
      pDst++;
    }
  } else if (eltInFormat == HSP_DMA_ELT_FMT_S16) {
    sign = 1;
    int16_t *pSrc = (int16_t *) pIn;
    int32_t *pDst = (int32_t *) pOu;
    for (uint32_t idx = 0; idx < size; idx++) {
      *pDst = (int32_t) *pSrc;
      pSrc += iJump;
      pDst++;
    }
  } else if (eltInFormat == HSP_DMA_ELT_FMT_64B) {
    uint32_t *pSrc = (uint32_t *) pIn;
    uint32_t *pDst = (uint32_t *) pOu;
    iJump--;
    iJump = iJump*2;
    for (uint32_t idx = 0; idx < size; idx++) {
      *pDst++ = (uint32_t) *pSrc++;
      *pDst = (uint32_t) *pSrc++;
      pSrc += iJump;
      pDst++;
    }
  } else {
    uint32_t *pSrc = (uint32_t *) pIn;
    uint32_t *pDst = (uint32_t *) pOu;
    for (uint32_t idx = 0; idx < size; idx++) {
      *pDst = (uint32_t) *pSrc;
      pSrc += iJump;
      pDst++;
    }
  }
#ifdef DEPRECATED_I2F_CONV
  if (eltInFormat == HSP_DMA_ELT_FMT_S32) {
    sign = 1;
  }
  if (dmaI2f == HSP_DMA_ELT_FMT_I2F) {
    if (sign) {
      int32_t *pOus = (int32_t *) pOu;
      float32_t *pDst = (float32_t *) pOus;
      for (uint32_t idx = 0; idx < size; idx++) {
        float32_t tmpf = (float32_t) pOus[idx];
        *pDst++ = tmpf;
      }
    } else {
      float32_t *pDst = (float32_t *) pOu;
      for (uint32_t idx = 0; idx < size; idx++) {
        float32_t tmpf = (float32_t) pOu[idx];
        *pDst++ = tmpf;
      }
    }
  }
#endif // DEPRECATED_I2F_CONV
#endif  // __HSP_DMA__
}


/**
 * Compare data table with ref
 * eltOuFormat Output vector format
 * data Output vector
 * size Number of elements to compare
 */
void conv_vectf_type(uint8_t eltOuFormat, uint8_t dmaI2f, uint8_t *pIn, uint32_t *pOu, uint32_t size,
                     uint8_t iJump)
{
#ifdef __HSP_DMA__
  iJump++;
  // First do jump in output buffer
  uint32_t *pDataI = (uint32_t *) pIn;
  uint32_t *pDataO = (uint32_t *) pOu;
  if (eltOuFormat == HSP_DMA_ELT_FMT_64B) {
    iJump--;
    for (uint32_t tmpi = 0; tmpi < (size >> 1); tmpi++) {
      *pDataO++ = *pDataI++;
      *pDataO++ = *pDataI++;
      pDataI += (2*iJump);
    }
  } else {
    for (uint32_t tmpi = 0; tmpi < size; tmpi++) {
      *pDataO++ = *pDataI;
      pDataI += iJump;
    }
  }
  // Then do integer conversion
#ifdef DEPRECATED_I2F_CONV
  if (dmaI2f == HSP_DMA_ELT_FMT_I2F) {
    uint32_t sign = 0;
    if (eltOuFormat == HSP_DMA_ELT_FMT_S16) {
      sign = 1;
    }
    if (eltOuFormat == HSP_DMA_ELT_FMT_S32) {
      sign = 1;
    }
    float32_t *pInf = (float32_t *) pOu;
    if (sign) {
      int32_t *pDst = (int32_t *) pOu;
      for (uint32_t idx = 0; idx < size; idx++) {
        int32_t tmpf = (int32_t) pInf[idx];
        *pDst++ = tmpf;
      }
    } else {
      uint32_t *pDst = (uint32_t *) pOu;
      for (uint32_t idx = 0; idx < size; idx++) {
        uint32_t tmpf = (uint32_t) pInf[idx];
        *pDst++ = tmpf;
      }
    }
  }
#endif // DEPRECATED_I2F_CONV

  // And finaly update type for 16-bits
  if (eltOuFormat == HSP_DMA_ELT_FMT_U16) {
    uint32_t *pSrc = (uint32_t *) pOu;
    uint32_t *pDst = (uint32_t *) pOu;
    for (uint32_t idx = 0; idx < size; idx++) {
      *pDst = *pSrc & 0xffff;
      pSrc++;
      pDst++;
    }
  } else if (eltOuFormat == HSP_DMA_ELT_FMT_S16) {
    int32_t *pSrc = (int32_t *) pOu;
    int32_t *pDst = (int32_t *) pOu;
    for (uint32_t idx = 0; idx < size; idx++) {
      *pDst = *pSrc >> 16;
      pSrc++;
      pDst++;
    }
  /* if (eltOuFormat == HSP_DMA_ELT_FMT_U16) { */
  /*   uint32_t *pSrc = (uint32_t *) pOu; */
  /*   uint32_t *pDst = (uint32_t *) pOu; */
  /*   for (uint32_t idx = 0; idx < size; idx++) { */
  /*     uint16_t tmp16 = (uint16_t) *pSrc; */
  /*     *pDst = (uint32_t) tmp16; */
  /*     pSrc++; */
  /*     pDst++; */
  /*   } */
  /* } else if (eltOuFormat == HSP_DMA_ELT_FMT_S16) { */
  /*   int32_t *pSrc = (int32_t *) pOu; */
  /*   int32_t *pDst = (int32_t *) pOu; */
  /*   for (uint32_t idx = 0; idx < size; idx++) { */
  /*     int16_t tmp16 = (int16_t) *pSrc; */
  /*     *pDst = (int32_t) tmp16; */
  /*     pSrc++; */
  /*     pDst++; */
  /*   } */
/*   } else if (eltOuFormat == HSP_DMA_ELT_FMT_64B) { */
/*     uint32_t *pSrc = (uint32_t *) pOu; */
/*     uint32_t *pDst = (uint32_t *) pOu; */
/*     for (uint32_t idx = 0; idx < size; idx++) { */
/*       *pDst++ = (uint32_t) *pSrc++; */
/*       *pDst = (uint32_t) *pSrc++; */
/*       pSrc++; */
/*       pDst++; */
/*     } */
/*   } else { */
/*     uint32_t *pSrc = (uint32_t *) pOu; */
/*     uint32_t *pDst = (uint32_t *) pOu; */
/*     for (uint32_t idx = 0; idx < size; idx++) { */
/*       *pDst = (uint32_t) *pSrc; */
/*       pSrc++; */
/*       pDst++; */
/*     } */
  }
#endif  // __HSP_DMA__
}

/**
 * Compare data table with ref
 * eltOuFormat Output vector
 * data Input vector
 * ref Reference vector to compare
 * size Number of elements to compare
 * return number of check failed
 */
void conv_vectf_type_jmp(uint8_t eltOuFormat, uint8_t dmaI2f, uint8_t *pIn, uint32_t *pOu, uint32_t size,
                         uint8_t oJump)
{
#ifdef __HSP_DMA__
  oJump++;

  if (eltOuFormat == HSP_DMA_ELT_FMT_U16) {
    uint16_t *pSrc = (uint16_t *) pIn;
    uint32_t *pDst = (uint32_t *) pOu;
    for (uint32_t idx = 0; idx < size; idx++) {
      *pDst = (uint32_t) *pSrc;
      pSrc += oJump;
      pDst++;
    }
  } else if (eltOuFormat == HSP_DMA_ELT_FMT_S16) {
    int16_t *pSrc = (int16_t *) pIn;
    int32_t *pDst = (int32_t *) pOu;
    for (uint32_t idx = 0; idx < size; idx++) {
      *pDst = (int32_t) *pSrc;
      pSrc += oJump;
      pDst++;
    }
  } else if (eltOuFormat == HSP_DMA_ELT_FMT_64B) {
    uint32_t *pSrc = (uint32_t *) pIn;
    uint32_t *pDst = (uint32_t *) pOu;
    oJump--;
    oJump = oJump*2;
    for (uint32_t idx = 0; idx < size; idx++) {
      *pDst++ = (uint32_t) *pSrc++;
      *pDst = (uint32_t) *pSrc++;
      pSrc += oJump;
      pDst++;
    }
  } else {
    uint32_t *pSrc = (uint32_t *) pIn;
    uint32_t *pDst = (uint32_t *) pOu;
    for (uint32_t idx = 0; idx < size; idx++) {
      *pDst = (uint32_t) *pSrc;
      pSrc += oJump;
      pDst++;
    }
  }
#endif  // __HSP_DMA__
}

/**
 * Read input file fileName, get uint32_t data in asccii hexa format
 * nbElem is number of element read in file
 */
void read_input32(const char *fileName, uint32_t nbElem, uint32_t *data)
{
  printf("Read %d inputs\n", nbElem);
  FILE *fin;
  fin = fopen(fileName, "r");
  if (fin == NULL) {
    printf("read_input32: Failed to open file %s\n", fileName);
  }
  assert(fin);
  printf("Read file %s\n", fileName);
  uint32_t resPtr;
  for (uint32_t idx = 0; idx < nbElem; idx++) {
    fscanf(fin, "%x", &resPtr);
    data[idx] = resPtr;
  }
  fclose(fin);
}

/**
 * Read input file fileName, get uint32_t data in asccii hexa format
 * nbElem is number of element read in file
 */
uint32_t read_input_file32(const char *fileName, uint32_t *data)
{
  uint32_t nbElem = 0;
  FILE *fin;
  fin = fopen(fileName, "r");
  if (fin == NULL) {
    printf("read_input_file32: Failed to open file %s\n", fileName);
  }
  assert(fin);
  printf("Read file %s\n", fileName);
  uint32_t resPtr;
  while (fscanf(fin, "%x", &resPtr) != EOF) {
    *data++ = resPtr;
    nbElem++;
  }
  fclose(fin);
  printf("Read %d inputs\n", nbElem);
  return nbElem;
}

#ifndef ARM_COMPILE
/**
 * Read matrix from file fileName, get uint32_t data in asccii hexa format
 */
void get_matrix_file32(const char *fileName, p60_matrix_t *mat)
{
  uint32_t nbElem = 0;
  FILE *fin;
  fin = fopen(fileName, "r");
  if (fin == NULL) {
    printf("read_input_file32: Failed to open file %s\n", fileName);
  }
  assert(fin);
  printf("Read file %s\n", fileName);
  uint32_t resPtr;
  // Get width
  fscanf(fin, "%x", &resPtr);
  mat->nCols = resPtr;
  // Get height
  fscanf(fin, "%x", &resPtr);
  mat->nRows = resPtr;
  printf("Read matrix %dx%d\n", mat->nCols, mat->nRows);
  uint32_t numSamples = mat->nCols * mat->nRows;
  mat->addr = (float32_t *) hyp_malloc(sizeof(float32_t *) * numSamples);
  ASSERT(mat->addr);
  uint32_t *ptmp32 = (uint32_t *) mat->addr;
  while (fscanf(fin, "%x", &resPtr) != EOF) {
    nbElem++;
    ASSERT(nbElem > numSamples);
    *ptmp32++ = resPtr;
  }
  fclose(fin);
}
#endif // ARM_COMPILE

/**
 * Write data in file fileName in asccii hexa format
 * nbElem is number of element write in file
 */
void write_file32(const char *fileName, uint32_t nbElem, uint32_t *data)
{
  FILE *fou;
  fou = fopen(fileName, "w");
  if (fou == NULL) {
    printf("write_file32: Failed to open file %s\n", fileName);
  }
  assert(fou);
  printf("Write file %s\n", fileName);
  for (uint32_t idx = 0; idx < nbElem; idx++) {
    fprintf(fou, "0x%08x\n", (uint32_t) data[idx]);
  }
  fclose(fou);
}

/**
 * Write data in file fileName in asccii hexa format
 * nbElem is number of element write in file
 */
void write_cfile32(const char *fileName, uint32_t nbElem, uint32_t *data)
{
  FILE *fou;
  char p[32];
  char *tmpName = p;
  strncpy(tmpName, fileName, 32);
  tmpName = strcat(tmpName, ".c");
  fou = fopen(tmpName, "w");
  if (fou == NULL) {
    printf("write_file32: Failed to open file %s\n", tmpName);
  }
  assert(fou);
  printf("Write file %s\n", tmpName);
  fprintf(fou, "// Generated reference file %s\n\n", tmpName);
  fprintf(fou, "uint32_t res[%d] = {", nbElem);
  for (uint32_t idx = 0; idx < nbElem; idx++) {
    if ((idx & 0x7) == 0) {
      fprintf(fou, "\n ");
    }
    fprintf(fou, " 0x%08x,", (uint32_t) data[idx]);
  }
  fprintf(fou, "\n};\n");
  fclose(fou);
}

/**
 * Write data in file fileName in asccii hexa format + float format
 * nbElem is number of element write in file
 */
void write_file32xf(const char *fileName, uint32_t nbElem, uint32_t *data)
{
  FILE *fou;
  fou = fopen(fileName, "w");
  if (fou == NULL) {
    printf("write_file32: Failed to open file %s\n", fileName);
  }
  assert(fou);
  printf("Write file %s\n", fileName);
  for (uint32_t idx = 0; idx < nbElem; idx++) {
    float32_t *tmpf = (float32_t *) &data[idx];
    fprintf(fou, "0x%08x %.8f\n", (uint32_t) data[idx], *tmpf);
  }
  fclose(fou);
}

/**
 * HSP check status error and return 0 if OK, else 1
 */
uint32_t hsp_check_status(const char *testName, uint32_t status, uint32_t ref_sts)
{
  uint32_t nbCheckFailed = 0;
  if (status != ref_sts) {
    nbCheckFailed++;
    TEST_INFO_REPORT(testName, "ERROR: Check status failed: Res 0x%08x != Exp 0x%08x\n", status, ref_sts);
  } else {
    TEST_INFO_REPORT(testName, "\tPASSED\n");
  }
  return nbCheckFailed;
}

#ifndef HYP_TOOLS
#ifndef HYP_UNITARY_TEST

#ifdef ARM_COMPILE

#ifdef STM32U3C5xx

HAL_StatusTypeDef test_send_event(HSP_HandleTypeDef *hhsp, uint8_t event)
{
	//printf("Sending event %d\n",(uint32_t)event);
	HAL_StatusTypeDef status = HAL_OK;

	// Enable event associated to this list
	if ((event > 0) && (event < 23))
	{
		/// Temporaire just for test !!!
		if (event <= 8)
		{
			//printf("value to write in EVTSRC0R = 0x%08x\n",6 << (4*((event-1)%8)));
			hhsp->instance->EVTSRC0R |= (6 << (4*((event-1)%8))); // enable CSEG source for event 1..8
			//printf("hhsp->EVTSRC0R=%d\n", hhsp->EVTSRC0R);
		}
		else if (event <= 16)
		{
			//printf("value to write in EVTSRC1R = 0x%08x\n",6 << (4*((event-1)%8)));
			hhsp->instance->EVTSRC1R |= (6 << (4*((event-1)%8))); // enable CSEG source for evet 9..16
			//printf("hhsp->EVTSRC1R=%d\n", hhsp->EVTSRC1R);
		}
		else if (event <= 22)
		{
			//printf("value to write in EVTSRC2R = 0x%08x\n",6 << (4*((event-1)%8)));
			hhsp->instance->EVTSRC2R |= (6 << (4*((event-1)%8))); // enable CSEG source for evet 17..22
			//printf("hhsp->EVTSRC2R=%d\n", hhsp->EVTSRC2R);
		}
		hhsp->instance->CSEGR = (1 << event);
	}
	else
	{
		// Wait until the CDEG is ready to accept the generation of a new event.
		while ( (hhsp->instance->CDEGR & 0x80000000) != 0);
		// HSP CPU dedicated event generation register
		hhsp->instance->CDEGR = (event & 0x3F);
	}
	return status;
}

HAL_StatusTypeDef test_enable_event(HSP_HandleTypeDef *hhsp, uint8_t event)
{
  	HAL_StatusTypeDef status = HAL_OK;

	// Enable event associated to this list
	if ((event > 0) && (event < 23))
	{
		//printf("hhsp->EVTENR=%d\n", hhsp->EVTENR);
		hhsp->instance->EVTENR &= ~(1 << event); // Need to update EVTSRCxR

		/// Temporaire just for test !!!
		if (event <= 8)
		{
			//printf("value to write in EVTSRC0R = 0x%08x\n",6 << (4*((event-1)%8)));
			hhsp->instance->EVTSRC0R |= (6 << (4*((event-1)%8))); // enable CSEG source for event 1..8
			//printf("hhsp->EVTSRC0R=%d\n", hhsp->EVTSRC0R);
		}
		else if (event <= 16)
		{
			//printf("value to write in EVTSRC1R = 0x%08x\n",6 << (4*((event-1)%8)));
			hhsp->instance->EVTSRC1R |= (6 << (4*((event-1)%8))); // enable CSEG source for evet 9..16
			//printf("hhsp->EVTSRC1R=%d\n", hhsp->EVTSRC1R);
		}
		else if (event <= 22)
		{
			//printf("value to write in EVTSRC2R = 0x%08x\n",6 << (4*((event-1)%8)));
			hhsp->instance->EVTSRC2R |= (6 << (4*((event-1)%8))); // enable CSEG source for evet 17..22
			//printf("hhsp->EVTSRC2R=%d\n", hhsp->EVTSRC2R);
		}
		// Enable CSEG
		hhsp->instance->ITFENR |= 0x10000000;
		/* !< HSP event enable register                         Address offset: 0x080 */
		hhsp->instance->EVTENR |= (1 << event); // hhsp->EVTENR |= (1 << event);
	}
	else
	{
		// Enable CDEG
		hhsp->instance->ITFENR |= 0x20000000;
	}
	return status;
}
                                                
HAL_StatusTypeDef test_enable_and_send_event(HSP_HandleTypeDef *hhsp, uint8_t event)
{
  	//printf("Sending event %d\n",(uint32_t)event);
	HAL_StatusTypeDef status = HAL_OK;


#ifdef ARM_COMPILE
#ifdef STM32H7P5xx
  __DSB();
  __DMB();
#endif
#endif
	// Enable event associated to this list
	if ((event > 0) && (event < 23))
	{
		//printf("hhsp->EVTENR=%d\n", hhsp->EVTENR);
		hhsp->instance->EVTENR &= ~(1 << event); // Need to update EVTSRCxR

		/// Temporaire just for test !!!
		if (event <= 8)
		{
			//printf("value to write in EVTSRC0R = 0x%08x\n",6 << (4*((event-1)%8)));
			hhsp->instance->EVTSRC0R |= (6 << (4*((event-1)%8))); // enable CSEG source for event 1..8
			//printf("hhsp->EVTSRC0R=%d\n", hhsp->EVTSRC0R);
		}
		else if (event <= 16)
		{
			//printf("value to write in EVTSRC1R = 0x%08x\n",6 << (4*((event-1)%8)));
			hhsp->instance->EVTSRC1R |= (6 << (4*((event-1)%8))); // enable CSEG source for evet 9..16
			//printf("hhsp->EVTSRC1R=%d\n", hhsp->EVTSRC1R);
		}
		else if (event <= 22)
		{
			//printf("value to write in EVTSRC2R = 0x%08x\n",6 << (4*((event-1)%8)));
			hhsp->instance->EVTSRC2R |= (6 << (4*((event-1)%8))); // enable CSEG source for evet 17..22
			//printf("hhsp->EVTSRC2R=%d\n", hhsp->EVTSRC2R);
		}
		// Enable CSEG
		hhsp->instance->ITFENR |= 0x10000000;
		/* !< HSP event enable register                         Address offset: 0x080 */
		hhsp->instance->EVTENR |= (1 << event); // hhsp->EVTENR |= (1 << event);
		hhsp->instance->CSEGR = (1 << event);
	}
	else
	{
		// Enable CDEG
		hhsp->instance->ITFENR |= 0x20000000;
		// Wait until the CDEG is ready to accept the generation of a new event.
		while ( (hhsp->instance->CDEGR & 0x80000000) != 0);
		// HSP CPU dedicated event generation register
		hhsp->instance->CDEGR = (event & 0x3F);
	}
	return status;
}


static HAL_StatusTypeDef HSP_ConfigureTaskComparator(HSP_TypeDef *hhsp, uint8_t taskNb, uint8_t taskCmpNb)
{
#ifdef HYPSA_SIMU
  return(HAL_OK);
#endif
#ifndef HYPSA_SIMU
  switch (taskCmpNb)
  {
    case 0:
      /* Enable TCCMP0 */
      hhsp->TCUCFGR = hhsp->TCUCFGR | (1U << HSP_TCUCFGR_TC0EN_Pos);
      /* Set task Number */
      hhsp->TCUCFGR = (hhsp->TCUCFGR | taskNb);
      /* Enable IT for EOTC */
      hhsp->EVT_IER = (hhsp->EVT_IER | ((1U << HSP_EVT_IER_EOTECP0IE_Pos)));
      break;
    case 1:
      /* Enable TCCMP0 */
      hhsp->TCUCFGR = hhsp->TCUCFGR | (1U << HSP_TCUCFGR_TC1EN_Pos);
      /* Set task Number */
      hhsp->TCUCFGR = (hhsp->TCUCFGR | (taskNb << HSP_TCUCFGR_TSKCMP1_Pos));
      /* Enable IT for EOTC */
      hhsp->EVT_IER = (hhsp->EVT_IER | ((1U << HSP_EVT_IER_EOTECP1IE_Pos)));
      break;
    case 2:
      /* Enable TCCMP0 */
      hhsp->TCUCFGR = hhsp->TCUCFGR | (1U << HSP_TCUCFGR_TC2EN_Pos);
      /* Set task Number */
      hhsp->TCUCFGR = (hhsp->TCUCFGR | (taskNb << HSP_TCUCFGR_TSKCMP2_Pos));
      /* Enable IT for EOTC */
      hhsp->EVT_IER = (hhsp->EVT_IER | ((1U << HSP_EVT_IER_EOTECP2IE_Pos)));
      break;
    case 3:
      /* Enable TCCMP0 */
      hhsp->TCUCFGR = hhsp->TCUCFGR | (1U << HSP_TCUCFGR_TC3EN_Pos);
      /* Set task Number */
      hhsp->TCUCFGR = (hhsp->TCUCFGR | (taskNb << HSP_TCUCFGR_TSKCMP3_Pos));
      /* Enable IT for EOTC */
      hhsp->EVT_IER = (hhsp->EVT_IER | ((1U << HSP_EVT_IER_EOTECP3IE_Pos)));
      break;
    default:
      return(HAL_ERROR);
      break;
  }
  return(HAL_OK);
#endif
}
/**
  * @brief Configure End Of Task signal from HSP to CPU
  * @param hhsp         HSP handle.
  * @param taskNb       Task number
  * @param taskCmpNb    Task comparator number
  * @retval            HAL status.
  */
HAL_StatusTypeDef HAL_HSP_ConfigureEOT(HSP_HandleTypeDef *hhsp, uint8_t taskNb, uint8_t taskCmpNb)
{
  if (HSP_ConfigureTaskComparator(hhsp->instance, taskNb, taskCmpNb) != HAL_OK)
  {
//    hhsp->ErrorCode = HAL_HSP_ERROR_INVALID_PARAM;
    return HAL_ERROR;
  }
  return HAL_OK;
}
#else // STM32U3C5xxx
                                                
/**
 * @brief Enable event to HSP
 * @param[in] hhsp    HSP handle.
 * @retval            HAL status.
 */
HAL_StatusTypeDef test_send_event(HSP_HandleTypeDef *hhsp, uint8_t event)
{
	//printf("Sending event %d\n",(uint32_t)event);
	HAL_StatusTypeDef status = HAL_OK;

	// Enable event associated to this list
	if ((event > 0) && (event < 23))
	{
		/// Temporaire just for test !!!
		if (event <= 8)
		{
			//printf("value to write in EVTSRC0R = 0x%08x\n",6 << (4*((event-1)%8)));
			hhsp->Instance->EVTSRC0R |= (6 << (4*((event-1)%8))); // enable CSEG source for event 1..8
			//printf("hhsp->EVTSRC0R=%d\n", hhsp->EVTSRC0R);
		}
		else if (event <= 16)
		{
			//printf("value to write in EVTSRC1R = 0x%08x\n",6 << (4*((event-1)%8)));
			hhsp->Instance->EVTSRC1R |= (6 << (4*((event-1)%8))); // enable CSEG source for evet 9..16
			//printf("hhsp->EVTSRC1R=%d\n", hhsp->EVTSRC1R);
		}
		else if (event <= 22)
		{
			//printf("value to write in EVTSRC2R = 0x%08x\n",6 << (4*((event-1)%8)));
			hhsp->Instance->EVTSRC2R |= (6 << (4*((event-1)%8))); // enable CSEG source for evet 17..22
			//printf("hhsp->EVTSRC2R=%d\n", hhsp->EVTSRC2R);
		}
		hhsp->Instance->CSEGR = (1 << event);
	}
	else
	{
		// Wait until the CDEG is ready to accept the generation of a new event.
		while ( (hhsp->Instance->CDEGR & 0x80000000) != 0);
		// HSP CPU dedicated event generation register
		hhsp->Instance->CDEGR = (event & 0x3F);
	}
	return status;
}

/**
 * @brief Send event to HSP
 * @param[in] hhsp    HSP handle.
 * @retval            HAL status.
 */
HAL_StatusTypeDef test_enable_event(HSP_HandleTypeDef *hhsp, uint8_t event)
{
	HAL_StatusTypeDef status = HAL_OK;

	// Enable event associated to this list
	if ((event > 0) && (event < 23))
	{
		//printf("hhsp->EVTENR=%d\n", hhsp->EVTENR);
		hhsp->Instance->EVTENR &= ~(1 << event); // Need to update EVTSRCxR

		/// Temporaire just for test !!!
		if (event <= 8)
		{
			//printf("value to write in EVTSRC0R = 0x%08x\n",6 << (4*((event-1)%8)));
			hhsp->Instance->EVTSRC0R |= (6 << (4*((event-1)%8))); // enable CSEG source for event 1..8
			//printf("hhsp->EVTSRC0R=%d\n", hhsp->EVTSRC0R);
		}
		else if (event <= 16)
		{
			//printf("value to write in EVTSRC1R = 0x%08x\n",6 << (4*((event-1)%8)));
			hhsp->Instance->EVTSRC1R |= (6 << (4*((event-1)%8))); // enable CSEG source for evet 9..16
			//printf("hhsp->EVTSRC1R=%d\n", hhsp->EVTSRC1R);
		}
		else if (event <= 22)
		{
			//printf("value to write in EVTSRC2R = 0x%08x\n",6 << (4*((event-1)%8)));
			hhsp->Instance->EVTSRC2R |= (6 << (4*((event-1)%8))); // enable CSEG source for evet 17..22
			//printf("hhsp->EVTSRC2R=%d\n", hhsp->EVTSRC2R);
		}
		// Enable CSEG
		hhsp->Instance->ITFENR |= 0x10000000;
		/* !< HSP event enable register                         Address offset: 0x080 */
		hhsp->Instance->EVTENR |= (1 << event); // hhsp->EVTENR |= (1 << event);
	}
	else
	{
		// Enable CDEG
		hhsp->Instance->ITFENR |= 0x20000000;
	}
	return status;
}

/**
 * @brief Send event to HSP
 * @param[in] hhsp    HSP handle.
 * @retval            HAL status.
 */
HAL_StatusTypeDef test_enable_and_send_event(HSP_HandleTypeDef *hhsp, uint8_t event)
{
	//printf("Sending event %d\n",(uint32_t)event);
	HAL_StatusTypeDef status = HAL_OK;


#ifdef ARM_COMPILE
#ifdef STM32H7P5xx
  __DSB();
  __DMB();
#endif
#endif
	// Enable event associated to this list
	if ((event > 0) && (event < 23))
	{
		//printf("hhsp->EVTENR=%d\n", hhsp->EVTENR);
		hhsp->Instance->EVTENR &= ~(1 << event); // Need to update EVTSRCxR

		/// Temporaire just for test !!!
		if (event <= 8)
		{
			//printf("value to write in EVTSRC0R = 0x%08x\n",6 << (4*((event-1)%8)));
			hhsp->Instance->EVTSRC0R |= (6 << (4*((event-1)%8))); // enable CSEG source for event 1..8
			//printf("hhsp->EVTSRC0R=%d\n", hhsp->EVTSRC0R);
		}
		else if (event <= 16)
		{
			//printf("value to write in EVTSRC1R = 0x%08x\n",6 << (4*((event-1)%8)));
			hhsp->Instance->EVTSRC1R |= (6 << (4*((event-1)%8))); // enable CSEG source for evet 9..16
			//printf("hhsp->EVTSRC1R=%d\n", hhsp->EVTSRC1R);
		}
		else if (event <= 22)
		{
			//printf("value to write in EVTSRC2R = 0x%08x\n",6 << (4*((event-1)%8)));
			hhsp->Instance->EVTSRC2R |= (6 << (4*((event-1)%8))); // enable CSEG source for evet 17..22
			//printf("hhsp->EVTSRC2R=%d\n", hhsp->EVTSRC2R);
		}
		// Enable CSEG
		hhsp->Instance->ITFENR |= 0x10000000;
		/* !< HSP event enable register                         Address offset: 0x080 */
		hhsp->Instance->EVTENR |= (1 << event); // hhsp->EVTENR |= (1 << event);
		hhsp->Instance->CSEGR = (1 << event);
	}
	else
	{
		// Enable CDEG
		hhsp->Instance->ITFENR |= 0x20000000;
		// Wait until the CDEG is ready to accept the generation of a new event.
		while ( (hhsp->Instance->CDEGR & 0x80000000) != 0);
		// HSP CPU dedicated event generation register
		hhsp->Instance->CDEGR = (event & 0x3F);
	}
	return status;
}
#endif

                                                          
#else // ARM_COMPILE
/**
  * @brief Configure End Of Task signal from HSP to CPU
  * @param hhsp         HSP handle.
  * @param taskNb       Task number
  * @param taskCmpNb    Task comparator number
  * @retval            HAL status.
  */
HAL_StatusTypeDef HAL_HSP_ConfigureEOT(HSP_HandleTypeDef *hhsp, uint8_t taskNb, uint8_t taskCmpNb)
{
  return HAL_OK;
}

/**
 * @brief Enable event to HSP
 * @param[in] hhsp    HSP handle.
 * @retval            HAL status.
 */
HAL_StatusTypeDef test_send_event(HSP_HandleTypeDef *hhsp, uint8_t event)
{
	//printf("Sending event %d\n",(uint32_t)event);
	HAL_StatusTypeDef status = HAL_OK;
    hypsa_send_evt(event);
	return status;
}

/**
 * @brief Send event to HSP
 * @param[in] hhsp    HSP handle.
 * @retval            HAL status.
 */
HAL_StatusTypeDef test_enable_event(HSP_HandleTypeDef *hhsp, uint8_t event)
{
	HAL_StatusTypeDef status = HAL_OK;
	return status;
}

HAL_StatusTypeDef test_enable_and_send_event(HSP_HandleTypeDef *hhsp, uint8_t event)
{
	//printf("Sending event %d\n",(uint32_t)event);
	HAL_StatusTypeDef status = HAL_OK;
    hypsa_send_evt(event);
	return status;
}
#endif
#endif // HYP_UNITARY_TEST

/**
 * @brief HSP API hw reset
 * @param[in] hhsp    HSP handle.
 * @retval            HAL status.
 */
// @ToDo est-ce une fct necessaire  ?
//HAL_StatusTypeDef HAL_HSP_HWReset(HSP_HandleTypeDef *hhsp)
void test_hw_reset(HSP_HandleTypeDef *hhsp)
{
	//ll_reset_hsp(hhsp->Instance);

#ifdef ARM_COMPILE
	/* RESET HSP */
	/* Pour le moment le FPGA utilise les signaux du DMA2D pour le HSP */
#ifdef STM32U3C5xx
  __HAL_RCC_HSP1_FORCE_RESET();
  __HAL_RCC_HSP1_RELEASE_RESET();
#endif // STM32U3C5xx
#ifdef STM32U575xx
	__HAL_RCC_DMA2D_FORCE_RESET();
	__HAL_RCC_DMA2D_RELEASE_RESET();
#endif // STM32U575xx
#ifdef STM32H7P5xx
 HAL_RCC_HSP_Reset();
  HAL_RCC_HSP_EnableClock();
//  HAL_RCC_HSPRAM_EnableClock();
#endif // STM32H7P5xx       
        
#endif // ARM_COMPILE

	//return HAL_OK;
}
#endif // HYP_TOOLS


#ifdef ARM_COMPILE
/**
 * Load HSP data test in BRAM
 */
void load_hsp_data_bram(uint32_t *pSrc, uint32_t *pDst, uint32_t length)
{
	for (int i = 0; i < length; i++)
	{
		// Write data in HSP BRAM
		pDst[i] = pSrc[i];
	}
}

#ifdef LOAD_BY_TEST_COMMON
/**
 * Load HSP CRAM code
 */
void load_hsp_cram(void)
{
    // printf("Adresse CRAM=0x%08x\n",HSP_CRAM_BASE_ADDR);
  uint32_t tmpi;
  uint32_t *tmpAddr = (uint32_t *) HSP_CRAM_BASE_ADDR;
  for (tmpi = 0; tmpi < HSP_CRAM_SIZE; tmpi++) {
    // Write data in HSP CRAM
    *tmpAddr++ = dataCRAMTab[tmpi];
  }
//  *tmpAddr = 0xFFFFFFFF;
}

/**
 * Load HSP DRAM code
 */
void load_hsp_dram(void)
{
  uint32_t tmpi;
  uint32_t *tmpAddr = (uint32_t *) HSP_DRAM_BASE_ADDR;
  for (tmpi = 0; tmpi < HSP_DRAM_SIZE; tmpi++) {
    // Write data in HSP CRAM
    *tmpAddr++ = dataDRAMTab[tmpi];
  }
}

/**
 * Load HSP Plugin in CRAM
 */
void load_hsp_data_cram(uint32_t *pSrc, uint32_t offset, uint32_t length)
{
	uint32_t tmpi;
	uint32_t tmp = HSP_CRAM_BASE_ADDR + (HSP_CRAM_SIZE + offset)*4;
	uint32_t *tmpAddr = (uint32_t *) tmp;
        tmpAddr--; // Last word of CRAM is 0xFFFFFFFF 
    printf("Load CRAM @0x%x\n", tmpAddr);
	for (tmpi = 0; tmpi < length; tmpi++)
	{
	// Write data in HSP CRAM
	*tmpAddr++ = pSrc[tmpi];
	}
}
#endif

#ifndef STM32H7P5xx
/**
 * Wait for HSP termination.
 */
void test_wait_for_hsp(void)
{
  // Synchronization method based on end of task interrupt
  while (hsp_it_evt == 0)
  {
    __WFI();
  }
  // Reset hsp_it_evt
  hsp_it_evt = 0;
}
#else
void test_wait_for_hsp(void)
{
	__disable_irq(); // Desactiver les interruptions

	// Verifier si une interruption est en attente
	if (SCB->ICSR & SCB_ICSR_ISRPENDING_Msk) {
		__enable_irq(); // Reactiver les interruptions
		return; // Une interruption est en attente, ne pas entrer en mode veille
	}

	if (hsp_it_evt)
	{
		__enable_irq(); // Reactiver les interruptions
		return; // Une interruption est en attente, ne pas entrer en mode veille
	}

#ifdef ARM_COMPILE
#ifdef STM32H7P5xx
  __DSB();
  __DMB();
#endif
#endif
	__WFI(); // Wait For Interrupt

	__enable_irq(); // Reactiver les interruptions apres WFI
}
#endif

/**
 * Wait for HSP Global IT
 */
void test_wait_for_gbl_hsp(void)
{
  // Synchronization method based on end of task interrupt
  while (hsp_it_gbl == 0)
  {
    __WFI();
  }
  // Reset hsp_it_evt
  hsp_it_gbl = 0;
}




#else // ARM_COMPILE

/**
 * Hyperion function called when event sent, then call scheduler
 */
void test_wait_for_hsp()
{
  // hypsa_extra_fct();
}

/**
 * Wait for HSP Global IT
 */
void test_wait_for_gbl_hsp(void)
{
}

/**
 * Load HSP data test in BRAM
 */
void load_hsp_data_bram(uint32_t *pSrc, uint32_t *pDst, uint32_t length)
{
	for (int i = 0; i < length; i++)
	{
		// Write data in HSP BRAM
		pDst[i] = pSrc[i];
	}
}

/**
 * Load HSP Plugin in CRAM
 */
void load_hsp_data_cram(uint32_t *pSrc, uint32_t offset, uint32_t length)
{
	uint32_t tmpi;
	uint32_t *tmpAddr = (uint32_t *) offset;
    printf("Load CRAM @0x%x\n", tmpAddr);
	uint32_t chess_storage(PMw) *ptrRam = (uint32_t chess_storage(PMw) *) offset;

	for (tmpi = 0; tmpi < length; tmpi++)
	{
		// Write data in HSP CRAM
		*ptrRam++ = pSrc[tmpi];
	}
}

#ifdef ARM_LOAD_BRAM
/**
 * Load HSP BRAM code
 */
void load_hsp_bram(void)
{
  uint32_t tmpi;
  uint32_t *tmpAddr = (uint32_t *) HSP_BRAM_AB_BASE_ADDR;
  for (tmpi = 0; tmpi < HSP_BRAM_SIZE; tmpi++) {
    // Write data in HSP CRAM
    *tmpAddr++ = dataBRAMTab[tmpi];
  }
}
#endif // ARM_LOAD_BRAM
#endif // ARM_COMPILE

/**
 * Fill HSP memory with value
 */
void fill_hsp_memory(uint32_t *pDst, uint32_t value, uint32_t length)
{
	for (uint32_t i = 0; i < length; i++)
	{
		// Write data in HSP BRAM
		pDst[i] = value;
	}
}
/**
 * Reset shared memory area
 * @param[in] addr   Start address of area to reset
 * @param[in] size   Size of area to reset
 * @param[in] data   Data to set to reset area
 */
void reset_hsp_shared_mem(uint32_t addr, uint32_t size, uint32_t data)
{
  uint32_t *pDst = (uint32_t *) addr;
  for (uint32_t i = 0; i < size; i++) {
    // Write data in HSP BRAM
    pDst[i] = data;
  }
}

/**
 * Start cycle counter
 */
void hsp_startcc(void)
{
#ifdef ARM_COMPILE
	cTimerCount_Start();
#else // ARM_COMPILE
  // Hyperion simulation compilation
  clrcc();
  startcc();
#endif // ARM_COMPILE
}

/**
 * Stop cycle counter
 */
void hsp_stopcc(void)
{
#ifdef ARM_COMPILE
	//uint32_t val;
	cTimerCount_Stop(_armMeasure);
	//return(val);
	_armMeasure = _armMeasure - 4; // Remove 2 cycles for startcc (HSP side)  and call to hsp_stopcc (ARM side)
#else // ARM_COMPILE
  // Hyperion simulation compilation
  stopcc();
  hspInternalMeasure = getcc();
  _armMeasure = hspInternalMeasure + 2; // Put all cycles in ARM measure + add 2 cycles scheduler
  hspInternalMeasure = hspInternalMeasure - 2; // To remove this call
#endif // ARM_COMPILE
}


/**
 * Add padding for CNN input
 * @param[in] pSrc   Input image to pad
 * @param[in] pDst   Output image padded
 * @param[in] nbCol  Input width
 * @param[in] nbLin  Input height
 * @param[in] nbLin  Input channels
 * @param[in] padX   Horizontal padding
 * @param[in] padY   Vertical padding
 * @param[in] padV   Padding value
 */
void gen_padding_img(uint8_t *pSrc, uint8_t *pDst, uint32_t nbCol, uint32_t nbLin, uint32_t nbChan, uint32_t padX,
                     uint32_t padY, uint32_t padV)
{
  uint8_t val = padV;
  // First lines pad
  for (uint32_t i = 0; i < padY; i++) {
    // Pad one full dest line
    for (uint32_t j = 0; j < ((nbCol + (2 * padX)) * nbChan); j++) {
      *pDst++ = val;
    }
  }
  // Middle lines to pad
  for (uint32_t i = 0; i < nbLin; i++) {
    // First column pad
    for (uint32_t c = 0; c < (padX * nbChan); c++) {
      *pDst++ = val;
    }
    //printf("pix[%d] = 0x%x\n", i, *pSrc);
    // Copy image line
    for (uint32_t j = 0; j < (nbCol * nbChan); j++) {
      *pDst++ = *pSrc++;
    }
    //printf("pl = 0x%02x%02x%02x%02x\n", pSrc[-1], pSrc[-2], pSrc[-3], pSrc[-4]);
    // Last column pad
    for (uint32_t c = 0; c < (padX * nbChan); c++) {
      *pDst++ = val;
    }
  }
  // Last lines pad
  for (uint32_t i = 0; i < padY; i++) {
    // Pad one full dest line
    for (uint32_t j = 0; j < ((nbCol + (2 * padX)) * nbChan); j++) {
      *pDst++ = val;
    }
  }
}

/**
 * Add padding for CNN input
 * @param[in] pSrc   Input image to pad
 * @param[in] pDst   Output image padded
 * @param[in] nbCol  Input width
 * @param[in] nbLin  Input height
 * @param[in] nbLin  Input channels
 * @param[in] padX   Horizontal padding
 * @param[in] padY   Vertical padding
 * @param[in] padV   Padding value
 */
void gen_padding_img2(uint8_t *pSrc, uint8_t *pDst, uint32_t nbCol, uint32_t nbLin, uint32_t nbChan, uint32_t padX0,
                      uint32_t padX1, uint32_t padY0, uint32_t padY1, uint32_t padV)
{
  printf("line size %d\n", ((nbCol + (padX0 + padX1)) * nbChan));
  uint8_t val = padV;
  // First lines pad
  for (uint32_t i = 0; i < padY0; i++) {
    // Pad one full dest line
    for (uint32_t j = 0; j < ((nbCol + (padX0 + padX1)) * nbChan); j++) {
      *pDst++ = val;
    }
  }
  // Middle lines to pad
  for (uint32_t i = 0; i < nbLin; i++) {
    // First column pad
    for (uint32_t c = 0; c < (padX0 * nbChan); c++) {
      *pDst++ = val;
    }
    //printf("pix[%d] = 0x%x\n", i, *pSrc);
    // Copy image line
    for (uint32_t j = 0; j < (nbCol * nbChan); j++) {
      *pDst++ = *pSrc++;
    }
    //printf("pl = 0x%02x%02x%02x%02x\n", pSrc[-1], pSrc[-2], pSrc[-3], pSrc[-4]);
    // Last column pad
    for (uint32_t c = 0; c < (padX1 * nbChan); c++) {
      *pDst++ = val;
    }
  }
  // Last lines pad
  for (uint32_t i = 0; i < padY1; i++) {
    // Pad one full dest line
    for (uint32_t j = 0; j < ((nbCol + (padX0 + padX1)) * nbChan); j++) {
      *pDst++ = val;
    }
  }
}

#ifdef HYPSA_SIMU

// For CNN hypsa modelisation
uint8_t *hypsa_cnn_pIn;
uint8_mema_t *hypsa_cnn_pSrc;
uint8_mema_t *hypsa_cnn_pSrcEnd;
uint8_mema_t *hypsa_cnn_pSrcA;
uint8_memb_t *hypsa_cnn_pSrcB;
uint8_memb_t *hypsa_cnn_pKb;
uint8_memb_t *hypsa_cnn_pSrcBEnd;
uint32_t hypsa_cnn_loop;
uint32_t hypsa_cnn_pKidx;
uint32_t hypsa_cnn_kloop;
uint8_t *hypsa_cnn_pKe;
uint8_t *hypsa_cnn_pOu;
uint8_mema_t *hypsa_cnn_pDst;
uint8_mema_t *hypsa_cnn_pDstEnd;
uint8_mema_t *hypsa_cnn_pDstStart;
uint8_memb_t *hypsa_cnn_pDstb;
uint8_memb_t *hypsa_cnn_pDstbEnd;
uint8_memb_t *hypsa_cnn_pDstbStart;
uint32_t hypsa_cnn_oloop;
uint32_t hypsa_cnn_stridey;
uint32_t hypsa_cnn_padx;
uint32_t hypsa_cnn_pady;
uint8_t hypsa_cnn_padv;
uint32_t hypsa_cnn_countlines;
uint32_t hypsa_cnn_countmax;
uint32_t hypsa_cnn_nbKblocks;
uint32_t hypsa_cnn_ouBlocks;
uint32_t hypsa_cnn_ouh; ///< output number of lines
uint32_t hypsa_cnn_ouc; ///< output channel number
uint32_t hypsa_cnn_nbchanb; ///< output channel block size
uint32_t hypsa_cnn_ouBcn; ///< output channel block number
uint32_t hypsa_cnn_ouw; ///< output width
uint32_t hypsa_cnn_ouBx;
uint32_t hypsa_cnn_ouBi;
uint32_t hypsa_cnn_ouBz;
uint32_t hypsa_cnn_bMode; ///< kernel block mode
uint32_t hypsa_cnn_bCount; ///< kernel block mode
uint32_t hypsa_cnn_state;
uint32_t hypsa_cnn_kcount;
uint32_t hypsa_cnn_kcountmax;
uint32_t hypsa_cnn_icount;
uint32_t hypsa_cnn_icountmax;
uint32_t hypsa_cnn_ocount;
uint32_t hypsa_cnn_ocountmax;
uint8_t *hypsa_cnn_pKeBase;
uint32_t hypsa_cnn_kh;
uint32_t hypsa_cnn_pw;
uint32_t hypsa_cnn_dw;
uint32_t hypsa_cnn_pool;
uint32_t hypsa_cnn_nbPadK0;

//#define PRINT_DBG_CNN

#ifndef HYP_UNITARY_TEST
/**
 * For FC hypsa test, get global var in payload
 */
void hypsa_cnn_fc_set_var(int8_t *pKe, uint32_t in_c, uint32_t ou_c)
{
  hypsa_cnn_pw = 0;
  hypsa_cnn_dw = 0;
  hypsa_cnn_pool = 0;
  hyp_cnn_param_t *param = (hyp_cnn_param_t *) hsp_mb_pay_tab;
  uint32_t k_c = in_c * ou_c;
  hypsa_cnn_pIn = NULL;
  hypsa_cnn_bMode = 10;
  hypsa_cnn_bCount = 0;
  hypsa_cnn_nbPadK0 = 0;
  if (in_c & 0x3) {
    // Not aligned on 4, add extra kernels to 0
    hypsa_cnn_nbPadK0 = 4 - (in_c & 0x3);
  }
  hypsa_cnn_nbKblocks = 1;
  hypsa_cnn_kloop = in_c; // one kernel per loop
  hypsa_cnn_pKeBase = (uint8_t *) pKe;
  hypsa_cnn_pKe = (uint8_t *) (pKe + hypsa_cnn_kloop); // Put Ke to second block
  hypsa_cnn_pSrcB = (uint8_memb_t *) hsp_reg.SPE_DCMDPTR1; // Ping addr
  hypsa_cnn_pKb = hypsa_cnn_pSrcB + (in_c + hypsa_cnn_nbPadK0); // Put Ke to second block
  hypsa_cnn_pSrcBEnd = hypsa_cnn_pSrcB + (2 * (in_c + hypsa_cnn_nbPadK0)); // Full kernels buffer
  hypsa_cnn_kh = 1;
  hypsa_cnn_kcount = 1; // First kernel already loaded
  hypsa_cnn_kcountmax = ou_c;
}

/**
 * For conv2D hypsa test, get global var in payload
 */
void hypsa_cnn_conv2d_set_var(int8_t *pIn, int8_t *pKe, int8_t *pOu, uint32_t padx0, uint32_t padx1, uint32_t pady0,
                              uint32_t pady1, uint32_t nbLinePerBlocks, uint32_t bMode)
{
  hypsa_cnn_pw = 0;
  hypsa_cnn_dw = 0;
  hypsa_cnn_pool = 0;
  hyp_cnn_param_t *param = (hyp_cnn_param_t *) hsp_mb_pay_tab;
  uint32_t inLineSize8 = param->in_c * param->inp_w; // 1 input line
  uint32_t outLineSize8 = param->ou_c * param->ou_w; // 1 ouput line
  uint32_t k_c = param->in_c * param->ou_c;
  hypsa_cnn_pIn = (uint8_t *) pIn;
  hypsa_cnn_pSrcA = (uint8_mema_t *) hsp_reg.SPE_DCMDPTR0;
  hypsa_cnn_pSrcEnd = hypsa_cnn_pSrcA + (((param->mode >> HSP_CNN_CFG_NB_IN_LINE_SHIFT) & HSP_CNN_CFG_MODE_MASK) * inLineSize8);
  hypsa_cnn_pSrc = hypsa_cnn_pSrcA + (inLineSize8 * param->k_h);
#ifdef PRINT_DBG_CNN
  printf("InA base 0x%x end 0x%x curr 0x%x\n", hypsa_cnn_pSrcA, hypsa_cnn_pSrcEnd, hypsa_cnn_pSrc);
#endif // PRINT_DBG_CNN
  hypsa_cnn_loop = inLineSize8 - ((padx0 + padx1) * param->in_c);
  //hypsa_cnn_nbKblocks = nbLinesOu;
  hypsa_cnn_nbKblocks = 0;
  hypsa_cnn_bMode = bMode;
  hypsa_cnn_bCount = 0;
  hypsa_cnn_pOu = (uint8_t *) pOu;
  hypsa_cnn_pDst = (uint8_mema_t *) hsp_reg.SPE_DCMDPTR2;
  hypsa_cnn_pDstEnd = hypsa_cnn_pDst + (nbLinePerBlocks * outLineSize8);
  hypsa_cnn_pDstStart = hypsa_cnn_pDst;
  hypsa_cnn_oloop = outLineSize8;
  hypsa_cnn_stridey = param->stridey;
  hypsa_cnn_padx = padx0 * param->in_c;
  hypsa_cnn_pady = pady0;
  hypsa_cnn_countlines = param->k_h;
  hypsa_cnn_countmax = param->inp_h - pady1;
  printf("hypsa_cnn_countmax %d = param->inp_h %d - pady1 %d\n", hypsa_cnn_countmax,  param->inp_h, pady1);
  int32_t *pOffset = (int32_t *) &(param->offIn);
  int8_t padV = (int8_t) *pOffset;
  padV = -padV;
  hypsa_cnn_padv = padV;
  hypsa_cnn_pDstb = 0;
  hypsa_cnn_pDstbEnd = 0;
  hypsa_cnn_pDstbStart = 0;
  hypsa_cnn_pKeBase = (uint8_t *) pKe;
  hypsa_cnn_pKe = 0;
  if (bMode == 20) {
    hypsa_cnn_pool = 1;
    hypsa_cnn_padv = 0x80;
    hypsa_cnn_pDstb = (uint8_memb_t *) hsp_reg.SPE_DCMDPTR2;
    hypsa_cnn_pDstbEnd = hypsa_cnn_pDstb + (nbLinePerBlocks * outLineSize8);
    hypsa_cnn_pDstbStart = hypsa_cnn_pDstb;
    hypsa_cnn_bMode = 0;
    bMode = 0;
  }
  hypsa_cnn_ouBlocks = 0;
  hypsa_cnn_ouh = 0;
  hypsa_cnn_ouw = param->ou_w;
  hypsa_cnn_ouBx = 0;
  hypsa_cnn_state = 0;
  hypsa_cnn_kcount = 0;
  hypsa_cnn_kcountmax = 0;
  hypsa_cnn_kh = param->k_h;
  hypsa_cnn_nbPadK0 = 0;
  if (bMode == 2) {
    // io1kl mode or 2 steps mode
    if ((param->k_w * param->in_c) & 0x3) {
      // Not aligned on 4, add extra kernels to 0
      hypsa_cnn_nbPadK0 = 4 - ((param->k_w * param->in_c) & 0x3);
    }
    hypsa_cnn_bMode = 2;
    hypsa_cnn_nbKblocks = 1;
    hypsa_cnn_kloop = param->k_h * (param->in_c * param->k_w); // one kernel per loop
    hypsa_cnn_pKeBase = (uint8_t *) pKe;
    hypsa_cnn_pKe = (uint8_t *) (pKe + hypsa_cnn_kloop); // Put Ke to second block
    hypsa_cnn_pSrcB = (uint8_memb_t *) hsp_reg.SPE_DCMDPTR1;
    hypsa_cnn_pKb = hypsa_cnn_pSrcB + (param->k_h * ((param->k_w * param->in_c) + hypsa_cnn_nbPadK0)); // Put Ke to second block
    hypsa_cnn_pSrcBEnd = hypsa_cnn_pSrcB + (param->k_h * param->ou_c * ((param->k_w * param->in_c) + hypsa_cnn_nbPadK0)); // Full kernels buffer
    if (hypsa_cnn_nbPadK0) {
      hypsa_cnn_kloop = (param->k_w * param->in_c);
    }
    hypsa_cnn_state = 1;
    hypsa_cnn_kcount = 1; // First kernel already loaded
    hypsa_cnn_kcountmax = param->ou_c;
/*     hypsa_cnn_pDstb = (uint8_memb_t *) hsp_reg.SPE_DCMDPTR2; */
/*     hypsa_cnn_pDstbEnd = hypsa_cnn_pDstb + (nbLinePerBlocks * outLineSize8); */
/*     hypsa_cnn_pDstbStart = hypsa_cnn_pDstb; */
    hypsa_cnn_ocountmax = param->ou_c;
    hypsa_cnn_ocount = 1;
  } else if (bMode == 3) {
    // iio mode
    if ((param->k_w * param->in_c) & 0x3) {
      // Not aligned on 4, add extra kernels to 0
      hypsa_cnn_nbPadK0 = (4 - (param->k_w * param->in_c) & 0x3);
    }
    hypsa_cnn_bMode = 3;
    uint32_t nbLineInPerBlocks = (nbLinePerBlocks * hypsa_cnn_stridey) + param->k_h - hypsa_cnn_stridey; // For circular mode
    hypsa_cnn_icount = param->k_h; // Already 3 input lines loaded
    hypsa_cnn_icountmax = nbLineInPerBlocks + 1;
    hypsa_cnn_ocountmax = nbLinePerBlocks;
    hypsa_cnn_ocount = 0;
    hypsa_cnn_kloop = param->k_h * (param->in_c * param->k_w); // one kernel per loop
    hypsa_cnn_pKeBase = (uint8_t *) pKe;
    hypsa_cnn_pKe = (uint8_t *) (pKe + hypsa_cnn_kloop); // Put Ke to second block
    hypsa_cnn_pSrcB = (uint8_memb_t *) hsp_reg.SPE_DCMDPTR1;
    hypsa_cnn_pKb = hypsa_cnn_pSrcB + (param->k_h * ((param->k_w * param->in_c) + hypsa_cnn_nbPadK0)); // Put Ke to second block
    hypsa_cnn_pSrcBEnd = hypsa_cnn_pKb + (param->k_h * 2 * ((param->k_w * param->in_c) + hypsa_cnn_nbPadK0)); // Ping pong on kernels
    if (hypsa_cnn_nbPadK0) {
      hypsa_cnn_kloop = (param->k_w * param->in_c);
    }
    hypsa_cnn_state = 1;
    hypsa_cnn_kcount = 1; // First kernel already loaded
    hypsa_cnn_kcountmax = param->ou_c;
    hypsa_cnn_pDstb = (uint8_memb_t *) hsp_reg.SPE_DCMDPTR2;
    hypsa_cnn_pDstbEnd = hypsa_cnn_pDstb + (nbLinePerBlocks * outLineSize8);
    hypsa_cnn_pDstbStart = hypsa_cnn_pDstb;
    //printf("hypsa_cnn_pKidx %d hypsa_cnn_kloop %d hypsa_cnn_pKb 0x%x\n", hypsa_cnn_pKidx, hypsa_cnn_kloop, hypsa_cnn_pKb);
  }
#ifdef PRINT_DBG_CNN
  printf("hypsa_cnn_pSrc @0x%x hypsa_cnn_pIn @0x%x loop %d stride %d hypsa_cnn_pSrcEnd @0x%x\n",
         hypsa_cnn_pSrc, hypsa_cnn_pIn, hypsa_cnn_loop, hypsa_cnn_stridey, hypsa_cnn_pSrcEnd);
#endif // PRINT_DBG_CNN
}

/**
 * For convDW hypsa test, get global var in payload
 */
void hypsa_cnn_convdw_set_var(int8_t *pIn, int8_t *pKe, int8_t *pOu, uint32_t padx0, uint32_t padx1, uint32_t pady0,
                              uint32_t pady1, uint32_t nbBlocks, uint32_t bMode)
{
	hypsa_cnn_pw = 0;
	hypsa_cnn_dw = 1;
    hypsa_cnn_pool = 0;
	hyp_cnn_dw_param_t *param = (hyp_cnn_dw_param_t *) hsp_mb_pay_tab;
	uint32_t inLineSize8 = param->in_c * param->inp_w; // 1 input line
	uint32_t outLineSize8 = param->ou_c * param->ou_w; // 1 ouput line
	uint32_t k_c = param->in_c; // * param->ou_c;
	hypsa_cnn_pIn = (uint8_t *) pIn;
	hypsa_cnn_pSrcA = (uint8_mema_t *) hsp_reg.SPE_DCMDPTR0;
	hypsa_cnn_pSrcEnd = hypsa_cnn_pSrcA + (((param->mode >> HSP_CNN_CFG_NB_IN_LINE_SHIFT) & HSP_CNN_CFG_MODE_MASK) * inLineSize8);
	hypsa_cnn_pSrc = hypsa_cnn_pSrcA + (inLineSize8 * param->k_h);
#ifdef PRINT_DBG_CNN
	printf("InA base 0x%x end 0x%x curr 0x%x\n", hypsa_cnn_pSrcA, hypsa_cnn_pSrcEnd, hypsa_cnn_pSrc);
#endif // PRINT_DBG_CNN
	hypsa_cnn_loop = inLineSize8 - ((padx0 + padx1) * param->in_c);
	hypsa_cnn_nbKblocks = nbBlocks;
	hypsa_cnn_bMode = bMode;
	hypsa_cnn_bCount = 0;
	if (hypsa_cnn_nbKblocks)
	{
		hypsa_cnn_kloop = (k_c * param->k_h * param->k_w) / nbBlocks;
		hypsa_cnn_pSrcB = (uint8_memb_t *) hsp_reg.SPE_DCMDPTR1;
		hypsa_cnn_pKidx = 1;
		//printf("pKe 0x%x hypsa_kloop %d\n", pKe, hypsa_cnn_kloop);
		hypsa_cnn_pKe = (uint8_t *) pKe;
	}
	hypsa_cnn_pOu = (uint8_t *) pOu;
	hypsa_cnn_pDst = (uint8_mema_t *) hsp_reg.SPE_DCMDPTR2;
	hypsa_cnn_pDstEnd = hypsa_cnn_pDst + (2 * outLineSize8);
	hypsa_cnn_pDstStart = hypsa_cnn_pDst;
	hypsa_cnn_oloop = outLineSize8;
	hypsa_cnn_stridey = param->stride_xy & 0xFF;
	hypsa_cnn_padx = padx0 * param->in_c;
	hypsa_cnn_pady = pady0;
	hypsa_cnn_countlines = param->k_h;
	hypsa_cnn_countmax = param->inp_h - pady1;
	//printf("hypsa_cnn_countmax %d = param->inp_h %d - pady1 %d\n", hypsa_cnn_countmax,  param->inp_h, pady1);
	int32_t *pOffset = (int32_t *) &(param->offIn);
	int8_t padV = (int8_t) *pOffset;
	padV = -padV;
	hypsa_cnn_padv = padV;
	hypsa_cnn_ouBlocks = 0;
	hypsa_cnn_ouh = 0;
	hypsa_cnn_ouw = param->ou_w;
	hypsa_cnn_ouBx = 0;
	hypsa_cnn_state = 0;
	hypsa_cnn_kcount = 0;
	hypsa_cnn_kcountmax = 0;
	hypsa_cnn_kh = param->k_h;
	hypsa_cnn_nbPadK0 = 0;
    hypsa_cnn_pDstb = 0;
    hypsa_cnn_pDstbEnd = 0;
    hypsa_cnn_pDstbStart = 0;
	if (bMode == 2)
	{
		// io1kl mode
		if (param->in_c & 0x3)
		{
			// Not aligned on 4, add extra kernels to 0
			hypsa_cnn_nbPadK0 = 4 - (( param->in_c) & 0x3);
		}
		hypsa_cnn_bMode = 2;
		hypsa_cnn_nbKblocks = 1;
		hypsa_cnn_kloop = param->k_h * param->k_w ; //param->k_h * param->k_w * 4; // one kernel per loop
		hypsa_cnn_pKeBase = (uint8_t *) pKe;
		// hypsa_cnn_pKe = (uint8_t *) (pKe + hypsa_cnn_kloop); // Put Ke to second block
		hypsa_cnn_pKe = (uint8_t *) (pKe + 4); // Put Ke to second block
		hypsa_cnn_pSrcB = (uint8_memb_t *) hsp_reg.SPE_DCMDPTR1;
		// hypsa_cnn_pKb = hypsa_cnn_pSrcB + (param->k_h * ((param->k_w * 4) + hypsa_cnn_nbPadK0)); // Put Ke to second block
		hypsa_cnn_pKb = hypsa_cnn_pSrcB +  4; // Put Ke to second block
		// hypsa_cnn_pSrcBEnd = hypsa_cnn_pSrcB + (param->k_h * param->ou_c * ((param->k_w * param->in_c) + hypsa_cnn_nbPadK0)); // Full kernels buffer
		hypsa_cnn_pSrcBEnd = hypsa_cnn_pSrcB + (param->k_h * param->k_w * (param->in_c + hypsa_cnn_nbPadK0)); // Full kernels buffer
		//if (hypsa_cnn_nbPadK0)
		//{
		//	hypsa_cnn_kloop = (param->k_w);
		//}
		hypsa_cnn_state = 1;
		hypsa_cnn_kcount = 4; // First kernel already loaded
		hypsa_cnn_kcountmax = param->ou_c + hypsa_cnn_nbPadK0; //param->ou_c;
/* 		hypsa_cnn_pDstb = (uint8_memb_t *) hsp_reg.SPE_DCMDPTR2; */
/* 		hypsa_cnn_pDstbEnd = hypsa_cnn_pDstb + (2 * outLineSize8); */
/* 		hypsa_cnn_pDstbStart = hypsa_cnn_pDstb; */
		hypsa_cnn_ocountmax = param->ou_c;
		hypsa_cnn_ouc = param->ou_c;
		hypsa_cnn_ocount = 1;
	} 
	else 
	{
		if (bMode == 3) 
		{
			// iio mode
			if (param->in_c & 0x3)
			{
				// Not aligned on 4, add extra kernels to 0
				hypsa_cnn_nbPadK0 = 4 - (( param->in_c) & 0x3);
			}
			hypsa_cnn_bMode = 3;
			uint32_t nbLinePerBlocks = nbBlocks;
			uint32_t nbLineInPerBlocks = (nbLinePerBlocks * hypsa_cnn_stridey) + param->k_h - hypsa_cnn_stridey; // For circular mode
			hypsa_cnn_icount = param->k_h; // Already 3 input lines loaded
			hypsa_cnn_icountmax = nbLineInPerBlocks + 1;
			hypsa_cnn_ocountmax = nbLinePerBlocks; //param->ou_c;
		        hypsa_cnn_ouc = param->ou_c;
			hypsa_cnn_ocount = 0;
			//hypsa_cnn_kloop = param->k_h * (param->in_c * param->k_w); // one kernel per loop
			hypsa_cnn_kloop = 4 * param->k_h * param->k_w; // 4 kernel per loop
			hypsa_cnn_pKeBase = (uint8_t *) pKe;
			hypsa_cnn_pKe = (uint8_t *) (pKe + 4); ; // Put Ke to second block
			hypsa_cnn_pSrcB = (uint8_memb_t *) hsp_reg.SPE_DCMDPTR1;
			// hypsa_cnn_pKb = hypsa_cnn_pSrcB + (param->k_h * ((param->k_w * param->in_c) + hypsa_cnn_nbPadK0)); // Put Ke to second block
			hypsa_cnn_pKb = hypsa_cnn_pSrcB +  (4 * param->k_h * param->k_w); // Put Ke to second block			
			// hypsa_cnn_pSrcBEnd = hypsa_cnn_pKb + (param->k_h * 2 * ((param->k_w * param->in_c) + hypsa_cnn_nbPadK0)); // Ping pong on kernels
			//hypsa_cnn_pSrcBEnd = hypsa_cnn_pSrcB + (param->k_h * param->k_w * (param->in_c + hypsa_cnn_nbPadK0)); // Full kernels buffer
			hypsa_cnn_pSrcBEnd = hypsa_cnn_pSrcB + (4 * param->k_h * param->k_w)*2; // Full kernels buffer
			// if (hypsa_cnn_nbPadK0)
			// {
				// hypsa_cnn_kloop = (param->k_w * param->in_c);
			// }
			hypsa_cnn_state = 1;
			hypsa_cnn_kcount = 4; // First kernel already loaded
			// hypsa_cnn_kcountmax =  param->in_c; //param->ou_c;
			hypsa_cnn_kcountmax = param->ou_c + hypsa_cnn_nbPadK0; //param->ou_c;
			hypsa_cnn_pDstb = (uint8_memb_t *) hsp_reg.SPE_DCMDPTR2;
			hypsa_cnn_pDstbEnd = hypsa_cnn_pDstb + (nbLinePerBlocks * outLineSize8);
			hypsa_cnn_pDstbStart = hypsa_cnn_pDstb;
			//printf("hypsa_cnn_pKidx %d hypsa_cnn_kloop %d hypsa_cnn_pKb 0x%x\n", hypsa_cnn_pKidx, hypsa_cnn_kloop, hypsa_cnn_pKb);
		} 
		else 
		{
			if ((hypsa_cnn_pIn == 0) || (bMode)) 
			{
				hypsa_cnn_bMode = param->inp_h;
				hypsa_cnn_bCount = param->k_h;
				uint32_t nbChanb = param->ou_c / nbBlocks;
				hypsa_cnn_ouc = param->ou_c;
				hypsa_cnn_nbchanb = nbChanb; ///< output channel number per block (size)
				hypsa_cnn_ouBcn = nbBlocks; ///< output channel number of blocks
				hypsa_cnn_ouBi = param->ou_c - nbChanb; // Jump for next x value
				hypsa_cnn_pKidx = nbChanb;
				hypsa_cnn_ouh = param->ou_h;
				hypsa_cnn_ouBz = 0;
				hypsa_cnn_pKb = hypsa_cnn_pSrcB + hypsa_cnn_kloop;
				hypsa_cnn_pSrcBEnd = hypsa_cnn_pKb + hypsa_cnn_kloop;
				hypsa_cnn_pDstEnd = hypsa_cnn_pDst + (2 * hypsa_cnn_nbchanb * param->ou_w);
				hypsa_cnn_pSrcEnd = hypsa_cnn_pSrcA + (param->inp_h * param->inp_w * param->in_c);
			}
		}
	}
#ifdef PRINT_DBG_CNN
	printf("hypsa_cnn_pSrc @0x%x hypsa_cnn_pIn @0x%x loop %d stride %d hypsa_cnn_pSrcEnd @0x%x\n",
	hypsa_cnn_pSrc, hypsa_cnn_pIn, hypsa_cnn_loop, hypsa_cnn_stridey, hypsa_cnn_pSrcEnd);
#endif // PRINT_DBG_CNN
}
#endif // HYP_UNITARY_TEST

/**
 * Hypsa CNN wait kernel data copy in internal memory
 */
void hypsa_cnn_wait_kblock()
{
  if (hypsa_cnn_bMode) {
    //printf("hypsa_cnn_wait_data %d\n", hypsa_cnn_pKidx);
    if ((hypsa_cnn_nbKblocks) || (hypsa_cnn_bMode == 2)) {
#ifdef PRINT_DBG_CNN
      printf("New K %d (0x%x) hypsa_cnn_kloop %d 0x%x (0x%x 0x%x)\n", hypsa_cnn_pKidx, hypsa_cnn_pKb,
             hypsa_cnn_kloop, hypsa_cnn_pKe, hypsa_cnn_pSrcB, hypsa_cnn_pSrcBEnd);
#endif // PRINT_DBG_CNN
      if (hypsa_cnn_nbPadK0) {
        if (hypsa_cnn_dw) {
 			if (hypsa_cnn_nbPadK0  && ((hypsa_cnn_kcount +4) >= hypsa_cnn_kcountmax))
			{
    			int8_t *ptmpKe = (int8_t *)hypsa_cnn_pKe;
	    		int8_memb_t  *ptmpKb = (int8_memb_t  *)hypsa_cnn_pKb;
				// hypsa_cnn_kloop = (param->k_w);
				for (uint32_t j = 0; j < hypsa_cnn_kloop; j++)
				{
					// HSP_MEMCPY(pSrcB, ptmp, 4);
					// pSrcB += (k_c);
					// ptmp += (k_c);
					ptmpKb[0] = ptmpKe[0];
					ptmpKb[1] = ptmpKe[1];
					ptmpKb[2] = ptmpKe[2];
					ptmpKb[3] = ptmpKe[3];
					if (hypsa_cnn_nbPadK0 >= 1) ptmpKb[3] = 0;
					if (hypsa_cnn_nbPadK0 >= 2) ptmpKb[2] = 0;
					if (hypsa_cnn_nbPadK0 >= 3) ptmpKb[1] = 0;
					
					// pad with 0
					
					//ptmpKb += (hypsa_cnn_ocountmax + hypsa_cnn_nbPadK0); // k_c
					//ptmpKe += hypsa_cnn_ocountmax;
					ptmpKb += (hypsa_cnn_ouc + hypsa_cnn_nbPadK0); // k_c
					ptmpKe += hypsa_cnn_ouc;
					
				}
				hypsa_cnn_pKe += 4;
				hypsa_cnn_pKb += (hypsa_cnn_nbPadK0 + 4);
			}
			else
			{
				int8_t *ptmpKe = (int8_t *)hypsa_cnn_pKe;
				int8_memb_t  *ptmpKb = (int8_memb_t  *)hypsa_cnn_pKb;
				
				for (uint32_t j = 0; j < hypsa_cnn_kloop; j++)
				{
					// HSP_MEMCPY(pSrcB, ptmp, 4);
					// pSrcB += (k_c);
					// ptmp += (k_c);
					ptmpKb[0] = ptmpKe[0];
					ptmpKb[1] = ptmpKe[1];
					ptmpKb[2] = ptmpKe[2];
					ptmpKb[3] = ptmpKe[3];
					//ptmpKb += hypsa_cnn_ocountmax + hypsa_cnn_nbPadK0; // k_c
					//ptmpKe += hypsa_cnn_ocountmax;
					ptmpKb += hypsa_cnn_ouc + hypsa_cnn_nbPadK0; // k_c
					ptmpKe += hypsa_cnn_ouc;
				}
				hypsa_cnn_pKe += 4;
				hypsa_cnn_pKb += 4;
			}
		}
        else {
          // Not aligned on 4, add extra kernels to 0
          for (uint32_t i = 0; i < hypsa_cnn_kh; i++) {
            for (uint32_t j = 0; j < hypsa_cnn_kloop; j++) {
              *hypsa_cnn_pKb++ = *hypsa_cnn_pKe++;
            }
            for (uint32_t kp = 0; kp < hypsa_cnn_nbPadK0; kp++) {
              *hypsa_cnn_pKb++ = 0;
            }
          }
        }
      } else {
		  // DEPTHWISE CASE !! Kernel are copied by column 4 by 4 !!
		  if (hypsa_cnn_dw)
		  {
		      if ((hypsa_cnn_bMode == 3) && ((hypsa_cnn_kcount +4) <= hypsa_cnn_kcountmax))
		      {
				int8_t *ptmpKe = (int8_t *)hypsa_cnn_pKe;
				int8_memb_t  *ptmpKb = (int8_memb_t  *)hypsa_cnn_pKb;
				// copy kernel by kernel
				for (uint32_t i = 0; i < (hypsa_cnn_kloop/4); i++)
				{
					// *hypsa_cnn_pKb++ = *hypsa_cnn_pKe++;
					ptmpKb[0] = ptmpKe[0];
					ptmpKb[1] = ptmpKe[1];
					ptmpKb[2] = ptmpKe[2];
					ptmpKb[3] = ptmpKe[3];
					ptmpKb += 4;
					//ptmpKe += hypsa_cnn_ocountmax;
					ptmpKe += hypsa_cnn_ouc;
					hypsa_cnn_pKb += 4;
				}
				hypsa_cnn_pKe += 4;
		      }
		      else
		      {
		          if (hypsa_cnn_bMode == 3) 
		          {
				int8_t *ptmpKe = (int8_t *)hypsa_cnn_pKe;
				int8_memb_t  *ptmpKb = (int8_memb_t  *)hypsa_cnn_pKb;
				
				// ESSAI VAL for (uint32_t j = 0; j < hypsa_cnn_kloop; j++)
				for (uint32_t j = 0; j < (hypsa_cnn_kloop/4); j++)
				{
					// HSP_MEMCPY(pSrcB, ptmp, 4);
					// pSrcB += (k_c);
					// ptmp += (k_c);
					ptmpKb[0] = ptmpKe[0];
					ptmpKb[1] = ptmpKe[1];
					ptmpKb[2] = ptmpKe[2];
					ptmpKb[3] = ptmpKe[3];
					//ptmpKb += hypsa_cnn_ocountmax; // k_c
					//ptmpKe += hypsa_cnn_ocountmax;
					ptmpKb += 4; //hypsa_cnn_ouc;
					ptmpKe += hypsa_cnn_ouc;
				        hypsa_cnn_pKb += 4;		        
				}
				hypsa_cnn_pKe += 4;
			  }
		          else
		          {
				int8_t *ptmpKe = (int8_t *)hypsa_cnn_pKe;
				int8_memb_t  *ptmpKb = (int8_memb_t  *)hypsa_cnn_pKb;
				
				for (uint32_t j = 0; j < hypsa_cnn_kloop; j++)
				{
					// HSP_MEMCPY(pSrcB, ptmp, 4);
					// pSrcB += (k_c);
					// ptmp += (k_c);
					ptmpKb[0] = ptmpKe[0];
					ptmpKb[1] = ptmpKe[1];
					ptmpKb[2] = ptmpKe[2];
					ptmpKb[3] = ptmpKe[3];
					//ptmpKb += hypsa_cnn_ocountmax; // k_c
					//ptmpKe += hypsa_cnn_ocountmax;
					ptmpKb += hypsa_cnn_ouc; // k_c
					ptmpKe += hypsa_cnn_ouc;
				}
				hypsa_cnn_pKe += 4;
				hypsa_cnn_pKb += 4;
		          }
		      }
		  }
		  else
		  {
			for (uint32_t i = 0; i < hypsa_cnn_kloop; i++) {
			*hypsa_cnn_pKb++ = *hypsa_cnn_pKe++;
			}
		  }
      }
      if (hypsa_cnn_pKb >= hypsa_cnn_pSrcBEnd) {
        hypsa_cnn_pKb = hypsa_cnn_pSrcB;
      }
      return;
    }
  } else {
    // Load next kernel block
    if (hypsa_cnn_nbPadK0) {
      // Not aligned on 4, add extra kernels to 0
      for (uint32_t i = 0; i < hypsa_cnn_kh; i++) {
        for (uint32_t j = 0; j < hypsa_cnn_kloop; j++) {
          *hypsa_cnn_pKb++ = *hypsa_cnn_pKe++;
        }
        for (uint32_t kp = 0; kp < hypsa_cnn_nbPadK0; kp++) {
          *hypsa_cnn_pKb++ = 0;
        }
      }
    } else {
      for (uint32_t i = 0; i < hypsa_cnn_kloop; i++) {
        *hypsa_cnn_pKb++ = *hypsa_cnn_pKe++;
      }
    }
    if (hypsa_cnn_pKb == hypsa_cnn_pSrcBEnd) {
      hypsa_cnn_pKb = hypsa_cnn_pSrcB;
    }
    return;
  }
}


/**
 * Hypsa CNN wait input data copy in internal memory
 */
void hypsa_cnn_wait_data()
{
  //printf("hypsa_cnn_wait_data %d\n", hypsa_cnn_pKidx);
  if (hypsa_cnn_bMode == 10) {
    // Fully connected
    hypsa_cnn_wait_kblock();
    return;
  } else if (hypsa_cnn_bMode == 3) {
    // iio mode
    if (hypsa_cnn_state == 1) {
      if (hypsa_cnn_kcount == 0) {
        // Get first kernel for this first new block
#ifdef PRINT_DBG_CNN
        printf("hypsa_cnn_state 2 line %d (%d)\n", hypsa_cnn_kcount, hypsa_cnn_kcountmax);
#endif // PRINT_DBG_CNN
        hypsa_cnn_wait_kblock();
        if (hypsa_cnn_dw) {
          hypsa_cnn_kcount += 4;
        } else {
          hypsa_cnn_kcount++;
        }
        // and load first line for this new block
        hypsa_cnn_icount = hypsa_cnn_kh;
        if (hypsa_cnn_padx || hypsa_cnn_pady) {
          hypsa_cnn_countlines++;
          for (uint32_t sidx = 0; sidx < hypsa_cnn_stridey; sidx++) chess_loop_range(1,) {
            if (hypsa_cnn_countlines > hypsa_cnn_countmax) {
#ifdef PRINT_DBG_CNN
              printf("WBP @0x%x 0x%08x %d\n", hypsa_cnn_pSrc, (int32_t) *hypsa_cnn_pIn, hypsa_cnn_loop);
#endif // PRINT_DBG_CNN
              // Last lines pad
              for (uint32_t i = 0; i < (hypsa_cnn_loop + (2 * hypsa_cnn_padx)); i++) chess_loop_range(1,) {
                *hypsa_cnn_pSrc++ = hypsa_cnn_padv;
              }
            } else {
#ifdef PRINT_DBG_CNN
              printf("WB @0x%x 0x%08x %d\n", hypsa_cnn_pSrc, (int32_t) *hypsa_cnn_pIn, hypsa_cnn_loop);
#endif // PRINT_DBG_CNN
              // First column pad
              for (uint32_t c = 0; c < hypsa_cnn_padx; c++) chess_loop_range(1,) {
                *hypsa_cnn_pSrc++ = hypsa_cnn_padv;
              }
              for (uint32_t i = 0; i < hypsa_cnn_loop; i++) chess_loop_range(1,) {
                *hypsa_cnn_pSrc++ = *hypsa_cnn_pIn++;
              }
              // Last column pad
              for (uint32_t c = 0; c < hypsa_cnn_padx; c++) chess_loop_range(1,) {
                *hypsa_cnn_pSrc++ = hypsa_cnn_padv;
              }
              if (hypsa_cnn_pSrc == hypsa_cnn_pSrcEnd) {
                hypsa_cnn_pSrc = hypsa_cnn_pSrcA;
              }
            }
          }
        } else {
          hypsa_cnn_countlines++;
          for (uint32_t sidx = 0; sidx < hypsa_cnn_stridey; sidx++) chess_loop_range(1,) {
#ifdef PRINT_DBG_CNN
            printf("WB @0x%x 0x%08x %d\n", hypsa_cnn_pSrc, (int32_t) *hypsa_cnn_pIn, hypsa_cnn_loop);
#endif // PRINT_DBG_CNN
            for (uint32_t i = 0; i < hypsa_cnn_loop; i++) chess_loop_range(1,) {
              *hypsa_cnn_pSrc++ = *hypsa_cnn_pIn++;
            }
            if (hypsa_cnn_pSrc == hypsa_cnn_pSrcEnd) {
              hypsa_cnn_pSrc = hypsa_cnn_pSrcA;
            }
          }
        }
      }
      // State == 1: load all input lines
#ifdef PRINT_DBG_CNN
      printf("hypsa_cnn_state 1 line %d (%d) (%d, %d)\n", hypsa_cnn_countlines, (hypsa_cnn_countmax + hypsa_cnn_pady),
             hypsa_cnn_icount, hypsa_cnn_icountmax);
#endif // PRINT_DBG_CNN
      // In first state, get input line
      if (hypsa_cnn_countlines >= (hypsa_cnn_countmax + hypsa_cnn_pady)) {
        // End of full input, got to step 2
        hypsa_cnn_state = 2;
      }
      hypsa_cnn_icount += hypsa_cnn_stridey;
      if (hypsa_cnn_icount >= hypsa_cnn_icountmax) {
        hypsa_cnn_state = 2;
        hypsa_cnn_icount = 0; // Reset icount
      }
    }
    if (hypsa_cnn_state == 2) {
      // In second state, get kernels
#ifdef PRINT_DBG_CNN
      printf("hypsa_cnn_state 2 line %d (%d)\n", hypsa_cnn_kcount, hypsa_cnn_kcountmax);
#endif // PRINT_DBG_CNN
      hypsa_cnn_wait_kblock();
          //hypsa_cnn_kcount++;
      if (hypsa_cnn_dw)
	  {
		  hypsa_cnn_kcount+= 4;
	  }
      else
	  {
		  hypsa_cnn_kcount++;
      }          
//      if (hypsa_cnn_kcount == hypsa_cnn_kcountmax) {
      if (hypsa_cnn_kcount >= hypsa_cnn_kcountmax) {
        hypsa_cnn_kcount = 0;
        hypsa_cnn_state = 3;
      }
      return;
    } else if (hypsa_cnn_state > 2) {
      // In third state, get output
      //printf("hypsa_cnn_state 3\n");
      return;
    }
  } else if (hypsa_cnn_bMode == 2) {
    // io1kl mode
    if (hypsa_cnn_state == 1) {
#ifdef PRINT_DBG_CNN
      printf("hypsa_cnn_state 1 line %d (%d) (%d, %d)\n", hypsa_cnn_countlines, (hypsa_cnn_countmax + hypsa_cnn_pady),
             hypsa_cnn_icount, hypsa_cnn_icountmax);
#endif // PRINT_DBG_CNN
      // In first state, get kernels
#ifdef PRINT_DBG_CNN
      printf("hypsa_cnn_state 2 line %d (%d)\n", hypsa_cnn_kcount, hypsa_cnn_kcountmax);
#endif // PRINT_DBG_CNN
      hypsa_cnn_wait_kblock();
      if (hypsa_cnn_dw)
	  {
		  hypsa_cnn_kcount+= 4;
	  }
      else
	  {
		  hypsa_cnn_kcount++;
      }
      if (hypsa_cnn_kcount == hypsa_cnn_kcountmax) {
        hypsa_cnn_kcount = 0;
        hypsa_cnn_state = 2;
      }
      return;
    } else if (hypsa_cnn_state > 1) {
      // In third state, get input and output
    }
  } else if (hypsa_cnn_bMode) {
    if (hypsa_cnn_bCount >= hypsa_cnn_bMode) {
      return;
    }
    hypsa_cnn_bCount += hypsa_cnn_stridey;
  }
  if (hypsa_cnn_pIn) {
    if (hypsa_cnn_pw) {
      // For pointwize remove lines strides
      for (uint32_t i = 0; i < hypsa_cnn_loop; i++) chess_loop_range(1,) {
        *hypsa_cnn_pSrc++ = *hypsa_cnn_pIn++;
      }
      if (hypsa_cnn_pSrc == hypsa_cnn_pSrcEnd) {
        hypsa_cnn_pSrc = hypsa_cnn_pSrcA;
      }
      for (uint32_t sidx = 1; sidx < hypsa_cnn_stridey; sidx++) {
        hypsa_cnn_countlines++;
#ifdef PRINT_DBG_CNN
        printf("W @0x%x 0x%08x %d\n", hypsa_cnn_pSrc, (int32_t) *hypsa_cnn_pIn, hypsa_cnn_loop);
#endif // PRINT_DBG_CNN
        hypsa_cnn_pIn += hypsa_cnn_loop;
      }
    } else {
#ifdef OLD_CODE
    if (hypsa_cnn_nbKblocks) {
      if (hypsa_cnn_pKidx == hypsa_cnn_nbKblocks) {
        hypsa_cnn_pKidx = 0;
      } else {
        //printf("New K %d (0x%x)\n", hypsa_cnn_pKidx, hypsa_cnn_pSrcB);
        for (uint32_t i = 0; i < hypsa_cnn_kloop; i++) {
          hypsa_cnn_pSrcB[i] = hypsa_cnn_pKe[((hypsa_cnn_kloop * hypsa_cnn_pKidx) + i)];
        }
        hypsa_cnn_pKidx++;
        return;
      }
    }
#endif // OLD_CODE
    //printf("New input (0x%x)\n", hypsa_cnn_pSrc);
    if (hypsa_cnn_padx || hypsa_cnn_pady) {
      for (uint32_t sidx = 0; sidx < hypsa_cnn_stridey; sidx++) chess_loop_range(1,) {
        hypsa_cnn_countlines++;
        //printf("hypsa_cnn_countlines %d, hypsa_cnn_countmax %d\n", hypsa_cnn_countlines, hypsa_cnn_countmax);
        if (hypsa_cnn_countlines > hypsa_cnn_countmax) {
          //printf("Last lines pad\n");
#ifdef PRINT_DBG_CNN
          printf("WP @0x%x 0x%08x %d\n", hypsa_cnn_pSrc, (int32_t) *hypsa_cnn_pIn, hypsa_cnn_loop);
#endif // PRINT_DBG_CNN
          // Last lines pad
          for (uint32_t i = 0; i < (hypsa_cnn_loop + (2 * hypsa_cnn_padx)); i++) chess_loop_range(1,) {
            *hypsa_cnn_pSrc++ = hypsa_cnn_padv;
          }
        } else {
#ifdef PRINT_DBG_CNN
          printf("W @0x%x 0x%08x %d\n", hypsa_cnn_pSrc, (int32_t) *hypsa_cnn_pIn, hypsa_cnn_loop);
#endif // PRINT_DBG_CNN
          // First column pad
          //printf("hypsa_cnn_padx %d hypsa_cnn_loop %d\n", hypsa_cnn_padx, hypsa_cnn_loop);
          for (uint32_t c = 0; c < hypsa_cnn_padx; c++) chess_loop_range(1,) {
            *hypsa_cnn_pSrc++ = hypsa_cnn_padv;
          }
          for (uint32_t i = 0; i < hypsa_cnn_loop; i++) chess_loop_range(1,) {
            *hypsa_cnn_pSrc++ = *hypsa_cnn_pIn++;
          }
          // Last column pad
          for (uint32_t c = 0; c < hypsa_cnn_padx; c++) chess_loop_range(1,) {
            *hypsa_cnn_pSrc++ = hypsa_cnn_padv;
          }
        }
        if (hypsa_cnn_pSrc == hypsa_cnn_pSrcEnd) {
          hypsa_cnn_pSrc = hypsa_cnn_pSrcA;
        }
      }
    } else {
      for (uint32_t sidx = 0; sidx < hypsa_cnn_stridey; sidx++) chess_loop_range(1,) {
        hypsa_cnn_countlines++;
#ifdef PRINT_DBG_CNN
        printf("W @0x%x 0x%08x %d\n", hypsa_cnn_pSrc, (int32_t) *hypsa_cnn_pIn, hypsa_cnn_loop);
#endif // PRINT_DBG_CNN
        for (uint32_t i = 0; i < hypsa_cnn_loop; i++) chess_loop_range(1,) {
          *hypsa_cnn_pSrc++ = *hypsa_cnn_pIn++;
        }
        if (hypsa_cnn_pSrc == hypsa_cnn_pSrcEnd) {
          hypsa_cnn_pSrc = hypsa_cnn_pSrcA;
        }
      }
    }
    }
  }
}

/**
 * Hypsa CNN copy output data in external buffer
 */
void hypsa_cnn_next_data()
{
  if (hypsa_cnn_bMode == 3) {
    // iio mode
    if (hypsa_cnn_state == 3) {
      hypsa_cnn_state = 4;
    } else if (hypsa_cnn_state == 4) {
#ifdef PRINT_DBG_CNN
      printf("hypsa_cnn_state 4 line %d (%d)\n", hypsa_cnn_ocount, hypsa_cnn_ocountmax);
#endif // PRINT_DBG_CNN
      for (uint32_t i = 0; i < hypsa_cnn_oloop; i++) {
        *hypsa_cnn_pOu++ = *hypsa_cnn_pDstb++;
      }
      if (hypsa_cnn_pDstb == hypsa_cnn_pDstbEnd) {
        hypsa_cnn_pDstb = hypsa_cnn_pDstbStart;
      }
      hypsa_cnn_ocount++;
      if (hypsa_cnn_ocountmax == hypsa_cnn_ocount) {
        hypsa_cnn_ocount = 0;
        hypsa_cnn_state = 1;
        // Reset Kernel load
        hypsa_cnn_pKe = hypsa_cnn_pKeBase;
      }
    }
  } else if (hypsa_cnn_ouh) {
    if (hypsa_cnn_ouBx == hypsa_cnn_ouh) {
      // Whole block done
      hypsa_cnn_ouBx = 0;
      hypsa_cnn_ouBz += hypsa_cnn_pKidx;
    }
    //printf("hypsa_cnn_next_data new line 0x%x %d %d %d %d\n", hypsa_cnn_pOu, hypsa_cnn_ouBx, hypsa_cnn_ouw, hypsa_cnn_nbchanb, hypsa_cnn_ouBz);
    uint8_t *pDst = hypsa_cnn_pOu + (hypsa_cnn_ouBx * hypsa_cnn_ouw * hypsa_cnn_ouc) + hypsa_cnn_ouBz;
/*     printf("hypsa_cnn_next_data K %d (0x%x) hypsa_cnn_nbchanb %d %d %d (0x%x)\n", hypsa_cnn_ouBx, pDst, hypsa_cnn_nbchanb, hypsa_cnn_ouw, */
/*            hypsa_cnn_ouBi, hypsa_cnn_pDst); */
    for (uint32_t tmpx = 0; tmpx < hypsa_cnn_ouw; tmpx++) {
      // For each X in the width of output
      //printf("hypsa_cnn_next_data cp @0x%x from 0x%x %d\n", pDst, hypsa_cnn_pDst, hypsa_cnn_nbchanb);
      for (uint32_t tmpc = 0; tmpc < hypsa_cnn_nbchanb; tmpc++) {
        // For each channel in this block
        *pDst++ = *hypsa_cnn_pDst++;
      }
      pDst += hypsa_cnn_ouBi; // Jump to next X
    }
    hypsa_cnn_ouBx++;
    if (hypsa_cnn_pDst == hypsa_cnn_pDstEnd) {
      //printf("hypsa_cnn_next_data Go back to ping\n");
      hypsa_cnn_pDst = hypsa_cnn_pDstStart;
    }
  } else if ((hypsa_cnn_bMode == 2) && (hypsa_cnn_state < 3)) {
    // io1kl mode
    if (hypsa_cnn_state == 2) {
      hypsa_cnn_state = 3;
    }
  } else if (hypsa_cnn_pool) {
    // Pooling mode pDst is in MEMB
    for (uint32_t i = 0; i < hypsa_cnn_oloop; i++) {
      *hypsa_cnn_pOu++ = *hypsa_cnn_pDstb++;
    }
    if (hypsa_cnn_pDstb == hypsa_cnn_pDstbEnd) {
      hypsa_cnn_pDstb = hypsa_cnn_pDstbStart;
    }
  } else {
    for (uint32_t i = 0; i < hypsa_cnn_oloop; i++) {
      *hypsa_cnn_pOu++ = *hypsa_cnn_pDst++;
    }
    if (hypsa_cnn_pDst == hypsa_cnn_pDstEnd) {
      //printf("hypsa_cnn_next_data Go back to ping\n");
      hypsa_cnn_pDst = hypsa_cnn_pDstStart;
    }
  }
}

#ifndef HYP_UNITARY_TEST
/**
 * For conv2D hypsa test, get global var in payload
 */
void hypsa_cnn_convpw2_set_var(int8_t *pIn, int8_t *pKe, int8_t *pOu, uint32_t circiSize, uint32_t bMode)
{
  hypsa_cnn_pw = 1;
  hypsa_cnn_pool = 0;
  hyp_cnn_pw_param_t *param = (hyp_cnn_pw_param_t *) hsp_mb_pay_tab;
  uint32_t inLineSize8 = param->in_c * param->inp_w; // 1 input line
  uint32_t outLineSize8 = param->ou_c * param->ou_w; // 1 ouput line
  uint32_t k_c = param->in_c * param->ou_c;
  hypsa_cnn_pIn = (uint8_t *) pIn;
  hypsa_cnn_pSrcA = (uint8_mema_t *) hsp_reg.SPE_DCMDPTR0;
  hypsa_cnn_pSrcEnd = hypsa_cnn_pSrcA + (circiSize * inLineSize8);
  hypsa_cnn_pSrc = hypsa_cnn_pSrcA + inLineSize8;
      if (hypsa_cnn_pSrc == hypsa_cnn_pSrcEnd) {
        hypsa_cnn_pSrc = hypsa_cnn_pSrcA;
      }
#ifdef PRINT_DBG_CNN
  printf("InA base 0x%x end 0x%x curr 0x%x\n", hypsa_cnn_pSrcA, hypsa_cnn_pSrcEnd, hypsa_cnn_pSrc);
#endif // PRINT_DBG_CNN
  hypsa_cnn_loop = inLineSize8;
  hypsa_cnn_nbKblocks = 1;
  hypsa_cnn_bMode = bMode;
  hypsa_cnn_bCount = 0;
  hypsa_cnn_pOu = (uint8_t *) pOu;
  hypsa_cnn_pDst = (uint8_mema_t *) hsp_reg.SPE_DCMDPTR2;
  hypsa_cnn_pDstEnd = hypsa_cnn_pDst + (2 * outLineSize8);
  hypsa_cnn_pDstStart = hypsa_cnn_pDst;
  hypsa_cnn_oloop = outLineSize8;
  hypsa_cnn_stridey = param->stridey;
  hypsa_cnn_padx = 0;
  hypsa_cnn_pady = 0;
  hypsa_cnn_countlines = 1;
  hypsa_cnn_countmax = param->inp_h;
  hypsa_cnn_ouBlocks = 0;
  hypsa_cnn_ouh = 0;
  hypsa_cnn_ouw = param->ou_w;
  hypsa_cnn_ouBx = 0;
  hypsa_cnn_state = 0;
  hypsa_cnn_kcount = 0;
  hypsa_cnn_kcountmax = 0;
  hypsa_cnn_kh = 1;
  hypsa_cnn_nbPadK0 = 0;
  if (bMode == 2) {
    // io1kl mode
    if (param->in_c & 0x3) {
      // Not aligned on 4, add extra kernels to 0
      hypsa_cnn_nbPadK0 = 4 - (param->in_c & 0x3);
    }
    hypsa_cnn_bMode = 2;
    hypsa_cnn_nbKblocks = 1;
    hypsa_cnn_kloop = param->in_c; // one kernel per loop
    hypsa_cnn_pKeBase = (uint8_t *) pKe;
    hypsa_cnn_pKe = (uint8_t *) (pKe + hypsa_cnn_kloop); // Put Ke to second block
    hypsa_cnn_pSrcB = (uint8_memb_t *) hsp_reg.SPE_DCMDPTR1;
    hypsa_cnn_pKb = hypsa_cnn_pSrcB + (param->in_c + hypsa_cnn_nbPadK0); // Put Ke to second block
    hypsa_cnn_pSrcBEnd = hypsa_cnn_pSrcB + (param->ou_c * (param->in_c + hypsa_cnn_nbPadK0)); // Full kernels buffer
    if (hypsa_cnn_nbPadK0) {
      hypsa_cnn_kloop = param->in_c;
    }
    hypsa_cnn_state = 1;
    hypsa_cnn_kcount = 1; // First kernel already loaded
    hypsa_cnn_kcountmax = param->ou_c;
    hypsa_cnn_pDstb = (uint8_memb_t *) hsp_reg.SPE_DCMDPTR2;
    hypsa_cnn_pDstbEnd = hypsa_cnn_pDstb + (2 * outLineSize8);
    hypsa_cnn_pDstbStart = hypsa_cnn_pDstb;
    hypsa_cnn_ocountmax = param->ou_c;
    hypsa_cnn_ocount = 1;
  } else if (bMode == 3) {
    // iio mode
    if (param->in_c & 0x3) {
      // Not aligned on 4, add extra kernels to 0
      hypsa_cnn_nbPadK0 = 4 - (param->in_c & 0x3);
    }
    hypsa_cnn_bMode = 3;
    uint32_t nbLinePerBlocks = circiSize;
    uint32_t nbLineInPerBlocks = nbLinePerBlocks * hypsa_cnn_stridey; // For circular mode
    hypsa_cnn_icount = 1; // Already 3 input lines loaded
    hypsa_cnn_icountmax = nbLineInPerBlocks + 1;
    hypsa_cnn_ocountmax = nbLinePerBlocks;
    hypsa_cnn_ocount = 0;
    hypsa_cnn_kloop = param->in_c; // one kernel per loop
    hypsa_cnn_pKeBase = (uint8_t *) pKe;
    hypsa_cnn_pKe = (uint8_t *) (pKe + hypsa_cnn_kloop); // Put Ke to second block
    hypsa_cnn_pSrcB = (uint8_memb_t *) hsp_reg.SPE_DCMDPTR1;
    hypsa_cnn_pKb = hypsa_cnn_pSrcB + (param->in_c + hypsa_cnn_nbPadK0); // Put Ke to second block
    hypsa_cnn_pSrcBEnd = hypsa_cnn_pSrcB + (2 * (param->in_c + hypsa_cnn_nbPadK0)); // Full kernels buffer
    if (hypsa_cnn_nbPadK0) {
      hypsa_cnn_kloop = param->in_c;
    }
    hypsa_cnn_state = 1;
    hypsa_cnn_kcount = 1; // First kernel already loaded
    hypsa_cnn_kcountmax = param->ou_c;
    hypsa_cnn_pDstb = (uint8_memb_t *) hsp_reg.SPE_DCMDPTR2;
    hypsa_cnn_pDstbEnd = hypsa_cnn_pDstb + (nbLinePerBlocks * outLineSize8);
    hypsa_cnn_pDstbStart = hypsa_cnn_pDstb;
  }
}
#endif // HYP_UNITARY_TEST



/* ***************************************************************** */
/* For hypsa only */
/* ***************************************************************** */

int8_t *hypsa_pIn;
int8_mema_t *hypsa_pSrc;
int8_mema_t *hypsa_pSrcEnd;
int8_mema_t *hypsa_pSrcA;
uint32_t hypsa_loop;
uint32_t hypsa_pKidx;
uint32_t hypsa_kloop;
int8_t *hypsa_pOu;
int8_mema_t *hypsa_pDst;
int8_mema_t *hypsa_pDstEnd;
int8_mema_t *hypsa_pDstB;
uint32_t hypsa_oloop;
uint32_t stride_h;
uint32_t firstXfert;
uint32_t hypsa_first;
uint32_t hypsa_nbLine;
int8_t hypsa_fullBuffer;

/**
 * For convpw hypsa test, get global var in payload
 */
void hypsa_cnn_convpw_set_var(int8_t *pInput8, int8_mema_t *pCurrSrc,
							  int8_t *pTmpOutput, int8_mema_t *pCurrDst,
							  int8_t fullBuffer, uint32_t nbLineinBuffer)
{
	hyp_cnn_pw_param_t *param = (hyp_cnn_pw_param_t *) hsp_mb_pay_tab;

	hypsa_pIn = (int8_t *)pInput8;
	hypsa_pSrc = (int8_mema_t *)pCurrSrc;
	hypsa_pSrcA = (int8_mema_t *)pCurrSrc;
	hypsa_loop = ((param->in_c * param->inp_w));
	hypsa_nbLine = nbLineinBuffer;
	hypsa_pDst = (int8_mema_t *)pCurrDst;
	hypsa_pDstB = (int8_mema_t *)pCurrDst;
	hypsa_oloop = (param->ou_c * param->ou_w);
	if (fullBuffer)
	{
		hypsa_oloop = hypsa_oloop * param->ou_h;
		hypsa_pSrcEnd = (int8_mema_t *)pCurrSrc + (((param->in_c * param->inp_w * param->inp_h )));
		hypsa_pDstEnd = hypsa_pDst + ((param->ou_c * param->ou_w * param->ou_h));
	}
	else
	{
		hypsa_pSrcEnd = (int8_mema_t *)pCurrSrc + (((param->in_c * param->inp_w))*nbLineinBuffer); // nbLine lines
		hypsa_pDstEnd = (int8_mema_t *)hypsa_pDst + ((param->ou_c * param->ou_w)*nbLineinBuffer); // nbLine lines
	}
	hypsa_pOu = pTmpOutput;
	stride_h = param->stridey;
	hypsa_fullBuffer = fullBuffer;
	/*
	printf("param->ou_c=%d x param->ou_w=%d  = %d\n", param->ou_c, param->ou_w, param->ou_c*param->ou_w);
	printf("hypsa_pIn=0x%08x hypsa_pSrcA=0x%08x hypsa_pSrcEnd=0x%08x hypsa_pSrc=0x%08x hypsa_loop=%d hypsa_oloop=%d \n",
		hypsa_pIn,hypsa_pSrcA, hypsa_pSrcEnd, hypsa_pSrc,hypsa_loop ,hypsa_oloop);
	*/
}

void hypsa_pw_wait_data()
{
	//ll_set_c2hmsgf(hhsp); // Only for synchro
	// Set bit in HSP_C2HSEMR register
	//HSPHandle.Instance->C2HSEMR = 1;
	if (hypsa_fullBuffer) // Copy all data in buffer
	{
		for (int j = 0; j < hypsa_nbLine; j++)
		{
			for (uint32_t i = 0; i < hypsa_loop; i++)
			{
				*hypsa_pSrc++ = *hypsa_pIn++;
			}
			if (stride_h > 1)
			{
				hypsa_pIn += (hypsa_loop * (stride_h - 1));
			}
		}
	}
	else
	{
		hypsa_pKidx = 0;
		//printf("New input hypsa_pIn=(0x%x)\n", hypsa_pIn);
		//printf("hypsa_pSrc=(0x%x)  hypsa_pIn=(0x%x) hypsa_loop=%d\n", hypsa_pSrc, hypsa_pIn,hypsa_loop);
		for (uint32_t i = 0; i < hypsa_loop; i++)
		{
#if 0
			if ((i!=0) && (i%8)==0) printf("\n");
			printf("0x%08x, ", *hypsa_pIn);
#endif
			*hypsa_pSrc++ = *hypsa_pIn++;
		}
#if 0
		printf("\n");
#endif

		if (hypsa_pSrc == hypsa_pSrcEnd)
		{
			hypsa_pSrc = hypsa_pSrcA;
		}
		if (stride_h > 1)
		{
			hypsa_pIn += (hypsa_loop * (stride_h - 1));
		}
	}
}

/* For hypsa only */
void hypsa_pw_next_data()
{
  //while (HSPHandle.Instance->C2HSEMR); // wait conv2d done
	//PDEBUG("copying %d data\n",hypsa_oloop);
	for (uint32_t i = 0; i < hypsa_oloop; i++)
	{
		*hypsa_pOu++ = *hypsa_pDst++;
	}
	if (hypsa_pDst == hypsa_pDstEnd)
	{
	//PDEBUG("hypsa_pDst=0x%08x hypsa_pDstB=0x%08x\n",hypsa_pDst,hypsa_pDstB);
	hypsa_pDst = hypsa_pDstB;
	}
}

void hypsa_dw_wait_data()
{
	// For stride , the first slice is fully copied

	//ll_set_c2hmsgf(hhsp); // Only for synchro
	// Set bit in HSP_C2HSEMR register
	//HSPHandle.Instance->C2HSEMR = 1;

	if (hypsa_first)
	{
		hypsa_first = 0;
		return;
	}
	//printf("New input (0x%x)\n", hypsa_pSrc);
	for (uint32_t j = 0; j < hypsa_nbLine; j++)
	{
		//printf("Coying %dieme line\n",j);
		for (uint32_t i = 0; i < hypsa_loop; i++)
		{
			*hypsa_pSrc++ = *hypsa_pIn++;
		}
		if (hypsa_pSrc == hypsa_pSrcEnd)
		{
			//printf("End of circular buffer, set pointer to start buffer\n");
			hypsa_pSrc = hypsa_pSrcA;
		}
	}
}

/* For hypsa only */
void hypsa_dw_next_data()
{
  //while (HSPHandle.Instance->C2HSEMR); // wait conv2d done

	for (uint32_t i = 0; i < hypsa_oloop; i++)
	{
		*hypsa_pOu++ = *hypsa_pDst++;
	}
	if (hypsa_pDst == hypsa_pDstEnd)
	{
		hypsa_pDst = hypsa_pDstB;
	}
}
#endif // HYPSA_SIMU

/**
 * Return HSP BRAM A address
 * @param[in] bramab  BRAMAB address to convert
 * @retval            Return BRAM A address
 */
uint32_t get_brama_addr(uint32_t bramab)
{
#ifdef ARM_COMPILE
  uint32_t abOffset = bramab - HSP_BRAM_AB_BASE_ADDR;
  abOffset += HSP_MEMA_BASE_ADDR;
#else // ARM_COMPILE
  uint32_t abOffset = bramab - HSP_HYP_BRAMAB_ADDR;
  abOffset += HSP_HYP_BRAMA_ADDR;
#endif // ARM_COMPILE
  return abOffset;
}

/**
 * Return HSP BRAM B address
 * @param[in] bramab  BRAMAB address to convert
 * @retval            Return BRAM B address
 */
uint32_t get_bramb_addr(uint32_t bramab)
{
#ifdef ARM_COMPILE
  uint32_t abOffset = bramab - HSP_BRAM_AB_BASE_ADDR;
  abOffset += HSP_MEMB_BASE_ADDR;
#else // ARM_COMPILE
  uint32_t abOffset = bramab - HSP_HYP_BRAMAB_ADDR;
  abOffset += HSP_HYP_BRAMB_ADDR;
#endif // ARM_COMPILE
  return abOffset;
}

/**
 * Reset external buffer area
 */
void reset_ebuff(uint32_t *tmpAddr, uint32_t size)
{
  for (uint32_t tmpi = 0; tmpi < size; tmpi++) {
    // Write data in HSP BRAM
    *tmpAddr++ = 0xfecacade;
  }
}

/**
 * Reset shared memory
 */
void reset_bram(uint32_t size)
{
  uint32_t *tmpAddr = (uint32_t *) HSP_BRAM_AB_BASE_ADDR;
  printf("Reset @BRAM 0x%x [%d]\n", tmpAddr, size);
  for (uint32_t tmpi = 0; tmpi < size; tmpi++) {
    // Write data in HSP BRAM
    *tmpAddr++ = 0xfecacade;
  }
}

/* /\** */
/*  * Reset shared memory */
/*  *\/ */
/* void reset_bram_a(uint32_t size) */
/* { */
/*   uint32_memb_t *tmpAddr = (uint32_memb_t *) HSP_MEMA_BASE_ADDR; */
/*   for (uint32_t tmpi = 0; tmpi < size; tmpi++) { */
/*     // Write data in HSP BRAM */
/*     *tmpAddr++ = 0xfecacade; */
/*   } */
/* } */

/**
 * Print conv2D kernel type
 */
void print_conv2d_type(void)
{
  uint32_t *tmpAddr = (uint32_t *) (HSP_DRAM_BASE_ADDR + 0x504);
  uint32_t hsp_dbg1_info = *tmpAddr;
  if (hsp_dbg1_info == 1) {
    // Circular mode
    printf("********** CNN_CONV2D: hyp_cnn_conv2d_circulario_1x3x3\n");
  } else if (hsp_dbg1_info == 2) {
    printf("********** CNN_CONV2D: hyp_cnn_conv2d_1x3x3\n");
  } else if (hsp_dbg1_info == 3) {
    printf("********** CNN_CONV2D: error %d\n", hsp_dbg1_info);
  } else if (hsp_dbg1_info == 4) {
    // Special case first layer 3x3 kernel Circular mode
    printf("********** CNN_CONV2D: hyp_cnn_conv2d_circulario_3x3x3\n");
  } else if (hsp_dbg1_info == 5) {
    printf("********** CNN_CONV2D: hyp_cnn_conv2d_3x3x3\n");
  } else if (hsp_dbg1_info == 6) {
    printf("********** CNN_CONV2D: error %d\n", hsp_dbg1_info);
  } else if (hsp_dbg1_info == 7) {
    // Not multiple of 4
    printf("********** CNN_CONV2D: error %d\n", hsp_dbg1_info);
  } else if (hsp_dbg1_info == 8) {
    // Channel input multiple of 4 Circular riio mode
    printf("********** CNN_CONV2D: hyp_cnn_conv2d_circulari2o\n");
  } else if (hsp_dbg1_info == 9) {
    printf("********** CNN_CONV2D: hyp_cnn_conv2d_circulariio\n");
  } else if (hsp_dbg1_info == 10) {
    // Circular mode
    printf("********** CNN_CONV2D: hyp_cnn_conv2d_circulario\n");
  } else if (hsp_dbg1_info == 11) {
    // Normal conv2D mode
    printf("********** CNN_CONV2D: hyp_cnn_conv2d\n");
  } else if (hsp_dbg1_info == 12) {
    // Normal conv2D mode
    printf("********** CNN_CONV2D: hyp_cnn_conv2d_circulario_1kl\n");
  } else if (hsp_dbg1_info == 13) {
    // Normal conv2D mode
    printf("********** CNN_CONV2D: hyp_cnn_conv2d_circulario\n");
  } else {
    printf("********** CNN_CONV2D: error %d @0x%x\n", hsp_dbg1_info, tmpAddr);
  }
}

/**
 * Print CC counter dbg info
 */
void print_dbgcc(uint32_t *pCcTrace)
{
/* #ifdef HYPSA_SIMU */
/*   extern uint32_t mydbg[]; */
/*   uint32_t *pCcTrace = (uint32_t *) mydbg; */
/* #else // HYPSA_SIMU */
/*   uint32_t *pCcTrace = (uint32_t *) (HSP_DRAM_BASE_ADDR + 0x640); */
/* #endif // HYPSA_SIMU */
  printf("CC table @0x%x\n", pCcTrace);
#ifdef ARM_COMPILE
#ifdef STM32U3C5xx
//  uint32_t conflicts = HSPHandle.instance->CCNTR;
//  uint32_t conflicts = HSPHandle.instance->CCNTR;
  uint32_t conflicts = h_hw_hsp_if[hmw.hsp_id].hhsp.instance->CCNTR;
  printf("RAM conflicts %d\tARM-HSP %d\n", conflicts, (_armMeasure - hspInternalMeasure));  
#else
  uint32_t conflicts = HSPHandle.Instance->CCNTR;
  printf("RAM conflicts %d\tARM-HSP %d\n", conflicts, (_armMeasure - hspInternalMeasure));
#endif
#endif // ARM_COMPILE
/*   FILE *fcc = fopen("mydbgcc.txt", "w"); */
/*   for (uint32_t i = 0; i < 128; i++) { */
/*     uint32_t val0 = *pCcTrace++; */
/*     uint32_t val1 = *pCcTrace++; */
/*     fprintf(fcc, "%d\t%d\n", val0, val1); */
/*   } */
/*   fclose(fcc); */
}

#ifndef HYP_TOOLS

/// This has been moved from HAL to testCommon because this function does not do job entirely !!
/**
 * @brief Configure and enable event provided by HSEG
 * @param hhsp    HSP handle.
 * @param event   Event to configure and enable through HSEG
 * @retval            HAL status.
 */
HAL_StatusTypeDef HAL_HSP_SPE_ConfigAndEnableEvent(HSP_HandleTypeDef *hhsp, uint8_t event)
{
#ifdef OLD_CODE_VA
	HAL_StatusTypeDef status = HAL_OK;

	// HSP_CHECK_STATE(hhsp, HAL_HSP_STATE_READY);

	if (event == 0)
	{
	  hhsp->ErrorCode = HAL_HSP_ERROR_INVALID_PARAM;
	  return HAL_ERROR;		
	}
	if (event <= 8)
	{
		hhsp->Instance->EVTSRC0R |= (5 << (4*((event-1)%8))); // enable HSEG source for event 1..8
	}
	else if (event <= 16)
	{
		hhsp->Instance->EVTSRC1R |= (5 << (4*((event-1)%8))); // enable HSEG source for evet 9..16
	}
	else if (event <= 22)
	{
		hhsp->Instance->EVTSRC2R |= (5 << (4*((event-1)%8))); // enable HSEG source for evet 17..22
	}
	/* HSP event enable  */
	hhsp->Instance->EVTENR |= (1 << event);

	return status;
#else
	HAL_StatusTypeDef status = HAL_OK;

	// HSP_CHECK_STATE(hhsp, HAL_HSP_STATE_READY);

	if (event == 0)
	{
	  // hhsp->ErrorCode = HAL_HSP_ERROR_INVALID_PARAM;
	  return HAL_ERROR;		
	}
	if (event <= 8)
	{
		hhsp->instance->EVTSRC0R |= (5 << (4*((event-1)%8))); // enable HSEG source for event 1..8
	}
	else if (event <= 16)
	{
		hhsp->instance->EVTSRC1R |= (5 << (4*((event-1)%8))); // enable HSEG source for evet 9..16
	}
	else if (event <= 22)
	{
		hhsp->instance->EVTSRC2R |= (5 << (4*((event-1)%8))); // enable HSEG source for evet 17..22
	}
	/* HSP event enable  */
	hhsp->instance->EVTENR |= (1 << event);

	return status;

#endif	
}
#endif // HYP_TOOLS
#endif // __HSP_TEST_COMMON_C__
