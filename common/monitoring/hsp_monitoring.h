/**
  ******************************************************************************
  * @file    hsp_monitoring.h
  * @brief   Header file for hsp_monitoring.c
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

/* Define to prevent recursive  ----------------------------------------------*/
#ifndef HSP_MONITORING_H
#define HSP_MONITORING_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "hsp_conf.h"
#include "hsp_if_conf.h"
#include "hsp_api_def.h"
#include "hsp_hw_if.h"

/** @addtogroup HSP_ENGINE
  * @{
  */

/** @defgroup HSP_MONITORING HSP Monitoring
  * @{
  */
typedef enum
{
  HSP_TIMESTAMP_SPE_BREAK,
  HSP_TIMESTAMP_TASK_CHANGE,
  HSP_TIMESTAMP_PFCT_CHANGE,
} hsp_monitor_tsc_mode_t;

/** @defgroup HSP_MONITORING_Exported_Functions HSP Core Exported Functions
  * @{
  */
/** @defgroup HSP_CORE_Exported_Functions_Group1 HSP Task Comparator Management
  * @{
  */
hsp_core_status_t HSP_MONITOR_EnableTaskComparator(hsp_engine_context_t *hmw, uint32_t tcu_id, uint32_t task_id);
hsp_core_status_t HSP_MONITOR_DisableTaskComparator(hsp_engine_context_t *hmw, uint32_t tcu_id);

hsp_core_status_t HSP_MONITOR_EnableTaskComparator_IT(hsp_engine_context_t *hmw, uint32_t tcu_id, uint32_t task_id);
hsp_core_status_t HSP_MONITOR_DisableTaskComparator_IT(hsp_engine_context_t *hmw, uint32_t tcu_id);

/**
  * @}
  */

/** @defgroup HSP_MONITORING_Exported_Functions_Group2 HSP TimeStamp Capture
  * @{
  */
hsp_core_status_t HSP_MONITOR_TSC_Enable(hsp_engine_context_t *hmw, hsp_monitor_tsc_mode_t mode);
hsp_core_status_t HSP_MONITOR_TSC_Disable(hsp_engine_context_t *hmw);

/**
  * @}
  */

/** @defgroup HSP_MONITORING_Exported_Functions_Group3 HSP SNOOP
  * @{
  */
hsp_core_status_t HSP_MONITOR_SNOOP_Enable(hsp_engine_context_t *hmw, uint32_t group_id,
                                           uint32_t signal);
hsp_core_status_t HSP_MONITOR_SNOOP_Disable(hsp_engine_context_t *hmw, uint32_t group_id);

/**
  * @}
  */

/** @defgroup HSP_MONITORING_Exported_Functions_Group4 HSP Counters
  * @{
  */
uint32_t HSP_MONITOR_GetPerformanceCounter(hsp_engine_context_t *hmw);

/**
  * @}
  */

/** @defgroup HSP_MONITORING_Exported_Functions_Group5 HSP Callbacks
  * @{
  */
hsp_core_status_t HSP_MONITOR_RegisterTCU_TaskStartedCallback(hsp_engine_context_t *hmw,
                                                              p_hsp_engine_one_param_cb_t p_callback);
hsp_core_status_t HSP_MONITOR_RegisterTCU_TaskEndedCallback(hsp_engine_context_t *hmw,
                                                            p_hsp_engine_one_param_cb_t p_callback);

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

#endif /* HSP_MONITORING_H */
