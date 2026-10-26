/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    App/app_hsp_bram_alloc.h
  * @brief   Header file
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef APP_HSP_BRAM_ALLOC_H
#define APP_HSP_BRAM_ALLOC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hsp_def.h"

/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

/** @addtogroup APP_HSP_ENGINE
  * @{
  */
/** @defgroup APP_HSP_BRAM_ALLOC_Exported_Constants Application HSP BRAM Allocation Constants
  * @{
  */
#define INPUT_SIGNAL_SAMPLES_SIZE  250U
#define OUTPUT_SAMPLES_SIZE  INPUT_SIGNAL_SAMPLES_SIZE

/* USER CODE BEGIN BRAM Constants */

/* USER CODE END BRAM Constants */

/**
  * @}
  */

/** @defgroup HSP_BRAM_STATIC_Resources HSP BRAM Static Resources
  * @{
  */
extern uint32_t pl_call;
extern uint32_t pop_out;

/* USER CODE BEGIN BRAM Static Allocation */

/* USER CODE END BRAM Static Allocation */

/**
  * @}
  */

/** @defgroup HSP_BRAM_DYNAMIC_Resources HSP BRAM Dynamic Resources
  * @{
  */
extern float32_t *p_buff_in;  /* BRAM Input Buffer */
extern float32_t *p_buff_out;  /* BRAM Output Buffer */
extern uint32_t *pPopOut;

/* USER CODE BEGIN BRAM Dynamic Allocation */

/* USER CODE END BRAM Dynamic Allocation */

/**
  * @}
  */

/** @defgroup APP_HSP_BRAM_ALLOC_Exported_Functions Application HSP BRAM Exported Functions
  * @{
  */
uint32_t MX_HSP_BRAM_Allocation(hsp_engine_context_t *hmw);

/* USER CODE BEGIN Exported Functions */

/* USER CODE END Exported Functions */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* APP_HSP_BRAM_ALLOC_H */
