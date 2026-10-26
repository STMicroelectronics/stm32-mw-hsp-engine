/**
  ******************************************************************************
  * @file    MW/Inc/stm32_hsp_mx.h
  * @author  GPM Application Team
  * @brief   This example describes how to configure the STM32U3xx MW API.
  ******************************************************************************
  */
#ifndef STM32_HSP_MX_H__
#define STM32_HSP_MX_H__

/* Includes ------------------------------------------------------------------*/
#include "hsp.h"
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

/* HSP Middleware handle */
extern hsp_core_handle_t hmw;


void MX_STM32_HSP_Init(void);

#endif /* STM32_HSP_MX_H__ */
