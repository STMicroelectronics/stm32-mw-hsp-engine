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
void mx_hsp_config_pl_id_3(hsp_core_handle_t *hmw);
void mx_hsp_config_pl_id_6(hsp_core_handle_t *hmw);

/* Processing List Recording Function prototypes **************/
void MX_STM32_HSP_ProcessList_Config(hsp_core_handle_t *hmw)
{
  mx_hsp_config_pl_id_3(hmw);
  mx_hsp_config_pl_id_6(hmw);
}

/**
  * @brief  Configure the Processing List MY_PROCLIST_USER_TOTO
  *    - event: None
  * @param  hmw  Handle to the HSP middleware.
  * @retval None.
  */
void mx_hsp_config_pl_id_3(hsp_core_handle_t *hmw)
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

  /* Configure a Stream Event used to trigger the Processing List  */
  /*  - Direction: CPU to HSP                                      */
  /*  - STREAM instance: BUFF[2]                                   */
  /*  - Synchronous with end of Task: None                         */
  hsp_core_event_stream_config_t evt_cfg;
  evt_cfg.stream_itf.direction = HSP_STREAM_DIRECTION_CPU_TO_HSP;
  evt_cfg.stream_itf.instance = 2U;
  evt_cfg.evt.task_sync = HSP_CORE_TASK_NONE;
  HSP_PROCLIST_ConfigEventStream(hmw, MY_PROCLIST_USER_TOTO, &evt_cfg);
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

  /* Configure a Stream Event used to trigger the Processing List  */
  /*  - Direction: HSP to CPU                                      */
  /*  - STREAM instance: BUFF[0]                                   */
  /*  - Synchronous with end of Task: None                         */
  hsp_core_event_stream_config_t evt_cfg;
  evt_cfg.stream_itf.direction = HSP_STREAM_DIRECTION_HSP_TO_CPU;
  evt_cfg.stream_itf.instance = 0U;
  evt_cfg.evt.task_sync = HSP_CORE_TASK_NONE;
  HSP_PROCLIST_ConfigEventStream(hmw, MY_PROCLIST_USER_LULU, &evt_cfg);
}