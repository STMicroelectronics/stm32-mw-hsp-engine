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
#include "hsp_fw_ram.h"
#else
// #include "hsp_fw_def_generic.h"
#include "hsp_fw_def.h"
#include "hsp_fw_ram.h"
#endif
#ifndef HYP_UNITARY_TEST
// #include "hsp_ll.h"
#endif // HYP_UNITARY_TEST

#ifndef HYP_TOOLS
#include "hsp_core.h"
#include "hsp_bram_if.h"
#include "hsp_hw_if.h"
//#include "hsp_fw_ram_generic.h"

#ifdef __HSP_DMA__
#include "hsp_proclist.h"
#include "hsp_hw_if.h"
#include "hsp_utilities.h"
#endif //__HSP_DMA__
#endif // HYP_TOOLS

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
#ifdef __HSP_DMA__
#define IF_ERROR HSP_IF_ERROR // In cube2 HSP_IF_ERROR is used instead of IF_ERROR
#endif // __HSP_DMA__

/// Destination buffer used by all tests
#ifdef ARM_COMPILE

#define IF_ERROR HSP_IF_ERROR // In cube2 HSP_IF_ERROR is used instead of IF_ERROR
#define IF_OK    HSP_IF_OK // In cube2 HSP_IF_OK is used instead of IF_OK

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
#define HSP1_BASE_NS HSP_BASE_NS
#define HSP_ARM_MEMORY_BASE_ADDR 0x80000
#define HSP_CRAM_BASE_ADDR ((HSP1_BASE_NS) + (HSP_ARM_MEMORY_BASE_ADDR))
#define HSP_DRAM_BASE_ADDR ((HSP1_BASE_NS) + (HSP_ARM_MEMORY_BASE_ADDR) + (HSP_MEM_CRAM_SIZE<<10))
#define HSP_CYCLE_COUNT_ADDR (HSP1_BASE_NS + HSP_BASE_DRAM_MEM + HSP_DRAM_CC_ADDR) ///< Temporary HSP internal CC address
#endif
#ifdef STM32H7P5xx
#define HSP_CRAM_BASE_ADDR  (HSP_ARM_MEMORY_BASE_ADDR)
#define HSP_DRAM_BASE_ADDR ((HSP_ARM_MEMORY_BASE_ADDR) + (HSP_MEM_CRAM_SIZE<<10))
#define HSP_CYCLE_COUNT_ADDR (HSP_BASE_DRAM_MEM + HSP_DRAM_CC_ADDR) ///< Temporary HSP internal CC address
#endif
#ifdef STM32G5C4xx
#define HSP_ARM_MEMORY_BASE_ADDR 0x20060000
#define HSP_CRAM_BASE_ADDR  (HSP_ARM_MEMORY_BASE_ADDR)
#define HSP_DRAM_BASE_ADDR ((HSP_ARM_MEMORY_BASE_ADDR) + (HSP_MEM_CRAM_SIZE<<10))
//#define HSP_CYCLE_COUNT_ADDR (HSP_BASE_DRAM_MEM + HSP_DRAM_CC_ADDR) ///< Temporary HSP internal CC address
//#define HSP_CYCLE_COUNT_ADDR (HSP_ARM_MEMORY_BASE_ADDR + (HSP_MEM_CRAM_SIZE << 10) + HSP_DRAM_CC_ADDR) ///< Temporary HSP internal CC address
#define HSP_CYCLE_COUNT_ADDR (0x20066008) ///< Temporary HSP internal CC address
#endif

//#pragma location = HYPSA_TEST_DST_ADDR
float32_t hspTestDst4096[8192];
float32_t hspTestDstExt4096[4096];
// Used for end of test synchronization
extern volatile uint32_t hsp_it_evt;
extern volatile uint32_t hsp_it_gbl;

#else // ARM_COMPILE
#define HSP_DRAM_BASE_ADDR 0
#define HSP_BRAM_AB_BASE_ADDR (0x40000 * 4)
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

#ifndef HYP_TOOLS
HSP_TypeDef *pHspReg;
#endif // HYP_TOOLS

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
                // printf("Check1 at[%3d]: Res %.52f != Exp %.52f (0x%08x 0x%08x)\n", idx, data[idx], ref[idx],	*pdata, *pref);	
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
		TEST_INFO_REPORT(testName, "Max difference %.8f (0x%08x) @[%d]=%.10f expected[%d]=%.10f\n", maxDiff, *pmax,imaxdiff,data[imaxdiff],imaxdiff,ref[imaxdiff]);
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
          if (noPrintPassed) {
            if (size == 1) {
              idx = noPrintPassed;
            }
          }
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
uint32_t compare_int32(const char *testName, uint32_t *data, uint32_t *ref, uint32_t size, uint32_t error)
{
  uint32_t noPrintPassed = 0;
  if (error == 0xffffffff) {
    noPrintPassed = 1;
  }
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
    if (noPrintPassed == 0) {
      TEST_INFO_REPORT(testName, "\tPASSED\n");
    }
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

//#ifdef STM32U3C5xx

HAL_StatusTypeDef test_send_event(uint8_t event)
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
			pHspReg->EVTSRC0R |= (6 << (4*((event-1)%8))); // enable CSEG source for event 1..8
			//printf("hhsp->EVTSRC0R=%d\n", hhsp->EVTSRC0R);
		}
		else if (event <= 16)
		{
			//printf("value to write in EVTSRC1R = 0x%08x\n",6 << (4*((event-1)%8)));
            pHspReg->EVTSRC1R |= (6 << (4*((event-1)%8))); // enable CSEG source for evet 9..16
		}
		else if (event <= 22)
		{
			//printf("value to write in EVTSRC2R = 0x%08x\n",6 << (4*((event-1)%8)));
			pHspReg->EVTSRC2R |= (6 << (4*((event-1)%8))); // enable CSEG source for evet 17..22
		}
		pHspReg->CSEGR = (1 << event);
	}
	else
	{
		// Wait until the CDEG is ready to accept the generation of a new event.
		while ( (pHspReg->CDEGR & 0x80000000) != 0);
		// HSP CPU dedicated event generation register
		pHspReg->CDEGR = (event & 0x3F);
	}
	return status;
}

HAL_StatusTypeDef test_enable_event(uint8_t event)
{
  	HAL_StatusTypeDef status = HAL_OK;

	// Enable event associated to this list
	if ((event > 0) && (event < 23))
	{
		//printf("hhsp->EVTENR=%d\n", hhsp->EVTENR);
		pHspReg->EVTENR &= ~(1 << event); // Need to update EVTSRCxR

		/// Temporaire just for test !!!
		if (event <= 8)
		{
			//printf("value to write in EVTSRC0R = 0x%08x\n",6 << (4*((event-1)%8)));
            pHspReg->EVTSRC0R |= (6 << (4*((event-1)%8))); // enable CSEG source for event 1..8
			//printf("hhsp->EVTSRC0R=%d\n", hhsp->EVTSRC0R);
		}
		else if (event <= 16)
		{
			//printf("value to write in EVTSRC1R = 0x%08x\n",6 << (4*((event-1)%8)));
            pHspReg->EVTSRC1R |= (6 << (4*((event-1)%8))); // enable CSEG source for evet 9..16
			//printf("hhsp->EVTSRC1R=%d\n", hhsp->EVTSRC1R);
		}
		else if (event <= 22)
		{
			//printf("value to write in EVTSRC2R = 0x%08x\n",6 << (4*((event-1)%8)));
            pHspReg->EVTSRC2R |= (6 << (4*((event-1)%8))); // enable CSEG source for evet 17..22
			//printf("hhsp->EVTSRC2R=%d\n", hhsp->EVTSRC2R);
		}
		pHspReg->ITFENR |= 0x10000000;
		/* !< HSP event enable register                         Address offset: 0x080 */
		pHspReg->EVTENR |= (1 << event); // hhsp->EVTENR |= (1 << event);
	}
	else
	{
		// Enable CDEG
        pHspReg->ITFENR |= 0x20000000;
	}
	return status;
}

HAL_StatusTypeDef test_enable_and_send_event(uint8_t event)
{
  HAL_StatusTypeDef status = HAL_OK;

#ifdef ARM_COMPILE
#ifdef STM32H7P5xx
  // H7
  __DSB();
  __DMB();
#endif
#endif
	// Enable event associated to this list
	if ((event > 0) && (event < 23))
	{
		//printf("hhsp->EVTENR=%d\n", hhsp->EVTENR);
		pHspReg->EVTENR &= ~(1 << event); // Need to update EVTSRCxR

		/// Temporaire just for test !!!
		if (event <= 8)
		{
			//printf("value to write in EVTSRC0R = 0x%08x\n",6 << (4*((event-1)%8)));
			pHspReg->EVTSRC0R |= (6 << (4*((event-1)%8))); // enable CSEG source for event 1..8
			//printf("hhsp->EVTSRC0R=%d\n", hhsp->EVTSRC0R);
		}
		else if (event <= 16)
		{
			//printf("value to write in EVTSRC1R = 0x%08x\n",6 << (4*((event-1)%8)));
			pHspReg->EVTSRC1R |= (6 << (4*((event-1)%8))); // enable CSEG source for evet 9..16
			//printf("hhsp->EVTSRC1R=%d\n", hhsp->EVTSRC1R);
		}
		else if (event <= 22)
		{
			//printf("value to write in EVTSRC2R = 0x%08x\n",6 << (4*((event-1)%8)));
			pHspReg->EVTSRC2R |= (6 << (4*((event-1)%8))); // enable CSEG source for evet 17..22
			//printf("hhsp->EVTSRC2R=%d\n", hhsp->EVTSRC2R);
		}
		// Enable CSEG
		pHspReg->ITFENR |= 0x10000000;
		/* !< HSP event enable register                         Address offset: 0x080 */
		pHspReg->EVTENR |= (1 << event); // hhsp->EVTENR |= (1 << event);
		pHspReg->CSEGR = (1 << event);
	}
	else
	{
		// Enable CDEG
		pHspReg->ITFENR |= 0x20000000;
		// Wait until the CDEG is ready to accept the generation of a new event.
		while ( (pHspReg->CDEGR & 0x80000000) != 0);
		// HSP CPU dedicated event generation register
		pHspReg->CDEGR = (event & 0x3F);
	}
	return status;
}


/**
  * @brief Configure End Of Task signal from HSP to CPU
  * @param hhsp         HSP handle.
  * @param taskNb       Task number
  * @param taskCmpNb    Task comparator number
  * @retval            HAL status.
  */
HAL_StatusTypeDef HAL_HSP_ConfigureEOT(uint8_t taskNb, uint8_t taskCmpNb)
{
  switch (taskCmpNb)
  {
    case 0:
      /* Enable TCCMP0 */
      pHspReg->TCUCFGR = pHspReg->TCUCFGR | (1U << HSP_TCUCFGR_TC0EN_Pos);
      /* Set task Number */
      pHspReg->TCUCFGR = (pHspReg->TCUCFGR | taskNb);
      /* Enable IT for EOTC */
      pHspReg->EVT_IER = (pHspReg->EVT_IER | ((1U << HSP_EVT_IER_EOTECP0IE_Pos)));
      break;
    case 1:
      /* Enable TCCMP0 */
      pHspReg->TCUCFGR = pHspReg->TCUCFGR | (1U << HSP_TCUCFGR_TC1EN_Pos);
      /* Set task Number */
      pHspReg->TCUCFGR = (pHspReg->TCUCFGR | (taskNb << HSP_TCUCFGR_TSKCMP1_Pos));
      /* Enable IT for EOTC */
      pHspReg->EVT_IER = (pHspReg->EVT_IER | ((1U << HSP_EVT_IER_EOTECP1IE_Pos)));
      break;
    case 2:
      /* Enable TCCMP0 */
      pHspReg->TCUCFGR = pHspReg->TCUCFGR | (1U << HSP_TCUCFGR_TC2EN_Pos);
      /* Set task Number */
      pHspReg->TCUCFGR = (pHspReg->TCUCFGR | (taskNb << HSP_TCUCFGR_TSKCMP2_Pos));
      /* Enable IT for EOTC */
      pHspReg->EVT_IER = (pHspReg->EVT_IER | ((1U << HSP_EVT_IER_EOTECP2IE_Pos)));
      break;
    case 3:
      /* Enable TCCMP0 */
      pHspReg->TCUCFGR = pHspReg->TCUCFGR | (1U << HSP_TCUCFGR_TC3EN_Pos);
      /* Set task Number */
      pHspReg->TCUCFGR = (pHspReg->TCUCFGR | (taskNb << HSP_TCUCFGR_TSKCMP3_Pos));
      /* Enable IT for EOTC */
      pHspReg->EVT_IER = (pHspReg->EVT_IER | ((1U << HSP_EVT_IER_EOTECP3IE_Pos)));
      break;
    default:
      return(HAL_ERROR);
      break;
  }
  return(HAL_OK);
}

#else // ARM_COMPILE
/**
  * @brief Configure End Of Task signal from HSP to CPU
  * @param hhsp         HSP handle.
  * @param taskNb       Task number
  * @param taskCmpNb    Task comparator number
  * @retval            HAL status.
  */
HAL_StatusTypeDef HAL_HSP_ConfigureEOT(uint8_t taskNb, uint8_t taskCmpNb)
{
  return HAL_OK;
}

/**
 * @brief Enable event to HSP
 * @param[in] hhsp    HSP handle.
 * @retval            HAL status.
 */
HAL_StatusTypeDef test_send_event(uint8_t event)
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
HAL_StatusTypeDef test_enable_event(uint8_t event)
{
	HAL_StatusTypeDef status = HAL_OK;
	return status;
}

HAL_StatusTypeDef test_enable_and_send_event(uint8_t event)
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
 */
void test_hw_reset(void)
{
#ifdef ARM_COMPILE
  pHspReg = (HSP_TypeDef *) HSP1;
  /* RESET HSP */
#ifdef STM32U3C5xx
  // U3
  __HAL_RCC_HSP1_FORCE_RESET();
  __HAL_RCC_HSP1_RELEASE_RESET();
#endif // STM32U3C5xx
#ifdef STM32U575xx
  // U5
  /* Pour le moment le FPGA utilise les signaux du DMA2D pour le HSP */
  __HAL_RCC_DMA2D_FORCE_RESET();
  __HAL_RCC_DMA2D_RELEASE_RESET();
#endif // STM32U575xx
#ifdef STM32H7P5xx
  // H7
  HAL_RCC_HSP_Reset();
  HAL_RCC_HSP_EnableClock();
//  HAL_RCC_HSPRAM_EnableClock();
#endif // STM32H7P5xx
#if defined(STM32G5C4xx)
  // G5
  STM32_SET_BIT(RCC->HSP1CFGR, RCC_HSP1CFGR_RST);
  STM32_CLEAR_BIT(RCC->HSP1CFGR, RCC_HSP1CFGR_RST);
#endif /* STM32U3H7Pxx */

#endif // ARM_COMPILE
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

#define LOAD_BY_TEST_COMMON
#ifdef LOAD_BY_TEST_COMMON
#ifdef HYPSA_SIMU
/// CRAM byte size
#define HSP_CRAM_SIZE (((HSP_HWCFGR1_RESET_VAL & HSP_HWCFGR1_CRAM_SIZE_Msk) >> HSP_HWCFGR1_CRAM_SIZE_Pos) << 8)
/// DRAM byte size
#define HSP_DRAM_SIZE (((HSP_HWCFGR1_RESET_VAL & HSP_HWCFGR1_DRAM_SIZE_Msk) >> HSP_HWCFGR1_DRAM_SIZE_Pos) << 8)
#else // HYPSA_SIMU
#ifdef STM32U575xx
/// CRAM byte size
#define HSP_CRAM_SIZE (((HSP_HWCFGR1_RESET_VAL & HSP_HWCFGR1_CRAM_SIZE_Msk) >> HSP_HWCFGR1_CRAM_SIZE_Pos) << 8)
/// DRAM byte size
#define HSP_DRAM_SIZE (((HSP_HWCFGR1_RESET_VAL & HSP_HWCFGR1_DRAM_SIZE_Msk) >> HSP_HWCFGR1_DRAM_SIZE_Pos) << 8)
#else // STM32U575xx
/// CRAM byte size
#define HSP_CRAM_SIZE 5120
/// DRAM byte size
#define HSP_DRAM_SIZE 3072
#endif // STM32U575xx
#endif // HYPSA_SIMU


/**
 * Load HSP CRAM code
 */
void load_hsp_cram(uint32_t *dataCRAMTab)
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
void load_hsp_dram(uint32_t *dataDRAMTab)
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
// void load_hsp_data_cram(uint32_t *pSrc, uint32_t offset, uint32_t length)
// {
  // uint32_t tmpi;
  // uint32_t tmp = HSP_CRAM_BASE_ADDR + (HSP_FW_DATA_CRAM_SIZE + offset) * 4;
  // uint32_t *tmpAddr = (uint32_t *) tmp;
  // tmpAddr--; // Last word of CRAM is 0xFFFFFFFF
  // printf("Load CRAM @0x%x (0x%x)\n", tmpAddr, HSP_FW_DATA_CRAM_SIZE);
  // for (tmpi = 0; tmpi < length; tmpi++) {
    // // Write data in HSP CRAM
    // *tmpAddr++ = pSrc[tmpi];
  // }
// }

/**
 * Load HSP Plugin in CRAM
 */
void load_hsp_data_cram(uint32_t *pSrc, uint32_t offset, uint32_t length)
{
  uint32_t tmpi;
  
  const hsp_fw_descriptor_t *desc = hsp_fw_getcram(); 
  uint32_t fw_size = desc->size_byte / sizeof(uint32_t);

  uint32_t tmp = HSP_CRAM_BASE_ADDR + (fw_size + offset) * 4;  
  uint32_t *tmpAddr = (uint32_t *) tmp;
  tmpAddr--; // Last word of CRAM is 0xFFFFFFFF
  printf("Load CRAM @0x%x (0x%x)\n", tmpAddr, fw_size);
  for (tmpi = 0; tmpi < length; tmpi++) {
    // Write data in HSP CRAM
    *tmpAddr++ = pSrc[tmpi];
  }
  
#if 0
  uint32_t tmp = HSP_CRAM_BASE_ADDR + (HSP_FW_DATA_CRAM_SIZE + offset) * 4;  
  uint32_t *tmpAddr = (uint32_t *) tmp;
  tmpAddr--; // Last word of CRAM is 0xFFFFFFFF
  printf("Load CRAM @0x%x (0x%x)\n", tmpAddr, HSP_FW_DATA_CRAM_SIZE);
  for (tmpi = 0; tmpi < length; tmpi++) {
    // Write data in HSP CRAM
    *tmpAddr++ = pSrc[tmpi];
  }
#endif
}
#endif

#if defined(STM32G5C4xx)
void test_wait_for_hsp(void)
{
#if 1
    // Synchronization method based on end of task interrupt
  while (hsp_it_evt == 0)
  {
//    __WFI();
  }
  // Reset hsp_it_evt
  hsp_it_evt = 0;

#else
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
#endif

#ifdef ARM_COMPILE
#ifdef STM32H7P5xx
  __DSB();
  __DMB();
#endif
#endif
	__WFI(); // Wait For Interrupt

	__enable_irq(); // Reactiver les interruptions apres WFI
}
#else // STM32G5C4xx

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
#endif //
#endif // STM32G5C4xx

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
#ifndef HYP_TOOLS
  printf("CC table @0x%x\n", pCcTrace);
  uint32_t conflicts = pHspReg->CCNTR;
  printf("RAM conflicts %d\tARM-HSP %d\n", conflicts, (_armMeasure - hspInternalMeasure));
#endif // HYP_TOOLS
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
 * @param event   Event to configure and enable through HSEG
 * @retval        error
 */
uint32_t hst_test_ConfigAndEnableEvent(uint32_t event)
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
		pHspReg->EVTSRC0R |= (5 << (4*((event-1)%8))); // enable HSEG source for event 1..8
	}
	else if (event <= 16)
	{
		pHspReg->EVTSRC1R |= (5 << (4*((event-1)%8))); // enable HSEG source for evet 9..16
	}
	else if (event <= 22)
	{
		pHspReg->EVTSRC2R |= (5 << (4*((event-1)%8))); // enable HSEG source for evet 17..22
	}
	/* HSP event enable  */
	pHspReg->EVTENR |= (1 << event);

	return status;
#else
	if (event == 0)
	{
	  // hhsp->ErrorCode = HAL_HSP_ERROR_INVALID_PARAM;
	  return 1;
	}
	if (event <= 8)
	{

		pHspReg->EVTSRC0R |= (5 << (4*((event-1)%8))); // enable HSEG source for event 1..8
	}
	else if (event <= 16)
	{
		pHspReg->EVTSRC1R |= (5 << (4*((event-1)%8))); // enable HSEG source for evet 9..16
	}
	else if (event <= 22)
	{
		pHspReg->EVTSRC2R |= (5 << (4*((event-1)%8))); // enable HSEG source for evet 17..22
	}
	/* HSP event enable  */
	pHspReg->EVTENR |= (1 << event);

	return 0;
#endif
}

/**
  * @brief Enable interruption for kernel event
  * @param event   Event to enable in HSP kernel event interrupt enable register
  */
void hst_test_EnableKerEventInterrupt(uint32_t event)
{
  /* HSP interrupt for kernel event */
  pHspReg->PFCTEVT_IER = pHspReg->PFCTEVT_IER | ((1U << event));
}

/**
  * @brief Send event through CDEG/CSEG to trig a processing list
  * @param listNumber    Processing list number
  * @param itf           Event generated by CDEG (0) or CSEG (1) interface
  */
void hst_test_TrigProcList(uint32_t listNumber, uint32_t itf)
{
#define HSP_MIN_EVENT_CSEG  1  /**< Minimal event number triggered by CSEG */
#define HSP_MAX_EVENT_CSEG  22 /**< Maximal event number triggered by CSEG */
  if (itf)
  {
    /* Send event through CSEG: only for processing lists number 1 to 22 */
    if ((listNumber >= HSP_MIN_EVENT_CSEG) && (listNumber <= HSP_MAX_EVENT_CSEG))
    {
      pHspReg->CSEGR = (1 << listNumber);
    }
    else
    {
      printf("ERROR: FAILED TrigProcList\n");
    }
  }
  else
  {
    /* Send event through CDEG: all processing list according the maximun number of task */
/*     if (listNumber > (((h_hw_hsp_if[0].hhsp.Instance->HWCFGR3 & HSP_HWCFGR3_NUM_TSK_MAX_Msk) >> HSP_HWCFGR3_NUM_TSK_MAX_Pos) - 1)) */
/*     { */
/*       printf("ERROR: FAILED TrigProcList\n"); */
/*     } */
    /* Send event through CDEG */
    /* Wait until the CDEG is ready to accept the generation of a new event. */
    while ((pHspReg->CDEGR & HSP_CDEGR_CDEGBSY) != 0);
    pHspReg->CDEGR = (listNumber & HSP_CDEGR_CTSKN);
  }
}

#ifdef HYPSA_SIMU
uint32_t hypsa_hw_reset();
#endif // HYPSA_SIMU

hsp_core_status_t HSP_WriteCommand(uint32_t command)
{
  /* Read the C2HMSGF bit via the HSP CPU to HSP message control register (HSP_C2HSEMR)
     Wait until C2HMSGF = 0. It indicates that the previous message has been read by the HSP,
     and the content of C2HDATA can be overwrite. */
  if (pHspReg->C2HSEMR) {
#ifdef HYPSA_SIMU
    printf("HSP_WriteCommand impossible because of pHspReg->C2HSEMR\n");
#endif // HYPSA_SIMU
    return HSP_CORE_ERROR;
  }
  if (pHspReg->H2CSEMR) {
    printf("HSP_WriteCommand error because of pHspReg->H2CSEMR\n");
#ifdef HYPSA_SIMU
    /* Set H2CMSGF to 0 to indicate that the message is read */
    pHspReg->H2CSEMR = 0;
#endif
#ifndef HYPSA_SIMU
    pHspReg->H2CSEMR = 1;
#endif
  }
  while (pHspReg->C2HSEMR);
  /* Write command in mailbox */
  pHspReg->C2HMSGDR = command;
  pHspReg->C2HSEMR = 1;
#ifdef HYPSA_SIMU
  /* HPSA: Used to synchronize with hyperion */
  hypsa_post_command();
#endif

  /* Wait and read status */
  while (pHspReg->H2CSEMR == 0);

  /* Read the H2CDATA via HSP HSP to CPU message data register (HSP_H2CMSGDR).= */
  hsp_core_status_t status = (hsp_core_status_t) pHspReg->H2CMSGDR;

#ifdef HYPSA_SIMU
  /* Set H2CMSGF to 0 to indicate that the message is read */
  pHspReg->H2CSEMR = 0;
#endif
#ifndef HYPSA_SIMU
  pHspReg->H2CSEMR = 1;
#endif
  if (status) {
    return HSP_CORE_ERROR;
  }
  return HSP_CORE_OK;
}

#ifdef __MDW_CUBE2__
hal_hsp_boot_config_t boot_cfg;
hal_hsp_boot_config_t *p_config = &boot_cfg;
#else /* __MDW_CUBE2__ */
HAL_HSP_Boot_ConfigTypeDef boot_cfg;
HAL_HSP_Boot_ConfigTypeDef *p_config = &boot_cfg;
#endif  /* __MDW_CUBE2__ */


void hst_test_HAL_HSP_Boot0(HSP_HandleTypeDef *hhsp, uint32_t timeout_ms)
{
  //HAL_StatusTypeDef HAL_HSP_Init(HSP_HandleTypeDef *hhsp)
#ifdef HYPSA_SIMU
  /* Call Hypsa simu soft reset */
  hypsa_hw_reset();

  /* Boot the HSP */
  // SET_BIT(h_hw_hsp_if[0].hhsp.Instance->CR, HSP_CR_BOOTEN);
  // h_hw_hsp_if[0].hhsp.Instance->CR = 1;
  SET_BIT(pHspReg->CR, HSP_CR_BOOTEN);
  pHspReg->CR = 1;

  // HSP_HandleTypeDef *hhsp = &(h_hw_hsp_if[0].hhsp);
  HSP_HandleTypeDef *hhsp = (HSP_HandleTypeDef *)(hmw.hdriver);

  HAL_HSP_WriteParameter(hhsp, HAL_HSP_PARAM_0, HAL_HSP1_BRAM_BASE_ADDRESS);

  HAL_HSP_WriteParameter(hhsp, HAL_HSP_PARAM_1, p_config->perf_mon);


/*   if (HAL_HSP_SendCommand(hhsp, p_config->boot_cmd_id, HSP_BOOT_TIMEOUT_MS) != HAL_OK) */
/*   { */
/*   } */

/*   /\* Enable the CDEG interface to allow the run of task by CPU *\/ */
/*   SET_BIT(h_hw_hsp_if[0].hhsp.Instance->ITFENR, HSP_ITFENR_CDEGEN); */

  /* HSP is ready to be configured, record processing list or process direct command */
  // hhsp->global_state = HAL_HSP_STATE_IDLE;
  // hhsp->global_state = HAL_HSP_STATE_READY;
  hhsp->global_state = HAL_HSP_STATE_READY;

#else // HYPSA_SIMU

#ifdef __MDW_CUBE2__
  /* Close the FW */
  *((__IO uint32_t *)(hhsp->cram_address_for_plugin)) = 0xffffffff;
  hhsp->dram_free_size_in_word--;

  /* Boot the HSP */

  STM32_SET_BIT(pHspReg->CR, HSP_CR_BOOTEN);

  /* Get timeout */
  uint32_t tickstart = HAL_GetTick();

  while (STM32_READ_BIT(pHspReg->CR, HSP_CR_BSTAT_Msk) != p_config->boot_success_code)
  {
    /* Check for the Timeout */
    if ((HAL_GetTick() - tickstart) > timeout_ms)
    {
      /* New check to avoid false timeout detection in case of preemption */
      uint32_t bstat = STM32_READ_BIT(pHspReg->CR, HSP_CR_BSTAT_Msk);
      if (bstat != p_config->boot_success_code)
      {
        hhsp->last_error_codes |= HAL_HSP_ERROR_BOOT;
        hhsp->boot_error_code = bstat;
        hhsp->global_state = HAL_HSP_STATE_FAULT;
      }
    }
  }

  /* The Boot is OK, but before to transmmit the BRAM address and the performance monitor state */
  /* to finalize the boot, we put the handle state to READY to allow the call of HAL_HSP_MSGBOX_SendCommand */
  hhsp->global_state = HAL_HSP_STATE_IDLE;

  /* FW need to know this address at boot */
  HAL_HSP_WriteParameter(hhsp, HAL_HSP_PARAM_0, HAL_HSP_GET_BRAMAB_BASE_ADDRESS((uint32_t)(HSP1)));

  HAL_HSP_WriteParameter(hhsp, HAL_HSP_PARAM_1, p_config->perf_mon);
#else /* __MDW_CUBE2__ */
  /* Close the FW */

  *((__IO uint32_t *)(hhsp->cram_address_for_plugin)) = 0xffffffff;
  hhsp->dram_free_size_in_word--;

  /* Boot the HSP */

  SET_BIT(pHspReg->CR, HSP_CR_BOOTEN);

  /* Get timeout */
  uint32_t tickstart = HAL_GetTick();

  while (READ_BIT(pHspReg->CR, HSP_CR_BSTAT_Msk) != p_config->boot_success_code)
  {
    /* Check for the Timeout */
    if ((HAL_GetTick() - tickstart) > timeout_ms)
    {
      /* New check to avoid false timeout detection in case of preemption */
      uint32_t bstat = READ_BIT(pHspReg->CR, HSP_CR_BSTAT_Msk);
      if (bstat != p_config->boot_success_code)
      {
        hhsp->last_error_codes |= HAL_HSP_ERROR_BOOT;
        hhsp->boot_error_code = bstat;
        hhsp->global_state = HAL_HSP_STATE_FAULT;
      }
    }
  }

  /* The Boot is OK, but before to transmmit the BRAM address and the performance monitor state */
  /* to finalize the boot, we put the handle state to READY to allow the call of HAL_HSP_MSGBOX_SendCommand */
  // hhsp->global_state = HAL_HSP_STATE_READY;
  hhsp->global_state = HSP_CORE_STATE_READY;

  /* FW need to know this address at boot */
  HAL_HSP_WriteParameter(hhsp, HAL_HSP_PARAM_0, HAL_HSP_GET_BRAMAB_BASE_ADDRESS((uint32_t)(HSP1)));

  HAL_HSP_WriteParameter(hhsp, HAL_HSP_PARAM_1, p_config->perf_mon);
#endif  /* __MDW_CUBE2__ */
#endif // HYPSA_SIMU
}

void hst_test_HAL_HSP_Boot1(void)
{
#ifdef HYPSA_SIMU
  if (HAL_HSP_SendCommand((HSP_HandleTypeDef *)(hmw.hdriver), p_config->boot_cmd_id, HSP_BOOT_TIMEOUT_MS) != HAL_OK)
  {
  }

	/* Enable the CDEG interface to allow the run of task by CPU */
	// SET_BIT(h_hw_hsp_if[0].hhsp.Instance->ITFENR, HSP_ITFENR_CDEGEN);
	SET_BIT(pHspReg->ITFENR, HSP_ITFENR_CDEGEN);

	/* HSP is ready to be configured, record processing list or process direct command */
	// h_hw_hsp_if[0].hhsp.global_state = HAL_HSP_STATE_IDLE;
	hmw.global_state = HSP_CORE_STATE_IDLE;

#else // HYPSA_SIMU
  HAL_HSP_MSGBOX_SendCommand((((HSP_HandleTypeDef *)(hmw.hdriver))), p_config->boot_cmd_id, HSP_BOOT_TIMEOUT_MS);

  /* Enable all event generators: CDEG, CSEG */
  pHspReg->ITFENR = (HSP_ITFENR_CSEGEN | HSP_ITFENR_CDEGEN);
#endif // HYPSA_SIMU
}

void hst_test_enableCycleCount(uint32_t enableCycleCount)
{
  pHspReg->PARAMR1 = enableCycleCount;
#ifdef __MDW_CUBE2__
  boot_cfg.perf_mon = (hal_hsp_perf_monitor_state_t)enableCycleCount;
#else /* __MDW_CUBE2__ */
  boot_cfg.perf_mon = (HAL_HSP_PERF_MONITOR_StateTypeDef)enableCycleCount;
#endif  /* __MDW_CUBE2__ */
}

/**
  * @brief Boot the HSP.
  * @param enableCycleCountEnable  Enable cycle count on HSP side
  * @retval Interface status.
  */
void hst_test_HSP_HW_IF_Boot(uint32_t enableCycleCount);
void hst_test_HSP_HW_IF_Boot(uint32_t enableCycleCount)
{
  boot_cfg.boot_cmd_id = HSP_CMD_FW_START;
  boot_cfg.boot_success_code = HSP_BSTAT_BOOTOK;
#ifdef __MDW_CUBE2__
  boot_cfg.perf_mon = (hal_hsp_perf_monitor_state_t)enableCycleCount;
#else /* __MDW_CUBE2__ */
  boot_cfg.perf_mon = (HAL_HSP_PERF_MONITOR_StateTypeDef)enableCycleCount;
#endif  /* __MDW_CUBE2__ */

  hst_test_HAL_HSP_Boot0(((HSP_HandleTypeDef *)(hmw.hdriver)), HSP_BOOT_TIMEOUT_MS);
}

hsp_core_status_t HSP_CORE_LoadFW(hsp_core_handle_t *hmw);

void hst_test_HSP_CORE_Init(hsp_core_handle_t *hmw)
{
  /* Interfaces Initialization ---------------------------------------------------------------------------------------*/
  /* Initialize the BRAM memory interface */
  // if (HSP_BRAM_IF_Init(&(hmw->hbram), 0) != IF_OK)
#ifdef __MDW_CUBE2__
  if (HSP_BRAM_IF_Init(&(hmw->hbram), hmw->hdriver) != HSP_IF_OK)
  {
    return;
  }
#else /* __MDW_CUBE2__ */
  // if (HSP_BRAM_IF_Init(&(hmw->hbram), hmw->hdriver) != IF_OK)
  if (HSP_BRAM_IF_Init(&(hmw->hbram), hmw->hdriver) != HSP_IF_OK)
  {
    return;
  }
#endif  /* __MDW_CUBE2__ */

  /* Initialize the Firmware Interface */
  // if (HSP_HW_IF_Init(0) != IF_OK)
  // {
    // return;
  // }

  /* Register MW HSP Processing Event Callbacks */
//  HSP_HW_IF_RegisterProcessingEventCallback(0, HSP_CORE_FWEVT_ProcessingEventCallback);

  /* Load the Firmware & Plugin --------------------------------------------------------------------------------------*/
  /* Call the weak function to load Firmware */
  if (HSP_CORE_LoadFW(hmw) != HSP_CORE_OK)
  {
    return;
  }
#if defined(USE_HSP_PLUGIN) && (USE_HSP_PLUGIN == 1)
  /* Call the weak function to load Plugins */
  if (HSP_CORE_LoadPlugins(hmw) != HSP_CORE_OK)
  {
    return;
  }
#endif
  /* Change HSP Middleware state */
  hmw->global_state = HSP_CORE_STATE_READY;

  /* Boot the HSP */
  hst_test_HSP_HW_IF_Boot(ENABLE_HSP_PERFORMANCE_MONITOR);

    /* Change HSP Middleware state */
  hmw->global_state = HSP_CORE_STATE_IDLE;
}

void hst_test_HSP_CORE_Init_NPlug(hsp_core_handle_t *hmw, uint32_t *pSrc, uint32_t length)
{
  /* Interfaces Initialization ---------------------------------------------------------------------------------------*/
  /* Initialize the BRAM memory interface */
  // if (HSP_BRAM_IF_Init(&(hmw->hbram), 0) != IF_OK)
  if (HSP_BRAM_IF_Init(&(hmw->hbram), hmw->hdriver) != HSP_IF_OK)
  {
    return;
  }
  /* Initialize the Firmware Interface */
  // if (HSP_HW_IF_Init(0) != IF_OK)
  // {
    // return;
  // }

  /* Register MW HSP Processing Event Callbacks */
//  HSP_HW_IF_RegisterProcessingEventCallback(0, HSP_CORE_FWEVT_ProcessingEventCallback);

  /* Load the Firmware & Plugin --------------------------------------------------------------------------------------*/
  /* Call the weak function to load Firmware */
  if (HSP_CORE_LoadFW(hmw) != HSP_CORE_OK)
  {
    return;
  }

#ifdef ARM_COMPILE
  load_hsp_data_cram(pSrc, 0, length);
#else // ARM_COMPILE
  uint32_t filler_cram = 0xffffffff;
  extern char _segment_end_cram_seg_PMw;
  uint32_t cram_start = (uint32_t) &_segment_end_cram_seg_PMw;
  printf("cram_start=0x%08x\n", cram_start);
  load_hsp_data_cram(pSrc, cram_start, length);
#endif // ARM_COMPILE

  HSP_HandleTypeDef *hhsp = (HSP_HandleTypeDef *)(hmw->hdriver);
  hhsp->cram_address_for_plugin += (length * 4);

#if defined(USE_HSP_PLUGIN) && (USE_HSP_PLUGIN == 1)
  /* Call the weak function to load Plugins */
  if (HSP_CORE_LoadPlugins(hmw) != HSP_CORE_OK)
  {
    return;
  }
#endif
  /* Change HSP Middleware state */
  hmw->global_state = HSP_CORE_STATE_READY;

  /* Boot the HSP */
#ifdef __MDW_CUBE2__
  HSP_HW_IF_Boot(hmw->hdriver, ENABLE_HSP_PERFORMANCE_MONITOR);
#else /* __MDW_CUBE2__ */
  HSP_HW_IF_Boot(hmw->hdriver, ENABLE_HSP_PERFORMANCE_MONITOR);
#endif  /* __MDW_CUBE2__ */

  /* Change HSP Middleware state */
  hmw->global_state = HSP_CORE_STATE_IDLE;
}

void hst_test_HSP_CORE_Init_NPlug3(hsp_core_handle_t *hmw, uint32_t *pSrc0, uint32_t l0,
                                   uint32_t *pSrc1, uint32_t l1, uint32_t *pSrc2, uint32_t l2)
{
  /* Interfaces Initialization ---------------------------------------------------------------------------------------*/
  /* Initialize the BRAM memory interface */
  // if (HSP_BRAM_IF_Init(&(hmw->hbram), 0) != IF_OK)
  if (HSP_BRAM_IF_Init(&(hmw->hbram), hmw->hdriver) != HSP_IF_OK)
  {
    return;
  }

  /* Initialize the Firmware Interface */
  // if (HSP_HW_IF_Init(0) != IF_OK)
  // {
    // return;
  // }

  /* Register MW HSP Processing Event Callbacks */
//  HSP_HW_IF_RegisterProcessingEventCallback(0, HSP_CORE_FWEVT_ProcessingEventCallback);

  /* Load the Firmware & Plugin --------------------------------------------------------------------------------------*/
  /* Call the weak function to load Firmware */
  if (HSP_CORE_LoadFW(hmw) != HSP_CORE_OK)
  {
    return;
  }

  uint32_t len = 0;
#ifndef ARM_COMPILE
  uint32_t filler_cram = 0xffffffff;
  extern char _segment_end_cram_seg_PMw;
  uint32_t cram_start = (uint32_t) &_segment_end_cram_seg_PMw;
  printf("cram_start=0x%08x\n", cram_start);
#endif // ARM_COMPILE
  if (l0) {
#ifdef ARM_COMPILE
    load_hsp_data_cram(pSrc0, 0, l0);
#else // ARM_COMPILE
    cram_start += (l0-1);
    load_hsp_data_cram(pSrc0, cram_start, l0);
#endif // ARM_COMPILE
    len = l0 - 1;
  }
  if (l1) {
#ifdef ARM_COMPILE
    load_hsp_data_cram(pSrc1, len, l1);
#else // ARM_COMPILE
    cram_start += (l1-1);
    load_hsp_data_cram(pSrc1, cram_start, l1);
#endif // ARM_COMPILE
    len += (l1 - 1);
  }
  if (l2) {
#ifdef ARM_COMPILE
    load_hsp_data_cram(pSrc2, len, l2);
#else // ARM_COMPILE
    cram_start += (l2-1);
    load_hsp_data_cram(pSrc2, cram_start, l2);
#endif // ARM_COMPILE
    len += (l2 - 1);
  }
  len++;
  HSP_HandleTypeDef *hhsp = (HSP_HandleTypeDef *)(hmw->hdriver);
  hhsp->cram_address_for_plugin += (len * 4);


#if defined(USE_HSP_PLUGIN) && (USE_HSP_PLUGIN == 1)
  /* Call the weak function to load Plugins */
  if (HSP_CORE_LoadPlugins(hmw) != HSP_CORE_OK)
  {
    return;
  }
#endif
  /* Change HSP Middleware state */
  hmw->global_state = HSP_CORE_STATE_READY;

  /* Boot the HSP */
#ifdef __MDW_CUBE2__
  HSP_HW_IF_Boot(hmw->hdriver, ENABLE_HSP_PERFORMANCE_MONITOR);
#else /* __MDW_CUBE2__ */
  HSP_HW_IF_Boot(hmw->hdriver, ENABLE_HSP_PERFORMANCE_MONITOR);
#endif  /* __MDW_CUBE2__ */

  /* Change HSP Middleware state */
  hmw->global_state = HSP_CORE_STATE_IDLE;
}

void hst_test_HSP_CORE_Init_NPlugE(hsp_core_handle_t *hmw, uint32_t *pSrc, uint32_t length, uint32_t fwCsize)
{
  /* Interfaces Initialization ---------------------------------------------------------------------------------------*/
  /* Initialize the BRAM memory interface */
  // if (HSP_BRAM_IF_Init(&(hmw->hbram), 0) != IF_OK)
  if (HSP_BRAM_IF_Init(&(hmw->hbram), hmw->hdriver) != HSP_IF_OK)
  {
    return;
  }

  /* Initialize the Firmware Interface */
  // if (HSP_HW_IF_Init(0) != IF_OK)
  // {
    // return;
  // }

  /* Register MW HSP Processing Event Callbacks */
//  HSP_HW_IF_RegisterProcessingEventCallback(0, HSP_CORE_FWEVT_ProcessingEventCallback);

  /* Load the Firmware & Plugin --------------------------------------------------------------------------------------*/
  /* Call the weak function to load Firmware */
  if (HSP_CORE_LoadFW(hmw) != HSP_CORE_OK)
  {
    return;
  }

#ifdef ARM_COMPILE
  load_hsp_data_cram(pSrc, 0, length);
#else // ARM_COMPILE
  uint32_t filler_cram = 0xffffffff;
  extern char _segment_end_cram_seg_PMw;
  uint32_t cram_start = (uint32_t) &_segment_end_cram_seg_PMw;
  printf("cram_start=0x%08x\n", cram_start);
  load_hsp_data_cram(pSrc, cram_start, length);
#endif // ARM_COMPILE

  // Force pluggin error malloc
/* #ifdef STM32U575xx */
/*   uint32_t cramSize8 = 20 * 1024; */
/*   uint32_t lastCramAdd = HSP_CRAM_BASE_ADDR + cramSize8 - 4; */
/*   uint32_t cramCurr = HSP_CRAM_BASE_ADDR + ((HSP_FW_DATA_CRAM_SIZE + 0) * 4) + (length * 4); */
/*   cramCurr -= 4; // Last word of CRAM is 0xFFFFFFFF */
/*   printf("CRAM curr @0x%x (0x%x 0x%x) (0x%x)\n", cramCurr, HSP_CRAM_BASE_ADDR, lastCramAdd, */
/*           HSP_FW_DATA_CRAM_SIZE); */
/*   for (; cramCurr < lastCramAdd; cramCurr += 4) { */
/*     // Write data in HSP CRAM */
/*     uint32_t *pTmp = (uint32_t *) cramCurr; */
/*     *pTmp = 0x99999999; */
/*   } */
/* #endif // STM32U575xx */

  /* Change HSP Middleware state */
  hmw->global_state = HSP_CORE_STATE_READY;

  /* Boot the HSP */
  pHspReg->CR = HSP_CR_BOOTEN;
  // Add tempo
  for (uint32_t tmpi = 0; tmpi < 20000; tmpi++) {
  }
#define HSP_DRAM_BASE_ADDR 0x41085000
#define HYP_DRAM_MAX_HEAP_ADD (HSP_DRAM_BASE_ADDR + 820) // hyp_dram_max_heap add
  uint32_t *pTmp = (uint32_t *) HYP_DRAM_MAX_HEAP_ADD;
  printf("HYP_DRAM_MAX_HEAP_ADD 0x%x\n", HYP_DRAM_MAX_HEAP_ADD);
  *pTmp = fwCsize;
  // Add tempo
  for (uint32_t tmpi = 0; tmpi < 20000; tmpi++) {
  }
   pHspReg->C2HSEMR = HSP_CR_BOOTEN;
  printf("HYP_DRAM_MAX_HEAP_ADD 0x%x\n", HYP_DRAM_MAX_HEAP_ADD);
  for (uint32_t tmpi = 0; tmpi < 20000; tmpi++) {
  }

  /* Change HSP Middleware state */
  hmw->global_state = HSP_CORE_STATE_IDLE;
}

#ifdef __HSP_DMA__

/* #define IF_ERROR HSP_IF_ERROR */
/* #define IF_OK HSP_IF_OK */

/** @addtogroup HSP_Exported_Functions_Group<TBD> HSP Motor Control family function
  *  @brief    HSP Motor Control functions for processing list
  *
@verbatim
  ==============================================================================
                  ##### HSP Motor Control functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to add function in processing list to:
    (+) Compute two phases input Clarke transformation + Park
    (+) Compute PI controller
    (+) Compute Circle_limitation
    (+) Compute PWMC setphasevoltage
    (+) Update FOC var structure
    (+) Compute the rotor electrical and mechanical angle

@endverbatim
  * @{
  */
/**
  * @brief Two phases input Clarke transformation (in float32 type) + Park
  *        Input angle is in q15 s16degree
  * @param hhsp      HSP handle.
  * @param pTheta    Input angle is in q15 s16degree
  * @param pIab      iab { a, b } type ab_t (float32_t)
  * @param pIqd      Output pointer for Iqd (float32_t)
  * @param ioType    User iotype information
  * @retval          Status returned.
  */
hsp_core_status_t HSP_SEQ_McClarkeParkS16d(hsp_core_handle_t *hmw, int32_t *pTheta, HSP_IabTypeDef2 *pIab,
                                           HSP_VqdTypeDef2 *pIqd, uint32_t ioType)
{
  uint32_t encoded = 0;
  uint32_t ouAddr1, ouAddr2, ouAddr3;

  if (HSP_UTILITIES_BuildParam(hmw, ioType, &encoded, (uint32_t) pTheta, &ouAddr1,
                               (uint32_t) pIab, &ouAddr2, (uint32_t) pIqd, &ouAddr3, 3) == IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM0, ouAddr1);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM1, ouAddr2);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM2, ouAddr3);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM15, encoded);
  if (HSP_HW_IF_SendCommand(hmw->hdriver, HSP_CMD_MC_CLARKE_PARK_S16D) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }
  return HSP_CORE_OK;
}

/**
  * @brief PI controller
  * @param hhsp       HSP handle.
  * @param inABuff    Input mesure: Stator values q or d (float32_t)
  * @param inBBuff    iqdref q or d (Q15)
  * @param cfgBuff    Handle buffer { KpGain, kiGain, pIntegralTerm, upperIntegralLimit, lowerIntegralLimit, UpperOutputLimit, LowerOutputLimit } (PID_Handle_t)
  * @param outBuff    Output Buffer identifier pidVdq q or d (float32_t)
  * @param ioType     User iotype information
  * @retval           Status returned.
  */
hsp_core_status_t HSP_SEQ_McPiController(hsp_core_handle_t *hmw, float32_t *inABuff, int32_t *inBBuff,
                                         HSP_McPiControllerTypeDef *cfgBuff, float32_t *outBuff, uint32_t ioType)
{
  uint32_t encoded = 0;
  uint32_t ouAddr1, ouAddr2, ouAddr3;

  if (HSP_UTILITIES_BuildParam(hmw, ioType, &encoded, (uint32_t) inABuff, &ouAddr1,
                               (uint32_t) inBBuff, &ouAddr2, (uint32_t) cfgBuff, &ouAddr3, 3) == IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }
  uint32_t ouAddr4;
  if (HSP_UTILITIES_ToBramABAddress(hmw, (uint32_t) outBuff, &ouAddr4) == IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM0, ouAddr1);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM1, ouAddr2);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM2, ouAddr3);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM3, ouAddr4);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM15, encoded);
  if (HSP_HW_IF_SendCommand(hmw->hdriver, HSP_CMD_MC_PI_CONTROLLER) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }
  return HSP_CORE_OK;
}

/**
  * @brief Circle_limitation
  * @param hhsp      HSP handle.
  * @param pVqd      Input Vdq (float32_t)
  * @param pCfg      Circle limitation handle { MaxModule, MaxVd } (CircleLimitation_Handle_t)
  * @param pQd       Circle limitation output q and d (float32_t)
  * @param ioType     User iotype information
  * @retval          Status returned.
  */
hsp_core_status_t HSP_SEQ_McCircleLimitation(hsp_core_handle_t *hmw, HSP_VqdTypeDef2 *pVqd,
                                             HSP_McClmBuffTypeDef *pCfg, HSP_VqdTypeDef2 *pQd, uint32_t ioType)
{
  uint32_t encoded = 0;
  uint32_t ouAddr1, ouAddr2, ouAddr3;

  if (HSP_UTILITIES_BuildParam(hmw, ioType, &encoded, (uint32_t) pVqd, &ouAddr1,
                               (uint32_t) pCfg, &ouAddr2, (uint32_t) pQd, &ouAddr3, 3) == IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM0, ouAddr1);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM1, ouAddr2);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM2, ouAddr3);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM15, encoded);
  if (HSP_HW_IF_SendCommand(hmw->hdriver, HSP_CMD_MC_CIRCLE_LIMITATION) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }
  return HSP_CORE_OK;
}

/**
  * @brief Inverse park for Q15S16 degree angle
  * @param hhsp      HSP handle.
  * @param pTheta    Input buffer for angle in Q15 S16degree
  * @param pVqd      Input buffer for Vqd (float32_t)
  * @param pVab      Output Buffer identifier valphabeta (alphabeta_t, float32_t)
  * @param ioType     User iotype information
  * @retval          Status returned.
  */
hsp_core_status_t HSP_SEQ_McIParkS16d(hsp_core_handle_t *hmw, int32_t *pTheta, HSP_VqdTypeDef2 *pVqd,
                                      HSP_ValphabetaTypeDef2 *pVab, uint32_t ioType)
{
  uint32_t encoded = 0;
  uint32_t ouAddr1, ouAddr2, ouAddr3;

  if (HSP_UTILITIES_BuildParam(hmw, ioType, &encoded, (uint32_t) pTheta, &ouAddr1,
                               (uint32_t) pVqd, &ouAddr2, (uint32_t) pVab, &ouAddr3, 3) == IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM0, ouAddr1);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM1, ouAddr2);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM2, ouAddr3);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM15, encoded);
  if (HSP_HW_IF_SendCommand(hmw->hdriver, HSP_CMD_MC_IPARK_S16D) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }
  return HSP_CORE_OK;
}

/**
  * @brief PWMC setphasevoltage: WARNING output buffer datas are uint32_t
  * @param hhsp         HSP handle.
  * @param pVab         Input buffer for Stator voltage Valpha and Vbeta (float32_t)
  * @param pHandle      Output Buffer identifier PWMC Handle in uint32_t { pwmPeriod, Sector, lowDuty, midDuty, highDuty, CntPhA, CntPhB, CntPhC } (PWMC_Handle_t)
  * @param ioType     User iotype information
  * @retval             Status returned.
  */
hsp_core_status_t HSP_SEQ_McPwmcSetPhaseVoltage(hsp_core_handle_t *hmw, HSP_ValphabetaTypeDef2 *pVab,
                                                HSP_McPwmcBuffTypeDef *pHandle, uint32_t ioType)
{
  uint32_t encoded = 0;
  uint32_t ouAddr1, ouAddr2;

  if (HSP_UTILITIES_BuildParam(hmw, ioType, &encoded, (uint32_t) pVab, &ouAddr1,
                               (uint32_t) pHandle, &ouAddr2, 0, NULL, 2) == IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM0, ouAddr1);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM1, ouAddr2);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM15, encoded);
  if (HSP_HW_IF_SendCommand(hmw->hdriver, HSP_CMD_MC_PWMC_SETPHASEVOLTAGE) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }
  return HSP_CORE_OK;
}

/**
  * @brief Update FOC var structure for intermediates results qdt in Q15 in struct but in float in HSP: Idq and Vqd
  * @param hhsp      HSP handle.
  * @param pFocVar   FOC var structure buffer ID
  * @param pIqd      Iqd buffer ID (float buffer)
  * @param pVqd      Vqd buffer ID (float buffer)
  * @param ioType     User iotype information
  * @retval          Status returned.
  */
hsp_core_status_t HSP_SEQ_McUpdateFocVar(hsp_core_handle_t *hmw, HSP_McFocVarBuffTypeDef *pFocVar,
                                         HSP_VqdTypeDef2 *pIqd, HSP_VqdTypeDef2 *pVqd, uint32_t ioType)
{
  uint32_t encoded = 0;
  uint32_t ouAddr1, ouAddr2, ouAddr3;

  if (HSP_UTILITIES_BuildParam(hmw, ioType, &encoded, (uint32_t) pFocVar, &ouAddr1,
                               (uint32_t) pIqd, &ouAddr2, (uint32_t) pVqd, &ouAddr3, 3) == IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM0, ouAddr1);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM1, ouAddr2);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM2, ouAddr3);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM15, encoded);
  if (HSP_HW_IF_SendCommand(hmw->hdriver, HSP_CMD_MC_UPDATE_FOC_VAR) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }
  return HSP_CORE_OK;
}

/**
  * @brief It calculates the rotor electrical and mechanical angle, on the basis of the instantaneous value of the timer counter
  * @param hhsp                    HSP handle.
  * @param superBuffId             SpeednPosFdbk_Handle_t buffer ID (float buffer)
  * @param timCntAddr              Get the counter value external addr: LL_TIM_GetCounter(pHandle->TIMx)
  * @param U32MAXdivPulseNumber    It stores U32MAX/hPulseNumber
  * @param ioType     User iotype information
  * @retval                        Status returned.
  */
hsp_core_status_t HSP_SEQ_McEncCalcAngle(hsp_core_handle_t *hmw, ENCODER_Handle_t *superBuff,
                                         uint32_t timCntAddr, uint32_t U32MAXdivPulseNumber, uint32_t ioType)
{
  uint32_t encoded = 0;
  uint32_t ouAddr1, ouAddr2;

  if (HSP_UTILITIES_BuildParam(hmw, ioType, &encoded, (uint32_t) superBuff, &ouAddr1,
                               (uint32_t) timCntAddr, &ouAddr2, 0, NULL, 2) == IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM0, ouAddr1);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM1, ouAddr2);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM2, U32MAXdivPulseNumber);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM15, encoded);
  if (HSP_HW_IF_SendCommand(hmw->hdriver, HSP_CMD_MC_ENC_CALC_ANGLE) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }
  return HSP_CORE_OK;
}
/**
  * @}
*/

/************************ Here Digital Control API  to be moved in MDW *******************************/

/**
  * @brief This function is the constant RAMP
  * @param hmw       HSP handle.
  * @param pSts      Status result of the ramp
  * @param pCfg      Ramp configuration parameters
  * @param pDst      Output Buffer address
  * @param ioType    User iotype information
  * @retval          Status returned.
  */
hsp_core_status_t HSP_SEQ_Ramp_f32(hsp_core_handle_t *hmw, uint32_t *pSts, hsp_dc_ramp_cfg_t *pCfg,
                                   float32_t *pDst, uint32_t ioType)
{
  uint32_t encoded = 0;
  uint32_t ouAddr1, ouAddr2, ouAddr3;

  if (HSP_UTILITIES_BuildParam(hmw, ioType, &encoded, (uint32_t) pSts, &ouAddr1,
                               (uint32_t) pCfg, &ouAddr2, (uint32_t) pDst, &ouAddr3, 3) == IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM0, ouAddr1);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM1, ouAddr2);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM2, ouAddr3);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM15, encoded);

  if (HSP_HW_IF_SendCommand(hmw->hdriver, HSP_CMD_RAMP_F32) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }
  return HSP_CORE_OK;
}
#endif //__HSP_DMA__
#endif // HYP_TOOLS

void hsp_assert_dbg_param_failed(uint8_t *file, uint32_t line)
{
  printf("ERROR in file %s at line %d\n",file, line);
}

#endif // __HSP_TEST_COMMON_C__
