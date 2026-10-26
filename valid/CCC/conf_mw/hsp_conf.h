/**
  ******************************************************************************
  * @file    hsp_conf.h
  * @author  MCD Application Team
  * @brief   Header file
  ******************************************************************************
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
#ifndef HSP_CONF_H
#define HSP_CONF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>

/** @addtogroup HSP_ENGINE
  * @{
  */

/** @defgroup HSP_CONF HSP Configuration
  * @{
  */

/** @defgroup HSP_CONF_Exported_Constants HSP Configuration Constants
  * @{
  */
/* HSP Firwmare --------------------------------------------------------------*/
///**
//  * @brief Define the version of FW to used
//  */
//#define HSP_VERSION(major, minor)  (((major) << 8U) | (minor))
//
//#define HSP_IP_VERSION               (HSP_VERSION(1U, 0U))  /*!<This value must be filled by CubeMX */
//#define HSP_DEVICE_CROM_VERSION      (HSP_VERSION(1U, 7U))  /*!<This value must be filled by CubeMX */
//#define HSP_FW_CRAM_TO_LOAD_VERSION  (HSP_VERSION(0xFU, 0xFFU))  /*!<This value can be changed manually based on FW version\
//                                                                provide by the HSP Middleware */
//// VAL: a voir avec Philippe  
//#define HSP_FW_DEF_ROM_VERSION_MAJOR (1U)
//#define HSP_FW_DEF_ROM_VERSION_MINOR (7U)
//#define HSP_FW_DEF_RAM_VERSION_MAJOR (0xFU)
//#define HSP_FW_DEF_RAM_VERSION_MINOR (0xFFU)

/* ################## HSP Modules Configuration ############### */
/**
  * @brief Set below the peripheral configuration to "1U" to add the support of the module
  */
#define USE_HSP_ENGINE_STREAM_BUFFER             1U
#define USE_HSP_MODULES_DIRECT_LIB               1U
#define USE_HSP_MODULES_DSP_LIB                  1U
#define USE_HSP_MODULES_CNN_LIB                  1U
#define USE_HSP_MODULES_PROCLIST_COMPLEX         1U
#define USE_HSP_MODULES_PROCLIST_CONDITIONAL     1U
#define USE_HSP_MODULES_PROCLIST_FILTER          1U
#define USE_HSP_MODULES_PROCLIST_MATRIX          1U
#define USE_HSP_MODULES_PROCLIST_SCALAR          1U
#define USE_HSP_MODULES_PROCLIST_TRANSFORM       1U
#define USE_HSP_MODULES_PROCLIST_VECTOR          1U
#ifndef __HSP_DMA__
#define USE_HSP_MODULES_PROCLIST_DIGITAL_CONTROL 0U
#else /* __HSP_DMA__ */
#define USE_HSP_MODULES_PROCLIST_DIGITAL_CONTROL 1U
#endif /* __HSP_DMA__ */

/**
  * @brief Enable the use of STM32 HSP memcpy
  *        (0U to use the standard lib C memcpy, 1U to use STM32 HSP memcpy)
  */
#define USE_HSP_MEMCPY                1U

/**
  * @brief Enable the Synchronous mode of Direct Command APIs
  *        (0U to disable, 1U to enable)
  */
#define USE_HSP_ACC_DIRECT_COMMAND_SYNCHRONOUS  1U
#define USE_HSP_ASSERT_DBG_PARAM  1U

/* HSP Performance Monitor ---------------------------------------------------*/
/**
  * @brief Enable the HSP Performance Monitor at boot step
           (0U to disable, 1U to enable)
  */
#define ENABLE_HSP_PERFORMANCE_MONITOR  1U

/* HSP Timeout ---------------------------------------------------------------*/
/**
  * @brief Allow to configure HSP Boot Timeout in millisecond
  */
#define HSP_BOOT_TIMEOUT_MS  500U

/**
  * @brief Allow to configure Timeout in millisecond for all polling functions
  */
#define HSP_TIMEOUT_MS  2000U

/* Cube AI -------------------------------------------------------------------*/
/**
  * @brief Define the BRAM Size reserved for CubeAI processing
  */
// #define HSP_BRAM_AI_SIZE 3072U  /*!< Size in byte */
#define HSP_BRAM_AI_SIZE 4096U  /*!< Size in byte */

/** @defgroup HSP_CONF_Exported_Macros HSP Configuration Macros
  * @{
  */
#if !defined(UNUSED)
#define UNUSED(X) ((void)X)      /* To avoid gcc/g++ warnings */
#endif /* UNUSED */

#if !defined(COUNTOF)
#define COUNTOF(a)  (sizeof(a) / sizeof(*(a)))
#endif /* COUNTOF */

/**
  * @brief Enable the load of Plugin (0U to disable, 1U to enable)
  *   If enabled the Application must allocate the array like this:
  *     1- hsp_plugin_t *name_of_array;
  *     2- hsp_plugin_t name_of_array[NB_HSP_PLUGIN];
  *     3- hsp_plugin_t name_of_array[] = { {}, {}...};
  *
  *   And the alias HSP_PLUGIN_ARRAY_NAME must be updated like this:
  *     #define HSP_PLUGIN_ARRAY_NAME  name_of_array
  */
#define USE_HSP_PLUGIN  0U
#if defined(USE_HSP_PLUGIN) && (USE_HSP_PLUGIN == 1)
/* Replace the literal "a_hsp_plugins" by the one defined by the Application */
#define HSP_PLUGIN_ARRAY_NAME  a_hsp_plugins
#define HSP_PLUGIN_ARRAY_SIZE  COUNTOF(HSP_PLUGIN_ARRAY_NAME)
#else /* USE_HSP_PLUGIN */
#define HSP_PLUGIN_ARRAY_NAME
#define HSP_PLUGIN_ARRAY_SIZE  0UL
#endif /* USE_HSP_PLUGIN */
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

#endif /* HSP_CONF_H */
