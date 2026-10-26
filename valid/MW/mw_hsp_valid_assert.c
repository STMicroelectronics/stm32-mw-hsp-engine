/**
  ******************************************************************************
  * @file    mw_hsp_valid_assert.c
  * @author  MDG-GPM application team
  * @brief   This file provides HSP validation services to test functions parameters (assert, check).
  *          Services common to all validation programs (LL, HAL, ...)
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "mw_hsp_valid_assert.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile valid_driver_checks_t   ValidCheckRunning;
         uint32_t                AssertFailedCounterExpected;
volatile uint32_t                AssertFailedCounter;
         uint32_t                AssertPassedCounterExpected;
volatile uint32_t                AssertPassedCounter;
VALID_PREVIOUS_CONTEXT           context;

/* Private functions ---------------------------------------------------------*/
#if defined(USE_HSP_ASSERT_DBG_PARAM)
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the hsp_assert_dbg_param_failed error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert error line source number
  * @retval None
  */
void hsp_assert_dbg_param_failed(uint8_t *file, uint32_t line)
{
  if (ValidCheckRunning == VALID_ASSERT_PARAM)
  {
    /* Increment assert failed counter */
    AssertFailedCounter++;
    /* Restore the context after an assert failed */
    VALID_RESTORE_CONTEXT(context, AssertFailedCounter);
  }
  else if (ValidCheckRunning == VALID_DEFAULT_CHECK) /* VALID_DEFAULT_CHECK: application use case */
  {
    /* Go to infinite loop */
    while (1)
    {
    }
  }
  /* Do nothing: let the function execution continue with wrong parameter */
}
#endif /* USE_HSP_ASSERT_DBG_PARAM */

#if defined(USE_HSP_ASSERT_DBG_STATE)
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the hsp_assert_dbg_state_failed error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert error line source number
  * @retval None
  */
void hsp_assert_dbg_state_failed(uint8_t *file, uint32_t line)
{
  if (ValidCheckRunning == VALID_ASSERT_STATE)
  {
    /* Increment assert failed counter */
    AssertFailedCounter++;
    /* Restore the context after an assert failed */
    VALID_RESTORE_CONTEXT(context, AssertFailedCounter);
  }
  else if (ValidCheckRunning == VALID_DEFAULT_CHECK) /* VALID_DEFAULT_CHECK: application use case */
  {
    /* Go to infinite loop */
    while (1)
    {
    }
  }/* Do nothing: let the function execution continue with wrong parameter */
}

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_dbg_state_passed error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert error line source number
  * @retval None
  */
void assert_dbg_state_passed(uint8_t *file, uint32_t line)
{
  if (ValidCheckRunning == VALID_ASSERT_STATE)
  {
    /* Increment assert ok counter */
    AssertPassedCounter++;
    /* Restore the context after an assert ok */
    VALID_RESTORE_CONTEXT(context, AssertPassedCounter);
  }
}
#endif /* USE_HSP_ASSERT_DBG_STATE */
