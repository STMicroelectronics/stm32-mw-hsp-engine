/**
  ******************************************************************************
  * @file mw_hsp_valid_testslist.c
  * @author MCD Application Team
  * @brief This file provides all the MW HSP validation tests list.
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
#include <stdio.h>
#include "mw_hsp_valid_testlist.h"
#include "mw_hsp_valid_e_assert.h"
#include "mw_hsp_valid_init.h"
#include "mw_hsp_valid_memcpy.h"
#include "mw_hsp_valid_stream_buffer.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
#define TESTLIST_SECTION(name) {1, (name), 0U, 0U, NULL, "", 0U}
#define TESTLIST_TEST(name, test, desc) {0, (name), 0U, 0U, (test), (desc), 0U}

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

mw_hsp_test_t a_valid_testlist[] =
{
  TESTLIST_SECTION("Assertions"),
    TESTLIST_TEST("Assertions for Core/BRAM/Proclist", MW_HSP_E_Test_AssertDbgParam, "Test CORE, BRAM & PROCLIST APIs Assertions"),
    TESTLIST_TEST("Assertions for interfaces", MW_HSP_E_Test_AssertDbgParam_interfaces, "Test Interfaces Assertions"),

  TESTLIST_SECTION("Init/DeInit"),
    TESTLIST_TEST("Init", MW_HSP_VALID_Test_Init, "Load FW/Plugin + Boot"),

  TESTLIST_SECTION("Utilities"),
    TESTLIST_TEST("stm32_hsp_memcpy", MW_HSP_VALID_Test_ST_Memcpy, "Check 32-bit aligned copy"),

  TESTLIST_SECTION("STREAM Buffers"),
    TESTLIST_TEST("STREAM Int2Float", MW_HSP_VALID_Test_Stream_Int2Float, "Enable/Disable Int2Float conversion"),
    TESTLIST_TEST("STREAM RX", MW_HSP_VALID_Test_Stream_RX, "Run a Process with STREAM Buffer in RX"),
};

const uint32_t a_valid_testlist_count = sizeof(a_valid_testlist) / sizeof(a_valid_testlist[0]);