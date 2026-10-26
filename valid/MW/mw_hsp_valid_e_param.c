/**
  ******************************************************************************
  * @file    mw_hsp_valid_e_param.c
  * @author  GPM Application Team
  * @brief   This file contains the MW HSP exhaustive param validation function.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "mw_hsp_valid_e_param.h"
#include "mw_valid_assert.h"
#include "mw_hsp_valid_util.h"

/* Private macro -------------------------------------------------------------*/
/* Cube 2 to Cube 1 conversion */
#define HAL_INVALID_PARAM  HAL_ERROR

/* Private variables ---------------------------------------------------------*/

/* Test scope: USE_FULL_ASSERT */

/**
  * @brief Test MW functions erroneous parameters
  * @par Test Description
  *  Test the MW driver functions erroneous parameters (example: pointer with value "NULL").
  *  Test done by passing wrong parameters values to functions and verifying function returned value.
  *  Note: Functions calls with correct parameters values are tested in other tests.
  * @par Expected Results
  *  Function returned value equal to HAL_ERROR with error code HAL_INVALID_PARAM
  * @par Required Preconditions
  *  USE_FULL_ASSERT == 1
  * @par Test Hardware Connection
  *  None
  * @par Configuration Reference
  *  CF1
  * @par SRS Requirement IDs
  *  REQ_HSP_ROBU_01
  * @retval
  * Value "0" for test passed, otherwise test failed
  */
uint32_t MW_HSP_E_Test_CheckParam(void)
{
#if defined(USE_FULL_ASSERT)
  // /* Test all instances */
  // for (uint32_t instance_index = 0; instance_index < COUNTOF(apInstances); instance_index++)
  {
    hal_status_t status;
    hal_hsp_handle_t hhsp;

    ValidCheckRunning = VALID_CHECK_PARAM;

    /******************************************************************************************************************/
    /* Init/DeInit                                                                                                    */
    /******************************************************************************************************************/
    /*-- HAL_HSP_Init --------------------------------------------------------*/
    status = HAL_HSP_Init((hal_hsp_handle_t *)NULL);
    if (status != HAL_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}

    hhsp.Instance = NULL;
    status = HAL_HSP_Init(&hhsp);
    if (status != HAL_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    if ((hhsp.last_error_codes & HAL_HSP_ERROR_INVALID_PARAM) != HAL_HSP_ERROR_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    hhsp.last_error_codes = 0U; /* Reset for next test */

    hhsp.Instance = HSP1;

    /*-- HAL_HSP_LoadFirmware ------------------------------------------------*/
    uint8_t binary = 0U;

    hhsp.global_state = HAL_HSP_STATE_INIT;

    status = HAL_HSP_LoadFirmware(&hhsp, NULL, 1U, &binary, 1U);
    if (status != HAL_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    if ((hhsp.last_error_codes & HAL_HSP_ERROR_INVALID_PARAM) != HAL_HSP_ERROR_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    hhsp.last_error_codes = 0U; /* Reset for next test */

    status = HAL_HSP_LoadFirmware(&hhsp, &binary, 0U, NULL, 1U);
    if (status != HAL_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    if ((hhsp.last_error_codes & HAL_HSP_ERROR_INVALID_PARAM) != HAL_HSP_ERROR_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    hhsp.last_error_codes = 0U; /* Reset for next test */

    /*-- HAL_HSP_LoadPlugin --------------------------------------------------*/
    status = HAL_HSP_LoadPlugin(&hhsp, NULL, 1U);
    if (status != HAL_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    if ((hhsp.last_error_codes & HAL_HSP_ERROR_INVALID_PARAM) != HAL_HSP_ERROR_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    hhsp.last_error_codes = 0U; /* Reset for next test */

    hhsp.global_state = HAL_HSP_STATE_READY_TO_BOOT;
    /*-- HAL_HSP_Boot --------------------------------------------------------*/
    uint32_t cram_fake_address;
    hhsp.cram_address_for_plugin = (uint32_t)&cram_fake_address;
    status = HAL_HSP_Boot(&hhsp, (hal_hsp_boot_config_t *)NULL, 1U);
    if (status != HAL_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    if ((hhsp.last_error_codes & HAL_HSP_ERROR_INVALID_PARAM) != HAL_HSP_ERROR_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    hhsp.last_error_codes = 0U; /* Reset for next test */

    /* Force State to RUNNING for the rest of API */
    hhsp.global_state = HAL_HSP_STATE_RUNNING;

    /******************************************************************************************************************/
    /* Command                                                                                                        */
    /******************************************************************************************************************/

    /******************************************************************************************************************/
    /* STREAM Interface                                                                                               */
    /******************************************************************************************************************/
    /* -- HAL_HSP_STREAM_SetConfig ----------------------------------------------------------*/
    status = HAL_HSP_STREAM_SetConfig(&hhsp, HAL_HSP_STREAM_BUFFER_0, (hal_hsp_stream_buffer_config_t *)NULL);
    if (status != HAL_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    if ((hhsp.last_error_codes & HAL_HSP_ERROR_INVALID_PARAM) != HAL_HSP_ERROR_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    hhsp.last_error_codes = 0U; /* Reset for next test */

    /* -- HAL_HSP_STREAM_GetConfig -------------------------------------------*/
    hhsp.Instance = HSP1;
    status = HAL_HSP_STREAM_GetConfig(&hhsp, HAL_HSP_STREAM_BUFFER_0, (hal_hsp_stream_buffer_config_t *)NULL);
    if (status != HAL_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    if ((hhsp.last_error_codes & HAL_HSP_ERROR_INVALID_PARAM) != HAL_HSP_ERROR_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    hhsp.last_error_codes = 0U; /* Reset for next test */

    /* -- HAL_HSP_STREAM_Enable ----------------------------------------------*/
    /* -- HAL_HSP_STREAM_Disable ---------------------------------------------*/

    /******************************************************************************************************************/
    /* TRGIN Interface                                                                                                */
    /******************************************************************************************************************/
    /* -- HAL_HSP_TRGIN_SetConfig --------------------------------------------*/
    hhsp.Instance = HSP1;
    status = HAL_HSP_TRGIN_SetConfig(&hhsp, HAL_HSP_TRGIN_0, (hal_hsp_trgin_config_t *)NULL);
    if (status != HAL_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    if ((hhsp.last_error_codes & HAL_HSP_ERROR_INVALID_PARAM) != HAL_HSP_ERROR_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    hhsp.last_error_codes = 0U; /* Reset for next test */

    /* -- HAL_HSP_TRGIN_GetConfig --------------------------------------------*/
    hhsp.Instance = HSP1;
    status = HAL_HSP_TRGIN_GetConfig(&hhsp, HAL_HSP_TRGIN_0, (hal_hsp_trgin_config_t *)NULL);
    if (status != HAL_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    if ((hhsp.last_error_codes & HAL_HSP_ERROR_INVALID_PARAM) != HAL_HSP_ERROR_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    hhsp.last_error_codes = 0U; /* Reset for next test */

    /* -- HAL_HSP_TRGIN_Enable -----------------------------------------------*/
    /* -- HAL_HSP_TRGIN_Disable ----------------------------------------------*/

    /* -- HAL_HSP_TRGIN_EnableIT ---------------------------------------*/
    /* -- HAL_HSP_TRGIN_DisableIT --------------------------------------------*/

    /******************************************************************************************************************/
    /* Event Interface                                                                                                */
    /******************************************************************************************************************/
    /* -- HAL_HSP_EVENT_SetConfig --------------------------------------------*/
    status = HAL_HSP_EVENT_SetConfig(&hhsp, (hal_hsp_event_config_t *)NULL);
    if (status != HAL_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    if ((hhsp.last_error_codes & HAL_HSP_ERROR_INVALID_PARAM) != HAL_HSP_ERROR_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    hhsp.last_error_codes = 0U; /* Reset for next test */

    /* -- HAL_HSP_EVENT_GetConfig --------------------------------------------*/
    status = HAL_HSP_EVENT_GetConfig(&hhsp, HAL_HSP_EVENT_1, (hal_hsp_event_config_t *)NULL);
    if (status != HAL_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    if ((hhsp.last_error_codes & HAL_HSP_ERROR_INVALID_PARAM) != HAL_HSP_ERROR_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    hhsp.last_error_codes = 0U; /* Reset for next test */

    /* -- HAL_HSP_EVENT_Enable -----------------------------------------------*/
    /* -- HAL_HSP_EVENT_Disable ----------------------------------------------*/

    /* -- HAL_HSP_EVENT_RequestSWTrigger -------------------------------------*/

    /* -- HAL_HSP_EVENT_PollForPending ----------------------------------------------*/
    hhsp.Instance = HSP1;
    status = HAL_HSP_EVENT_PollForPending(&hhsp, HAL_HSP_POLLING_FOR_ALL_EVENT, HAL_HSP_EVENT_1, 0U, NULL);
    if (status != HAL_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    if ((hhsp.last_error_codes & HAL_HSP_ERROR_INVALID_PARAM) != HAL_HSP_ERROR_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    hhsp.last_error_codes = 0U; /* Reset for next test */

    /* -- HAL_HSP_SMARTCLOCKING_Enable ---------------------------------------*/

    /* -- HAL_HSP_SMARTCLOCKING_Disable --------------------------------------*/

    /******************************************************************************************************************/
    /* Task Comparator                                                                                                */
    /******************************************************************************************************************/
    /* --HAL_HSP_TCU_EnableOverlap ---------------------------------------*/
    /* --HAL_HSP_TCU_DisableOverlap --------------------------------------*/

    /* -- HAL_HSP_TCU_SetConfigComparator -------------------------------------*/

    /* -- HAL_HSP_TCU_EnableComparator ---------------------------------------*/

    /* -- HAL_HSP_TCU_DisableComparator --------------------------------------*/

    /* -- HAL_HSP_TCU_PollForEvent -------------------------------------------*/
    hhsp.Instance = HSP1;
    status =  HAL_HSP_TCU_PollForEvent(&hhsp, HAL_HSP_POLLING_FOR_ALL_EVENT, 0U, 0U, NULL);
    if (status != HAL_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    if ((hhsp.last_error_codes & HAL_HSP_ERROR_INVALID_PARAM) != HAL_HSP_ERROR_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    hhsp.last_error_codes = 0U; /* Reset for next test */

    /* -- HAL_HSP_TCU_EnableIT -----------------------------------------------*/

    /* -- HAL_HSP_TCU_DisableIT ----------------------------------------------*/

    /* -- HAL_HSP_OUTPUT_SetConfigTrigger ------------------------------------*/

    /* -- HAL_HSP_OUTPUT_Enable ----------------------------------------------*/

    /* -- HAL_HSP_OUTPUT_Disable ---------------------------------------------*/

    /* -- HAL_HSP_TSC_SetConfig ----------------------------------------------*/
    hhsp.Instance = HSP1;
    status =  HAL_HSP_TSC_SetConfig(&hhsp, NULL);
    if (status != HAL_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    if ((hhsp.last_error_codes & HAL_HSP_ERROR_INVALID_PARAM) != HAL_HSP_ERROR_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    hhsp.last_error_codes = 0U; /* Reset for next test */

    /* -- HAL_HSP_TSC_GetConfig ----------------------------------------------*/
    hhsp.Instance = HSP1;
    status =  HAL_HSP_TSC_GetConfig(&hhsp, NULL);
    if (status != HAL_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    if ((hhsp.last_error_codes & HAL_HSP_ERROR_INVALID_PARAM) != HAL_HSP_ERROR_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    hhsp.last_error_codes = 0U; /* Reset for next test */

    /* -- HAL_HSP_TSC_Enable -------------------------------------------------*/

    /* -- HAL_HSP_TSC_Disable ------------------------------------------------*/

    /******************************************************************************************************************/
    /* HSP Performance                                                                                                */
    /******************************************************************************************************************/
    /* --HAL_HSP_BRAM_EnableConflictAccessCounter -----------------------------------------------------------*/

    /* --HAL_HSP_BRAM_DisableConflictAccessCounter -----------------------------------------------------------*/

    /* --HAL_HSP_BRAM_SetBandwidthArbitration -----------------------------------------------------------*/

    /******************************************************************************************************************/
    /* HSP Protection                                                                                                 */
    /******************************************************************************************************************/
    /* -- HAL_HSP_Lock -------------------------------------------------------*/

    /******************************************************************************************************************/
    /* HSP Processing List Management                                                                                 */
    /******************************************************************************************************************/
    /* -- HAL_HSP_TASK_Run ---------------------------------------------------*/

    /* -- HAL_HSP_TASK_Run_IT ------------------------------------------------*/

    /* -- HAL_HSP_PROCLIST_PollForNotification -------------------------------*/
    hhsp.Instance = HSP1;
    status =  HAL_HSP_PROCLIST_PollForNotification(&hhsp, HAL_HSP_POLLING_FOR_ALL_EVENT, 0U, 0U, NULL);
    if (status != HAL_ERROR) {VALIDATION_CHECK_FAIL(__LINE__);}
    if ((hhsp.last_error_codes & HAL_HSP_ERROR_INVALID_PARAM) != HAL_HSP_ERROR_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
    hhsp.last_error_codes = 0U; /* Reset for next test */

    /* -- HAL_HSP_PROCLIST_EnableIT ------------------------------------------*/

    /* -- HAL_HSP_PROCLIST_DisableIT -----------------------------------------*/

    /***************************************************/
    /* Callbacks registering                           */
    /***************************************************/
    // status = HAL_HSP_RegisterSWTriggerWriteCpltCallback(&hhsp, (hal_hsp_cb_t)NULL);
    // if (status != HAL_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}

    // status = HAL_HSP_RegisterEdgeTriggerWriteCpltCallback(&hhsp, (hal_hsp_cb_t)NULL);
    // if (status != HAL_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}

    // status = HAL_HSP_RegisterLUTOutputRisingCallback(&hhsp, (hal_hsp_lut_output_cb_t)NULL);
    // if (status != HAL_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}

    // status = HAL_HSP_RegisterLUTOutputFallingCallback(&hhsp, (hal_hsp_lut_output_cb_t)NULL);
    // if (status != HAL_INVALID_PARAM) {VALIDATION_CHECK_FAIL(__LINE__);}
  }

  ValidCheckRunning = VALID_DEFAULT_CHECK;

  return VALIDATION_RETURN_TEST_DONE;
#else
  /* Error: Test should not be run, to be skipped in "testlist.c" */
  VALIDATION_TEST_UNTESTABLE_RUNTIME("USE_FULL_ASSERT is Disabled");
  return VALIDATION_RETURN_TEST_SKIPPED;
#endif /* USE_FULL_ASSERT */  /* Test end */
}
