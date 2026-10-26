/**
  ******************************************************************************
  * @file    mw_hsp_valid_test_log.h
  * @author  GPM Application Team
  * @brief   Header for mw_hsp_valid_testlist.c module
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
#ifndef MW_HSP_VALID_TEST_LOG_H
#define MW_HSP_VALID_TEST_LOG_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "mw_hsp_valid_testlist.h"

/* Exported constants --------------------------------------------------------*/

#define LOG_FILENAME "Validation_MW_HSP_Engine_"
#define REPORT_FILENAME "Validation_MW_HSP_Engine_Report_V1.0_N/A_2025_05_14.txt"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void print_report(const char *filename, mw_hsp_test_t *testlist, uint32_t count);

#endif /* MW_HSP_VALID_TEST_LOG_H */
