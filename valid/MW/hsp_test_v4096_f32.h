/**
  ******************************************************************************************
  * \file hsp_test_v4096_f32.h
  * \brief Common vector test with 4096 values for f32
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
  * <h2><center>&copy; COPYRIGHT 2020 STMicroelectronics - All Rights Reserved</center></h2>
  *
  ******************************************************************************************
  */

#ifndef __HSP_TEST_V4096_F32_H__
#define __HSP_TEST_V4096_F32_H__


/*------------------------------------------------------------------------------
 * Includes
 *----------------------------------------------------------------------------*/
#include "hsp_test_common.h"

/*------------------------------------------------------------------------------
 * Defines
 *----------------------------------------------------------------------------*/
/// Vector buffer size
#define HSP_TEST_V4096_F32_S 4096

#ifndef ARM_COMPILE
#ifdef GCC_COMPILE
#define HYPSA_TEST_SRCA_ADDR hspTestV4096AF32 ///< Hypsa platform SrcB addr
#ifndef HSP_TEST_V4096_F32_RANDOM
#define HYPSA_TEST_SRCB_ADDR hspTestV4096BF32 ///< Hypsa platform SrcB addr
#else // HSP_TEST_V4096_F32_RANDOM
#define HYPSA_TEST_SRCB_ADDR hspTestV4096RF32 ///< Hypsa platform SrcB addr
#endif // HSP_TEST_V4096_F32_RANDOM
#endif // GCC_COMPILE
#endif // ARM_COMPILE

/// Matrix width
#define HSP_TEST_MATS_F32_W 8

/// Matrix heigt
#ifdef GEN_MAT_INV_REF
#define HSP_TEST_MATS_F32_H 511
#else // GEN_MAT_INV_REF
#define HSP_TEST_MATS_F32_H 512
#endif // GEN_MAT_INV_REF

/*------------------------------------------------------------------------------
 * Types
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 * Variables
 *----------------------------------------------------------------------------*/
/// Input vector to test
extern uint32_t chess_storage(hypDM:HYPSA_TEST_SRCA_ADDR) hspTestV4096AF32[HSP_TEST_V4096_F32_S];
/// Input vector to test
extern uint32_t chess_storage(hypDM:HYPSA_TEST_SRCB_ADDR) hspTestV4096BF32[HSP_TEST_V4096_F32_S];

/// Input MatrixA
extern p60_matrix_t hspTestM4096AF32;
extern p60_matrix_t hspTestM4096BF32;

/*------------------------------------------------------------------------------
 * Functions
 *----------------------------------------------------------------------------*/

#endif // __HSP_TEST_V4096_F32_H__
