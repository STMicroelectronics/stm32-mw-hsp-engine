/**
  ******************************************************************************
  * @file    hsp_conf.h
  * @author  GPM Application Team
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

/** @addtogroup HSP
  * @{
  */

/** @defgroup HSP_CONF HSP Configuration
  * @{
  */

/** @defgroup HSP_CONF_Exported_Constants HSP Configuration Constants
  * @{
  */
/* HSP Firmware --------------------------------------------------------------*/
/**
  * @brief Define the version of FW to used
  */
#define HSP_VERSION(major, minor)  (((major) << 8U) | (minor))

#define HSP_IP_VERSION               (HSP_VERSION(1U, 0U))  /*!<This value must be filled by CubeMX */
#define HSP_DEVICE_CROM_VERSION      (HSP_VERSION(1U, 7U))  /*!<This value must be filled by CubeMX */
#define HSP_FW_CRAM_TO_LOAD_VERSION  (HSP_VERSION(1U, 4U))  /*!<This value can be changed manually based on FW version\
                                                                provide by the HSP Middleware */

/* ################## HSP Modules Configuration ############### */
/**
  * @brief Set below the peripheral configuration to "1U" to add the support of the module
  */
#define USE_HSP_MODULES_DIRECT_LIB               1U
#define USE_HSP_MODULES_DSP_LIB                  1U
#define USE_HSP_MODULES_CNN_LIB                  1U
#define USE_HSP_MODULES_PROCLIST_COMPLEX         0U
#define USE_HSP_MODULES_PROCLIST_CONDITIONAL     0U
#define USE_HSP_MODULES_PROCLIST_CRC             0U
#define USE_HSP_MODULES_PROCLIST_FIR             0U
#define USE_HSP_MODULES_PROCLIST_MATRIX          0U
#define USE_HSP_MODULES_PROCLIST_MEMORY          0U
#define USE_HSP_MODULES_PROCLIST_SCALAR          0U
#define USE_HSP_MODULES_PROCLIST_TRANSFORM       0U
#define USE_HSP_MODULES_PROCLIST_VECTOR          0U

/**
  * @brief Enable the Synchronous mode of Direct Command APIs
  *        (0U to disable, 1U to enable)
  */
#define USE_HSP_DIRECT_COMMAND_SYNCHRONOUS  1U

/* HSP Performance Monitor ---------------------------------------------------*/
/**
  * @brief Enable the HSP Performance Monitor at boot step
           (0U to disable, 1U to enable)
  */
#define ENABLE_HSP_PERFORMANCE_MONITOR  0U

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
#define HSP_BRAM_AI_SIZE 0U  /*!< Size in word */

/** @defgroup HSP_CONF_Exported_Macros HSP Configuration Macros
  * @{
  */
#if !defined(UNUSED)
#define UNUSED(X) ((void)X)      /* To avoid gcc/g++ warnings */
#endif /* UNUSED */

#if !defined(COUNTOF)
#define COUNTOF(a)  (sizeof(a) / sizeof(*(a)))
#endif /* COUNTOF */

/* HSP FW Legacy -------------------------------------------------------------------*/
/* CRAM Aliases */
#define HSP_DIRECT_CMD_RFFT_F32  HSP_DIRECT_CMD_RFFT
#define HSP_CMD_SCA_SIN_F32  HSP_CMD_SCA_SIN
#define HSP_CMD_SCA_ADD_F32  HSP_CMD_SCA_ADD
#define HSP_IOTYPE_IMM  0U

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
