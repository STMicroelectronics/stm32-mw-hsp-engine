/**
  ******************************************************************************
  * @file    hsp_if_conf_template.h
  * @brief   Header file for interfaces
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
#ifndef HSP_IF_CONF_TEMPLATE_H
#define HSP_IF_CONF_TEMPLATE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "interface.h"
#include "stm32u3xx_hal.h" /* Select the hal file corresponding to the device in use (i.e. stm32f3xx_hal.h, stm32f0xx_hal.h, ...) */
#include "hsp_api_def.h"

/** @addtogroup HSP_ENGINE
  * @{
  */

/** @defgroup HSP_CONF
  * @{
  */

/** @defgroup HSP_CONF_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup HSP_CONF_Exported_Types
  * @{
  */


//typedef enum
//{
//  HSP_HW_IF_POINTER0  = 0U,
//  HSP_HW_IF_POINTER1  = 1U,
//  HSP_HW_IF_POINTER2  = 2U,
//} hsp_hw_if_pointer_t;

  //typedef enum
//{
//  HSP_CORE_TRGO_0 = HAL,
//  HSP_CORE_TRGO_1,
//  HSP_CORE_TRGO_2,
//  HSP_CORE_TRGO_3
//} hsp_core_trgo_t;
  
/** @defgroup HSP_TRGIN_ID  HSP Trigger Input Identifiers
  * @{
  */
//#define HSP_HW_IF_TRGIN_0  HAL_HSP_TRGIN_0
//#define HSP_HW_IF_TRGIN_1  HAL_HSP_TRGIN_1
//#define HSP_HW_IF_TRGIN_2  HAL_HSP_TRGIN_2
//#define HSP_HW_IF_TRGIN_3  HAL_HSP_TRGIN_3
//#define HSP_HW_IF_TRGIN_4  HAL_HSP_TRGIN_4
//#define HSP_HW_IF_TRGIN_5  HAL_HSP_TRGIN_5
//#define HSP_HW_IF_TRGIN_6  HAL_HSP_TRGIN_6
//#define HSP_HW_IF_TRGIN_7  HAL_HSP_TRGIN_7
//#define HSP_HW_IF_TRGIN_8  HAL_HSP_TRGIN_8
//#define HSP_HW_IF_TRGIN_9  HAL_HSP_TRGIN_9

#define HSP_STREAM_BUFFER_0  HAL_HSP_STREAM_0
#define HSP_STREAM_BUFFER_1  HAL_HSP_STREAM_1
#define HSP_STREAM_BUFFER_2  HAL_HSP_STREAM_2
#define HSP_STREAM_BUFFER_3  HAL_HSP_STREAM_3

#define HSP_STREAM_BUFFER_SYNC_DISABLE  HAL_HSP_STREAM_SYNC_DISABLE
#define HSP_STREAM_BUFFER_SYNC_ENABLE   HAL_HSP_STREAM_SYNC_ENABLE

  
#define HSP_TASK_COMPARATOR_0  HAL_HSP_TASK_COMPARATOR_0
#define HSP_TASK_COMPARATOR_1  HAL_HSP_TASK_COMPARATOR_1
#define HSP_TASK_COMPARATOR_2  HAL_HSP_TASK_COMPARATOR_2
#define HSP_TASK_COMPARATOR_3  HAL_HSP_TASK_COMPARATOR_3

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Defines for TRGIN signals -------------------------------------------------*/
/*
  For ADF: #define HSP_TRGIN_ADF_x  HAL_HSP_TRGIN_ADFxxxxx
    #define HSP_TRGIN_ADF_0  HAL_HSP_TRGIN_ADF1_SAD_DET

  For DMA Transfer Complete: #define HSP_TRGIN_DMA_TC_x  HAL_HSP_TRGIN_<G|H|LP>DMA<y>_CH<z>_TC
    ex: #define HSP_TRGIN_DMA_TC_5  HAL_HSP_TRGIN_HDMA2_CH12_TC

  For EXTI: #define HSP_TRGIN_EXTI_x  HAL_HSP_TRGIN_EXT<y>
    ex: #define HSP_TRGIN_EXTI_5  HAL_HSP_TRGIN_EXTI0

  For LPTIM: #define HSP_TRGIN_LPTIM_x  HAL_HSP_TRGIN_LPTIM<y>_CH<z>
    ex: #define HSP_TRGIN_LPTIM_17  HAL_HSP_TRGIN_LPTIM2_CH2

  For MDF Filter RX Interrupt: #define HSP_TRGIN_MDF_FLT_RX_IT_x  HAL_HSP_TRGIN_MDF_FLT<y>_RX_IT
    ex: #define HSP_TRGIN_MDF_FLT_RX_IT_3 HAL_HSP_TRGIN_MDF_FLT1_RX_IT

  For NPU : #define HSP_TRGIN_NPU_x  HAL_HSP_TRGIN_NPU_<literal><[0..9]*>
    ex: #define HSP_TRGIN_NPU_0  HAL_HSP_TRGIN_NPU_HOST_IN3

  For TIM TRGO: #define HSP_TRGIN_TIM_TRGO_x  HAL_HSP_TRGIN_TIM<y>_TRGO<empty | [0..9]>
    ex: #define HSP_TRGIN_TIM_TRGO_1 HAL_HSP_TRGIN_TIM7_TRGO
    ex: #define HSP_TRGIN_TIM_TRGO_5 HAL_HSP_TRGIN_TIM25_TRGO2

  For PLAY OUT: #define HSP_TRGIN_PLAY_OUT_x  HAL_HSP_TRGIN_PLAY<y>_OUT<z>
    ex: #define HSP_TRGIN_PLAY_OUT_0 HAL_HSP_TRGIN_PLAY1_OUT6
  */

/* Defines for HSP TRGO --------------------------------------------------*/
#define HSP_CORE_TRGO_0  (uint32_t)HAL_HSP_OUTPUT_TRIGGER_0
#define HSP_CORE_TRGO_1  (uint32_t)HAL_HSP_OUTPUT_TRIGGER_1
#define HSP_CORE_TRGO_2  (uint32_t)HAL_HSP_OUTPUT_TRIGGER_2
#define HSP_CORE_TRGO_3  (uint32_t)HAL_HSP_OUTPUT_TRIGGER_3

#define HSP_CORE_TRGO_SOURCE_STREAM  (uint32_t)HAL_HSP_OUTPUT_TRIGGER_STREAM
#define HSP_CORE_TRGO_SOURCE_SPE     (uint32_t)HAL_HSP_OUTPUT_TRIGGER_CORE
#define HSP_CORE_TRGO_SOURCE_TSC     (uint32_t)HAL_HSP_OUTPUT_TRIGGER_TIMESTAMPCAPTURE


/* Defines for GPO signals ---------------------------------------------------*/
/*
  For DMA Trigger: #define HSP_GPO_DMA_TRIG_x  HAL_HSP_GPO_<G|H|LP>DMA<y>_TRIG<z>
    #define HSP_GPO_DMA_TRIG_0  HAL_HSP_GPO_GPDMA1_TRIG38

*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/


/** @defgroup HSP_CONF_Exported_Variables
  * @{
  */
hsp_core_status_t HSP_Engine_IF_Init(hsp_engine_context_t *hmw);

/**
  * @}
  */

/** @defgroup HSP_CONF_Exported_FunctionsPrototype
  * @{
  */

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

#endif /* HSP_IF_CONF_TEMPLATE_H */
