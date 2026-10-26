/**
 ******************************************************************************
 * @file fpga_hsp_valid_test_log.c
 * @author MCD Application Team
 * @brief This file provides all the HAL HSP validation tests list.
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
#include "mw_hsp_valid_test_log.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void print_report_header(void);
void print_report_footer(uint32_t total, uint32_t passed, uint32_t failed);

/* Private functions ---------------------------------------------------------*/
void print_report_header(void)
{
  printf("Report filename: %s\n", REPORT_FILENAME);
  printf("______________________________________________________________________________________________________________________________\n");
  printf("                                               Validation datalog report\n\n");
  printf("IP name   : HSP                                                              Generated on: May 14 2025, 09:32:33\n");
  printf("IP version: v1.0                                                             Compiler: IAR EWARM, version 9020001\n");
  printf("Device    : N/A\n");
  printf("Board     : N/A\n\n");
  printf("  _________________________________________________________________________________________________________________________\n");
  printf("  |Sect.|  Test  |                 Test name                 | Result |            Description                            |\n");
  printf("  |  Gr.|   ID   |                                           |        |                                                   |\n");
  printf("  _________________________________________________________________________________________________________________________\n");
}

void print_report_footer(uint32_t total, uint32_t passed, uint32_t failed)
{
  printf("  _________________________________________________________________________________________________________________________\n\n");
  printf("Test sequence completed.\n\n");
  printf("Summary:\n");
  printf("  Number of tests listed:         %u\n", total);
  printf("  Number of tests executed:       %u              Executed tests ratio   => 100%% \n", total);
  printf("   - Number of tests untestable:  0             - Untestable tests ratio =>   0%% \n");
  printf("   - Number of tests passed:      %u            - Passed tests ratio     =>  %u%% \n", passed, (passed*100)/total);
  printf("   - Number of tests failed:      %u            - Failed tests ratio     =>  %u%% \n", failed, (failed*100)/total);
}

void print_report(const char *filename, mw_hsp_test_t *testlist, uint32_t count)
{
  uint32_t total = 0, passed = 0, failed = 0;

  print_report_header();

  for (uint32_t i = 0; i < count; ++i) {
    mw_hsp_test_t *t = &testlist[i];
    if (t->is_group_header)
    {
      /* Display the Group name */
      printf("  |  %-116s |\n", t->name);
    } else {
      /* Display the Test result */
      char res_str[10] = "OK";
      if (t->result > 0U)  sprintf(res_str, "%d", t->result);
      printf("  |     | %5d | %-42s | %-6s | %-49s |\n", t->id, t->name, res_str, t->description);
      total++;
      if (t->result == 0) passed++;
      else failed++;
    }
  }

  print_report_footer( total, passed, failed);
}