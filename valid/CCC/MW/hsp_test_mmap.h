/**
  ******************************************************************************************
  * \file hsp_test_mmap.h
  * \brief HSP BRAM memory map for FW test on FPGA
  *
  ******************************************************************************************
  * \attention
  *
  *  ST makes no warranty express or implied including but not limited to, any warranty of
  *  (i) merchantability or fitness for a particular purpose and/or (ii) requirements, for
  *  a particular purpose in relation to the LICENSED MATERIALS, which is provided <93>AS IS<94>,
  *  WITH ALL FAULTS. ST does not represent or warrant that the LICENSED MATERIALS provided
  *  hereunder is free of infringement of any third party patents, copyrights, trade secrets
  *  or other intellectual property rights. ALL WARRANTIES, CONDITIONS OR OTHER TERMS
  *  IMPLIED BY LAW ARE EXCLUDED TO THE FULLEST EXTENT PERMITTED BY LAW.
  *
  * <h2><center>&copy; COPYRIGHT 2019 STMicroelectronics - All Rights Reserved</center></h2>
  *
  ******************************************************************************************
  */

#ifndef __HSP_TEST_MMAP_H__
#define __HSP_TEST_MMAP_H__

/*------------------------------------------------------------------------------
 * Includes
 *----------------------------------------------------------------------------*/
#ifdef ARM_COMPILE
#ifdef STM32U575xx
#include "stm32u5xx_hal.h"
#endif
#ifdef STM32U3C5xx
#include "stm32u3xx_hal.h"
#endif
#ifdef STM32U575xx
#include "stm32u5xx_hal_def.h"
#endif
#ifdef STM32G5C4xx
#include "stm32g5dsxx_hal_def.h"
#endif
#endif

#ifndef ARM_COMPILE
#include "HSP_UserSpec_CPU_RstVal_Vx_x_x.h"
#else // ARM_COMPILE
#ifdef __HSP_DMA__
#define HSP_HWCFGR1_RESET_VAL                        0x20080100
#define HSP_HWCFGR1_RESET_MSK                        0xFFFFFFFF
#else // __HSP_DMA__
#define HSP_HWCFGR1_RESET_VAL                        0x140C0020
#define HSP_HWCFGR1_RESET_MSK                        0xFFFFFFFF
#endif // __HSP_DMA__
#endif // ARM_COMPILE

/*------------------------------------------------------------------------------
 * Defines
 *----------------------------------------------------------------------------*/

#if defined(STM32U3C5xx)  || (STM32G5C4xx)

#ifdef STM32U3C5xx // NEEDED NOW BY MDW
#define HSP_ARM_MEMORY_BASE_ADDR 0x20090000
#endif
#ifdef STM32G5C4xx
//#define HSP_ARM_MEMORY_BASE_ADDR 0x20090000
#endif
#define HSP_CNN_PARAM_ADDR (HSP_BASE_DRAM_MEM + HSP_DRAM_CNN_PARAM_ADDR) ///< Temporary CNN param address

#ifdef ARM_COMPILE // FIX VAL

/// HSP BRAM AB size in byte
#define HSP_MEM_BRAMAB_SIZE HSP1_BRAMAB_SIZE
/// CRAM byte size
#define HSP_CRAM_SIZE_8 HSP1_CRAM_SIZE
/// DRAM byte size
#define HSP_DRAM_SIZE_8  HSP1_DRAM_SIZE
#else
/// HSP BRAM AB size in byte
#define HSP_MEM_BRAMAB_SIZE (((HSP_HWCFGR1_RESET_VAL & HSP_HWCFGR1_BRAM_SIZE_Msk) >> HSP_HWCFGR1_BRAM_SIZE_Pos) << 9)
/// CRAM byte size
#define HSP_CRAM_SIZE_8 (((HSP_HWCFGR1_RESET_VAL & HSP_HWCFGR1_CRAM_SIZE_Msk) >> HSP_HWCFGR1_CRAM_SIZE_Pos) << 10)
/// DRAM byte size
#define HSP_DRAM_SIZE_8 (((HSP_HWCFGR1_RESET_VAL & HSP_HWCFGR1_DRAM_SIZE_Msk) >> HSP_HWCFGR1_DRAM_SIZE_Pos) << 10)
#endif

/// BRAM A byte address
#define HSP_MEMA_BASE_ADDR (HSP_ARM_MEMORY_BASE_ADDR + HSP_CRAM_SIZE_8 + HSP_DRAM_SIZE_8)
/// BRAM B byte address
#define HSP_MEMB_BASE_ADDR (HSP_ARM_MEMORY_BASE_ADDR + HSP_CRAM_SIZE_8 + HSP_DRAM_SIZE_8 + HSP_MEM_BRAMAB_SIZE)

#else
   
#define HSP_CNN_PARAM_ADDR (HSP1_BASE_NS + HSP_BASE_DRAM_MEM + HSP_DRAM_CNN_PARAM_ADDR) ///< Temporary CNN param address
/// HSP BRAM AB size in byte
#define HSP_MEM_BRAMAB_SIZE (((HSP_HWCFGR1_RESET_VAL & HSP_HWCFGR1_BRAM_SIZE_Msk) >> HSP_HWCFGR1_BRAM_SIZE_Pos) << 9)

/// CRAM byte size
#define HSP_CRAM_SIZE_8 (((HSP_HWCFGR1_RESET_VAL & HSP_HWCFGR1_CRAM_SIZE_Msk) >> HSP_HWCFGR1_CRAM_SIZE_Pos) << 10)
/// DRAM byte size
#define HSP_DRAM_SIZE_8 (((HSP_HWCFGR1_RESET_VAL & HSP_HWCFGR1_DRAM_SIZE_Msk) >> HSP_HWCFGR1_DRAM_SIZE_Pos) << 10)
/// BRAM A byte address
#define HSP_MEMA_BASE_ADDR (HSP1_BASE_NS + HSP_ARM_MEMORY_BASE_ADDR + HSP_CRAM_SIZE_8 + HSP_DRAM_SIZE_8)
/// BRAM B byte address
#define HSP_MEMB_BASE_ADDR (HSP1_BASE_NS + HSP_ARM_MEMORY_BASE_ADDR + HSP_CRAM_SIZE_8 + HSP_DRAM_SIZE_8 + HSP_MEM_BRAMAB_SIZE)
#endif

// Hypsa memory mapping for all TESTS
#ifdef ARM_COMPILE

#ifdef __HSP_DMA__
#ifdef STM32G5C4xx
#define HSP_MEM_CROM_SIZE  48
#define HSP_MEM_CRAM_SIZE  24
#define HSP_MEM_DRAM_SIZE  12
#define HSP_MEM_BRAM_SIZE  32
#else // STM32G5C4xx
#define HSP_MEM_CROM_SIZE  48
#define HSP_MEM_CRAM_SIZE  32
#define HSP_MEM_DRAM_SIZE  12
#define HSP_MEM_BRAM_SIZE 256
#endif // STM32G5C4xx
#else // __HSP_DMA__
#define HSP_MEM_CROM_SIZE   16
#define HSP_MEM_CRAM_SIZE   20
#define HSP_MEM_DRAM_SIZE   12
#define HSP_MEM_BRAM_SIZE   32
#endif // __HSP_DMA__

#define HSP_BASE_SHARED_MEM (HSP_ARM_MEMORY_BASE_ADDR + (HSP_MEM_CRAM_SIZE<<10) + (HSP_MEM_DRAM_SIZE<<10) + (HSP_MEM_BRAM_SIZE<<10))
#define HSP_BASE_DRAM_MEM (HSP_ARM_MEMORY_BASE_ADDR + (HSP_MEM_CRAM_SIZE << 10))

#ifdef STM32U3C5xx
#define HSP_MEM_COV_SIZE ((((HSP_MEM_CRAM_SIZE + HSP_MEM_CROM_SIZE) << 10) / 2) / 32) // 576 in mini 1024 in full
#define HYPSA_SHARED_MEM_BASE_ADDR (HSP_BASE_SHARED_MEM) ///< Hypsa platform shared addr
#endif
#ifdef STM32U575xx
#define HSP_MEM_COV_SIZE ((((HSP_MEM_CRAM_SIZE + HSP_MEM_CROM_SIZE) << 10) / 2) / 32) // 576 in mini 1024 in full
#define HYPSA_SHARED_MEM_BASE_ADDR (HSP1_BASE_NS + HSP_BASE_SHARED_MEM) ///< Hypsa platform shared addr
#endif
#if defined(STM32H7P5xx) || defined(STM32H7P4xx)
#define HYPSA_SHARED_MEM_BASE_ADDR (HSP_BASE_SHARED_MEM) ///< Hypsa platform shared addr
#endif
#ifdef STM32G5C4xx
#define HYPSA_SHARED_MEM_BASE_ADDR (HSP_BASE_SHARED_MEM) ///< Hypsa platform shared addr
#endif


#define HYPSA_TEST_REF_ADDR  0 ///< Hypsa platform Ref addr
#define HYPSA_TEST_DST_ADDR  0 ///< Hypsa platform Dst addr
#define HYPSA_TEST_SRCA_ADDR 0 ///< Hypsa platform SrcA addr
#define HYPSA_TEST_SRCB_ADDR 0 ///< Hypsa platform SrcB addr
#define HYPSA_INT_BUFF_ADDR  0 ///< Hypsa platform Internal buffer addr
#define HYPSA_INT_STATE_ADDR 0 ///< Hypsa platform Internal state buffer addr

#define HSP_INTERNAL_DMA_BUFF_INDEX (0x7e00*4) ///< HSP DMA region

#else // ARM_COMPILE

// Hypsa platform
#define HSP1_BASE_NS 0
#define HSP_BASE_DRAM_MEM 0

// #define HSP_MEMA_BASE_ADDR HSP_HYP_BRAMA_ADDR
// #define HSP_MEMB_BASE_ADDR HSP_HYP_BRAMB_ADDR

#ifdef HAS_BYTE
// Hyperion byte support
#define HYPSA_SHARED_MEM_BASE_ADDR ((0x040000+(1024 + 580)) * 4) ///< Hypsa platform shared addr
#define HYPSA_TEST_REF_ADDR  (0x048000 * 4) ///< Hypsa platform Ref addr
#define HYPSA_TEST_DST_ADDR  (0x04c000 * 4) ///< Hypsa platform Dst addr
#define HYPSA_TEST_SRCA_ADDR (0x04b000 * 4) ///< Hypsa platform SrcA addr

#ifdef GCC_COMPILE
#define HYPSA_TEST_SRCB_ADDR hspTestV4096BF32 ///< Hypsa platform SrcB addr
#else // GCC_COMPILE
#define HYPSA_TEST_SRCB_ADDR (0x04a000 * 4) ///< Hypsa platform SrcB addr
#endif // GCC_COMPILE
#define HYPSA_INT_BUFF_ADDR  ((0x04E000+(1024 + 580)) * 4) ///< Hypsa platform Internal buffer addr
#define HYPSA_INT_STATE_ADDR (0x04E000 * 4) ///< Hypsa platform Internal state buffer addr

#define HYPSA_TEST_SHA_SIZE (4*0x2000 * 4) ///< Hypsa shared memory size: REF + DST+ SRCA + SRCB + PARAM
#define HYPSA_TEST_FFT_SHA_SIZE (4*0x2000 * 4) ///< Hypsa shared memory size: REF + DST+ SRCA + SRCB + PARAM

#define HSP_INTERNAL_DMA_BUFF_INDEX (0x7e00 * 4) ///< HSP DMA region

#else // HAS_BYTE
// Hyperion word adressing
#define HYPSA_SHARED_MEM_BASE_ADDR (0x040000+(1024 + 580)) ///< Hypsa platform shared addr
#define HYPSA_TEST_REF_ADDR  0x048000 ///< Hypsa platform Ref addr
#define HYPSA_TEST_DST_ADDR  0x04c000 ///< Hypsa platform Dst addr
#define HYPSA_TEST_SRCA_ADDR 0x04b000 ///< Hypsa platform SrcA addr

#ifdef GCC_COMPILE
#define HYPSA_TEST_SRCB_ADDR hspTestV4096BF32 ///< Hypsa platform SrcB addr
#else // GCC_COMPILE
#define HYPSA_TEST_SRCB_ADDR 0x04a000 ///< Hypsa platform SrcB addr
#endif // GCC_COMPILE
#define HYPSA_INT_BUFF_ADDR  (0x04E000+(1024 + 580)) ///< Hypsa platform Internal buffer addr
#define HYPSA_INT_STATE_ADDR 0x04E000 ///< Hypsa platform Internal state buffer addr

#define HYPSA_TEST_SHA_SIZE (4*0x2000) ///< Hypsa shared memory size: REF + DST+ SRCA + SRCB + PARAM
#define HYPSA_TEST_FFT_SHA_SIZE (4*0x2000) ///< Hypsa shared memory size: REF + DST+ SRCA + SRCB + PARAM

#define HSP_INTERNAL_DMA_BUFF_INDEX 0x7e00 ///< HSP DMA region

#endif // HAS_BYTE

#endif // ARM_COMPILE


/*------------------------------------------------------------------------------
 * Types
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 * Variables
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 * Functions
 *----------------------------------------------------------------------------*/

#endif // __HSP_TEST_MMAP_H__
