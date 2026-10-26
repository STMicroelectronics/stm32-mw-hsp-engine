/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file   app_hsp_engine_seq.c
  * @brief  This file implements the application using Processing List 
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
/* USER CODE END Header */

#include "app_hsp_engine_seq.h"
#include "app_hsp_bram_alloc.h"
#include "hsp_proclist.h"
#include "hsp_modules_def.h"
#include "hsp_trigger_conf.h"
#include <string.h>

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */
/* Exported variables ------------------------------------------------------- */

/* Access to external variables --------------------------------------------- */
extern hsp_engine_context_t hmw;
extern void Error_Handler(void);

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* USER CODE BEGIN PFP */
/* Private function prototypes ---------------------------------------------- */

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/* -----------------------------------------------------------------------------
   Example of function to record a Processing List no attached to any event
   -------------------------------------------------------------------------- */
/**
 * @brief Record FIR Processing list
 * @param hsp_core_handle_t
 * @retval uint32_t
 */
uint32_t MX_HSP_SEQ_Record_PL_FIR(hsp_engine_context_t *hmw)
{
  uint32_t error = 0UL;
  hsp_core_status_t mw_status;

  mw_status = HSP_SEQ_StartRecordPL(hmw, HSP_SEQ_PL_ID_FIR);
  if (mw_status != HSP_CORE_OK) error++;

  mw_status = HSP_SEQ_ScaInc_u32(hmw, &pl_call, &pl_call, HSP_SEQ_IOTYPE_DEFAULT);
  if (mw_status != HSP_CORE_OK) error++;

  /* ----- Execute the FIR ----- */
  volatile uint32_t *p_stream_buffer0 = HSP_SEQ_STREAM_GetBufferAddress(hmw, HSP_SEQ_STREAM_BUFFER_0);

//  mw_status = HSP_SEQ_ScaNeg_f32(hmw, (float *)p_stream_buffer0, (float32_t *)pPopOut/*&fir_pop_out*/, (HSP_SEQ_IOTYPE_RXTX_0 | HSP_SEQ_IOTYPE_POP_1));
//  if (mw_status != HSP_CORE_OK) error++;
#if defined(USE_STATIC_BRAM_POP_VARIABLE)
  mw_status = HSP_SEQ_ScaAbs_f32(hmw, (float *)p_stream_buffer0, (float32_t *)/*pPopOut*/&pop_out, (HSP_SEQ_IOTYPE_RXTX_0 | HSP_SEQ_IOTYPE_POP_1));
  if (mw_status != HSP_CORE_OK) error++;

  mw_status = HSP_SEQ_ScaIModAdd_u32(hmw, /*pPopOut*/&pop_out, (1U), (uint32_t) p_buff_out, (2*INPUT_SIGNAL_SAMPLES_SIZE), HSP_SEQ_IOTYPE_DEFAULT);
  if (mw_status != HSP_CORE_OK) error++;
#else
  mw_status = HSP_SEQ_ScaAbs_f32(hmw, (float *)p_stream_buffer0, (float32_t *)pPopOut, (HSP_SEQ_IOTYPE_RXTX_0 | HSP_SEQ_IOTYPE_POP_1));
  if (mw_status != HSP_CORE_OK) error++;

  mw_status = HSP_SEQ_ScaIModAdd_u32(hmw, pPopOut, (1U), (uint32_t) p_buff_out, (2*INPUT_SIGNAL_SAMPLES_SIZE), HSP_SEQ_IOTYPE_DEFAULT);
  if (mw_status != HSP_CORE_OK) error++;
#endif /* USE_STATIC_BRAM_POP_VARIABLE */
  mw_status = HSP_SEQ_StopRecordPL(hmw);
  if (mw_status != HSP_CORE_OK) error++;

  /* Configure the Event with DMA as trigger */
  hsp_seq_event_stream_buffer_config_t event_cfg;
  event_cfg.instance = HSP_SEQ_STREAM_BUFFER_0;
  event_cfg.direction = HSP_SEQ_STREAM_BUFFER_RX;
  event_cfg.sync = HSP_SEQ_STREAM_BUFFER_SYNC_DISABLE;
  event_cfg.evt_sync = HSP_SEQ_EVENT_SYNC_TCU_DISABLED;

  mw_status = HSP_SEQ_EVENT_SetConfig_StreamBuffer(hmw, HSP_SEQ_PL_ID_FIR, &event_cfg);
  if (mw_status != HSP_CORE_OK) error++;

//  /* Configure the Event Synchro */
//  mw_status = HSP_SEQ_EVENT_SetConfig_CSEG(hmw, HSP_SEQ_PL_ID_FIR_FFT, HSP_SEQ_EVENT_SYNC_TCU_DISABLED);
//  if (mw_status != HSP_CORE_OK) error++;

  return error;
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

