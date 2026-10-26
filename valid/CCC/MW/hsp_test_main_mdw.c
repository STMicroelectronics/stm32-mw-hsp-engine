/**
  ******************************************************************************
  * @file    hsp_test_main_mdw.c
  * @author  MCD Application Team
  * @brief   This file contains the HAL ip driver validation.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024-2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "hsp.h"
#include "hsp_test_common.h"


/* Private constants ---------------------------------------------------------*/
#define BRAM_SIZE 4096 // 16KB

/* HSP Middleware handle */
hsp_core_handle_t hmw;
HSP_HandleTypeDef hhsp1;
  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void Error_Handler(void);

/* Private function prototypes -----------------------------------------------*/
//static void MX_STM32_HSP_Init(void);

/* Private functions ---------------------------------------------------------*/
int hsp_test_main(void);

/* Private variables ---------------------------------------------------------*/
__IO uint32_t ErrorCount = 0;



/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{

  /*****************************************************************************
  *                          Common Configuration                              *
  *****************************************************************************/
  // /* Init HAL driver */
  // HAL_Init();

// //  hmw.instance = (HSP_TypeDef *)HSP1;
  
  // /* Init the HSP Middelware for HSP Peripheral */
// //  if (HSP_CORE_Init(&hmw) != HSP_CORE_OK)
// //  {
// //    Error_Handler();
// //  }

 
    // // TO BE CLARIFIED : quid des IT evt : ERR ?? 
  // HAL_NVIC_SetPriority(HSP1_IRQn, 0, 0);
  // HAL_NVIC_EnableIRQ(HSP1_IRQn); // Global HSP interrupt
// //  
// //  fill_hsp_memory((uint32_t *)HYPSA_SHARED_MEM_BASE_ADDR, 0xCAFEDECA, BRAM_SIZE);

  // int rc = hsp_test_main();
// //  int rc = 0;
  // printf("returning from HSP test rc=%d \n",rc);

  // return (rc);
  
  
    /*****************************************************************************
  *                          Common Configuration                              *
  *****************************************************************************/
  /* Init HAL driver */
  HAL_Init();

    // TO BE CLARIFIED : quid des IT evt : ERR ?? 
  HAL_NVIC_SetPriority(HSP1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(HSP1_IRQn); // Global HSP interrupt

//  fill_hsp_memory((uint32_t *)HYPSA_SHARED_MEM_BASE_ADDR, 0xCAFEDECA, BRAM_SIZE);
  /* Init HSP Ip. */
  
  pHspReg = (HSP_TypeDef *) HSP1;
  hhsp1.Instance = HSP1;
  if (HAL_HSP_Init(&hhsp1) != HAL_OK)
  {
    return 1;
  }

  /* Link the driver to the MW. */
  hmw.hdriver = &hhsp1;

  int rc = hsp_test_main();
//  int rc = 0;
  printf("returning from HSP test rc=%d \n",rc);

  return (rc);
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  while (1)
  {
  }
}
