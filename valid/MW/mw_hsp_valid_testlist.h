/**
  ******************************************************************************
  * @file    mw_hsp_valid_testlist.h
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
#ifndef MW_HSP_VALID_TESTLIST_H
#define MW_HSP_VALID_TESTLIST_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Exported constants --------------------------------------------------------*/
#define MAX_NAME_LEN 64
#define MAX_DESC_LEN 128
#define LOG_FILENAME "Validation_MW_HSP_Engine_"
#define REPORT_FILENAME "Validation_MW_HSP_Engine_Report_V1.0_N/A_2025_05_14.txt"

/* Exported macro ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
// Structure pour chaque test/scénario
typedef struct {
  uint8_t is_group_header;
  char name[MAX_NAME_LEN];
  int group;
  int id;

  uint32_t (*func)(void);
  char description[MAX_DESC_LEN];
  uint32_t result;
} mw_hsp_test_t;

/* Exported functions --------------------------------------------------------*/
extern mw_hsp_test_t a_valid_testlist[];
extern const uint32_t a_valid_testlist_count;

#endif /* MW_HSP_VALID_TESTLIST_H */
