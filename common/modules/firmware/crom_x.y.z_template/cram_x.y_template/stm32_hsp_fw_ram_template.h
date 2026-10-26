/**
  ******************************************************************************
  * @file    stm32_hsp_fw_ram.h
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

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Exported constants --------------------------------------------------------*/
#define HSP_CRAM_SIZE 4545 ///< Size of the HSP CRAM buffer to load
#define HSP_DRAM_SIZE 3008 ///< Size of the HSP DRAM buffer to load

extern const uint32_t dataCRAMTab[];
extern const uint32_t dataDRAMTab[];

