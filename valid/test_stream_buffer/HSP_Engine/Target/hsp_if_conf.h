/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    target/hsp_if_conf.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HSP_IF_CONF_H
#define HSP_IF_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "interface.h"
#include "hsp_api_def.h"
#include "stm32u3xx_hal.h"

/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

/** @addtogroup HSP
  * @{
  */

/** @defgroup HSP_IF_CONF
  * @{
  */

/** @defgroup HSP_IF_CONF_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup HSP_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup HSP_IF_CONF_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup HSP_IF_CONF_Exported_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup HSP_IF_CONF_Exported_FunctionsPrototype
  * @{
  */
hsp_if_status_t HSP_Engine_IF_Init(hsp_engine_context_t *hmw);

void HSP1_IRQHandler(void);
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

#endif /* HSP_IF_CONF_H */
