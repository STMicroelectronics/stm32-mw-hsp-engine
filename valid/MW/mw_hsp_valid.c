/**
  ******************************************************************************
  * @file    fpga_hsp_valid.c
  * @author  GPM Application Team
  * @brief   This file contains the HAL ip driver validation.
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
#include "mw_hsp_valid_testlist.h"
#include "mw_hsp_valid_test_log.h"

/* Imported functions --------------------------------------------------------*/
extern uint32_t SystemClock_Config(void);

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t current_instance = 0U;

/* Private function prototypes -----------------------------------------------*/
void Error_Handler(void);
void Valid_Seq_Test_PreConfig(void);

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
void main(void)
{
  /* Init HAL driver */
  HAL_Init();

  /* HAL_Delay allow to check if Vector Table is correct and Systick worked fine */
  //HAL_Delay(1000);

  /* System configuration */

  /*******************************************************************************
  *                             Validation sequencer                             *
  *******************************************************************************/
  /* Validation test program completed */
  for (int i = 0; i < a_valid_testlist_count; ++i)
  {
    if (!a_valid_testlist[i].is_group_header && a_valid_testlist[i].func != NULL) 
    {
      a_valid_testlist[i].result = a_valid_testlist[i].func();
    }
  }

  print_report("my_report", a_valid_testlist, a_valid_testlist_count);
#ifndef CODECOV_DYN
  while (1)
#else
  while (0)
#endif
  {
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
#if !defined(CODECOV_DYN)
  while (1)
  {
  }
#endif /* CODECOV_DYN */
}

/**
  * @brief  Validation function executed before each test.
  * @note   Intended to perform repetitive tasks needed in each test: handles reset, variables initialization, ...
  * @param  None
  * @retval None
  */
void Valid_Seq_Test_PreConfig(void)
{
  /* Reset the HSP before each test to ensure a success HSP boot process */
//  STM32_SET_BIT(RCC->HSP1CFGR, RCC_HSP1CFGR_RST);
//  STM32_CLEAR_BIT(RCC->HSP1CFGR, RCC_HSP1CFGR_RST);
}

#if defined(USE_ASSERT_DBG_PARAM)
void assert_dbg_param_failed(uint8_t *file, uint32_t line)
{
  while(1);
}
#endif /* USE_ASSERT_DBG_PARAM */

#if defined(USE_ASSERT_DBG_STATE)
void assert_dbg_state_failed(uint8_t *file, uint32_t line)
{
  while(1);
}
#endif /* USE_ASSERT_DBG_STATE */
