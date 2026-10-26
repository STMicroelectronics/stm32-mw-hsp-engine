/**
  ******************************************************************************************
  * \file nreg_hyp_set_gpo.c
  * \brief Test vect_set_gpo kernel
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
#include "hsp_test_common.h"
#include "hsp_test_mmap.h"
#ifdef HYPSA_SIMU
#include "core/hsp.h"
#else
#include "hsp.h"
#endif /* HYPSA_SIMU */

#include "hsp_core.h"

/*------------------------------------------------------------------------------
 * Defines
 *----------------------------------------------------------------------------*/

/// Info message name for this test
#ifdef HYP_UNITARY_TEST
#define TEST_NAME "nregs hyp vect_set_gpo"
#else // HYP_UNITARY_TEST
#define TEST_NAME "nregs HSP vect_set_gpo"
#endif // HYP_UNITARY_TEST

/*------------------------------------------------------------------------------
 * Types
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 * Variables
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 * Functions
 *----------------------------------------------------------------------------*/

/**
 * Check kernel result
 * Return nb check failed
 */
static uint32_t run_nreg(uint32_t fieldMask, uint32_t fieldVal)
{
  TEST_INFO_REPORT(TEST_NAME, "check F32\n");

  _errorReportCount = 0;
#define CMD_EVT 1

  test_hw_reset();
  hsp_core_status_t status = HSP_CORE_Init(&hmw, hmw.hdriver);

  status += HAL_HSP_ConfigureEOT(CMD_EVT, 0);

  // Start process configuration for list 0, trigger 0
  status += HSP_SEQ_StartRecordPL(&hmw, CMD_EVT);
  status += HSP_SEQ_SetGpo(&hmw, fieldMask, fieldVal);
  status += HSP_SEQ_StopRecordPL(&hmw);

  uint32_t nbCheckFailed = 0;
  // Now check eq sat
  status += test_enable_and_send_event(CMD_EVT);
  // Extra function to allow running scheduler when running on Hypsa platform
  test_wait_for_hsp();
  _errorReportCount = (status == HAL_OK) ? _errorReportCount : (_errorReportCount + 1);
  TEST_MEASURE_REPORT(TEST_NAME, 1, "F32\n");

  HSP_CORE_DeInit(&hmw);
  return nbCheckFailed;
}

/**
 * Check kernel result
 * Return nb check failed
 */
#ifdef __HSP_DMA__
static uint32_t run_nreg_err(uint32_t fieldMask, uint32_t fieldVal)
{
  TEST_INFO_REPORT(TEST_NAME, "check F32\n");

  _errorReportCount = 0;
#define CMD_EVT 1

  test_hw_reset();
  hsp_core_status_t status = HSP_CORE_Init(&hmw, hmw.hdriver);

  status += HAL_HSP_ConfigureEOT(CMD_EVT, 0);

  // Start process configuration for list 0, trigger 0
  status += HSP_SEQ_StartRecordPL(&hmw, CMD_EVT);
  status += HSP_SEQ_SetGpo(&hmw, fieldMask, fieldVal);
  status += HSP_SEQ_StopRecordPL(&hmw);

  uint32_t nbCheckFailed = 0;
  // Now check eq sat
  status += test_enable_and_send_event(CMD_EVT);
  // Extra function to allow running scheduler when running on Hypsa platform
  test_wait_for_hsp();
  _errorReportCount = (status == HAL_OK) ? _errorReportCount : (_errorReportCount + 1);
  TEST_MEASURE_REPORT(TEST_NAME, 1, "F32\n");
  uint32_t error = pHspReg->FWERR;
  if (error != HSP_CMD_STATUS_ERROR_GPO6N7_RESERVED) {
    TEST_INFO_REPORT(TEST_NAME, "Error: status 0x%x, error 0x%x\n", status, error);
    nbCheckFailed++;
  }

  HSP_CORE_DeInit(&hmw);
  return nbCheckFailed;
}
#endif // __HSP_DMA__


/**
 * Main test function
 */
int hsp_test_main(void)
{
  TEST_INFO_REPORT(TEST_NAME, "Starting test\n");
  uint32_t nbCheckFailed = 0;

#ifndef HYP_UNITARY_TEST
  nbCheckFailed += run_nreg(1, 1);
  nbCheckFailed += run_nreg(2, 2);
  nbCheckFailed += run_nreg(3, 1);
  nbCheckFailed += run_nreg(4, 2);
  nbCheckFailed += run_nreg(7, 7);
#endif // HYP_UNITARY_TEST

#ifdef __HSP_DMA__
  nbCheckFailed += run_nreg_err(0xc0, 6);
#endif // __HSP_DMA__

  TEST_END_REPORT(TEST_NAME, nbCheckFailed);
  return nbCheckFailed;
}
