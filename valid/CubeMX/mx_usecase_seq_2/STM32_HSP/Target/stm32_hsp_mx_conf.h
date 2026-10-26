/**
  ******************************************************************************
  * @file    MW/Src/stm32_hsp_mx_conf.c
  * @author  GPM Application Team
  * @brief   This example describes how to configure the STM32U3xx MW API.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "hsp.h"

#define MY_PROCLIST_USER_1   HSP_CORE_EVENT_1
#define MY_PROCLIST_USER_34  34U
#define HSP_PL_ALL_EVENTS_MASK  \
  HSP_CORE_EVENT_ID_TO_BITMASK(MY_PROCLIST_USER_1)

/* Processing List Recording Function prototypes **************/
void MX_STM32_HSP_ProcessList_Config(hsp_core_handle_t *hmw);

