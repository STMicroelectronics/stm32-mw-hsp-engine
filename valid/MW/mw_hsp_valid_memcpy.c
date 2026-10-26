/**
  ******************************************************************************
  * @file    mw_hsp_valid_init.c
  * @author  GPM Application Team
  * @brief   This file contains the HAL HSP functional validation functions.
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
#include "mw_hsp_valid_memcpy.h"
#include "hsp_memcpy.h"

/* Private constants ---------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BUFFER_SIZE  32U
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
int compare_buffers(const uint8_t *buf1, const uint8_t *buf2, uint32_t size);

/* Exported functions --------------------------------------------------------*/
/**
  * @brief Check the stm32_hsp_memcpy function
  * @par Test Description
  *  - Check the copy of aligned 32-bit buffer
  *  - Check the copy of unalgined 32-bit buffer
  * @par Required Preconditions
  * None
  * @par Expected Results
  *   The copies must be passed
  * @retval
  * 0: Test passed
  * Value different from 0: Test failed
  */
uint32_t MW_HSP_VALID_Test_ST_Memcpy(void)
{
  uint8_t ref_buffer[BUFFER_SIZE] = {
    0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF1,
    0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x10,
    0x32, 0x54, 0x76, 0x98, 0xBA, 0xDC, 0xFE, 0x21,
    0x43, 0x65, 0x87, 0xA9, 0xCB, 0xED, 0x1F, 0x3E
  };
  uint8_t dst[BUFFER_SIZE];

  /* Test aligned 32-bit */
  stm32_hsp_memcpy(dst, ref_buffer, BUFFER_SIZE);
  if (compare_buffers(dst, ref_buffer, BUFFER_SIZE) != 0U)
  {
    VALIDATION_CHECK_FAIL(__LINE__);
  }

  /* Test not aligned 32-bit */
  stm32_hsp_memcpy(dst + 1, ref_buffer + 1, BUFFER_SIZE - 1);
  if (compare_buffers(dst + 1, ref_buffer + 1, BUFFER_SIZE - 1) != 0U)
  {
    VALIDATION_CHECK_FAIL(__LINE__);
  }

  /* Test end */
  return VALIDATION_RETURN_TEST_DONE;
}

int compare_buffers(const uint8_t *buf1, const uint8_t *buf2, uint32_t size)
{
  for (uint32_t i = 0U; i < size; i++) 
  {
    if (buf1[i] != buf2[i])
    {
        return 1; /* Diff found */
    }
  }

  return 0U;
}