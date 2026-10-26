/**
  ******************************************************************************
  * @file    mw_hsp_valid_e_param.h
  * @author  GPM Application Team
  * @brief   Header for mw_hsp_valid_e_param.c module
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MW_HSP_VALID_E_PARAM_H
#define MW_HSP_VALID_E_PARAM_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint32_t MW_HSP_E_Test_CheckParam(void);  /* Test HAL HSP APIs with wrong parameters where APIs return a MW Error */

#endif /* MW_HSP_VALID_E_PARAM_H */
