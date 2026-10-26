/**
  ******************************************************************************
  * @file    mw_hsp_valid_init.c
  * @author  GPM Application Team
  * @brief   This file contains the HAL HSP functional validation functions.
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
#include "mw_hsp_valid_init.h"
#include "mw_hsp_valid_hsp1.h"
#include "hsp_core.h"

/* Private constants ---------------------------------------------------------*/
#define VALID_HSP_TIMEOUT_MS  500U  /* timeout in millisecond */
#define hal_status_t HAL_StatusTypeDef

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/**
  * @brief Check the MW Init
  * @par Test Description
  *   - Check the MW initialization without Plugin
  *   Only HSP FW RAM is loaded.
  * @par Required Preconditions
  * None
  * @par Expected Results
  *   The Middleware must returned HPS_CORE_OK
  * @retval
  * 0: Test passed
  * Value different from 0: Test failed
  */
uint32_t MW_HSP_VALID_Test_Init(void)
{
  hsp_core_status_t ret_mw = HSP_CORE_ERROR;

  hal_hsp_handle_t *hhsp;
  hsp_engine_context_t hhspmw;

  /* Init the HAL HSP */
  hhsp = mw_hsp_valid_hsp1_hal_init();

  /* Init the MW HSP Engine */
  ret_mw = HSP_CORE_Init(&hhspmw, hhsp);
  if (ret_mw != HSP_CORE_OK)
  {
    VALIDATION_CHECK_FAIL(__LINE__);
  }

  /* DeInit the MW HSP Engine */
  HSP_CORE_DeInit(&hhspmw);

  /* Deinit the HAL HSP */
  mw_hsp_valid_hsp1_hal_deinit();

  /* Test end */
  return VALIDATION_RETURN_TEST_DONE;
}
