/**
  ******************************************************************************************
  * \file hsp_test_vects_256_f32.h
  * \brief Common vector test with corner values for f32
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

#ifndef __HSP_TEST_VECTS_256_F32_H__
#define __HSP_TEST_VECTS_256_F32_H__

/*------------------------------------------------------------------------------
 * Includes
 *----------------------------------------------------------------------------*/
#include "hsp_test_common.h"

/*------------------------------------------------------------------------------
 * Defines
 *----------------------------------------------------------------------------*/
#ifndef ARM_COMPILE
#ifdef GCC_COMPILE
#define HYPSA_TEST_SRCA_ADDR hspTestVectsAF32 ///< Hypsa platform SrcB addr
#define HYPSA_TEST_SRCB_ADDR hspTestVectsBF32 ///< Hypsa platform SrcB addr
#endif // GCC_COMPILE
#endif // ARM_COMPILE

/// Vector buffer size
#define HSP_TEST_VECTS_F32_S 256

/// Matrix width
#define HSP_TEST_MATS_F32_W 8

/// Matrix heigt
#define HSP_TEST_MATS_F32_H 32

/*------------------------------------------------------------------------------
 * Types
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 * Variables
 *----------------------------------------------------------------------------*/
/// Input vector to test
extern uint32_t chess_storage(hypDM:HYPSA_TEST_SRCA_ADDR) hspTestVectsAF32[HSP_TEST_VECTS_F32_S];
/// Input vector to test
extern uint32_t chess_storage(hypDM:HYPSA_TEST_SRCB_ADDR) hspTestVectsBF32[HSP_TEST_VECTS_F32_S];
/// Input MatrixA
extern p60_matrix_t hspTestMatsAF32;
/// Input MatrixB
extern p60_matrix_t hspTestMatsBF32;

/*------------------------------------------------------------------------------
 * Functions
 *----------------------------------------------------------------------------*/

#endif // __HSP_TEST_VECTS_256_F32_H__
