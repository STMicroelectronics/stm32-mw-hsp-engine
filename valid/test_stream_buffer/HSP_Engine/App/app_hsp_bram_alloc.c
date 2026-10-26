/* USER CODE BEGIN Header */
/**
  **********************************************************************************************
  * @file           : App/app_hsp_bram_alloc.c
  * @version        : v1_0_Cube
  * @brief          : This file contains resources allocated in HSP BRAM region memory
  ***********************************************************************************************
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
/* USER CODE END Header */

#include "app_hsp_bram_alloc.h"
#include "hsp_bram.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */
/* Exported variables --------------------------------------------------------*/
/* BRAM Resources Static Allocation -----------------------------------------*/

/* USER CODE BEGIN BRAM Static Allocation */
uint32_t pl_call __attribute__((section("HSP_DATA_BRAM"))) = 0U;
uint32_t pop_out __attribute__((section("HSP_DATA_BRAM"))) = 0U;

/* USER CODE END BRAM Static Allocation */

/* BRAM Resources Dynamic Allocation ----------------------------------------*/

float32_t *p_buff_in;  /* BRAM Input Buffer */
float32_t *p_buff_out;  /* BRAM Output Buffer */
uint32_t *pPopOut;


/* USER CODE BEGIN BRAM Dynamic Allocation */

/* USER CODE END BRAM Dynamic Allocation */

/* Access to external variables ----------------------------------------------*/
extern hsp_engine_context_t hmw;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/*
 * -- Insert your variables declaration here --
 */
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

uint32_t MX_HSP_BRAM_Allocation(hsp_engine_context_t *hmw)
{
  uint32_t error = 0UL;

  p_buff_in = (float32_t *)HSP_BRAM_Malloc(hmw, INPUT_SIGNAL_SAMPLES_SIZE, HSP_BRAM_ALLOCATION_DEFAULT);
  if (p_buff_in == NULL) error++;

  p_buff_out = (float32_t *)HSP_BRAM_Malloc(hmw, OUTPUT_SAMPLES_SIZE, HSP_BRAM_ALLOCATION_DEFAULT);
  if (p_buff_out == NULL) error++;

  pPopOut = (uint32_t *) HSP_BRAM_Malloc(hmw, 1, HSP_BRAM_ALLOCATION_DEFAULT);
  if (p_buff_out == NULL) error++;
  pop_out = (uint32_t) p_buff_out;
  
  return error;
}


/**
  * @}
  */

/**
  * @}
  */

