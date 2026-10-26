/**
  ******************************************************************************
  * @file    fpga_hsp_valid_it.c
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
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
#include "mw_hsp_valid.h"
#include "mw_hsp_valid_it.h"

//extern hal_dma_handle_t  hgpdma1_ch7;
//extern hal_dma_handle_t  hgpdma1_ch6;
//extern hal_dma_handle_t  hgpdma1_ch5;
//extern hal_dma_handle_t  hgpdma1_ch4;
//extern hal_dma_handle_t  hgpdma1_ch1;
//
//extern hal_dma_handle_t  hgpdma2_ch7;
//extern hal_dma_handle_t  hgpdma2_ch6;
//extern hal_dma_handle_t  hgpdma2_ch5;
//extern hal_dma_handle_t  hgpdma2_ch4;
//extern hal_dma_handle_t  hgpdma2_ch1;
//
//extern hal_dma_handle_t  hgpdma3_ch7;
//extern hal_dma_handle_t  hgpdma3_ch6;
//extern hal_dma_handle_t  hgpdma3_ch5;
//extern hal_dma_handle_t  hgpdma3_ch4;
//extern hal_dma_handle_t  hgpdma3_ch1;

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
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
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
//
///**
//  * @brief This function handles GPDMA1 Channel 7 global interrupt.
//  */
//void GPDMA1_CH7_IRQHandler(void)
//{
//  HAL_DMA_IRQHandler(&hgpdma1_ch7);
//}
//
///**
//  * @brief This function handles GPDMA1 Channel 6 global interrupt.
//  */
//void GPDMA1_CH6_IRQHandler(void)
//{
//  HAL_DMA_IRQHandler(&hgpdma1_ch6);
//}
//
///**
//  * @brief This function handles GPDMA1 Channel 5 global interrupt.
//  */
//void GPDMA1_CH5_IRQHandler(void)
//{
//  HAL_DMA_IRQHandler(&hgpdma1_ch5);
//}
//
///**
//  * @brief This function handles GPDMA1 Channel 4 global interrupt.
//  */
//void GPDMA1_CH4_IRQHandler(void)
//{
//  HAL_DMA_IRQHandler(&hgpdma1_ch4);
//}
//
///**
//  * @brief This function handles GPDMA1 Channel 1 global interrupt.
//  */
//void GPDMA1_CH1_IRQHandler(void)
//{
//  HAL_DMA_IRQHandler(&hgpdma1_ch1);
//}
//
///**
//  * @brief This function handles GPDMA2 Channel 7 global interrupt.
//  */
//void GPDMA2_CH7_IRQHandler(void)
//{
//  HAL_DMA_IRQHandler(&hgpdma2_ch7);
//}
//
///**
//  * @brief This function handles GPDMA2 Channel 6 global interrupt.
//  */
//void GPDMA2_CH6_IRQHandler(void)
//{
//  HAL_DMA_IRQHandler(&hgpdma2_ch6);
//}
//
///**
//  * @brief This function handles GPDMA2 Channel 5 global interrupt.
//  */
//void GPDMA2_CH5_IRQHandler(void)
//{
//  HAL_DMA_IRQHandler(&hgpdma2_ch5);
//}
//
///**
//  * @brief This function handles GPDMA2 Channel 4 global interrupt.
//  */
//void GPDMA2_CH4_IRQHandler(void)
//{
//  HAL_DMA_IRQHandler(&hgpdma2_ch4);
//}
//
///**
//  * @brief This function handles GPDMA2 Channel 1 global interrupt.
//  */
//void GPDMA2_CH1_IRQHandler(void)
//{
//  HAL_DMA_IRQHandler(&hgpdma2_ch1);
//}
//
///**
//  * @brief This function handles GPDMA3 Channel 7 global interrupt.
//  */
//void GPDMA3_CH7_IRQHandler(void)
//{
//  HAL_DMA_IRQHandler(&hgpdma3_ch7);
//}
//
///**
//  * @brief This function handles GPDMA3 Channel 6 global interrupt.
//  */
//void GPDMA3_CH6_IRQHandler(void)
//{
//  HAL_DMA_IRQHandler(&hgpdma3_ch6);
//}
//
///**
//  * @brief This function handles GPDMA3 Channel 5 global interrupt.
//  */
//void GPDMA3_CH5_IRQHandler(void)
//{
//  HAL_DMA_IRQHandler(&hgpdma3_ch5);
//}
//
///**
//  * @brief This function handles GPDMA3 Channel 4 global interrupt.
//  */
//void GPDMA3_CH4_IRQHandler(void)
//{
//  HAL_DMA_IRQHandler(&hgpdma3_ch4);
//}
//
///**
//  * @brief This function handles GPDMA3 Channel 1 global interrupt.
//  */
//void GPDMA3_CH1_IRQHandler(void)
//{
//  HAL_DMA_IRQHandler(&hgpdma3_ch1);
//}

