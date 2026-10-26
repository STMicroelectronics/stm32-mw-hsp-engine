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
static float inBuffer[HSP_INBUFFER_SIZE] __attribute__((section("HSP_DATA_BRAM")));
static float outBuffer[HSP_OUTBUFFER_SIZE] __attribute__((section("HSP_DATA_BRAM")));

/* Private function prototypes -----------------------------------------------*/
extern void Error_Handler(void);
void mx_hsp_config_pl_id_1(hsp_core_handle_t *hmw);
void mx_hsp_config_pl_id_34(hsp_core_handle_t *hmw);

/* Processing List Recording Function prototypes **************/
void MX_STM32_HSP_ProcessList_Config(hsp_core_handle_t *hmw)
{
  mx_hsp_config_pl_id_34(hmw);
  mx_hsp_config_pl_id_1(hmw);
}
/**
  * @brief  Configure the Processing List MY_PROCLIST_USER_34
  *    - event: None
  * @param  hmw  Handle to the HSP middleware.
  * @retval None.
  */
void mx_hsp_config_pl_id_34(hsp_core_handle_t *hmw)
{
  /* Record the processing list */
  if (HSP_PROCLIST_StartRecord(hmw, (uint32_t)MY_PROCLIST_USER_34) != HSP_CORE_OK)
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

  /* Configure the Event used to trigger the PL */
  /* No Event configuration */
}

/**
  * @brief  Configure the Processing List MY_PROCLIST_USER_1
  *    - event: STREAM2
  * @param  hmw  Handle to the HSP middleware.
  * @retval None.
  */
void mx_hsp_config_pl_id_1(hsp_core_handle_t *hmw)
{
  /* Record the processing list */
  if (HSP_PROCLIST_StartRecord(hmw, (uint32_t)MY_PROCLIST_USER_1) != HSP_CORE_OK)
  {
    Error_Handler();
  }

  if (HSP_PROCLIST_ScalarIAdd_f32(hmw, &inBuffer, 1.0f, &outBuffer, 0U) != HSP_CORE_OK)
  {
    Error_Handler();
  }

  if (HSP_PROCLIST_StopRecord(hmw) != HSP_CORE_OK)
  {
    Error_Handler();
  }

  /* Configure a Trigger Event used to trigger the Processing List */
  hsp_core_event_config_t evt_cfg;
  evt_cfg.task_sync = HSP_CORE_TASK_NONE;
  HSP_PROCLIST_ConfigEventCPU(hmw, MY_PROCLIST_USER_1, &evt_cfg);
}
