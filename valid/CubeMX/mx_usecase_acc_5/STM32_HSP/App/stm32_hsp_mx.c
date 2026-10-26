/**
  ******************************************************************************
  * @file    MW/Src/main.c
  * @author  GPM Application Team
  * @brief   This example describes how to configure the STM32U3xx MW API.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32_hsp_mx.h"

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
hsp_core_handle_t hmw;

/* Private function prototypes -----------------------------------------------*/

/* Application functions prototypes *******/
extern void Error_Handler(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief Middleware HSP Initialization Function
  * @param None
  * @retval None
  */
void MX_STM32_HSP_Init(void)
{
  /* Init the HSP Middleware for HSP Peripheral */
  if (HSP_CORE_Init(&hmw) != HSP_CORE_OK)
  {
    Error_Handler();
  }
}
