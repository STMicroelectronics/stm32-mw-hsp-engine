/**
  ******************************************************************************
  * @file    hsp_monitoring.c
  * @brief   This file implements the HSP Core functions.
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

/* Includes ------------------------------------------------------------------*/
#include "hsp_monitoring.h"
#include "hsp_hw_if.h"

/** @addtogroup HSP_ENGINE
  * @{
  */

/** @addtogroup HSP_MONITORING
  * @{
  */

/** @addtogroup HSP_MONITORING_Exported_Functions
  * @{
  */

/** @addtogroup HSP_MONITORING_Exported_Functions_Group1
  * @{
  */
/**
  * @brief Configure and enable a Task Comparator.
  * @param  hmw      Pointer to a hsp_engine_context_t.
  * @param  tcu_id   ID of the Task Comparator Unit.
  * @param  task_id  Task ID to monitor.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_MONITOR_EnableTaskComparator(hsp_engine_context_t *hmw, uint32_t tcu_id, uint32_t task_id)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_EnableTaskComparator(hmw->hdriver, tcu_id, task_id) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Disable a Task Comparator.
  * @param  hmw     Pointer to a hsp_engine_context_t.
  * @param  tcu_id  ID of the Task Comparator Unit.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_MONITOR_DisableTaskComparator(hsp_engine_context_t *hmw, uint32_t tcu_id)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_DisableTaskComparator(hmw->hdriver, tcu_id) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Configure and enable a Task Comparator.
  * @param  hmw      Pointer to a hsp_engine_context_t.
  * @param  tcu_id   ID of the Task Comparator Unit.
  * @param  task_id  Task ID to monitor.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_MONITOR_EnableTaskComparator_IT(hsp_engine_context_t *hmw, uint32_t tcu_id, uint32_t task_id)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_EnableTaskComparator_IT(hmw->hdriver, tcu_id, task_id) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Disable a Task Comparator.
  * @param  hmw     Pointer to a hsp_engine_context_t.
  * @param  tcu_id  ID of the Task Comparator Unit.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_MONITOR_DisableTaskComparator_IT(hsp_engine_context_t *hmw, uint32_t tcu_id)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_DisableTaskComparator_IT(hmw->hdriver, tcu_id) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @}
  */

/** @addtogroup HSP_MONITORING_Exported_Functions_Group2
  * @{
  */
/**
  * @brief  Enable the Timestamp capture.
  * @param  hmw   Pointer to the MW context.
  * @param  mode  Mode of capture.
  * @retval HSP_CORE_OK            MW HSP handle has been correctly initialized.
  * @retval HSP_CORE_INVALID_PARAM One of parameter is NULL
  * @retval HSP_CORE_ERROR         MW HSP handle not initialized
  */
hsp_core_status_t HSP_MONITOR_TSC_Enable(hsp_engine_context_t *hmw, hsp_monitor_tsc_mode_t mode)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  switch (mode)
  {
    case HSP_TIMESTAMP_SPE_BREAK:
      /* To do */
      break;
    case HSP_TIMESTAMP_TASK_CHANGE:
      /* To do */
      break;
    case HSP_TIMESTAMP_PFCT_CHANGE:
      /* To do */
      break;
    default:
      return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief  Disable the Timestamp capture.
  * @param  hmw   Pointer to the MW context.
  * @retval HSP_CORE_OK            MW HSP handle has been correctly initialized.
  * @retval HSP_CORE_INVALID_PARAM One of parameter is NULL
  * @retval HSP_CORE_ERROR         MW HSP handle not initialized
  */
hsp_core_status_t HSP_MONITOR_TSC_Disable(hsp_engine_context_t *hmw)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  if (HSP_HW_IF_TSC_Disable(hmw->hdriver) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @}
  */

/** @addtogroup HSP_MONITORING_Exported_Functions_Group3
  * @{
  */
/**
  * @brief Enable a group of HSP signals.
  * @param  hmw  Pointer to the MW context.
  * @param  group_id  SNOOP Group ID
  * @param  signal    Set of signals
  * @retval HSP_CORE_OK     Success.
  * @retval HSP_CORE_ERROR  Running failed.
  */
hsp_core_status_t HSP_MONITOR_SNOOP_Enable(hsp_engine_context_t *hmw, uint32_t group_id,
                                           uint32_t signal)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);


  return HSP_CORE_OK;
}

/**
  * @brief Disable a group of HSP signals.
  * @param  hmw  Pointer to the MW context.
  * @param  group_id  SNOOP Group ID
  * @retval HSP_CORE_OK     Success.
  * @retval HSP_CORE_ERROR  Running failed.
  */
hsp_core_status_t HSP_MONITOR_SNOOP_Disable(hsp_engine_context_t *hmw, uint32_t group_id)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);


  return HSP_CORE_OK;
}

/**
  * @}
 */

/** @addtogroup HSP_MONITORING_Exported_Functions_Group4
  * @{
  */
/**
  * @brief Get HSP Performance counter.
  * @param  hmw  Pointer to the MW context.
  * @return  counter value
  */
uint32_t HSP_MONITOR_GetPerformanceCounter(hsp_engine_context_t *hmw)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  return HSP_HW_IF_GetPerformanceCounter(hmw->hdriver);
}

/**
  * @}
  */

/** @addtogroup HSP_MONITORING_Exported_Functions_Group5
  * @{
  */
hsp_core_status_t HSP_MONITOR_RegisterTCU_TaskStartedCallback(hsp_engine_context_t *hmw,
                                                              p_hsp_engine_one_param_cb_t p_callback)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  if (HSP_HW_IF_RegisterTCU_TaskStartedCallback(hmw->hdriver, p_callback) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

hsp_core_status_t HSP_MONITOR_RegisterTCU_TaskEndedCallback(hsp_engine_context_t *hmw,
                                                            p_hsp_engine_one_param_cb_t p_callback)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  if (HSP_HW_IF_RegisterTCU_TaskEndedCallback(hmw->hdriver, p_callback) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @}
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
