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
HAL_HSP_HandleTypeDef hhsp1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Application functions prototypes *******/
void Error_Handler(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration ---------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN */

  /* USER CODE END */

  /* Configure the system clock */
//  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
//  MX_HSP1_Init();

  /* Initialize all middlewares */
  MX_STM32_HSP_Init();

  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

void Error_Handler(void)
{
  while (1);
}

///**
//  * @brief HSP Initialization Function
//  * @param None
//  * @retval None
//  */
//static void MX_HSP1_Init(void)
//{
//
//  /* USER CODE BEGIN HSP_Init 0 */
//
//  /* USER CODE END HSP_Init 0 */
//
//  hhsp1.Instance = HSP1;
//  if (HAL_HSP_Init(&hhsp1) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /* HSP1 interrupt Init */
//  NVIC_SetPriority(HSP1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
//  NVIC_EnableIRQ(HSP1_IRQn);
//
//  /* USER CODE BEGIN HSP_Init 1 */
//
//  /* USER CODE END HSP_Init 1 */
//
//  /* USER CODE BEGIN HSP_Init 2 */
//
//  /* USER CODE END HSP_Init 2 */
//}