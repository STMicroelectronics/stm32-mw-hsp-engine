/**
  ******************************************************************************
  * @file    stm32u3xx_it.c
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32u3xx_hal.h"
#include "stm32u3xx_it.h"

#include "hsp_hw_if.h"

/** @addtogroup stm32u3xx_HAL_Validation
  * @{
  */

/** @addtogroup HAL
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t hsp_it = 0;
volatile uint32_t hsp_it_evt = 0;
volatile uint32_t hsp_it_gbl = 0;
volatile uint32_t hsp_it_err = 0;
//extern hw_hsp_if_handle_t h_hw_hsp_if[];
// extern hsp_core_handle_t hmw;
extern hsp_engine_context_t hmw;

void HSP1_IRQHandler(void);

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
uint8_t enableCheckSystickFrequency = 0;

/******************************************************************************/
/*            Cortex-M33 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Secure Fault exception.
  * @param  None
  * @retval None
  */
void SecureFault_Handler(void)
{
  /* Go to infinite loop when Secure Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
  /* Switch back Thread mode to privileged */
  __set_CONTROL(0);

  /* Execute ISB instruction to flush pipeline as recommended by Arm */
  __ISB();
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

/******************************************************************************/
/*                 stm32u3xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32u3xx.s).                                               */
/******************************************************************************/
/**
  * @brief This function handles HSP global interrupt.
  */
void HSP1_IRQHandler(void)
{
  /* Check the interrupt and clear flag */
  //printf("Entree DMA2D_IRQHandler\n");
  //HAL_HSP_IRQHandler(&hdma_cordic_write);
//  uint32_t event = hmw.hdriver->Instance->ERR_ISR;
  uint32_t event =  ((HSP_HandleTypeDef *)(hmw.hdriver))->Instance->ERR_ISR;
     
 if (((HSP_HandleTypeDef *)(hmw.hdriver))->Instance->ERR_ISR)
  {
    // if (((hsp_it_err & HSPHandle.Instance->ERR_ISR) == 0))
    {
//      printf("HSPHandle.Instance->ERR_ISR=0x%08x\n",HSPHandle.Instance->ERR_ISR);
      // printf("HSPHandle.Instance->ERR_ISR=0x%08x\n",HSPHandle.Instance->ERR_ISR);
      // hsp_it_err |= HSPHandle.Instance->ERR_ISR;
	  hsp_it_err++;
      if (((HSP_HandleTypeDef *)(hmw.hdriver))->Instance->ERR_ISR & 0x00800000) ((HSP_HandleTypeDef *)(hmw.hdriver))->Instance->ERR_ICR |= (1 << 23);
      if (((HSP_HandleTypeDef *)(hmw.hdriver))->Instance->ERR_ISR & 0x00040000) ((HSP_HandleTypeDef *)(hmw.hdriver))->Instance->ERR_ICR |= (1 << 18);
      event = ((HSP_HandleTypeDef *)(hmw.hdriver))->Instance->ERR_ISR;
    }
  }
// else
 {
   if (((event & 0x00800000) == 0) && ((event & 0x00040000) == 0))
   {
      // reset interrupt status register
      ((HSP_HandleTypeDef *)(hmw.hdriver))->Instance->ERR_ICR = 0xFFFFFFFF;
      ((HSP_HandleTypeDef *)(hmw.hdriver))->Instance->EVT_ICR = 0xFFFFFFFF;
      ((HSP_HandleTypeDef *)(hmw.hdriver))->Instance->PFCTEVT_ICR = 0xFFFFFFFF;
      hsp_it_gbl++;
      hsp_it_evt++;
   }
 }
}


/**
  * @}
  */

/**
  * @}
  */
