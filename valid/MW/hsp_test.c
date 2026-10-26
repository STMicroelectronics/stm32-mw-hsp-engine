/**
  ******************************************************************************************
  * \file nreg_hyp_3x3x32x32_cnn_conv2d_circio.c
  * \brief V4096 for CNN_CONV2D kernel
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
  * <h2><center>&copy; COPYRIGHT 2024 STMicroelectronics - All Rights Reserved</center></h2>
  *
  ******************************************************************************************
  */

/*------------------------------------------------------------------------------
 * Includes
 *----------------------------------------------------------------------------*/
#include "hsp_test_common.h"
#ifdef HYP_UNITARY_TEST
#include "hyp_lib.h"
#else // HYP_UNITARY_TEST
#ifdef HYPSA_SIMU
#include "core/hsp.h"
#else
#include "hsp.h"
#endif /* HYPSA_SIMU */
#endif // HYP_UNITARY_TEST
#include "hsp_core.h"

// Include Vector test
#include "hsp_test_v4096_f32.h"
#include "hsp_test_v4096_f32.c"

/*------------------------------------------------------------------------------
 * Defines
 *----------------------------------------------------------------------------*/

/// Info message name for this test
#ifdef HYP_UNITARY_TEST
#define TEST_NAME "3x3x32x32 hyp cnn_conv2d_circio"
#else // HYP_UNITARY_TEST
#define TEST_NAME "3x3x32x32 HSP cnn_conv2d_circio"
#endif // HYP_UNITARY_TEST

#define PADX 1
#define PADY 1

#define STRIDEX 1
#define STRIDEY 1

#define OU_W 8
#define OU_H 8
#define OU_C 32

#define IN_W (OU_W * STRIDEX)
#define IN_H (OU_H * STRIDEY)
#define INP_W (IN_W + (2 * PADX))
#define INP_H (IN_H + (2 * PADY))
#define IN_C 32

#define K_W 3
#define K_H 3
#define K_C (IN_C*OU_C)

#define CNN_RES_S (OU_W * OU_H * OU_C)
#define CNN_INP_S (INP_W * INP_H * IN_C)

#define NBL_BOU_M2 (OU_H - 3) ///< 0 is for ping pong

// test_bin/test_armnn_conv2d -cnni 8 8 32 -cnno 8 8 32 -cnnk 3 3 1024 -cnnq 1 1 -cnns 1 1 -cnnc 75 -82 -cnnp 1 1

/*------------------------------------------------------------------------------
 * Types
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 * Variables
 *----------------------------------------------------------------------------*/

/// Input padding image
uint8_t inPad[CNN_INP_S];

/// Input padding image
uint32_t myBias[OU_C];

int32_t convOffset[2] = { 75, -82};
int32_t convRelu[2] = { 0xffffff80, 0x0000007f};

float32_t in_scale = 0.1;
float32_t out_scale = 0.001;
uint32_t p_wt_scale[OU_C] = {
  0x36eae18b, 0x36eb3771, 0x36eb8d57, 0x36ebe33d, 0x36ec3923, 0x36ec8f09, 0x36ece4ef, 0x36ed3ad5,
  0x36ed90bb, 0x36ede6a1, 0x36ee3c87, 0x36ee926d, 0x36eee853, 0x36ef3e39, 0x36ef941f, 0x36efea05,
  0x36f03feb, 0x36f095d1, 0x36f0ebb7, 0x36f1419d, 0x36f19783, 0x36f1ed69, 0x36f2434f, 0x36f29935,
  0x36f2ef1b, 0x36f34501, 0x36f39ae7, 0x36f3f0cd, 0x36f446b3, 0x36f49c99, 0x36f4f27f, 0x36f54865,
};

const int32_t qmul[OU_C] =
{
  0x5bc01a80, 0x5be1a800, 0x5c033600, 0x5c24c400, 0x5c465180, 0x5c67df80, 0x5c896d80, 0x5caafb00,
  0x5ccc8900, 0x5cee1700, 0x5d0fa480, 0x5d313280, 0x5d52c080, 0x5d744e80, 0x5d95dc00, 0x5db76a00,
  0x5dd8f800, 0x5dfa8580, 0x5e1c1380, 0x5e3da180, 0x5e5f2f00, 0x5e80bd00, 0x5ea24b00, 0x5ec3d880,
  0x5ee56680, 0x5f06f480, 0x5f288200, 0x5f4a1000, 0x5f6b9e00, 0x5f8d2c00, 0x5faeb980, 0x5fd04780,
};

const int32_t qshi[OU_C] =
{
  0xfffffff6, 0xfffffff6, 0xfffffff6, 0xfffffff6, 0xfffffff6, 0xfffffff6, 0xfffffff6, 0xfffffff6,
  0xfffffff6, 0xfffffff6, 0xfffffff6, 0xfffffff6, 0xfffffff6, 0xfffffff6, 0xfffffff6, 0xfffffff6,
  0xfffffff6, 0xfffffff6, 0xfffffff6, 0xfffffff6, 0xfffffff6, 0xfffffff6, 0xfffffff6, 0xfffffff6,
  0xfffffff6, 0xfffffff6, 0xfffffff6, 0xfffffff6, 0xfffffff6, 0xfffffff6, 0xfffffff6, 0xfffffff6,
};

const uint32_t chess_storage(hypDM:HYPSA_TEST_REF_ADDR) testRef[CNN_RES_S/4] =
{
  0x63f27f7f, 0x7f7f722e, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x4d7f7f7f, 0x527fd670, 0x808080c0,
  0x78057f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7ff97f, 0x80808080,
  0x7f977f57, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x777fcf33, 0x80808080,
  0x29807f38, 0x7f7f7f69, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x247f804c, 0x80808080,
  0x55807f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x5e7f7f7f, 0x607f807e, 0x80808080,
  0x52a27f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f8024, 0x80808080,
  0x7f117ff7, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7fdf61, 0x80808080,
  0x31c27fd4, 0x7f7f7f72, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x627f7f7f, 0xea7fa240, 0x80808080,
  0x382b7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x647f7f7f, 0x7f7f8078, 0x808080c0,
  0x7ffd7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f807f, 0x808080e1,
  0x52897f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f807f, 0x808080c6,
  0xf20c7f1e, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f807f, 0x808080be,
  0x607f7f70, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x217f967f, 0x80808080,
  0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x80a68080,
  0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x80808080,
  0x7f467f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f707f, 0x80808080,
  0x7f6c7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x617f347f, 0x80808080,
  0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f3b7f, 0x80808080,
  0x307f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f027f, 0x806c8080,
  0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f2a7f, 0x80808080,
  0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7fdd7f, 0x80808080,
  0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x80808080,
  0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x80808080,
  0x7f7f7f77, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f257f7f, 0x80808080,
  0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x80808080,
  0x567f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x80808080,
  0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x80808080,
  0x497f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f297f, 0x80808081,
  0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f6d7f, 0x808080c7,
  0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x808080b4,
  0x7f697f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x80808085,
  0x7f517f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x747f7f7f, 0x327f697f, 0x80808092,
  0x7f777f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f3d7f, 0x80808080,
  0x7f727f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x808080b4,
  0x7f707f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f5e7f, 0x80808080,
  0x7f477f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x80808080,
  0x7f347f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x80808080,
  0x7f757f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f547f, 0x80808080,
  0x7f727f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x80808080,
  0x7a377f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x147f7f7f, 0x567f227f, 0x808080bd,
  0x600b7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7fd072, 0x80808087,
  0x7f1f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f117f, 0x808080cb,
  0x7f0a7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f307f, 0x80808084,
  0x7f3e7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f0d7f, 0x80808080,
  0x7f117f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7fe07f, 0x808080c6,
  0x783d7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7fb97f, 0x80808080,
  0x7f4f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7ff07f, 0x8080809e,
  0x3d237f7e, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x307f7f7f, 0x217f8062, 0x808080ca,
  0x33087f78, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7fa151, 0x80808080,
  0x752b7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7fc87f, 0x808080a5,
  0x7f1a7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f807f, 0x80808080,
  0x38e57f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7fbc7f, 0x80808008,
  0x7f1d7f52, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f807f, 0x80808080,
  0x5e237f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f8c54, 0x80808080,
  0x14f67f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x767f807f, 0x808080b0,
  0x0d3e7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x6e7f7f7f, 0x507f9875, 0x8080809f,
  0xe0157f5f, 0x7f7f7f13, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0xfd7f800a, 0x80b98098,
  0xe2437f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7fa97f, 0x80aa8027,
  0x55177f7f, 0x7f7f7f7e, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7fc1fa, 0x809880bc,
  0x2b6f7f6c, 0x7f7f7f53, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x727f7f7f, 0x7f7fb23b, 0x80bf8027,
  0xec447f7f, 0x7f7f7f30, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x577f807f, 0x80ab80f7,
  0xeb627f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7fa119, 0x809880ee,
  0x176c7f7f, 0x7f7f7f00, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x7a7f7f7f, 0x7f7fcb34, 0x80ad800d,
  0xb9687f7f, 0x7f7f7f60, 0x7f7f7f7f, 0x7f7f7f7f, 0x7f7f7f7f, 0x667f7f7f, 0x7f7f8065, 0x80998015,
};

/*------------------------------------------------------------------------------
 * Functions
 *----------------------------------------------------------------------------*/

/**
 * Check F32 result
 * Return nb check failed
 */
static uint32_t run_perf(uint32_t mode)
{
  TEST_INFO_REPORT(TEST_NAME, "check F32\n");
  _errorReportCount = 0;

#define CMD_EVT 1
  // Run kernel
  test_hw_reset(&(h_hw_hsp_if[0].hhsp));
  hsp_core_status_t status = HSP_CORE_Init(&hmw);


  uint8_t *pDst = (uint8_t *) hspTestDst4096;

  printf("input image %dx%dx%d = %d (%d W)\n", INP_W, INP_H, IN_C, (INP_W * INP_H * IN_C),
         ((INP_W * INP_H * IN_C)/4));
  printf("kernel size %dx%dx%d = %d (%d W)\n", K_W, K_H, K_C, (K_W * K_H * K_C), ((K_W * K_H * K_C)/4));
  printf("output image %dx%dx%d = %d (%d W)\n", OU_W, OU_H, OU_C, (OU_W * OU_H * OU_C), ((OU_W * OU_H * OU_C)/4));
  reset_ebuff((uint32_t *) pDst, 4096);
  reset_bram(4096);

  if (mode) {
    // Padding is done by CNN API function
    TEST_INFO_REPORT(TEST_NAME, "Padding is done by CNN API function\n");
    // Send direct command
#ifdef __HSP_DMA__
    hsp_startcc();
    HAL_HSP_Direct_Cnn_Conv2D1StepPad(&hmw, IN_W, IN_H, IN_C, K_W, K_H, OU_W, OU_H, OU_C, STRIDEX, STRIDEY,
                                    (int8_t *) hspTestV4096AF32, (int8_t *) hspTestV4096BF32, (int8_t *) pDst,
                                    (uint32_t *) myBias,  in_scale, out_scale, (const float32_t*)p_wt_scale,
                                    *((uint32_t *) (convOffset)), *((uint32_t *) (convOffset + 1)),
                                    *((uint32_t *) (convRelu)), *((uint32_t *) (convRelu + 1)), PADX, PADY, NBL_BOU_M2);
    hsp_stopcc();
#endif // __HSP_DMA__
  } else {
    // Padding is done by application
    // Ref was generated without padding, then dor not use gen_padding in this test or update ref
    gen_padding_img((uint8_t *) hspTestV4096AF32, inPad, IN_W, IN_H, IN_C, PADX, PADY, (-*convOffset));

    // Send direct command
#ifdef __HSP_DMA__
    hsp_startcc();
    HAL_HSP_Direct_Cnn_Conv2D1Step(&hmw, INP_W, INP_H, IN_C, K_W, K_H, OU_W, OU_H, OU_C, STRIDEX, STRIDEY,
                                 (int8_t *) inPad, (int8_t *) hspTestV4096BF32, (int8_t *) pDst,
                                 (uint32_t *) myBias,  in_scale, out_scale, (const float32_t*)p_wt_scale,
                                 *((uint32_t *) (convOffset)), *((uint32_t *) (convOffset + 1)),
                                 *((uint32_t *) (convRelu)), *((uint32_t *) (convRelu + 1)), NBL_BOU_M2);
    hsp_stopcc();
#endif // __HSP_DMA__
  }

  print_conv2d_type();
  _errorReportCount = (status == HAL_OK) ? _errorReportCount : (_errorReportCount + 1);

  TEST_MEASURE_REPORT_D(TEST_NAME, CNN_RES_S, "dims %dx%dx%d %dx%d %dx%dx%d %d %d %d %d (%d)\n", IN_H, IN_W, IN_C,
                        K_H, K_W, OU_H, OU_W, OU_C, STRIDEY, STRIDEX, PADY, PADX, mode);

  // Compare res with ref
  uint32_t nbCheckFailed = compare_int8(TEST_NAME, pDst, (uint8_t *) testRef, CNN_RES_S, P60_CHECK_DO_CMP);

  HSP_CORE_DeInit(&hmw);
  return nbCheckFailed;
}

/**
 * Main test function
 */
int hsp_test_main(void)
{
  TEST_INFO_REPORT(TEST_NAME, "Starting test\n");
  uint32_t nbCheckFailed = 0;

  for (uint32_t tmpi = 0; tmpi < OU_C; tmpi++) {
    int8_t bval8 = ((int8_t) tmpi) - 16;
    myBias[tmpi] = (int32_t) bval8;
  }

#ifdef __HSP_DMA__
  nbCheckFailed += run_perf(0);
  nbCheckFailed += run_perf(1); // include padding
#endif // __HSP_DMA__

  TEST_END_REPORT(TEST_NAME, nbCheckFailed);
  return nbCheckFailed;
}
