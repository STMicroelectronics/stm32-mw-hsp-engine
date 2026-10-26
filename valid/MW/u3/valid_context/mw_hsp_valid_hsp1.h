/**
  ******************************************************************************
  * file           : mw_hsp_valid_hsp1.h
  * brief          : Header for mw_hsp_valid_hsp1.c file.
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MW_HSP_VAID_HSP1_H
#define MW_HSP_VAID_HSP1_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32u3xx_hal.h"
#define hal_hsp_handle_t  HSP_HandleTypeDef

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/**
  * @brief mx_hsp1_hal init function
  * This function configures the hardware resources used in this example
  * @retval pointer to handle or NULL in case of failure
  */
hal_hsp_handle_t *mw_hsp_valid_hsp1_hal_init(void);

/**
  * @brief  De-initialize hsp1 instance and return it.
  */
void mw_hsp_valid_hsp1_hal_deinit(void);

/**
  * @brief  Get the HSP1 object.
  * @retval Pointer on the HSP1 Handle
  */
hal_hsp_handle_t *mw_hsp_valid_hsp1_hal_gethandle(void);

/******************************************************************************/
/*                     HSP global non-secure interrupt                        */
/******************************************************************************/
void HSP1_IRQHandler(void);
void HSP1_ERR_IRQHandler(void);
void HSP1_EVT_IRQHandler(void);
void HSP1_FWEVT_IRQHandler(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MW_HSP_VAID_HSP1_H */
