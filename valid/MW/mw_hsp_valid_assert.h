/**
  ******************************************************************************
  * @file    hsp_valid_assert.h
  * @author  MDG-GPM application team
  * @brief   Header for HSP validation program
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HSP_VALID_ASSERT_H
#define HSP_VALID_ASSERT_H

/* Includes ------------------------------------------------------------------*/
#include <setjmp.h>
#include <stdint.h>
#include "hsp_api_def.h" /* ASSERT_DBG_PARAM, ASSERT_DBG_STATE */
#include "mw_hsp_valid.h" /* VALIDATION_CHECK_FAIL */

/* Exported types ------------------------------------------------------------*/
/* Functions parameters test (assert, check) */
typedef enum
{
  VALID_DEFAULT_CHECK        = 0x00U, /* Default case: any wrong parameter will result in infinite loop
                                         (under condition USE_ASSERT_DBG_PARAM or USE_ASSERT_DBG_STATE) */
  VALID_ASSERT_PARAM         = 0x01U, /* Test macro ASSERT_DBG_PARAM calling assert_dbg_param_failed
                                         (under condition USE_ASSERT_DBG_PARAM) */
  VALID_ASSERT_STATE         = 0x02U, /* Test macro ASSERT_DBG_STATE calling assert_dbg_param_failed
                                         (under condition USE_ASSERT_DBG_STATE) */
  VALID_CHECK_PARAM          = 0x03U, /* Test checks of parameters returning HAL_INVALID_PARAM
                                         (under condition USE_HAL_CHECK_PARAM) */
  VALID_CHECK_PROCESS_STATE  = 0x04U, /* Test checks of state returning HAL_BUSY
                                         (under condition USE_HAL_CHECK_PROCESS_STATE) */
  VALID_ASSERT_BYPASS        = 0x05U, /* Bypass assert check */
} valid_driver_checks_t;

/* Management of legacy define "USE_FULL_ASSERT" */
//#if defined(USE_FULL_ASSERT)
//#ifndef USE_ASSERT_DBG_PARAM
//#define USE_ASSERT_DBG_PARAM
//#endif /* !USE_ASSERT_DBG_PARAM */
//#endif /* USE_FULL_ASSERT */

/* Exported constants --------------------------------------------------------*/
#define VALID_STORE_CONTEXT    setjmp
#define VALID_RESTORE_CONTEXT  longjmp
#define VALID_PREVIOUS_CONTEXT jmp_buf

/* Exported macro ------------------------------------------------------------*/
#define VALID_CHECK_RESULT()                                      \
  {                                                               \
    if (AssertFailedCounter != AssertFailedCounterExpected)       \
    {                                                             \
      VALIDATION_CHECK_FAIL(__LINE__); goto __goto_end;           \
    }                                                             \
    assert_failed_counter_previous = AssertFailedCounterExpected; \
  }

/* Exported variables --------------------------------------------------------*/
extern volatile valid_driver_checks_t   ValidCheckRunning;
extern          uint32_t                AssertFailedCounterExpected;
extern volatile uint32_t                AssertFailedCounter;
extern          uint32_t                AssertPassedCounterExpected;
extern volatile uint32_t                AssertPassedCounter;
extern VALID_PREVIOUS_CONTEXT           context;

/* Exported functions --------------------------------------------------------*/
#if defined(USE_HSP_ASSERT_DBG_PARAM)
void assert_dbg_param_failed(uint8_t *file, uint32_t line);
#endif /* USE_HSP_ASSERT_DBG_PARAM */

#if defined(USE_ASSERT_DBG_STATE)
void assert_dbg_state_failed(uint8_t *file, uint32_t line);
void assert_dbg_state_passed(uint8_t *file, uint32_t line);
#endif /* USE_ASSERT_DBG_STATE  */

#endif /* HSP_VALID_ASSERT_H */
