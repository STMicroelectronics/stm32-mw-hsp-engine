/**
  ******************************************************************************
  * @file           : mw_hsp_valid_hsp1.c
  * @brief          : HSP1 Peripheral initialization
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
#include "mw_hsp_valid_hsp1.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported variables by reference -------------------------------------------*/
static hal_hsp_handle_t hHSP1;

/******************************************************************************/
/* Exported functions for HSP1 in HAL layer (SW instance MyHSP_1) */
/******************************************************************************/
hal_hsp_handle_t *mw_hsp_valid_hsp1_hal_init(void)
{
  __HAL_RCC_HSP1_CLK_ENABLE();

  hHSP1.Instance = HSP1;
  hHSP1.global_state = HAL_HSP_STATE_RESET;

  if (HAL_HSP_Init(&hHSP1) != HAL_OK)
  {
    return NULL;
  }

  /* Enable HSP interrupt */
  HAL_NVIC_SetPriority(HSP1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(HSP1_IRQn);

  return &hHSP1;
}

void mw_hsp_valid_hsp1_hal_deinit(void)
{
  /* Disable the interruption for HSP */
  HAL_NVIC_DisableIRQ(HSP1_IRQn);

  HAL_HSP_DeInit(&hHSP1);

  __HAL_RCC_HSP1_FORCE_RESET();
  __HAL_RCC_HSP1_RELEASE_RESET();

  __HAL_RCC_HSP1_CLK_DISABLE();
}

hal_hsp_handle_t *mw_hsp_valid_hsp1_hal_gethandle(void)
{
  return &hHSP1;
}

/******************************************************************************/
/*                     HSP global non-secure interrupt                    */
/******************************************************************************/
/**
  * @brief This function handles HSP global interrupt.
  */
void HSP1_IRQHandler(void)
{
  HAL_HSP_IRQHandler(&hHSP1);
}

/**
  * @brief This function handles HSP Error interrupt.
  */
void HSP1_ERR_IRQHandler(void)
{
  HAL_HSP_ERR_IRQHandler(&hHSP1);
}

/**
  * @brief This function handles HSP Event interrupt.
  */
void HSP1_EVT_IRQHandler(void)
{
  HAL_HSP_EVT_IRQHandler(&hHSP1);
}

/**
  * @brief This function handles HSP Firmware Event interrupt.
  */
void HSP1_FWEVT_IRQHandler(void)
{
  HAL_HSP_FWEVT_IRQHandler(&hHSP1);
}

