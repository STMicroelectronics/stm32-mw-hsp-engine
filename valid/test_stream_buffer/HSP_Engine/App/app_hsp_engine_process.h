/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : app_hsp_engine_process.h
  * @brief          : Header for app_hsp_engine_process.c file.
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
#ifndef APP_HSP_ENGINE_PROCESS_H
#define APP_HSP_ENGINE_PROCESS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

/** @addtogroup HSP_DRIVER
  * @{
  */

/** @defgroup HSP
  * @{
  */

/** @defgroup HSP_Engine_Exported_Variables HSP_Engine_Exported_Variables
  * @brief Public variables.
  * @{
  */

/**
* @}
*/

/** @defgroup HSP_Engine_Exported_FunctionsPrototype HSP_Engine_Exported_FunctionsPrototype
  * @brief Declaration of public functions for HSP Engine.
  * @{
  */

/* Exported functions -------------------------------------------------------*/
/* USER CODE BEGIN Exported Functions */
uint32_t APP_HSP_Engine_StreamBufferWriteTest(void);

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

#endif /* APP_HSP_ENGINE_PROCESS_H */
