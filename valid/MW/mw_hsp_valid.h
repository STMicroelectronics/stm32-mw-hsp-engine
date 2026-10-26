/**
  ******************************************************************************
  * @file    mw_hsp_valid.h
  * @author  GPM Application Team
  * @brief   Header for mw_hsp_valid.c module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MW_HSP_VALID_H
#define MW_HSP_VALID_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
//#include "stm32_hal.h"
#include "stm32u3xx_hal.h"
// #include "hsp_valid_desc_features.h"
// #include "hsp_valid_assert.h"
// #include "validation_sequencer.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define VALIDATION_CHECK_FAIL(code)  printf("failed: %d\n", code);

/* Literals for tests execution */
#define VALIDATION_RETURN_TEST_DONE                0    /* Value to be returned when a test has been executed (with or without fails) */
#define VALIDATION_RETURN_TEST_SKIPPED          9999    /* Legacy valid seq v1, to be avoided (recommendation: skip test in tests list with a justification string) */
#define VALIDATION_TEST_UNTESTABLE_RUNTIME  puts
/* Uncomment this line to run the exhaustive validation tests */
#define ENABLE_E_VALID

/* Uncomment this line to run the 'automatic' functional validation tests */
//#define ENABLE_AF_VALID

/* Uncomment this line to run the 'manual' functional validation tests */
//#define ENABLE_MF_VALID

/* Exported macro ------------------------------------------------------------*/
/* Exported variables ------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

#endif /* MW_HSP_VALID_H */
