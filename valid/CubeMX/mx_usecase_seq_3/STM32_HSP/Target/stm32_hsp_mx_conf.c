/**
  ******************************************************************************
  * @file    MW/Src/stm32_hsp_mx_conf.c
  * @author  GPM Application Team
  * @brief   This example describes how to configure the STM32U3xx MW API.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hsp_mx_conf.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* HSP BRAM Static Allocation *********************************/
static float my_var1 __attribute__((section("HSP_DATA_BRAM")));

/* Private function prototypes -----------------------------------------------*/
extern void Error_Handler(void);
void mx_hsp_config_pl_id_2(hsp_core_handle_t *hmw);
void mx_hsp_config_pl_id_5(hsp_core_handle_t *hmw);

/* Processing List Recording Function prototypes **************/
void MX_STM32_HSP_ProcessList_Config(hsp_core_handle_t *hmw)
{
  mx_hsp_config_pl_id_2(hmw);
  mx_hsp_config_pl_id_5(hmw);
}

/**
  * @brief  Configure the Processing List MY_PROCLIST_USER_TOT
  *    - event: None
  * @param  hmw  Handle to the HSP middleware.
  * @retval None.
  */
void mx_hsp_config_pl_id_2(hsp_core_handle_t *hmw)
{
  /* Record the processing list */
  if (HSP_PROCLIST_StartRecord(hmw, (uint32_t)MY_PROCLIST_USER_TOTO) != HSP_CORE_OK)
  {
    Error_Handler();
  }

  if (HSP_PROCLIST_ScalarIAdd_f32(hmw, &my_var1, 1.0f, &my_var1, 0U) != HSP_CORE_OK)
  {
    Error_Handler();
  }

  if (HSP_PROCLIST_StopRecord(hmw) != HSP_CORE_OK)
  {
    Error_Handler();
  }

  /* Configure a Trigger Event used to trigger the Processing List */
  /*  - Signal Source: Transfer Complete from Channel9 of DMA1     */
  /*  - Trigger polarity: on Rising Edge                           */
  /*  - TRGIN instance : TRGIN[4]                                  */
  /*  - Synchronous with end of Task: None                         */
  hsp_core_event_trigger_config_t evt_cfg;
  evt_cfg.trig_itf.polarity = HSP_POLARITY_RISING;
  evt_cfg.trig_itf.source = HSP_DMA1_CHANNEL9_TC; /*<! Constant define in stm32_hsp_trigger_conf.h */
  evt_cfg.trig_itf.instance = 4U;
  evt_cfg.evt.task_sync = HSP_CORE_TASK_NONE;
  HSP_PROCLIST_ConfigEventTrigger(hmw, MY_PROCLIST_USER_TOTO, &evt_cfg);
}

/**
  * @brief  Configure the Processing List MY_PROCLIST_USER_LULU
  *    - event: None
  * @param  hmw  Handle to the HSP middleware.
  * @retval None.
  */
void mx_hsp_config_pl_id_5(hsp_core_handle_t *hmw)
{
  /* Record the processing list */
  if (HSP_PROCLIST_StartRecord(hmw, (uint32_t)MY_PROCLIST_USER_LULU) != HSP_CORE_OK)
  {
    Error_Handler();
  }

  if (HSP_PROCLIST_ScalarIAdd_f32(hmw, &my_var1, 1.0f, &my_var1, 0U) != HSP_CORE_OK)
  {
    Error_Handler();
  }

  if (HSP_PROCLIST_StopRecord(hmw) != HSP_CORE_OK)
  {
    Error_Handler();
  }

  /* Configure a Trigger Event used to trigger the Processing List */
  /*  - Signal Source: Transfer Complete from Channel9 of DMA1     */
  /*  - Trigger polarity: on Falling Edge                          */
  /*  - TRGIN instance : TRGIN[7]                                  */
  /*  - Synchronous with end of Task: None                         */
  hsp_core_event_trigger_config_t evt_cfg;
  evt_cfg.trig_itf.polarity = HSP_POLARITY_FALLING;
  evt_cfg.trig_itf.source = HSP_TIM3_TRGO; /*<! Constant define in stm32_hsp_trigger_conf.h */
  evt_cfg.trig_itf.instance = 7U;
  evt_cfg.evt.task_sync = HSP_CORE_TASK_NONE;
  HSP_PROCLIST_ConfigEventTrigger(hmw, MY_PROCLIST_USER_LULU, &evt_cfg);
}