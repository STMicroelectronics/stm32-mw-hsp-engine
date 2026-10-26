/**
  ******************************************************************************
  * @file    mw_hsp_valid_e_assert.c
  * @author  MDG-GPM application team
  * @brief   This file contains the MW HSP exhaustive assert validation function.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "mw_hsp_valid.h"
#include "mw_hsp_valid_e_assert.h"
#include "mw_hsp_valid_assert.h"
#include "hsp.h"
#include "hsp_bram_if.h"
#include "hsp_hw_if.h"
//#include "mw_valid_util_hsp.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
#define VALID_CHECK_RESULT() {                                  \
  if (AssertFailedCounter != AssertFailedCounterExpected)       \
  {                                                             \
    VALIDATION_CHECK_FAIL(__LINE__); goto __goto_end;           \
  }                                                             \
  assert_failed_counter_previous = AssertFailedCounterExpected; \
}

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private function ----------------------------------------------------------*/
static void empty_cb0(uint32_t mw_id);
static void empty_cb1(uint32_t mw_id, uint32_t value);
static void empty_cb2(uint32_t mw_id, uint32_t value1, uint32_t value2);

/**
  * @brief Exhaustive test: Check MW functions assert parameters
  * @par Test Description
  *  Check MW functions assert parameters.
  *  Test done by passing wrong parameters values to functions and verifying assert macro fail callback.
  *  Note: Functions calls with correct parameters values are tested in other tests.
  * @par Expected Results
  * Assert macro fail callback count corresponding to functions calls with wrong parameters count
  * @par Required Preconditions
  *  USE_HSP_ASSERT_DBG_PARAM == 1
  * @par SRS Requirement IDs
  *  None
  * @par Configuration Reference
  *  CF1
  * @retval
  * 0: Test passed
  * Value different from 0: Test failed
  */
uint32_t MW_HSP_E_Test_AssertDbgParam(void)
{
#if defined(USE_HSP_ASSERT_DBG_PARAM)
  uint32_t assert_failed_counter_previous = 0U;
  hsp_engine_context_t hmw;

  ValidCheckRunning = VALID_ASSERT_PARAM;

  AssertFailedCounterExpected = 0U;
  AssertFailedCounter = 0U;

  /***** HSP_CORE_Xxxx ************************************************************************************************/
  /* Tested : HAL_HSP_Init -------------------------------------------------------------------------------------------*/
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_CORE_Init(NULL, (void *)0xFFFFFFFFU); /* Wrong context address */
  }
  VALID_CHECK_RESULT();

    VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;

    HSP_CORE_Init(&hmw, NULL); /* Wrong driver address */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_CORE_DeInit ----------------------------------------------------------------------------------------*/
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_CORE_DeInit(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_CORE_OUTPUT_SetConfig -----------------------------------------------------------------------------------*/
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_CORE_OUTPUT_SetConfig(NULL, 0U, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_CORE_OUTPUT_Enable ------------------------------------------------------------------------------------ */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_CORE_OUTPUT_Enable(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_CORE_OUTPUT_Disable ------------------------------------------------------------------------------------------ */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_CORE_OUTPUT_Disable(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_CORE_OUTPUT_IsEnabled ---------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_CORE_OUTPUT_IsEnabled(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_CORE_EnableSmartClocking ---------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_CORE_EnableSmartClocking(NULL, HSP_CORE_SMART_CLOCKING_SPE); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_CORE_DisableSmartClocking ------------------------------------------------------------------------------ */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    HAL_HSP_STREAM_Buffer_ConfigTypeDef cfg = {.direction = HAL_HSP_STREAM_BUFFER_DIRECTION_RX, .sync_state = HAL_HSP_STREAM_BUFFER_SYNC_DISABLE};
    AssertFailedCounterExpected++;
    HSP_CORE_DisableSmartClocking(NULL, HSP_CORE_SMART_CLOCKING_SPE); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_CORE_GetSmartClockingStatus ------------------------------------------------------------------------------ */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    hal_hsp_stream_buffer_config_t cfg;
    AssertFailedCounterExpected++;
    HSP_CORE_GetSmartClockingStatus(NULL, HSP_CORE_SMART_CLOCKING_SPE); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_CORE_Lock --------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_CORE_Lock(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_CORE_GetState -------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_CORE_GetState(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_CORE_RegisterErrorCallback ----------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_CORE_RegisterErrorCallback(NULL, empty_cb2); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_CORE_RegisterStreamBufferWriteCpltCallback ---------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_CORE_RegisterStreamBufferWriteCpltCallback(NULL, empty_cb1); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_CORE_RegisterStreamBufferReadCpltCallback -------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_CORE_RegisterStreamBufferReadCpltCallback(NULL, empty_cb1); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /***** HSP_BRAM_Xxxx ************************************************************************************************/
  /* Tested : HSP_BRAM_Malloc ----------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_Malloc(NULL, 0U, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_GetFreeSize ------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_GetFreeSize(NULL, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_SetPopAddress ------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    hal_hsp_trgin_config_t cfg;
    AssertFailedCounterExpected++;
    HSP_BRAM_SetPopAddress(NULL, 0U, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_MallocStateBuffer_Fir ---------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_MallocStateBuffer_Fir(NULL, 0U, 0U, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_MallocStateBuffer_FirDecimate ---------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_MallocStateBuffer_FirDecimate(NULL, 0U, 0U, 0U, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_MallocStateBuffer_BiquadCascadeDf1 --------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_MallocStateBuffer_BiquadCascadeDf1(NULL, 0U, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_MallocStateBuffer_BiquadCascadeDf2t --------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_MallocStateBuffer_BiquadCascadeDf2t(NULL, 0U, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_MallocStateBuffer_Lms --------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_MallocStateBuffer_Lms(NULL, 0U, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_MallocStateBuffer_IirLattice --------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_MallocStateBuffer_IirLattice(NULL, 0U, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_MallocStateBuffer_IirDf1 -------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_MallocStateBuffer_IirDf1(NULL, 0U, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();
  
#if defined(__HSP_DMA__)
  /* Tested : HSP_BRAM_MallocStateBuffer_Iir4p4z -------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_MallocStateBuffer_Iir4p4z(NULL, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();
#endif /* __HSP_DMA__ */

  /* Tested : HSP_BRAM_MallocStateBuffer_Iir3p3z -------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_MallocStateBuffer_Iir3p3z(NULL, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_MallocStateBuffer_Iir2p2z -------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_MallocStateBuffer_Iir2p2z(NULL, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_EnableConflictAccessCounter -------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_EnableConflictAccessCounter(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_DisableConflictAccessCounter ----------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_DisableConflictAccessCounter(NULL); /* Wrong handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_GetConflictAccessCounter ------------------------------------------------------------------------------ */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_GetConflictAccessCounter(NULL); /* Wrong handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_SetBandwidthArbitration ------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_SetBandwidthArbitration(NULL, HSP_BRAM_ARBITRATION_LATENCY_16_CYCLES); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_GetBandwidthArbitration ------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_GetBandwidthArbitration(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /***** HSP_SEQ_Xxxx *************************************************************************************************/
  /* Tested : HSP_SEQ_StartRecordPL ------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_SEQ_StartRecordPL(NULL, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_SEQ_StopRecordPL ------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_SEQ_StopRecordPL(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_SEQ_RunTask ------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_SEQ_RunTask(NULL, 0U, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_SEQ_ResetPL ------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_SEQ_ResetPL(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_SEQ_EVENT_SetConfig_StreamBuffer ---------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    hsp_seq_event_stream_buffer_config_t cfg;
    AssertFailedCounterExpected++;
    HSP_SEQ_EVENT_SetConfig_StreamBuffer(NULL, HSP_SEQ_EVENT_1, &cfg); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_SEQ_EVENT_SetConfig_StreamBuffer(&hmw, HSP_SEQ_EVENT_1, NULL); /* NULL config */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_SEQ_STREAM_GetBufferAddress --------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_SEQ_STREAM_GetBufferAddress(NULL, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_SEQ_STREAM_Buffer_Start ------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    int32_t buffer[2U];
    AssertFailedCounterExpected++;
    HSP_SEQ_STREAM_Buffer_Start(NULL, 0U, buffer, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_SEQ_STREAM_Buffer_Start(&hmw, 0U, NULL, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_SEQ_STREAM_EnableIntToFloat ------------------------------------------------------------------------ */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_SEQ_STREAM_EnableIntToFloat(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_SEQ_STREAM_DisableIntToFloat -------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_SEQ_STREAM_DisableIntToFloat(NULL); /* Wrong handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_SEQ_STREAM_Enable -------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_SEQ_STREAM_Enable(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_SEQ_STREAM_Disable ------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_SEQ_STREAM_Disable(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_SEQ_EVENT_SetConfig_Trigger ----------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    hsp_seq_event_trigger_config_t cfg;
    AssertFailedCounterExpected++;
    HSP_SEQ_EVENT_SetConfig_Trigger(NULL, HSP_SEQ_EVENT_1, &cfg); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_SEQ_EVENT_SetConfig_Trigger(&hmw, HSP_SEQ_EVENT_1, NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_SEQ_EVENT_SetConfig_CSEG -------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_SEQ_EVENT_SetConfig_CSEG(NULL, HSP_SEQ_EVENT_1, HSP_SEQ_EVENT_SYNC_TCU_DISABLED); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_SEQ_EVENT_SetConfig_SPE --------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_SEQ_EVENT_SetConfig_SPE(NULL, HSP_SEQ_EVENT_1, HSP_SEQ_EVENT_SYNC_TCU_DISABLED); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_SEQ_EVENT_Enable ---------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_SEQ_EVENT_Enable(NULL, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_SEQ_EVENT_Disable ---------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_SEQ_EVENT_Disable(NULL, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_SEQ_EVENT_GetStatus ---------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_SEQ_EVENT_GetStatus(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_SEQ_EVENT_Trig_CSEG -------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_SEQ_EVENT_Trig_CSEG(NULL, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_SEQ_EVENT_PollForPending ----------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_SEQ_EVENT_PollForPending(NULL, 0U, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_OUTPUT_SetConfigTrigger(&hhsp, (hal_hsp_output_trigger_t)0xFFFFFFFFUL, HAL_HSP_OUTPUT_TRIGGER_NONE); /* Wrong TRIGGER */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_OUTPUT_SetConfigTrigger(&hhsp, HAL_HSP_OUTPUT_TRIGGER_0, (hal_hsp_output_trigger_source_t)0xFFFFFFFFUL); /* Wrong Source */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_OUTPUT_GetConfigTrigger ----------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_OUTPUT_GetConfigTrigger(NULL, HAL_HSP_OUTPUT_TRIGGER_0); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_OUTPUT_GetConfigTrigger(&hhsp, (hal_hsp_output_trigger_t)0xFFFFFFFFUL); /* Wrong TRIGGER */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_OUTPUT_Enable ----------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_OUTPUT_Enable(NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_OUTPUT_Disable ----------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_OUTPUT_Disable(NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_OUTPUT_IsEnabled ------------------------------------------------------------------------------ */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_OUTPUT_IsEnabled(NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_TSC_SetConfig --------------------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    hal_hsp_tsc_config_t cfg;
//    AssertFailedCounterExpected++;
//    HAL_HSP_TSC_SetConfig(NULL, &cfg); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    hal_hsp_tsc_config_t cfg;
//    cfg.prescaler = (hal_hsp_tsc_prescaler_t)0xFFFFFFFFUL;
//    cfg.counter = HAL_HSP_TSC_FREE_COUNTER_DISABLE;
//    cfg.filter = HAL_HSP_TSC_TASK_FILTER_NONE;
//    AssertFailedCounterExpected++;
//    HAL_HSP_TSC_SetConfig(&hhsp, &cfg); /* Wrong prescaler */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    hal_hsp_tsc_config_t cfg;
//    cfg.prescaler = HAL_HSP_TSC_PRESCALER_BYPASSED;
//    cfg.counter = (hal_hsp_tsc_free_running_counter_state_t)0xFFFFFFFFUL;
//    cfg.filter = HAL_HSP_TSC_TASK_FILTER_NONE;
//    AssertFailedCounterExpected++;
//    hhsp.Instance = (HSP_TypeDef *)0xFFFFFFFFUL;
//    HAL_HSP_TSC_SetConfig(&hhsp, &cfg); /* Wrong counter */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    hal_hsp_tsc_config_t cfg;
//    cfg.prescaler = HAL_HSP_TSC_PRESCALER_BYPASSED;
//    cfg.counter = HAL_HSP_TSC_FREE_COUNTER_DISABLE;
//    cfg.filter = (hal_hsp_tsc_task_filter_t)0xFFFFFFFFUL;
//    AssertFailedCounterExpected++;
//    hhsp.Instance = (HSP_TypeDef *)0xFFFFFFFFUL;
//    HAL_HSP_TSC_SetConfig(&hhsp, &cfg); /* Wrong filter */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_TSC_GetConfig --------------------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    hal_hsp_tsc_config_t cfg;
//    AssertFailedCounterExpected++;
//    HAL_HSP_TSC_GetConfig(NULL, &cfg); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_TSC_Enable ------------------------------------------------------------------------------------ */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_TSC_Enable(NULL, HAL_HSP_TSC_CAPTURE_MODE_SPE_BREAKS); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_TSC_Enable(&hhsp, (hal_hsp_tsc_capture_mode_t)0xFFFFFFFFUL); /* Wrong mode */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_TSC_Disable ----------------------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_TSC_Disable(NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_TSC_IsActiveFlag ------------------------------------------------------------------------------ */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_TSC_IsActiveFlag(NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_TSC_GetTimeStamp ------------------------------------------------------------------------------ */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    hal_hsp_tsc_timestamp_t timestamp;
//    AssertFailedCounterExpected++;
//    HAL_HSP_TSC_GetTimeStamp(NULL, &timestamp); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_TSC_Enable_IT --------------------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_TSC_Enable_IT(NULL, HAL_HSP_TSC_CAPTURE_MODE_SPE_BREAKS); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_TSC_Enable_IT(&hhsp, (hal_hsp_tsc_capture_mode_t)0xFFFFFFFFUL); /* Wrong mode */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_TSC_Disable_IT -------------------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_TSC_Disable_IT(NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_BRAM_EnableConflictAccessCounter -------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_BRAM_EnableConflictAccessCounter(NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_BRAM_DisableConflictAccessCounter ------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_BRAM_DisableConflictAccessCounter(NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_BRAM_IsEnabledConflictAccessCounter ----------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_BRAM_IsEnabledConflictAccessCounter(NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_BRAM_GetConflictAccessCounter ----------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_BRAM_GetConflictAccessCounter(NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_BRAM_SetBandwidthArbitration ------------------------------------------------------------------ */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_BRAM_SetBandwidthArbitration(NULL, HAL_HSP_BRAM_ARBITRATION_LATENCY_16_CYCLES); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_BRAM_SetBandwidthArbitration(&hhsp, (hal_hsp_bram_arbitration_t)0xFFFFFFFFUL); /* Wrong mode */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_BRAM_GetBandwidthArbitration ------------------------------------------------------------------ */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_BRAM_GetBandwidthArbitration(NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_GetPerformanceCycleCount ---------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_GetPerformanceCycleCount(NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_GetFirmwareError ------------------------------------------------------------------------------ */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_GetFirmwareError(NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_SPE_EVENT_EnableIT ---------------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_SPE_EVENT_EnableIT(NULL, HAL_HSP_IT_EVT_SPE_ENTER_IN_WFE); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  hhsp.Instance = HSP1;
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_SPE_EVENT_EnableIT(&hhsp, HAL_HSP_IT_ERR_SPE_FW); /* Wrong Event IT */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_EVENT_SPE_DisableIT --------------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_SPE_EVENT_DisableIT(NULL, HAL_HSP_IT_EVT_SPE_ENTER_IN_WFE); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_SPE_EVENT_DisableIT(&hhsp, HAL_HSP_IT_ERR_SPE_FW); /* Wrong Event IT */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_SPE_EVENT_IsEnabledIT ------------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_SPE_EVENT_IsEnabledIT(NULL, HAL_HSP_IT_EVT_SPE_ENTER_IN_WFE); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_SPE_EVENT_IsEnabledIT(&hhsp, HAL_HSP_IT_ERR_SPE_FW); /* Wrong Event IT */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_SPE_ERROR_EnableIT ---------------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_SPE_ERROR_EnableIT(NULL, HAL_HSP_IT_ERR_SPE_FW); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_SPE_ERROR_EnableIT(&hhsp, HAL_HSP_IT_EVT_SPE_ENTER_IN_WFE); /* Wrong Error IT */
//  }
//  VALID_CHECK_RESULT();
//
//    /* Tested : HAL_HSP_SPE_ERROR_DisableIT ------------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_SPE_ERROR_DisableIT(NULL, HAL_HSP_IT_ERR_SPE_FW); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_SPE_ERROR_DisableIT(&hhsp, HAL_HSP_IT_EVT_SPE_ENTER_IN_WFE); /* Wrong Error IT */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_SPE_ERROR_IsEnabledIT ------------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_SPE_ERROR_IsEnabledIT(NULL, HAL_HSP_IT_ERR_SPE_FW); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_SPE_ERROR_IsEnabledIT(&hhsp, HAL_HSP_IT_EVT_SPE_ENTER_IN_WFE); /* Wrong Error IT */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_SNOOP_Enable ---------------------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_SNOOP_Enable(NULL, 0U); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_SNOOP_Enable(&hhsp, 0xFFFFFFFFUL); /* Wrong signals */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_SNOOP_Disable --------------------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_SNOOP_Disable(NULL, 0U); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_SNOOP_Disable(&hhsp, 0xFFFFFFFFUL); /* Wrong group id */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_BREAK_EnableCriticalEvent --------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_BREAK_EnableCriticalEvent(NULL, HAL_HSP_BREAK_OUTPUT_0, HAL_HSP_BREAK_CRITICAL_EVENT_ALL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_BREAK_EnableCriticalEvent(&hhsp, (hal_hsp_break_output_t)0xFFFFFFFFUL, HAL_HSP_BREAK_CRITICAL_EVENT_ALL); /* Wrong output id */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_BREAK_EnableCriticalEvent(&hhsp, HAL_HSP_BREAK_OUTPUT_0, 0xFFFFFFFFUL); /* Wrong event id */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_BREAK_DisbleCriticalEvent --------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_BREAK_DisableCriticalEvent(NULL, HAL_HSP_BREAK_OUTPUT_0, HAL_HSP_BREAK_CRITICAL_EVENT_ENABLED); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_BREAK_DisableCriticalEvent(&hhsp, (hal_hsp_break_output_t)0xFFFFFFFFUL, HAL_HSP_BREAK_CRITICAL_EVENT_ALL); /* Wrong output id */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_BREAK_DisableCriticalEvent(&hhsp, HAL_HSP_BREAK_OUTPUT_0, 0xFFFFFFFFUL); /* Wrong event id */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_BREAK_IsEnabledCriticalEvent ------------------------------------------------------------------ */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_BREAK_IsEnabledCriticalEvent(NULL, HAL_HSP_BREAK_OUTPUT_0, 0U); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_BREAK_IsEnabledCriticalEvent(&hhsp, (hal_hsp_break_output_t)0xFFFFFFFFUL, 0U); /* Wrong output id */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_BREAK_IsEnabledCriticalEvent(&hhsp, HAL_HSP_BREAK_OUTPUT_0, 0xFFFFFFFFUL); /* Wrong event id */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_BREAK_EnableFreezeEvent ----------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_BREAK_EnableFreezeEvent(NULL, HAL_HSP_BREAK_FREEZE_EVENT_ALL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_BREAK_EnableFreezeEvent(&hhsp, 0xFFFFFFFFUL); /* Wrong event id */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_BREAK_DisableFreezeEvent ---------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_BREAK_DisableFreezeEvent(NULL, HAL_HSP_BREAK_FREEZE_EVENT_ALL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_BREAK_DisableFreezeEvent(&hhsp, 0xFFFFFFFFUL); /* Wrong event id */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_BREAK_IsEnabledFreezeEvent -------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_BREAK_IsEnabledFreezeEvent(NULL, HAL_HSP_BREAK_FREEZE_EVENT_ALL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_BREAK_IsEnabledFreezeEvent(&hhsp, 0xFFFFFFFFUL); /* Wrong event id */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_Lock ------------------------------------------------------------------------------------------ */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_Lock(NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_CNN_EnterSafeMode ----------------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_CNN_EnterSafeMode(NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_CNN_ExitSafeMode ------------------------------------------------------------------------------ */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_CNN_ExitSafeMode(NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//#if defined(USE_HAL_HSP_REGISTER_CALLBACKS) && (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
//  /* Tested : HAL_HSP_RegisterMspInitCallback ----------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterMspInitCallback(NULL, NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterMspInitCallback(&hhsp, NULL); /* NULL callback */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_RegisterMspDeInitCallback --------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterMspDeInitCallback(NULL, NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterMspDeInitCallback(&hhsp, NULL); /* NULL callback */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_RegisterSPE_DirectCommandCpltCallback --------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterSPE_DirectCommandCpltCallback(NULL, NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterSPE_DirectCommandCpltCallback(&hhsp, NULL); /* NULL callback */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_RegisterSPE_TaskCpltCallback ------------------------------------------------------------------ */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterSPE_TaskCpltCallback(NULL, NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterSPE_TaskCpltCallback(&hhsp, NULL); /* NULL callback */
//  }
//  VALID_CHECK_RESULT();
//  
//  /* Tested : HAL_HSP_RegisterSPE_FPUSaturationCallback ------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterSPE_FPUSaturationCallback(NULL, NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterSPE_FPUSaturationCallback(&hhsp, NULL); /* NULL callback */
//  }
//  VALID_CHECK_RESULT();
//  
//  /* Tested : HAL_HSP_RegisterSPE_RunStateCallback ------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterSPE_RunStateCallback(NULL, NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterSPE_RunStateCallback(&hhsp, NULL); /* NULL callback */
//  }
//  VALID_CHECK_RESULT();
//  
//  /* Tested : HAL_HSP_RegisterSTREAM_BufferEmptyCallback ------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterSTREAM_BufferEmptyCallback(NULL, NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterSTREAM_BufferEmptyCallback(&hhsp, NULL); /* NULL callback */
//  }
//  VALID_CHECK_RESULT();
//  
//  /* Tested : HAL_HSP_RegisterSTREAM_BufferFullCallback ------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterSTREAM_BufferFullCallback(NULL, NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterSTREAM_BufferFullCallback(&hhsp, NULL); /* NULL callback */
//  }
//  VALID_CHECK_RESULT();
//  
//  /* Tested : HAL_HSP_RegisterTCU_TaskOverlapCallback --------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterTCU_TaskOverlapCallback(NULL, NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterTCU_TaskOverlapCallback(&hhsp, NULL); /* NULL callback */
//  }
//  VALID_CHECK_RESULT();
//  
//  /* Tested : HAL_HSP_RegisterTCU_TaskStartedCallback --------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterTCU_TaskStartedCallback(NULL, NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterTCU_TaskStartedCallback(&hhsp, NULL); /* NULL callback */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_RegisterTCU_TaskEndedCallback ----------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterTCU_TaskEndedCallback(NULL, NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterTCU_TaskEndedCallback(&hhsp, NULL); /* NULL callback */
//  }
//  VALID_CHECK_RESULT();
//  
//  /* Tested : HAL_HSP_RegisterTSC_TimestampReadyCallback ------------------------------------------------------------ */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterTSC_TimestampReadyCallback(NULL, NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterTSC_TimestampReadyCallback(&hhsp, NULL); /* NULL callback */
//  }
//  VALID_CHECK_RESULT();
//  
//  /* Tested : HAL_HSP_RegisterErrorCallback ------------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterErrorCallback(NULL, NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterErrorCallback(&hhsp, NULL); /* NULL callback */
//  }
//  VALID_CHECK_RESULT();
//  
//  /* Tested : HAL_HSP_RegisterFWEVT_ProcessingEventCallback --------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterFWEVT_ProcessingEventCallback(NULL, NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_RegisterFWEVT_ProcessingEventCallback(&hhsp, NULL); /* NULL callback */
//  }
//  VALID_CHECK_RESULT();
//#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
//
//  /* Tested : HAL_HSP_GetState -------------------------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_GetState(NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_GetError -------------------------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_GetError(NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_GetBootErrorCode ------------------------------------------------------------------------------ */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_GetBootErrorCode(NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HAL_HSP_GetMsgBoxErrorCode ---------------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HAL_HSP_GetBootErrorCode(NULL); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();

__goto_end:
  ValidCheckRunning = VALID_DEFAULT_CHECK;

#else
  VALIDATION_TEST_UNTESTABLE_RUNTIME("USE_HSP_ASSERT_DBG_PARAM is Disabled");
  return VALIDATION_RETURN_TEST_SKIPPED;

#endif /* USE_HSP_ASSERT_DBG_PARAM */

  /* Test end */
  return VALIDATION_RETURN_TEST_DONE;
}

/**
  * @brief Exhaustive test: Check MW Interfaces functions assert parameters
  * @par Test Description
  *  Check MW functions assert parameters.
  *  Test done by passing wrong parameters values to functions and verifying assert macro fail callback.
  *  Note: Functions calls with correct parameters values are tested in other tests.
  * @par Expected Results
  * Assert macro fail callback count corresponding to functions calls with wrong parameters count
  * @par Required Preconditions
  *  USE_HSP_ASSERT_DBG_PARAM == 1
  * @par SRS Requirement IDs
  *  None
  * @par Configuration Reference
  *  CF1
  * @retval
  * 0: Test passed
  * Value different from 0: Test failed
  */
uint32_t MW_HSP_E_Test_AssertDbgParam_interfaces(void)
{
#if defined(USE_HSP_ASSERT_DBG_PARAM)
  uint32_t assert_failed_counter_previous = 0U;
  hsp_bram_handle_t hbram;

  ValidCheckRunning = VALID_ASSERT_PARAM;

  AssertFailedCounterExpected = 0U;
  AssertFailedCounter = 0U;

  /***** HSP_BRAM_IF_Xxx **********************************************************************************************/
  /* Tested : HSP_BRAM_IF_GetFreeSize -------------------------------------------------------------------------------------------*/
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_IF_GetFreeSize(NULL, HSP_BRAM_ALLOCATION_DEFAULT); /* Wrong context address */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_IF_Init ----------------------------------------------------------------------------------------*/
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_IF_Init(NULL, (void *)0xDEADDEAD); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_IF_Init(&hbram, NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_IF_DeInit -----------------------------------------------------------------------------------*/
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_IF_DeInit(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_IF_Malloc ------------------------------------------------------------------------------------ */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_IF_Malloc(NULL, 0U, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_IF_SetPopAddress ------------------------------------------------------------------------------------------ */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_IF_SetPopAddress(NULL, (void *)0xDEADDEAD, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_IF_SetPopAddress(&hbram, NULL, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_IF_MallocStateBuffer_Fir ---------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_IF_MallocStateBuffer_Fir(NULL, 0U, 0U, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_IF_MallocStateBuffer_FirDecimate ---------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_IF_MallocStateBuffer_FirDecimate(NULL, 0U, 0U, 0U, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_IF_MallocStateBuffer_BiquadCascadeDf1 ------------------------------------------------------------------------------ */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    HAL_HSP_STREAM_Buffer_ConfigTypeDef cfg = {.direction = HAL_HSP_STREAM_BUFFER_DIRECTION_RX, .sync_state = HAL_HSP_STREAM_BUFFER_SYNC_DISABLE};
    AssertFailedCounterExpected++;
    HSP_BRAM_IF_MallocStateBuffer_BiquadCascadeDf1(NULL, 0U, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_IF_MallocStateBuffer_BiquadCascadeDf2t ------------------------------------------------------------------------------ */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    hal_hsp_stream_buffer_config_t cfg;
    AssertFailedCounterExpected++;
    HSP_BRAM_IF_MallocStateBuffer_BiquadCascadeDf2t(NULL, 0U, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_IF_MallocStateBuffer_Lms --------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_IF_MallocStateBuffer_Lms(NULL, 0U, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_IF_MallocStateBuffer_IirLattice -------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_IF_MallocStateBuffer_IirLattice(NULL, 0U, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_IF_MallocStateBuffer_IirDf1 ----------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_IF_MallocStateBuffer_IirDf1(NULL, 0U, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

#if defined(__HSP_DMA__)
  /* Tested : HSP_BRAM_IF_MallocStateBuffer_Iir4p4z ---------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_IF_MallocStateBuffer_Iir4p4z(NULL, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();
#endif /* __HSP_DMA__ */

  /* Tested : HSP_BRAM_IF_MallocStateBuffer_Iir3p3z -------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_IF_MallocStateBuffer_Iir3p3z(NULL, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_IF_MallocStateBuffer_Iir2p2z ----------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_IF_MallocStateBuffer_Iir2p2z(NULL,HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_GetFreeSize ------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_GetFreeSize(NULL, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_SetPopAddress ------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    hal_hsp_trgin_config_t cfg;
    AssertFailedCounterExpected++;
    HSP_BRAM_SetPopAddress(NULL, 0U, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_MallocStateBuffer_Fir ---------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_MallocStateBuffer_Fir(NULL, 0U, 0U, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_MallocStateBuffer_FirDecimate ---------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_MallocStateBuffer_FirDecimate(NULL, 0U, 0U, 0U, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_MallocStateBuffer_BiquadCascadeDf1 --------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_MallocStateBuffer_BiquadCascadeDf1(NULL, 0U, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_MallocStateBuffer_BiquadCascadeDf2t --------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_MallocStateBuffer_BiquadCascadeDf2t(NULL, 0U, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_MallocStateBuffer_Lms --------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_MallocStateBuffer_Lms(NULL, 0U, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_MallocStateBuffer_IirLattice --------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_MallocStateBuffer_IirLattice(NULL, 0U, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_MallocStateBuffer_IirDf1 -------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_MallocStateBuffer_IirDf1(NULL, 0U, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();
  
#if defined(__HSP_DMA__)
  /* Tested : HSP_BRAM_MallocStateBuffer_Iir4p4z -------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_MallocStateBuffer_Iir4p4z(NULL, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();
#endif /* __HSP_DMA__ */

  /* Tested : HSP_BRAM_MallocStateBuffer_Iir3p3z -------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_MallocStateBuffer_Iir3p3z(NULL, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_BRAM_MallocStateBuffer_Iir2p2z -------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_BRAM_MallocStateBuffer_Iir2p2z(NULL, HSP_BRAM_ALLOCATION_DEFAULT); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /***** HSP_HW_IF_Xxx ************************************************************************************************/
  /* Tested : HSP_HW_IF_Init -------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_Init(NULL, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_LoadFW ----------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_LoadFW(NULL, (void *)0xDEADDEAD, (void *)0xDEADDEAD); /* Wrong handle */
  }
  VALID_CHECK_RESULT();

  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_LoadFW((void *)0xDEADDEAD, NULL, (void *)0xDEADDEAD); /* Wrong handle */
  }
  VALID_CHECK_RESULT();

  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_LoadFW((void *)0xDEADDEAD, (void *)0xDEADDEAD, NULL); /* Wrong handle */
  }
  VALID_CHECK_RESULT();
  
  /* Tested : HSP_HW_IF_LoadPlugin ------------------------------------------------------------------------------ */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_LoadPlugin(NULL, (void *)0xDEADDEAD, 0U); /* Wrong handle */
  }
  VALID_CHECK_RESULT();

  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_LoadPlugin((void *)0xDEADDEAD, NULL, 0U); /* Wrong handle */
  }
  VALID_CHECK_RESULT();
  
  /* Tested : HSP_HW_IF_Boot ------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_Boot(NULL, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_GetPerformanceCounter ------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_GetPerformanceCounter(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_EnableSmartClocking ------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_EnableSmartClocking(NULL, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_STI_SetPortAddress ------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_STI_SetPortAddress(NULL, 0U, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_OUTPUT_SetConfig ------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_OUTPUT_SetConfig(NULL, 0U, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_OUTPUT_Enable ------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_OUTPUT_Enable(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_OUTPUT_IsEnabled ---------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_OUTPUT_IsEnabled(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_SendCommand --------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_SendCommand(NULL, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_WriteParameter ------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_WriteParameter(NULL, 0U, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_ClearFWERR ------------------------------------------------------------------------ */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_ClearFWERR(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_SEQ_StartRecord -------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_SEQ_StartRecord(NULL, 0U); /* Wrong handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_SEQ_StopRecord -------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_SEQ_StopRecord(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_SEQ_ResetPL ------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_SEQ_ResetPL(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_SEQ_RunTask ----------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    hsp_seq_event_trigger_config_t cfg;
    AssertFailedCounterExpected++;
    HSP_HW_IF_SEQ_RunTask(NULL, 0U, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_SEQ_EVENT_SetConfig_StreamBuffer -------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_SEQ_EVENT_SetConfig_StreamBuffer(NULL, 0U, 0U, 0U, 0U, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_SEQ_STREAM_EnableIntToFloat --------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_SEQ_STREAM_EnableIntToFloat(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_SEQ_STREAM_DisableIntToFloat ---------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_SEQ_STREAM_DisableIntToFloat(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_SEQ_STREAM_Enable ---------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_SEQ_STREAM_Enable(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_SEQ_STREAM_Disable ---------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_SEQ_STREAM_Disable(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_SEQ_STREAM_GetBufferAddress -------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_SEQ_STREAM_GetBufferAddress(NULL, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_SEQ_STREAM_Buffer_Start ----------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_SEQ_STREAM_Buffer_Start(NULL, 0U, (int32_t *)0xDEADDEAD, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_SEQ_STREAM_Buffer_Start((void *)0xDEADDEAD, 0U, NULL, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_SEQ_EVENT_SetConfig_Trigger ----------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_SEQ_EVENT_SetConfig_Trigger(NULL, 0U, 0U, 0U, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_SEQ_EVENT_SetConfig_CSEG ----------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_SEQ_EVENT_SetConfig_CSEG(NULL, 0U, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_SEQ_EVENT_SetConfig_SPE ----------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_SEQ_EVENT_SetConfig_SPE(NULL, 0U, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_SEQ_EVENT_Enable ------------------------------------------------------------------------------ */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_SEQ_EVENT_Enable(NULL, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_SEQ_EVENT_Disable --------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    hal_hsp_tsc_config_t cfg;
    AssertFailedCounterExpected++;
    HSP_HW_IF_SEQ_EVENT_Disable(NULL, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_SEQ_EVENT_Trig_CSEG --------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    hal_hsp_tsc_config_t cfg;
    AssertFailedCounterExpected++;
    HSP_HW_IF_SEQ_EVENT_Trig_CSEG(NULL, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_SEQ_EVENT_PollForPending ------------------------------------------------------------------------------------ */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_SEQ_EVENT_PollForPending(NULL, 0U, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_BRAM_EnableConflictAccessCounter ----------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_BRAM_EnableConflictAccessCounter(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_BRAM_DisableConflictAccessCounter ------------------------------------------------------------------------------ */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_BRAM_DisableConflictAccessCounter(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_BRAM_GetConflictAccessCounter ------------------------------------------------------------------------------ */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_BRAM_GetConflictAccessCounter(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_BRAM_SetBandwidthArbitration --------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_BRAM_SetBandwidthArbitration(NULL, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_BRAM_GetBandwidthArbitration -------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_BRAM_GetBandwidthArbitration(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_Lock -------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_Lock(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

//  /* Tested : HSP_HW_IF_SEQ_EnableProclistEventsIT ------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HSP_HW_IF_SEQ_EnableProclistEventsIT(NULL, 0U); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  /* Tested : HSP_HW_IF_SEQ_DisableProclistEventsIT ----------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HSP_HW_IF_SEQ_DisableProclistEventsIT(NULL, 0U); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_EnableTaskComparator ----------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_EnableTaskComparator(NULL, 0U, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_DisableTaskComparator ------------------------------------------------------------------ */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_DisableTaskComparator(NULL, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_EnableTaskComparator_IT ------------------------------------------------------------------ */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_EnableTaskComparator_IT(NULL, 0U, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_DisableTaskComparator_IT ---------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_DisableTaskComparator_IT(NULL, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_TSC_EnableSPEBreak ------------------------------------------------------------------------------ */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_TSC_EnableSPEBreak(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_TSC_EnablePFCT ---------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_TSC_EnablePFCT(NULL, 0U, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_TSC_Disable --------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_TSC_Disable(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_GetFirmwareError ------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_GetFirmwareError(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_WaitAndReleaseSemaphore ---------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_WaitAndReleaseSemaphore(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

    /* Tested : HSP_HW_IF_WaitSemaphore ------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_WaitSemaphore(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_ReleaseSemaphore ------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_ReleaseSemaphore(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_CNN_Begin ---------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_CNN_Begin(NULL, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_CNN_StartOfProcess --------------------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_CNN_StartOfProcess(NULL, 0U); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_CNN_WaitEndOfProcess --------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_CNN_WaitEndOfProcess(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_CNN_End --------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_CNN_End(NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_RegisterErrorCallback ------------------------------------------------------------------ */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_RegisterErrorCallback(NULL, &empty_cb2); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_RegisterErrorCallback((void *)0xDEADDEAD, NULL); /* NULL handle */
  }
  VALID_CHECK_RESULT();

//  /* Tested : HSP_HW_IF_RegisterProcListEventsCallback ----------------------------------------------------------------------- */
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HSP_HW_IF_RegisterProcListEventsCallback(NULL, &empty_cb1); /* NULL handle */
//  }
//  VALID_CHECK_RESULT();
//
//  VALID_STORE_CONTEXT(context);
//  if (AssertFailedCounterExpected == assert_failed_counter_previous)
//  {
//    AssertFailedCounterExpected++;
//    HSP_HW_IF_RegisterProcListEventsCallback((void *)0xDEADDEAD, NULL); /* Wrong event id */
//  }
//  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_RegisterStreamBufferWriteCpltCallback ---------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_RegisterStreamBufferWriteCpltCallback(NULL, &empty_cb1); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_RegisterStreamBufferWriteCpltCallback((void *)0xDEADDEAD, NULL); /* Wrong event id */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_RegisterStreamBufferReadCpltCallback -------------------------------------------------------------------- */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_RegisterStreamBufferReadCpltCallback(NULL, &empty_cb1); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_RegisterStreamBufferReadCpltCallback((void *)0xDEADDEAD, NULL); /* Wrong event id */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_RegisterTCU_TaskStartedCallback ------------------------------------------------------------------------------------------ */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_RegisterTCU_TaskStartedCallback(NULL, &empty_cb1); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_RegisterTCU_TaskStartedCallback((void *)0xDEADDEAD, NULL); /* Wrong event id */
  }
  VALID_CHECK_RESULT();

  /* Tested : HSP_HW_IF_RegisterTCU_TaskEndedCallback ------------------------------------------------------------------------------------------ */
  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_RegisterTCU_TaskEndedCallback(NULL, &empty_cb1); /* NULL handle */
  }
  VALID_CHECK_RESULT();

  VALID_STORE_CONTEXT(context);
  if (AssertFailedCounterExpected == assert_failed_counter_previous)
  {
    AssertFailedCounterExpected++;
    HSP_HW_IF_RegisterTCU_TaskEndedCallback((void *)0xDEADDEAD, NULL); /* Wrong event id */
  }
  VALID_CHECK_RESULT();
{
  if (AssertFailedCounter != AssertFailedCounterExpected)
  {
    VALIDATION_CHECK_FAIL(__LINE__);
    goto __goto_end;
  }
  assert_failed_counter_previous = AssertFailedCounterExpected;
}

__goto_end:
  ValidCheckRunning = VALID_DEFAULT_CHECK;

#else
  VALIDATION_TEST_UNTESTABLE_RUNTIME("USE_HSP_ASSERT_DBG_PARAM is Disabled");
  return VALIDATION_RETURN_TEST_SKIPPED;

#endif /* USE_HSP_ASSERT_DBG_PARAM */

  /* Test end */
  return VALIDATION_RETURN_TEST_DONE;
}

                             
                             
                             
                             

static void empty_cb0(uint32_t mw_id)
{}

static void empty_cb1(uint32_t mw_id, uint32_t value)
{}

static void empty_cb2(uint32_t mw_id, uint32_t value1, uint32_t value2)
{}
