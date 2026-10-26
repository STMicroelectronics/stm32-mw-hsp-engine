/**
  ******************************************************************************************
  * \file hsp_test_common.h
  * \brief Common header file with usefull macro for all P60 unitary tests
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

#ifndef __HSP_TEST_COMMON_H__
#define __HSP_TEST_COMMON_H__
/*------------------------------------------------------------------------------
 * Includes
 *----------------------------------------------------------------------------*/
#include <assert.h>
#include <stdio.h>
#ifndef ARM_COMPILE
#include "measure.h"
#include "hyp_types.h"
#ifndef HYPSA_SIMU
#define HYP_TOOLS
#endif // HYPSA_SIMU
#else // ARM_COMPILE
#include <stdint.h>
#include "hsp_test_mmap.h"
#include "hyp_types_gcc.h"
// #include "hsp_fw_ram_generic.h"
#include "hsp_fw_def.h"
#endif // ARM_COMPILE
#ifndef GCC_COMPILE
#include "hyp_mmap.h"
#include "hsp_test_mmap.h"
#endif // GCC_COMPILE

#ifdef STM32H7P5xx
#include "stm32_hal.h"
#include "stm32h7pxx_hal_rcc.h"
#endif

#ifdef STM32U575xx
#define HSP1_BASE_NS HSP_BASE_NS
#define HSP_ARM_MEMORY_BASE_ADDR 0x80000
#include "mystm32u5xx_hal_hsp.h"
#ifdef __HSP_DMA__
#define __HSP_U5DMA__
#endif // __HSP_DMA__
#endif // STM32U575xx

#ifndef HYP_TOOLS
#ifdef HYPSA_SIMU
#include "hal_hsp.h"
#include "hypsa.h"
#endif /* HYPSA_SIMU */

#include "hsp_hw_if.h"
#include "hsp_def.h"
#endif // HYP_TOOLS

#ifdef HYPSA_SIMU
#define HSP_MEMA_BASE_ADDR (0x08000 * 4) /**< BRAM A addr */
#define HSP_MEMB_BASE_ADDR (0x24000 * 4) /**< BRAM B addr */
#ifdef __HSP_DMA__
#define __HSP_U5DMA__
#endif // __HSP_DMA__
#endif

/*------------------------------------------------------------------------------
 * Defines
 *----------------------------------------------------------------------------*/
// Address  of coverage memory: HSP base addr  + size MEMAB + offset memory ????
//#define TEST_ADDR_MEM_COVERAGE  (0x410EA000)
#define TEST_ADDR_MEM_COVERAGE  (HYPSA_SHARED_MEM_BASE_ADDR + HSP_MEM_BRAMAB_SIZE)

#define hsp_core_handle_t hsp_engine_context_t

/* ------------------------ */
/* PL programmation  */
/* ------------------------ */

// #define HSP_PROCLIST_StartRecord(hmw, pl_id)\
  // HSP_SEQ_StartRecordPL(hmw, pl_id)

// #define HSP_PROCLIST_StopRecord(hmw)\
  // HSP_SEQ_StopRecordPL(hmw)

// #define HSP_PROCLIST_Run(hmw, pl, mode)\
  // HSP_SEQ_RunTask(hmw, pl, mode)

// Filter state allocation define: add parameter to slect allcoation area: persistent or default
/* ------------------------ */
/* Allocation Filter State  */
/* ------------------------ */
#define HSP_BRAM_Malloc_test(hmw, size_in_word)\
 HSP_BRAM_Malloc(hmw, size_in_word, HSP_BRAM_ALLOCATION_DEFAULT)

#define  HSP_BRAM_MallocStateBuffer_Fir_test(hmw, nbTaps, nbSamples)\
  HSP_BRAM_MallocStateBuffer_Fir(hmw, nbTaps, nbSamples, HSP_BRAM_ALLOCATION_DEFAULT)

#define  HSP_BRAM_MallocStateBuffer_FirDecimate_test(hmw, nbTaps, nbSamples, decimFactor)\
  HSP_BRAM_MallocStateBuffer_FirDecimate(hmw, nbTaps, nbSamples, decimFactor, HSP_BRAM_ALLOCATION_DEFAULT)

#define  HSP_BRAM_MallocStateBuffer_BiquadCascadeDf1_test(hmw, nbStages)\
  HSP_BRAM_MallocStateBuffer_BiquadCascadeDf1(hmw, nbStages, HSP_BRAM_ALLOCATION_DEFAULT)

#define  HSP_BRAM_MallocStateBuffer_BiquadCascadeDf2t_test(hmw, nbStages)\
  HSP_BRAM_MallocStateBuffer_BiquadCascadeDf2t(hmw, nbStages, HSP_BRAM_ALLOCATION_DEFAULT)

#define  HSP_BRAM_MallocStateBuffer_Lms_test(hmw, nbTaps)\
  HSP_BRAM_MallocStateBuffer_Lms(hmw, nbTaps, HSP_BRAM_ALLOCATION_DEFAULT)

#define  HSP_BRAM_MallocStateBuffer_IirLattice_test(hmw, nbStages)\
  HSP_BRAM_MallocStateBuffer_IirLattice(hmw, nbStages, HSP_BRAM_ALLOCATION_DEFAULT)

#define  HSP_BRAM_MallocStateBuffer_IirDf1_test(hmw, nbStages)\
  HSP_BRAM_MallocStateBuffer_IirDf1(hmw, nbStages, HSP_BRAM_ALLOCATION_DEFAULT)

#define  HSP_BRAM_MallocStateBuffer_Iir4p4z_test(hmw)\
  HSP_BRAM_MallocStateBuffer_Iir4p4z(hmw, HSP_BRAM_ALLOCATION_DEFAULT)

#define  HSP_BRAM_MallocStateBuffer_Iir3p3z_test(hmw)\
  HSP_BRAM_MallocStateBuffer_Iir3p3z(hmw, HSP_BRAM_ALLOCATION_DEFAULT)

#define  HSP_BRAM_MallocStateBuffer_Iir2p2z_test(hmw)\
  HSP_BRAM_MallocStateBuffer_Iir2p2z(hmw, HSP_BRAM_ALLOCATION_DEFAULT)


// CNN define for pad4 merge function, in order to not modify tests
#ifndef HYP_TOOLS
#ifdef __HSP_DMA__
#define USE_CNN_DMA_IN_TEST
#ifdef USE_CNN_DMA_IN_TEST
#include "hsp_cnn_dma.h"
#endif // USE_CNN_DMA_IN_TEST
#endif // __HSP_DMA__
#endif // HYP_TOOLS

#ifdef USE_CNN_DMA_IN_TEST
#define HSP_ACC_CnnConv2d0S_s8 HSP_ACC_CnnConv2d0D_s8
#define HSP_ACC_CnnConv2d1S_s8 HSP_ACC_CnnConv2d1D_s8
#define HSP_ACC_CnnConv2d2S_s8 HSP_ACC_CnnConv2d2D_s8
#define HSP_ACC_CnnConv2d3S_s8 HSP_ACC_CnnConv2d3D_s8
#define HSP_ACC_CnnFullyConnected0S_s8 HSP_ACC_CnnFullyConnected0D_s8
#define HSP_ACC_CnnFullyConnected1S_s8 HSP_ACC_CnnFullyConnected1D_s8
#define HSP_ACC_CnnPool0S_s8 HSP_ACC_CnnPool0D_s8
#define HSP_ACC_CnnPool1S_s8 HSP_ACC_CnnPool1D_s8
#define HSP_ACC_CnnConvPointwise0S_s8 HSP_ACC_CnnConvPointwise0D_s8
#define HSP_ACC_CnnConvPointwise1S_s8 HSP_ACC_CnnConvPointwise1D_s8
#define HSP_ACC_CnnConvPointwise2S_s8 HSP_ACC_CnnConvPointwise2D_s8
#define HSP_ACC_CnnConvPointwise3S_s8 HSP_ACC_CnnConvPointwise3D_s8
#define HSP_ACC_CnnConvDepthwise1S_s8 HSP_ACC_CnnConvDepthwise1D_s8
#define HSP_ACC_CnnConvDepthwise2S_s8 HSP_ACC_CnnConvDepthwise2D_s8
#define HSP_ACC_CnnConvDepthwise3S_s8 HSP_ACC_CnnConvDepthwise3D_s8
#else // USE_CNN_DMA_IN_TEST
#ifdef __HSP_DMA__
#define HSP_ACC_CnnConv2d0S_s8 HSP_ACC_CnnConv2d0_s8
#else // __HSP_DMA__
#define HSP_ACC_CnnConv2d0S_s8 HSP_ACC_CnnConv2d1_s8 // Force to 1 step for test compilation
#endif // __HSP_DMA__
#define HSP_ACC_CnnConv2d1S_s8 HSP_ACC_CnnConv2d1_s8
#define HSP_ACC_CnnConv2d2S_s8 HSP_ACC_CnnConv2d2_s8
#define HSP_ACC_CnnConv2d3S_s8 HSP_ACC_CnnConv2d3_s8
#define HSP_ACC_CnnFullyConnected0S_s8 HSP_ACC_CnnFullyConnected0_s8
#define HSP_ACC_CnnFullyConnected1S_s8 HSP_ACC_CnnFullyConnected1_s8
#define HSP_ACC_CnnPool0S_s8 HSP_ACC_CnnPool0_s8
#define HSP_ACC_CnnPool1S_s8 HSP_ACC_CnnPool1_s8
#ifdef __HSP_U5DMA__
#define HSP_ACC_CnnConvPointwise0S_s8 HSP_ACC_CnnConvPointwise0_s8 // 0 step not exist without DMA
#else // __HSP_U5DMA__
#define HSP_ACC_CnnConvPointwise0S_s8 HSP_ACC_CnnConvPointwise1_s8 // 0 step not exist without DMA
#endif // __HSP_U5DMA__
#define HSP_ACC_CnnConvPointwise1S_s8 HSP_ACC_CnnConvPointwise1_s8
#define HSP_ACC_CnnConvPointwise2S_s8 HSP_ACC_CnnConvPointwise2_s8
#define HSP_ACC_CnnConvPointwise3S_s8 HSP_ACC_CnnConvPointwise3_s8
#define HSP_ACC_CnnConvDepthwise1S_s8 HSP_ACC_CnnConvDepthwise1_s8
#define HSP_ACC_CnnConvDepthwise2S_s8 HSP_ACC_CnnConvDepthwise2_s8
#define HSP_ACC_CnnConvDepthwise3S_s8 HSP_ACC_CnnConvDepthwise3_s8
#endif // USE_CNN_DMA_IN_TEST

/* ------------------------ */
/* DEPTHWISE                */
/* ------------------------ */
#ifdef USE_CNN_DMA_IN_TEST
#define HAL_HSP_Direct_Cnn_Depthwise1Step(hmw, in_w,  in_h, in_c,\
                                 k_w,  k_h, ou_w,  ou_h, ou_c, stridex, stridey,\
                                 pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale,\
                                 offIn, offOu, satMin, satMax) \
  HSP_ACC_CnnConvDepthwise1D_s8(hmw, in_w,  in_h, in_c,\
                                 k_w,  k_h, ou_w,  ou_h, ou_c, stridex, stridey,\
                                 pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale,\
                                 offIn, offOu, satMin, satMax, 0, 0, 0, 0)
								 
#define HAL_HSP_Direct_Cnn_Depthwise1StepPad4(hmw, in_w,  in_h, in_c,\
                                 k_w,  k_h, ou_w,  ou_h, ou_c, stridex, stridey,\
                                 pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale,\
                                 offIn, offOu, satMin, satMax, padx0, padx1, pady0, pady1) \
  HSP_ACC_CnnConvDepthwise1D_s8(hmw, in_w,  in_h, in_c,\
                                 k_w,  k_h, ou_w,  ou_h, ou_c, stridex, stridey,\
                                 pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale,\
                                 offIn, offOu, satMin, satMax, padx0, padx1, pady0, pady1)
								 
#define HAL_HSP_Direct_Cnn_Depthwise2StepPad4(hmw, in_w,  in_h, in_c,\
                                 k_w,  k_h, ou_w,  ou_h, ou_c, stridex, stridey,\
                                 pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale,\
                                 offIn, offOu, satMin, satMax, padx0, padx1, pady0, pady1, nboutline) \
  HSP_ACC_CnnConvDepthwise2D_s8(hmw, in_w,  in_h, in_c,\
                                 k_w,  k_h, ou_w,  ou_h, ou_c, stridex, stridey,\
                                 pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale,\
                                 offIn, offOu, satMin, satMax, padx0, padx1, pady0, pady1, nboutline)

#define HAL_HSP_Direct_Cnn_Depthwise3StepPad4(hmw, in_w,  in_h, in_c,\
                                 k_w,  k_h, ou_w,  ou_h, ou_c, stridex, stridey,\
                                 pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale,\
                                 offIn, offOu, satMin, satMax, padx0, padx1, pady0, pady1, nboutline) \
  HSP_ACC_CnnConvDepthwise3D_s8(hmw, in_w,  in_h, in_c,\
                                 k_w,  k_h, ou_w,  ou_h, ou_c, stridex, stridey,\
                                 pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale,\
                                 offIn, offOu, satMin, satMax, padx0, padx1, pady0, pady1, nboutline)
						
#else /* USE_CNN_DMA_IN_TEST */
#define HAL_HSP_Direct_Cnn_Depthwise1Step(hmw, in_w,  in_h, in_c,\
                                 k_w,  k_h, ou_w,  ou_h, ou_c, stridex, stridey,\
                                 pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale,\
                                 offIn, offOu, satMin, satMax) \
  HSP_ACC_CnnConvDepthwise1_s8(hmw, in_w,  in_h, in_c,\
                                 k_w,  k_h, ou_w,  ou_h, ou_c, stridex, stridey,\
                                 pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale,\
                                 offIn, offOu, satMin, satMax, 0, 0, 0, 0)

#define HAL_HSP_Direct_Cnn_Depthwise1StepPad4(hmw, in_w,  in_h, in_c,\
                                 k_w,  k_h, ou_w,  ou_h, ou_c, stridex, stridey,\
                                 pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale,\
                                 offIn, offOu, satMin, satMax, padx0, padx1, pady0, pady1) \
  HSP_ACC_CnnConvDepthwise1_s8(hmw, in_w,  in_h, in_c,\
                                 k_w,  k_h, ou_w,  ou_h, ou_c, stridex, stridey,\
                                 pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale,\
                                 offIn, offOu, satMin, satMax, padx0, padx1, pady0, pady1)

#define HAL_HSP_Direct_Cnn_Depthwise2StepPad4(hmw, in_w,  in_h, in_c,\
                                 k_w,  k_h, ou_w,  ou_h, ou_c, stridex, stridey,\
                                 pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale,\
                                 offIn, offOu, satMin, satMax, padx0, padx1, pady0, pady1, nboutline) \
  HSP_ACC_CnnConvDepthwise2_s8(hmw, in_w,  in_h, in_c,\
                                 k_w,  k_h, ou_w,  ou_h, ou_c, stridex, stridey,\
                                 pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale,\
                                 offIn, offOu, satMin, satMax, padx0, padx1, pady0, pady1, nboutline)								
#define HAL_HSP_Direct_Cnn_Depthwise3StepPad4(hmw, in_w,  in_h, in_c,\
                                 k_w,  k_h, ou_w,  ou_h, ou_c, stridex, stridey,\
                                 pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale,\
                                 offIn, offOu, satMin, satMax, padx0, padx1, pady0, pady1, nboutline) \
  HSP_ACC_CnnConvDepthwise3_s8(hmw, in_w,  in_h, in_c,\
                                 k_w,  k_h, ou_w,  ou_h, ou_c, stridex, stridey,\
                                 pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale,\
                                 offIn, offOu, satMin, satMax, padx0, padx1, pady0, pady1, nboutline)
#endif /* USE_CNN_DMA_IN_TEST */

/* ------------------------------------------------------------------------- */
/* MAPPING OF ALL DIRECT COMMAND */
/* ------------------------------------------------------------------------- */
#define HSP_DIRECT_RFFT_f32( hmw,  buff,  log2Nbp,   ifftFlag,  bitrev,  fftVariant)\
HSP_ACC_Rfft_f32( hmw,  buff,  log2Nbp,   ifftFlag,  bitrev,  fftVariant)

#define HSP_DIRECT_FFT_f32( hmw,  buff,  log2Nbp,  ifftFlag,  bitrev)\
HSP_ACC_Fft_f32( hmw,  buff,  log2Nbp,  ifftFlag,  bitrev)

#define HSP_DIRECT_DCT_f32( hmw,  buff,  log2Nbp)\
HSP_ACC_Dct_f32( hmw,  buff,  log2Nbp)

#define HSP_DIRECT_IDCT_f32( hmw,  buff,  log2Nbp)\
HSP_ACC_IDct_f32( hmw,  buff,  log2Nbp)

#define HSP_DIRECT_VECTOR_Abs_f32( hmw,  inBuff,  outBuff,  nbSamples)\
HSP_ACC_VectAbs_f32( hmw,  inBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_Add_f32( hmw,  inABuff,  inBBuff,  outBuff,  nbSamples)\
HSP_ACC_VectAdd_f32( hmw,  inABuff,  inBBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_Avg_f32( hmw,  inBuff,  outBuff,  nbSamples)\
HSP_ACC_VectAvg_f32( hmw,  inBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_Copy( hmw,  inBuff,  outBuff,  nbSamples)\
HSP_ACC_VectCopy_f32( hmw,  inBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_Cos_f32( hmw,  inBuff,  outBuff,  nbSamples)\
HSP_ACC_VectCos_f32( hmw,  inBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_Div_f32( hmw,  inABuff,  inBBuff,  outBuff,  nbSamples)\
HSP_ACC_VectDiv_f32( hmw,  inABuff,  inBBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_DotProd_f32( hmw,  inABuff,  inBBuff,  outBuff,  nbSamples)\
HSP_ACC_VectDotProd_f32( hmw,  inABuff,  inBBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_AbsMax_f32( hmw,  inBuff,  outVal,  outIdx,  nbSamples)\
HSP_ACC_VectAbsMax_f32( hmw,  inBuff,  outVal,  outIdx,  nbSamples)

#define HSP_DIRECT_VECTOR_Max_f32( hmw,  inBuff,  outVal,  outIdx,  nbSamples)\
HSP_ACC_VectMax_f32( hmw,  inBuff,  outVal,  outIdx,  nbSamples)

#define HSP_DIRECT_VECTOR_Min_f32( hmw,  inBuff,  outVal,  outIdx,  nbSamples)\
HSP_ACC_VectMin_f32( hmw,  inBuff,  outVal,  outIdx,  nbSamples)

#define HSP_DIRECT_VECTOR_Mul_f32( hmw,  inABuff,  inBBuff,  outBuff,  nbSamples)\
HSP_ACC_VectMul_f32( hmw,  inABuff,  inBBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_Offset_f32( hmw,  inABuff,  inBBuff,  outBuff,  nbSamples)\
HSP_ACC_VectOffset_f32( hmw,  inABuff,  inBBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_RMS_f32( hmw,  inBuff,  outBuff,  nbSamples)\
HSP_ACC_VectRms_f32( hmw,  inBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_Scale_f32( hmw,  inABuff,  inBBuff,  outBuff,  nbSamples)\
HSP_ACC_VectScale_f32( hmw,  inABuff,  inBBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_Set_f32( hmw,  inBuff,  outBuff,  nbSamples)\
HSP_ACC_VectSet_f32( hmw,  inBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_Sqrt_f32( hmw,  inBuff,  outBuff,  nbSamples)\
HSP_ACC_VectSqrt_f32( hmw,  inBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_Sin_f32( hmw,  inBuff,  outBuff,  nbSamples)\
HSP_ACC_VectSin_f32( hmw,  inBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_Sub_f32( hmw,  inABuff,  inBBuff,  outBuff,  nbSamples)\
HSP_ACC_VectSub_f32( hmw,  inABuff,  inBBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_SinCos_f32( hmw,  inBuff,  outBuff,  nbSamples)\
HSP_ACC_VectSinCos_f32( hmw,  inBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_F2I( hmw,  inBuff,  outBuff,   nbSamples)\
HSP_ACC_VectF2I( hmw,  inBuff,  outBuff,   nbSamples)

#define HSP_DIRECT_VECTOR_I2F( hmw,  inBuff,  outBuff,  nbSamples)\
HSP_ACC_VectI2F( hmw,  inBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_F2U( hmw,  inBuff,  outBuff,  nbSamples)\
HSP_ACC_VectF2U( hmw,  inBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_U2F( hmw,  inBuff,  outBuff,  nbSamples)\
HSP_ACC_VectU2F( hmw,  inBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_24S2F( hmw,  inBuff,  outBuff,  nbSamples)\
HSP_ACC_Vect24S2F( hmw,  inBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_Decim_f32( hmw,  inBuff,  decim,  outBuff,  sizeOu)\
HSP_ACC_VectDecim_f32( hmw,  inBuff,  decim,  outBuff,  sizeOu)

#define HSP_DIRECT_VECTOR_ZIns_f32( hmw,  inBuff,  interp,  outBuff,  sizeIn)\
HSP_ACC_VectZIns_f32( hmw,  inBuff,  interp,  outBuff,  sizeIn)

#define HSP_DIRECT_VECTOR_Atan2_f32( hmw,  inABuff,  inBBuff,  outBuff,  nbSamples)\
HSP_ACC_VectAtan2_f32( hmw,  inABuff,  inBBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_Ln_f32( hmw,  inBuff,  outBuff,  nbSamples)\
HSP_ACC_VectLn_f32( hmw,  inBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_Log10_f32( hmw,  inBuff,  outBuff,  nbSamples)\
HSP_ACC_VectLog10_f32( hmw,  inBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_Exp_f32( hmw,  inBuff,  outBuff,  nbSamples)\
HSP_ACC_VectExp_f32( hmw,  inBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_Exp10_f32( hmw,  inBuff,  outBuff,  nbSamples)\
HSP_ACC_VectExp10_f32( hmw,  inBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_MulCos_f32( hmw,  inBuff,  startBuff,  outBuff,  nbSamples,  step)\
HSP_ACC_VectMulCos_f32( hmw,  inBuff,  startBuff,  outBuff,  nbSamples,  step)

#define HSP_DIRECT_VECTOR_MulSin_f32( hmw,  inBuff,  startBuff,  outBuff,  nbSamples,  step)\
HSP_ACC_VectMulSin_f32( hmw,  inBuff,  startBuff,  outBuff,  nbSamples,  step)

#define HSP_DIRECT_VECTOR_IOffset_f32( hmw,  inBuff,  offset,  outBuff,  nbSamples)\
HSP_ACC_VectIOffset_f32( hmw,  inBuff,  offset,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_IScale_f32( hmw,  inBuff,  scale,  outBuff,  nbSamples)\
HSP_ACC_VectIScale_f32( hmw,  inBuff,  scale,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_Q312F( hmw,  inBuff,  outBuff,  nbSamples)\
HSP_ACC_VectQ312F( hmw,  inBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_F2Q31( hmw,  inBuff,  outBuff,  nbSamples)\
HSP_ACC_VectF2Q31( hmw,  inBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_Q152F( hmw,  inBuff,  outBuff,  nbSamples)\
HSP_ACC_VectQ152F( hmw,  inBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_F2Q15( hmw,  inBuff,  outBuff,  nbSamples)\
HSP_ACC_VectF2Q15( hmw,  inBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_VECTOR_Saturation_f32( hmw,  inBuff,  inSat,  outBuff,  nbSamples,  isSat)\
HSP_ACC_VectSaturation_f32( hmw,  inBuff,  inSat,  outBuff,  nbSamples,  isSat)

#define HSP_DIRECT_VECTOR_MemA2B( hmw,  inBuff,  outBuff,  nbSamples)\
HSP_ACC_VectMemA2B( hmw,  inBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_CMPLX_Conj_f32( hmw,  inBuff,  outBuff,  nbSamples)\
HSP_ACC_CmplxConj_f32( hmw,  inBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_CMPLX_DotProd_f32( hmw,  inABuff,  inBBuff,  outBuff,  nbSamples)\
HSP_ACC_CmplxDotProd_f32( hmw,  inABuff,  inBBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_CMPLX_Mag_f32( hmw,  inBuff,  outBuff,  nbSamples)\
HSP_ACC_CmplxMag_f32( hmw,  inBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_CMPLX_MagSquared_f32( hmw,  inBuff,  outBuff,  nbSamples)\
HSP_ACC_CmplxMagSquared_f32( hmw,  inBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_CMPLX_Mul_f32( hmw,  inABuff,  inBBuff,  outBuff,  nbSamples)\
HSP_ACC_CmplxMul_f32( hmw,  inABuff,  inBBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_CMPLX_RMul_f32( hmw,  inABuff,  inBBuff,  outBuff,  nbSamples)\
HSP_ACC_CmplxRMul_f32( hmw,  inABuff,  inBBuff,  outBuff,  nbSamples)

#define HSP_DIRECT_CMPLX_MulExp_f32( hmw,  inBuff,  startBuff,  outBuff,  nbSamples,  step)\
HSP_ACC_CmplxMulExp_f32( hmw,  inBuff,  startBuff,  outBuff,  nbSamples,  step)

#define HSP_DIRECT_MATRIX_Abs_f32( hmw,  inBuff,  outBuff,  nCols,  nRows)\
HSP_ACC_MatAbs_f32( hmw,  inBuff,  outBuff,  nCols,  nRows)

#define HSP_DIRECT_MATRIX_Add_f32( hmw,  inABuff,  inBBuff,  outBuff,  nCols,  nRows)\
HSP_ACC_MatAdd_f32( hmw,  inABuff,  inBBuff,  outBuff,  nCols,  nRows)

#define HSP_DIRECT_MATRIX_Offset_f32( hmw,  inABuff,  inBBuff,  outBuff,  nCols,  nRows)\
HSP_ACC_MatOffset_f32( hmw,  inABuff,  inBBuff,  outBuff,  nCols,  nRows)

#define HSP_DIRECT_MATRIX_Scale_f32( hmw,  inABuff,  inBBuff,  outBuff,  nCols,  nRows)\
HSP_ACC_MatScale_f32( hmw,  inABuff,  inBBuff,  outBuff,  nCols,  nRows)

#define HSP_DIRECT_MATRIX_Sub_f32( hmw,  inABuff,  inBBuff,  outBuff,  nCols,  nRows)\
HSP_ACC_MatSub_f32( hmw,  inABuff,  inBBuff,  outBuff,  nCols,  nRows)

#define HSP_DIRECT_MATRIX_Inv_f32( hmw,  inBuff,  outBuff,  nCols,  nRows)\
HSP_ACC_MatInv_f32( hmw,  inBuff,  outBuff,  nCols,  nRows)

#define HSP_DIRECT_MATRIX_Mult_f32( hmw,  inABuff,  inBBuff,  outBuff,  nRowsA,  nColsA,  nRowsB,  nColsB)\
HSP_ACC_MatMult_f32( hmw,  inABuff,  inBBuff,  outBuff,  nRowsA,  nColsA,  nRowsB,  nColsB)

#define HSP_DIRECT_MATRIX_Trans_f32( hmw,  inBuff,  outBuff,  nCols,  nRows)\
HSP_ACC_MatTrans_f32( hmw,  inBuff,  outBuff,  nCols,  nRows)

#define HSP_DIRECT_FILTER_Fir_f32( hmw,  inBuff,  coefBuff,  stateId,  outBuff,  nbSamples)\
HSP_ACC_Fir_f32( hmw,  inBuff,  coefBuff,  stateId,  outBuff,  nbSamples)

#define HSP_DIRECT_FILTER_FirDecimate_f32( hmw,  inBuff,  coefBuff,  stateId,  outBuff,  nbSamples,  decimFactor)\
HSP_ACC_FirDecimate_f32( hmw,  inBuff,  coefBuff,  stateId,  outBuff,  nbSamples,  decimFactor)

#define HSP_DIRECT_FILTER_BiquadCascadeDf1_f32( hmw,  inBuff,  coefBuff,  stateId,  outBuff,  nbSamples)\
HSP_ACC_BiquadCascadeDf1_f32( hmw,  inBuff,  coefBuff,  stateId,  outBuff,  nbSamples)

#define HSP_DIRECT_FILTER_BiquadCascadeDf2T_f32( hmw,  inBuff, coefBuff,  stateId,  outBuff,  nbSamples)\
HSP_ACC_BiquadCascadeDf2T_f32( hmw,  inBuff, coefBuff,  stateId,  outBuff,  nbSamples)

#define HSP_DIRECT_FILTER_Conv_f32( hmw,  inABuff,  inBBuff,   outBuff,  sizeA,  sizeB)\
HSP_ACC_Conv_f32( hmw,  inABuff,  inBBuff,   outBuff,  sizeA,  sizeB)

#define HSP_DIRECT_FILTER_Correlate_f32( hmw,  inABuff,   inBBuff,  outBuff,  sizeA,  sizeB)\
HSP_ACC_Correlate_f32( hmw,  inABuff,   inBBuff,  outBuff,  sizeA,  sizeB)

#define HSP_DIRECT_FILTER_FltBank_f32( hmw,  spectrCol,  startIdx,  idxSize,  coef,  fltbankCol,  nFltbanks)\
HSP_ACC_FltBank_f32( hmw,  spectrCol,  startIdx,  idxSize,  coef,  fltbankCol,  nFltbanks)

#define HSP_DIRECT_FILTER_FltBankExtC_f32( hmw,  spectrCol,  startIdx,  idxSize,  coef,  fltbankCol,  nFltbanks,  dmaAdd,  dmaSize)\
HSP_ACC_FltBankExtC_f32( hmw,  spectrCol,  startIdx,  idxSize,  coef,  fltbankCol,  nFltbanks,  dmaAdd,  dmaSize)

#define HSP_DIRECT_FILTER_Lms_f32( hmw,  inBuff,  coefBuff,  stateId,  outBuff,  refBuff,  errBuff,  nbSamples,  mu)\
HSP_ACC_Lms_f32( hmw,  inBuff,  coefBuff,  stateId,  outBuff,  refBuff,  errBuff,  nbSamples,  mu)

#define HSP_DIRECT_FILTER_IirLattice_f32( hmw,  inBuff,  coeffsk,  coeffsv,  stateId,  outBuff,  nbSamples)\
HSP_ACC_IirLattice_f32( hmw,  inBuff,  coeffsk,  coeffsv,  stateId,  outBuff,  nbSamples)

#define HSP_DIRECT_FILTER_IirDf1_f32( hmw,  inBuff,  coefBuff,  stateId,  outBuff,  nbSamples)\
HSP_ACC_IirDf1_f32( hmw,  inBuff,  coefBuff,  stateId,  outBuff,  nbSamples)

#define HSP_DIRECT_FILTER_WinSym_f32( hmw,  inBuff,  inWin,  outBuff,  sizeWin,  sizePad0)\
HSP_ACC_WinSym_f32( hmw,  inBuff,  inWin,  outBuff,  sizeWin,  sizePad0)

#define HSP_DIRECT_FILTER_FirResetStateBuffer( hmw,  stateId)\
HSP_ACC_FirResetStateBuffer( hmw,  stateId)

#define HSP_DIRECT_FILTER_FirDecimateResetStateBuffer( hmw,  stateId)\
HSP_ACC_FirDecimateResetStateBuffer( hmw,  stateId)

#define HSP_DIRECT_FILTER_BiquadCascadeDf1ResetStateBuffer( hmw,  stateId)\
HSP_ACC_BiquadCascadeDf1ResetStateBuffer( hmw,  stateId)

#define HSP_DIRECT_FILTER_BiquadCascadeDf2TResetStateBuffer( hmw,  stateId)\
HSP_ACC_BiquadCascadeDf2TResetStateBuffer( hmw,  stateId)

#define HSP_DIRECT_FILTER_LmsResetStateBuffer( hmw,  stateId)\
HSP_ACC_LmsResetStateBuffer( hmw,  stateId)

#define HSP_DIRECT_FILTER_IirLatticeResetStateBuffer( hmw,  stateId)\
HSP_ACC_IirLatticeResetStateBuffer( hmw,  stateId)

#define HSP_DIRECT_FILTER_IirDf1ResetStateBuffer( hmw,  stateId)\
HSP_ACC_IirDf1ResetStateBuffer( hmw,  stateId)

#define HSP_DIRECT_FILTER_Iir3P3ZResetStateBuffer( hmw,  stateId)\
HSP_ACC_Iir3P3ZResetStateBuffer( hmw,  stateId)

#define HSP_DIRECT_FILTER_Iir2P2ZResetStateBuffer( hmw,  stateId)\
HSP_ACC_Iir2P2ZResetStateBuffer( hmw,  stateId)

#define HSP_DIRECT_FILTER_FirSetStateBuffer( hmw,  stateId,   inBuffer)\
HSP_ACC_FirSetStateBuffer( hmw,  stateId,   inBuffer)

#define HSP_DIRECT_FILTER_FirDecimateSetStateBuffer( hmw,  stateId,  inBuffer)\
HSP_ACC_FirDecimateSetStateBuffer( hmw,  stateId,  inBuffer)

#define HSP_DIRECT_FILTER_BiquadCascadeDf1SetStateBuffer( hmw,  stateId,  inBuffer)\
HSP_ACC_BiquadCascadeDf1SetStateBuffer( hmw,  stateId,  inBuffer)

#define HSP_DIRECT_FILTER_BiquadCascadeDf2TSetStateBuffer( hmw,  stateId,  inBuffer)\
HSP_ACC_BiquadCascadeDf2TSetStateBuffer( hmw,  stateId,  inBuffer)

#define HSP_DIRECT_FILTER_LmsSetStateBuffer( hmw,  stateId,  inBuffer)\
HSP_ACC_LmsSetStateBuffer( hmw,  stateId,  inBuffer)

#define HSP_DIRECT_FILTER_IirLatticeSetStateBuffer( hmw,  stateId,  inBuffer)\
HSP_ACC_IirLatticeSetStateBuffer( hmw,  stateId,  inBuffer)

#define HSP_DIRECT_FILTER_IirDf1SetStateBuffer( hmw,  stateId,  inBuffer)\
HSP_ACC_IirDf1SetStateBuffer( hmw,  stateId,  inBuffer)

#define HSP_DIRECT_FILTER_Iir3P3ZSetStateBuffer( hmw,  stateId,  inBuffer)\
HSP_ACC_Iir3P3ZSetStateBuffer( hmw,  stateId,  inBuffer)

#define HSP_DIRECT_FILTER_Iir2P2ZSetStateBuffer( hmw,  stateId,  inBuffer)\
HSP_ACC_Iir2P2ZSetStateBuffer( hmw,  stateId,  inBuffer)

#define HSP_DIRECT_FILTER_FirGetStateBuffer( hmw,  stateId,  outBuffer)\
HSP_ACC_FirGetStateBuffer( hmw,  stateId,  outBuffer)

#define HSP_DIRECT_FILTER_FirDecimateGetStateBuffer( hmw,  stateId,  outBuffer)\
HSP_ACC_FirDecimateGetStateBuffer( hmw,  stateId,  outBuffer)

#define HSP_DIRECT_FILTER_BiquadCascadeDf1GetStateBuffer( hmw,  stateId,  outBuffer)\
HSP_ACC_BiquadCascadeDf1GetStateBuffer( hmw,  stateId,  outBuffer)

#define HSP_DIRECT_FILTER_BiquadCascadeDf2TGetStateBuffer( hmw,  stateId,  outBuffer)\
HSP_ACC_BiquadCascadeDf2TGetStateBuffer( hmw,  stateId,  outBuffer)

#define HSP_DIRECT_FILTER_LmsGetStateBuffer( hmw,  stateId,  outBuffer)\
HSP_ACC_LmsGetStateBuffer( hmw,  stateId,  outBuffer)

#define HSP_DIRECT_FILTER_IirLatticeGetStateBuffer( hmw,  stateId,  outBuffer)\
HSP_ACC_IirLatticeGetStateBuffer( hmw,  stateId,  outBuffer)

#define HSP_DIRECT_FILTER_IirDf1GetStateBuffer( hmw,  stateId,  outBuffer)\
HSP_ACC_IirDf1GetStateBuffer( hmw,  stateId,  outBuffer)

#define HSP_DIRECT_FILTER_Iir3P3ZGetStateBuffer( hmw,  stateId,  outBuffer)\
HSP_ACC_Iir3P3ZGetStateBuffer( hmw,  stateId,  outBuffer)

#define HSP_DIRECT_FILTER_Iir2P2ZGetStateBuffer( hmw,  stateId,  outBuffer)\
HSP_ACC_Iir2P2ZGetStateBuffer( hmw,  stateId,  outBuffer)

#define HSP_DIRECT_CRC32( hmw,  pState,  pCRC,  blockSize,  posFEOR,  posFEOB,  memType)\
HSP_ACC_Crc32( hmw,  pState,  pCRC,  blockSize,  posFEOR,  posFEOB,  memType)

#define HSP_DIRECT_BACKGROUND_Ext2Int( hmw,  inAddr,  ouAddr,  nbElem,  eltFormat,  pingpong,  dmaChan,  perIdx,  pingPl,  pongPl)\
HSP_ACC_BackgroundExt2Int( hmw,  inAddr,  ouAddr,  nbElem,  eltFormat,  pingpong,  dmaChan,  perIdx,  pingPl,  pongPl)

#define HSP_DIRECT_BACKGROUND_Int2Ext( hmw,  inAddr,  ouAddr,  nbElem,  eltFormat,  pingpong,  dmaChan,  perIdx,  pingPl,  pongPl)\
HSP_ACC_BackgroundInt2Ext( hmw,  inAddr,  ouAddr,  nbElem,  eltFormat,  pingpong,  dmaChan,  perIdx,  pingPl,  pongPl)

#define  HSP_DIRECT_BACKGROUND_SuspendResumeExt2Int( hmw,  dmaChan,  flag)\
 HSP_ACC_BackgroundSuspendResumeExt2Int( hmw,  dmaChan,  flag)

#define HSP_DIRECT_COUNTER_Set( hmw,  cntIdx,  val)\
HSP_ACC_CounterSet( hmw,  cntIdx,  val)

/* ------------------------------------------------------------------------- */
/* END OF MAPPING */
/* ------------------------------------------------------------------------- */

/*------------------------------------------------------------------------------
 * Types
 *----------------------------------------------------------------------------*/

// Used by CNN test only !
/** CMSIS-NN object to contain the width and height of a tile */
typedef struct
{
    int32_t w; /**< Width */
    int32_t h; /**< Height */
} stm32_hsp_cmsis_nn_tile;
/** CMSIS-NN object for the quantized Relu activation */
typedef struct
{
    int32_t min; /**< Min value used to clamp the result */
    int32_t max; /**< Max value used to clamp the result */
} stm32_hsp_cmsis_nn_activation;
typedef struct
{
    int32_t input_offset;  /**< Zero value for the input tensor */
    int32_t output_offset; /**< Zero value for the output tensor */
    stm32_hsp_cmsis_nn_tile stride;
    stm32_hsp_cmsis_nn_tile padding;
    stm32_hsp_cmsis_nn_tile dilation;
    stm32_hsp_cmsis_nn_activation activation;
} stm32_hsp_cmsis_nn_conv_params;


typedef struct
{
    int32_t *multiplier; /**< Multiplier values */
    int32_t *shift;      /**< Shift values */
} stm32_hsp_cmsis_nn_per_channel_quant_params;

typedef struct
{
	int32_t n; /**< Generic dimension to contain either the batch size or output channels.
				 Please refer to the function documentation for more information */
	int32_t h; /**< Height */
	int32_t w; /**< Width */
	int32_t c; /**< Input channels */

} stm32_hsp_cmsis_nn_dims;
/// ARM need to load BRAM
//#define ARM_LOAD_BRAM



#ifndef ARM_COMPILE

//////////////// FIX VAL TO BE REWORK
// #define __IO
// #define HSP_INSTANCE_NBR  1U
// #define __CLZ
// #define __RBIT
// #define HSB_REG_BASE_ADDR (0x80000 * 4) ///< HSP register base address from v0.0.8
// #define HSP1 (HSB_REG_BASE_ADDR + 0x1000)
// #define __STATIC_FORCEINLINE

// #include "hyp_types.h"
// #include "HSP_UserSpec_CPU_RegMap_Vx_x_x.h"
// typedef enum
// {
  // HAL_HSP_STATE_RESET = 0U,           /*!< HSP not yet initialized                    */
  // HAL_HSP_STATE_INIT  = (1U << 31U),  /*!< HSP initialized but not yet configured     */
  // HAL_HSP_STATE_READY = (1U << 30U),  /*!< HSP initialized, configured but not locked */
  // HAL_HSP_STATE_BUSY  = (1U << 29U),  /*!< HSP configured and locked                  */
  // HAL_HSP_STATE_ERROR = (1U << 28U),  /*!< HSP is not functional                      */
// } HAL_HSP_StateTypeDef;

// #define __IO
// #include "HSP_UserSpec_CPU_RegMap_Vx_x_x.h"

///////////////////////////////////////////////////////////

#ifndef HYP_UNITARY_TEST
extern void hypsa_post_command();
#endif

#else
#ifdef STM32U575xx
typedef HAL_HSP_HandleTypeDef HSP_HandleTypeDef;
#endif // STM32U575xx
#ifdef __MDW_CUBE2__
#define HAL_StatusTypeDef hal_status_t
#define HSP_HandleTypeDef hal_hsp_handle_t
#endif

void hsp_startcc(void);
void hsp_stopcc(void);

#define getARMCycle() (0xFFFFFF - SysTick->VAL)
#endif

#ifndef ARM_COMPILE
#define hspInternalMeasure hypInternalMeasure
#endif // ARM_COMPILE


/*------------------------------------------------------------------------------
 * Typedef
 *----------------------------------------------------------------------------*/

#ifndef HYP_TOOLS
#ifdef __HSP_DMA__
#ifdef HYPSA_SIMU
/**
  * @brief TIM
  */
typedef struct
{
  __IO uint32_t CR1;         /*!< TIM control register 1,                   Address offset: 0x00 */
  __IO uint32_t CR2;         /*!< TIM control register 2,                   Address offset: 0x04 */
  __IO uint32_t SMCR;        /*!< TIM slave mode control register,          Address offset: 0x08 */
  __IO uint32_t DIER;        /*!< TIM DMA/interrupt enable register,        Address offset: 0x0C */
  __IO uint32_t SR;          /*!< TIM status register,                      Address offset: 0x10 */
  __IO uint32_t EGR;         /*!< TIM event generation register,            Address offset: 0x14 */
  __IO uint32_t CCMR1;       /*!< TIM capture/compare mode register 1,      Address offset: 0x18 */
  __IO uint32_t CCMR2;       /*!< TIM capture/compare mode register 2,      Address offset: 0x1C */
  __IO uint32_t CCER;        /*!< TIM capture/compare enable register,      Address offset: 0x20 */
  __IO uint32_t CNT;         /*!< TIM counter register,                     Address offset: 0x24 */
  __IO uint32_t PSC;         /*!< TIM prescaler,                            Address offset: 0x28 */
  __IO uint32_t ARR;         /*!< TIM auto-reload register,                 Address offset: 0x2C */
  __IO uint32_t RCR;         /*!< TIM repetition counter register,          Address offset: 0x30 */
  __IO uint32_t CCR1;        /*!< TIM capture/compare register 1,           Address offset: 0x34 */
  __IO uint32_t CCR2;        /*!< TIM capture/compare register 2,           Address offset: 0x38 */
  __IO uint32_t CCR3;        /*!< TIM capture/compare register 3,           Address offset: 0x3C */
  __IO uint32_t CCR4;        /*!< TIM capture/compare register 4,           Address offset: 0x40 */
  __IO uint32_t BDTR;        /*!< TIM break and dead-time register,         Address offset: 0x44 */
  __IO uint32_t CCR5;        /*!< TIM capture/compare register 5,           Address offset: 0x48 */
  __IO uint32_t CCR6;        /*!< TIM capture/compare register 6,           Address offset: 0x4C */
  __IO uint32_t CCMR3;       /*!< TIM capture/compare mode register 3,      Address offset: 0x50 */
  __IO uint32_t DTR2;        /*!< TIM deadtime register 2,                  Address offset: 0x54 */
  __IO uint32_t ECR;         /*!< TIM encoder control register,             Address offset: 0x58 */
  __IO uint32_t TISEL;       /*!< TIM Input Selection register,             Address offset: 0x5C */
  __IO uint32_t AF1;         /*!< TIM alternate function option register 1, Address offset: 0x60 */
  __IO uint32_t AF2;         /*!< TIM alternate function option register 2, Address offset: 0x64 */
  __IO uint32_t OR ;         /*!< TIM option register,                      Address offset: 0x68 */
  uint32_t RESERVED0[220];/*!< Reserved,                               Address offset: 0x6C */
  __IO uint32_t DCR;         /*!< TIM DMA control register,                 Address offset: 0x3DC */
  __IO uint32_t DMAR;        /*!< TIM DMA address for full transfer,        Address offset: 0x3E0 */
} TIM_TypeDef;
#endif

/**
  * @brief  HSP_CMD_SCA_CLARKE ICLARKE configuration fields: [alpha, beta]
  */
typedef struct
{
  float32_t alpha; /**< alpha */
  float32_t beta;  /**< beta */
} HSP_IalphabetaTypeDef2;

/**
  * @brief  HSP_CMD_SCA_PARK IPARK configuration fields: [alpha, beta]
  */
typedef struct
{
  float32_t alpha; /**< alpha */
  float32_t beta;  /**< beta */
} HSP_ValphabetaTypeDef2;

/**
  * @brief  HSP_CMD_SCA_PARK IPARK configuration fields: [q, d]
  */
typedef struct
{
  float32_t q; /**< q */
  float32_t d; /**< d */
} HSP_VqdTypeDef2;

typedef struct
{
  HSP_IalphabetaTypeDef2 Iab; /**< @brief Stator current on stator reference frame abc */ // => float
  HSP_ValphabetaTypeDef2 Ialphabeta; /**< @brief Stator current on stator reference frame alfa-beta*/ // => float si observer dans hsp sinon int32
  HSP_VqdTypeDef2 Iqd;        /**< @brief Stator current on rotor reference frame qd */ // => integer 32
  HSP_VqdTypeDef2 Iqdref;     /**< @brief Stator current on rotor reference frame qd */ // => integer 32
  HSP_VqdTypeDef2 Vqd; /**< @brief Phase voltage on rotor reference frame qd */ // => integer 32 (car type qd_t) (=> float si observer dans hsp sinon int32)
  HSP_ValphabetaTypeDef2 Valphabeta; /**< @brief Phase voltage on stator reference frame alpha-beta*/ // => float si observer dans hsp sinon int32
  float32_t hElAngle; /**< @brief Electrical angle used for reference frame transformation  */ // => float32 ? or int32
  // Attention ici un pb d'alignement pour les champs non utilisÃÆÃâÃâ Ã¢â¬â¢ÃÆÃ¢â¬Å¡ÃâÃÂ©s par le hsp
  //  qd_t IqdHF; /**< @brief Stator current on stator reference frame alfa-beta*/ // => a bouger a la fin
  //   int16_t UserIdref; /**< @brief User value for the Idref stator current */ // => a bouger a la fin
  //   int16_t hTeref; /**< @brief Reference torque */ // => a bouger a la fin
  //   uint16_t hCodeError; /**< @brief error message */
  //   CurrRefSource_t bDriveInput; /**< @brief It specifies whether the current reference source must be #INTERNAL or #EXTERNAL*/
} HSP_McFocVarBuffTypeDef;


/* Modify field in struct to introduce REV_PARK_ANGLE_COMPENSATION_FACTOR
   InstantaneousElSpeedDppWithCompensation  = SPD_GetInstElSpeedDpp(speedHandle) * REV_PARK_ANGLE_COMPENSATION_FACTOR; */
typedef struct
{
  int32_t bElToMecRatio; // => int32  /*!< Coefficient used to transform electrical to mechanical quantities and viceversa. It usually coincides with motor pole pairs number*/
  int32_t hElAngle; // => float32 ? or int32
  int32_t hMecAngle; // => int32
  int32_t wMecAngle; // => int32
  int32_t InstantaneousElSpeedDppWithCompensation; // New var = InstantaneousElSpeedDpp * REV_PARK_ANGLE_COMPENSATION_FACTOR  InstantaneousElSpeedDpp; // => int32
  // ATTENTION, alignement des vars non utilisees par le HSP:
  int32_t  InstantaneousElSpeedDpp; // => int32
  uint8_t  bSpeedErrorNumber;
  uint8_t  SpeedUnit;                 /*!< The speed unit value is defined into mc_stm_types.h */
  uint8_t  bMaximumSpeedErrorsNumber; /*!< Maximum value of not valid measurements before an error is reported. */
  int16_t  hAvrMecSpeedUnit;
  int16_t  hElSpeedDpp;
  int16_t  hMecAccelUnitP;
  uint16_t hMaxReliableMecSpeedUnit;  /*!< Maximum value of measured mechanical speed that is considered to be valid. Expressed in the unit defined by #SPEED_UNIT.*/
  uint16_t hMinReliableMecSpeedUnit;  /*!< Minimum value of measured mechanical speed that is considered to be valid. Expressed in the unit defined by #SPEED_UNIT.*/
  uint16_t hMaxReliableMecAccelUnitP; /*!< Maximum value of measured acceleration that is considered to be valid. Expressed in the unit defined by #SPEED_UNIT */
  uint16_t hMeasurementFrequency;     /*!< Frequency at which the user will request a measurement of the rotor electrical angle. Expressed in PWM_FREQ_SCALING*Hz. It is also used to convert measured speed from the unit defined by #SPEED_UNIT to dpp and viceversa.*/
  uint32_t DPPConvFactor; /* (65536/PWM_FREQ_SCALING) */
} SpeednPosFdbk_Handle_t;

/**
  * @brief  ENCODER class parameters definition
  */
typedef struct
{
  SpeednPosFdbk_Handle_t _Super;
  TIM_TypeDef             *TIMx; /*!< Timer used for ENCODER sensor management.*/
  uint32_t                U32MAXdivPulseNumber; // => uint32 /*! <It stores U32MAX/hPulseNumber*/
#ifdef FULL_STRUCT_DEFINITION
  // ATTENTION, alignement des vars non utilisees par le HSP:
  uint32_t SpeedSamplingFreqUnit; /*!< Frequency at which motor speed is to be computed. It must be equal to the frequency at which function SPD_CalcAvrgMecSpeedUnit is called.*/
  int32_t  DeltaCapturesBuffer[ENC_SPEED_ARRAY_SIZE]; /*!< Buffer used to store captured variations of timer counter*/
  uint16_t SpeedSamplingFreqHz; /*! <Frequency (Hz) at which motor speed is to be computed. */
  /* SW Settings */
  uint16_t PulseNumber; /*!< Number of pulses per revolution, provided by each of the two encoder signals, multiplied by 4 */
  volatile uint16_t TimerOverflowNb; /*!< Number of overflows occurred since last speed measurement event*/
  uint16_t PreviousCapture; /*!< Timer counter value captured during previous speed measurement event*/
  FunctionalState RevertSignal; /*!< To be enabled if measured speed is opposite to real one (ENABLE/DISABLE)*/
  uint8_t SpeedBufferSize; /*!< Size of the buffer used to calculate the average speed. It must be <= 16.*/
  bool SensorIsReliable; /*!< Flag to indicate sensor/decoding is not properly working.*/
  uint8_t ICx_Filter; /*!< Input Capture filter selection */
  volatile uint8_t DeltaCapturesIndex; /*! <Buffer index*/
  bool TimerOverflowError; /*!< true if the number of overflow occurred is greater than 'define' ENC_MAX_OVERFLOW_NB*/
#endif /* FULL_STRUCT_DEFINITION */
} ENCODER_Handle_t;

/**
  *   @brief Motor control two components q, d type definition configuration fields: [q, d]
  */
typedef struct
{
  float32_t q; /**< Two components q, d type definition: q */
  float32_t d; /**< Two components q, d type definition: d */
} HSP_McQdBuffTypeDef;

/**
  *   @brief Motor control two components q, d type definition configuration fields: [q, d]
  */
typedef struct
{
  int32_t q; /**< Two components q, d type definition: q */
  int32_t d; /**< Two components q, d type definition: d */
} HSP_VqdQ15TypeDef;

/**
  *   @brief HSP_CMD_MC_PI_CONTROLLER configuration fields: [pIntegralTerm, UpperOutputLimit, LowerOutputLimit, KpGain, kiGain, upperIntegralLimit, lowerIntegralLimit]
  */
typedef struct
{
  float32_t kpGain; /**< KpGain: gain used by PID component */
  float32_t kiGain; /**< kiGain: gain used by PID component */
  float32_t integralTerm; /**< integral term */
  float32_t upperIntegralLimit; /**< Upper limit used to saturate the integral term given by @f$\frac{K_{ig}}{K_{id}} @f$ * integral of process variable error */
  float32_t lowerIntegralLimit; /**< Upper limit used to saturate the integral term given by @f$\frac{K_{ig}}{K_{id}} @f$ * integral of process variable error */
  float32_t upperOutputLimit;   /**< Upper limit used to saturate the PI output */
  float32_t lowerOutputLimit;   /**< Upper limit used to saturate the PI output */
} HSP_McPiControllerTypeDef;


/**
  *   @brief HSP_CMD_MC_CIRCLE_LIMITATION configuration fields: [MaxModule, MaxVd]
  */
typedef struct
{
  float32_t maxModule;  /**< Circle limitation maximum allowed module */
  float32_t maxVd;      /**< Circle limitation maximum allowed module */
} HSP_McClmBuffTypeDef;


/**
  *   @brief  HSP_CMD_MC_PWMC_SETPHASEVOLTAGE handle fields: [Sector, lowDuty, midDuty, highDuty, CntPhA, CntPhB, CntPhC]
  */
typedef struct
{
  float32_t pwmPeriod; /**< PWM period expressed in timer clock cycles unit: @f$hPWMPeriod = TimerFreq_{CLK} / F_{PWM}@f$    */
  uint32_t sector;     /**< the space vector sector number */
  uint32_t lowDuty;    /**< lowDuty */
  uint32_t midDuty;    /**< midDuty */
  uint32_t highDuty;   /**< highDuty */
  uint32_t cntPhA;     /**< PWM Duty cycle for phase A */
  uint32_t cntPhB;     /**< PWM Duty cycle for phase B */
  uint32_t cntPhC;     /**< PWM Duty cycle for phase C */
} HSP_McPwmcBuffTypeDef;

/**
  * @brief  HSP_CMD_SCA_CLARKE ICLARKE configuration fields: [a, b]
  */
typedef struct
{
  float32_t a; /**< a */
  float32_t b; /**< b */
} HSP_IabTypeDef2;

hsp_core_status_t HSP_SEQ_McClarkeParkS16d(hsp_core_handle_t *hmw, int32_t *pTheta, HSP_IabTypeDef2 *pIab,
                                           HSP_VqdTypeDef2 *pIqd, uint32_t ioType);
hsp_core_status_t HSP_SEQ_McPiController(hsp_core_handle_t *hmw, float32_t *inABuff, int32_t *inBBuff,
                                         HSP_McPiControllerTypeDef *cfgBuff, float32_t *outBuff, uint32_t ioType);
hsp_core_status_t HSP_SEQ_McCircleLimitation(hsp_core_handle_t *hmw, HSP_VqdTypeDef2 *pVqd,
                                             HSP_McClmBuffTypeDef *pCfg, HSP_VqdTypeDef2 *pQd, uint32_t ioType);
hsp_core_status_t HSP_SEQ_McIParkS16d(hsp_core_handle_t *hmw, int32_t *pTheta, HSP_VqdTypeDef2 *pVqd,
                                      HSP_ValphabetaTypeDef2 *pVab, uint32_t ioType);
hsp_core_status_t HSP_SEQ_McPwmcSetPhaseVoltage(hsp_core_handle_t *hmw, HSP_ValphabetaTypeDef2 *pVab,
                                                HSP_McPwmcBuffTypeDef *pHandle, uint32_t ioType);
hsp_core_status_t HSP_SEQ_McUpdateFocVar(hsp_core_handle_t *hmw, HSP_McFocVarBuffTypeDef *pFocVar,
                                         HSP_VqdTypeDef2 *pIqd, HSP_VqdTypeDef2 *pVqd, uint32_t ioType);
hsp_core_status_t HSP_SEQ_McEncCalcAngle(hsp_core_handle_t *hmw, ENCODER_Handle_t *superBuff,
                                         uint32_t timCntAddr, uint32_t U32MAXdivPulseNumber, uint32_t ioType);
#endif /* __HSP_DMA__ */
#endif // HYP_TOOLS

/*------------------------------------------------------------------------------
 * Variables
 *----------------------------------------------------------------------------*/
#ifndef HYP_TOOLS
/// Global HSP handler variable
// extern HSP_HandleTypeDef HSPHandle;
uint32_t hst_test_ConfigAndEnableEvent(uint32_t event);
void hst_test_EnableKerEventInterrupt(uint32_t event);
void hst_test_TrigProcList(uint32_t listNumber, uint32_t itf);

// FOR MDW
 extern HSP_TypeDef *pHspReg;
 extern hsp_core_handle_t hmw;
#ifdef HYPSA_SIMU
#ifdef ISABELLE	
extern hw_hsp_if_handle_t h_hw_hsp_if[];
#endif // ISABELLE
#endif
#endif // HYP_TOOLS


/// Test loop for command list played (bug with EVTC set to 1: tbm with 2)
#define HSP_TEST_EVT_LOOP 2 // temporay for EVTC bug instead of 2

#ifdef __NOPRINTF__
#define printf(f, ...)
#endif

/// Start measure using global _startCycles
//#define START_MEASURE _startCycles = chess_cycle_count()
#define START_MEASURE \
	startcc(); \
	_startCycles = getcc()

/// Stop measure using global hspInternalMeasure
#define STOP_MEASURE \
	stopcc(); \
	hspInternalMeasure = GET_CYCLE_DIFF

#define M_PI 3.14159265358979

#ifdef ARM_COMPILE
/* Systick Start */
#define TimerCount_Start()\
{\
	SysTick->LOAD = 0xFFFFFF ;  /* Set reload register */   \
	SysTick->VAL = 0 ;          /* Clear Counter */         \
	SysTick->CTRL = 0x5 ;       /* Enable Counting*/        \
}
/* Systick Stop and retrieve CPU Clocks count */
#define TimerCount_Stop(Value)\
{\
	SysTick->CTRL = 0;           /* Disable Counting */                \
	Value = SysTick->VAL;       /* Load the SysTick Counter Value */    \
	Value = 0xFFFFFF - Value;   /* Capture Counts in CPU Cycles*/       \
}
#else // ARM_COMPILE
#define TimerCount_Start()
#define TimerCount_Stop(Value)
#endif // ARM_COMPILE

/**
 * Test report status
 */

#ifdef FPGA_COMPILE
#define TEST_WRITE_STATUS(error) *_mbStatus = 0x80000000 | error; soft_break();
#else // FPGA_COMPILE
#define TEST_WRITE_STATUS(error) *_mbStatus = 0x80000000 | error
#endif // FPGA_COMPILE

/**
 * Test report define
 */
#define TEST_INFO_REPORT(name, fmt, ...) \
{ \
  printf("Test %s: ", name); \
  printf(fmt, ##__VA_ARGS__); \
}

#if defined (__GNUC__) || defined (ARM_COMPILE)
/**
 * Test end report define
 */
#define TEST_END_REPORT(name, error) \
{ \
  TEST_INFO_REPORT(name, "\n");   \
  TEST_INFO_REPORT(name, "\t*************************\n"); \
  if (error > 0) { \
    TEST_INFO_REPORT(name, "\t*** TEST FAILED %5d ***\n", error); \
  } \
  else { \
	TEST_INFO_REPORT(name, "\t***    TEST PASSED    ***\n"); \
  } \
  TEST_INFO_REPORT(name, "\t*************************\n\n");\
}

/**
 * Return internal measure from last lib function called
 */
#define TEST_MEASURE_REPORT(name, size, fmt, ...) \
  printf("Test %s\t%8d\t nb cycles per operation test_measure_report loop\t%d\t%6d\tcycles for\t", name, \
         ((int32_t) (((hspInternalMeasure) + (size >> 1)) / ((int32_t) size))), \
         (uint16_t) size, hspInternalMeasure); \
  printf(fmt, ##__VA_ARGS__);


/**
 * Return internal measure from last lib function called
 */
#define TEST_MEASURE_REPORT_D(name, size, fmt, ...) \
  printf("Test %s\t%8d\t nb cycles per operation test_measure_report loop\t%d\t%6d\tcycles \t%6d\t arm cycles for\t", name, \
         ((int32_t) (((hspInternalMeasure) + (size >> 1)) / ((int32_t) size))), \
         (uint16_t) size, hspInternalMeasure, _armMeasure); \
  printf(fmt, ##__VA_ARGS__);

#else // __GNUC__

// Here hypsa copmilation

/**
 * Test end report define
 */
#define TEST_END_REPORT(name, error) \
{ \
  TEST_INFO_REPORT(name, "\n"); \
  TEST_INFO_REPORT(name, "\t*************************\n"); \
  if (error > 0) { \
    TEST_INFO_REPORT(name, "\t*** TEST FAILED %5ld ***\n", error); \
  } \
  else { \
	TEST_INFO_REPORT(name, "\t***    TEST PASSED    ***\n"); \
  } \
  TEST_INFO_REPORT(name, "\t*************************\n\n"); \
  TEST_WRITE_STATUS(error); \
}

/**
 * Return internal measure from last lib function called
 */
#define TEST_MEASURE_REPORT(name, size, fmt, ...) \
  printf("Test %s\t%8ld\t nb cycles per operation test_measure_report loop\t%d\t%6ld\tcycles for\t", name, \
         ((int32_t) (((hspInternalMeasure) + (size >> 1)) / ((int32_t) size))), \
         (uint16_t) size, hspInternalMeasure); \
  printf(fmt, ##__VA_ARGS__);\
/**
 * Return internal measure from last lib function called
 */
#define TEST_MEASURE_REPORT_D(name, size, fmt, ...) \
  printf("Test %s\t%8ld\t nb cycles per operation test_measure_report loop\t%d\t%6ld\tcycles \t%6ld\t arm cycles for\t", name, \
         ((int32_t) (((hspInternalMeasure) + (size >> 1)) / ((int32_t) size))), \
         (uint16_t) size, hspInternalMeasure, _armMeasure); \
  printf(fmt, ##__VA_ARGS__);
#endif // __GNUC__

/// Define for check functions
#define P60_CHECK_DO_CMP 0 ///< Do comparison when call check functions
#define P60_CHECK_NO_CMP 1 ///< Do not comparison when call check functions but check _errorReportCount is set

#ifdef HYP_UNITARY_TEST
#ifndef GCC_COMPILE
#define hsp_test_main main
#endif
#endif// HYP_UNITARY_TEST

/*------------------------------------------------------------------------------
 * Types
 *----------------------------------------------------------------------------*/

#ifndef HYP_TOOLS
/************************ Here Digital Control API  to be moved in MDW *******************************/
#ifdef __HSP_DMA__
#if 0
#define HSP_DC_PID_FILTER_BYP 0 // To be moved in hsp_fw_def.h
#define HSP_DC_PID_FILTER_F1  1 // To be moved in hsp_fw_def.h
#define HSP_DC_PID_FILTER_F2  2 // To be moved in hsp_fw_def.h

/// Common structure for all PIs
typedef struct {
  float32_t kp; /**< Proportional gain */
  float32_t ki; /**< Integral gain */
  float32_t kfb; /**< Feedback gain (discharge) */
  float32_t itg; /**< integral term */
  float32_t itgL[2]; /**< Integral threshold */
  float32_t pItgL[2]; /**< Output threshold */
  float32_t ffd; /**< Feed-forward requested by Artesyn */
} hyp_dc_pipx_ctrl_t;

/// Structure for PID controllers
typedef struct {
  hyp_dc_pipx_ctrl_t pip;
  float32_t outL[2]; /**< Output threshold */
  float32_t kd; /**< Differential gain */
  float32_t err1; /**< previous process variable error */
  float32_t A; /**< A = W/(W+2); W=2*tan(pi* Fc/Fs) */
  float32_t B; /**< B = (W-2)/(W+2); */
  float32_t diff1; /**< previous process diff. value */
  uint32_t cfgLpf;
} hyp_dc_pidpx_ctrl_t;

/// Structure for generic PID controller
typedef struct {
  hyp_dc_pipx_ctrl_t pip;
  float32_t outL[2]; /**< Output threshold */
  float32_t kd; /**< Differential gain */
  float32_t err1; /**< previous process variable error */
  float32_t A; /**< A = W/(W+2); W=2*tan(pi* Fc/Fs) */
  float32_t B; /**< B = (W-2)/(W+2); */
  float32_t diff1; /**< previous process diff. value */
  uint32_t cfgLpf;
  uint32_t pis;
  uint32_t dis;
  uint32_t diff;
} hyp_dc_gpid_ctrl_t;

/// Proportional resonant data structure
typedef struct {
  float32_t kp; /**< Proportional gain */
  float32_t a1; /**< filter coef a1	*/
  float32_t b0; /**< filter coef 1/b0 */
  float32_t b1; /**< filter coef b1 */
  float32_t b2; /**< filter coef b2 */
  float32_t resL[2]; /**< Resonant threshold */
  float32_t outL[2]; /**< Output threshold */
} hyp_dc_ppr1_ctrl_t;

/// Structure for generic PID controller
typedef struct {
  hyp_dc_pipx_ctrl_t pip;
  float32_t busComp;
  float32_t xclpO;
  float32_t xclpI;
} hyp_dc_pis3_ctrl_t;

/// Proportional resonant state structure
typedef struct {
  float32_t err1;
  float32_t err2;
  float32_t out1;
  float32_t out2;
} hyp_dc_ppr1_sta_t;

/**
  * @brief This function is the PI serial controller named SCA_PIDP1_F1
  * @param hhsp      HSP handle.
  * @param pSrc      Input A Buffer address
  * @param pSet      Input B Buffer address
  * @param pDst      Output Buffer address
  * @param pCfg      Config struct address (hyp_dc_pidpx_ctrl_t)
  * @retval          HAL status.
  */
HAL_StatusTypeDef HAL_HSP_DcPidP1(HSP_HandleTypeDef *hhsp, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                  hyp_dc_pidpx_ctrl_t *pCfg);

/**
  * @brief This function is the PI serial controller named SCA_PIDP1_F1
  * @param hhsp      HSP handle.
  * @param pSrc      Input A Buffer address
  * @param pSet      Input B Buffer address
  * @param pDst      Output Buffer address
  * @param pCfg      Config struct address
  * @retval          HAL status.
  */
HAL_StatusTypeDef HAL_HSP_DcPidP2(HSP_HandleTypeDef *hhsp, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                  hyp_dc_pidpx_ctrl_t *pCfg);

/**
  * @brief This function is the PI serial controller named SCA_PIDP1_F1
  * @param hhsp      HSP handle.
  * @param pSrc      Input A Buffer address
  * @param pSet      Input B Buffer address
  * @param pDst      Output Buffer address
  * @param pCfg      Config struct address
  * @retval          HAL status.
  */
HAL_StatusTypeDef HAL_HSP_DcPidP3(HSP_HandleTypeDef *hhsp, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                  hyp_dc_pidpx_ctrl_t *pCfg);

/**
  * @brief This function is the PI parallel controller named SCA_PIP1
  * @param hhsp      HSP handle.
  * @param pSrc      Input A Buffer address
  * @param pSet      Input B Buffer address
  * @param pDst      Output Buffer address
  * @param pCfg      Config struct address
  * @retval          HAL status.
  */
HAL_StatusTypeDef HAL_HSP_DcPip1(HSP_HandleTypeDef *hhsp, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                 hyp_dc_pipx_ctrl_t *pCfg);

/**
  * @brief This function is the PI parallel controller named SCA_PIP1
  * @param hhsp      HSP handle.
  * @param pSrc      Input A Buffer address
  * @param pSet      Input B Buffer address
  * @param pDst      Output Buffer address
  * @param pCfg      Config struct address
  * @retval          HAL status.
  */
HAL_StatusTypeDef HAL_HSP_DcPip2(HSP_HandleTypeDef *hhsp, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                 hyp_dc_pipx_ctrl_t *pCfg);

/**
  * @brief This function is the PI parallel controller named DC_PIS2
  * @param hhsp      HSP handle.
  * @param pSrc      Input A Buffer address
  * @param pSet      Input B Buffer address
  * @param pDst      Output Buffer address
  * @param pCfg      Config struct address
  * @retval          HAL status.
  */
HAL_StatusTypeDef HAL_HSP_DcPis2(HSP_HandleTypeDef *hhsp, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                 hyp_dc_pipx_ctrl_t *pCfg);

/**
  * @brief This function is the PI parallel controller named DC_PIS3
  * @param hhsp      HSP handle.
  * @param pSrc      Input A Buffer address
  * @param pSet      Input B Buffer address
  * @param pDst      Output Buffer address
  * @param pCfg      Config struct address
  * @retval          HAL status.
  */
HAL_StatusTypeDef HAL_HSP_DcPis3(HSP_HandleTypeDef *hhsp, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                 hyp_dc_pis3_ctrl_t *pCfg);

/**
  * @brief This function is a generic PID controller
  * @param hhsp      HSP handle.
  * @param pSrc      Input A Buffer address
  * @param pSet      Input B Buffer address
  * @param pDst      Output Buffer address
  * @param pCfg      Config struct address
  * @retval          HAL status.
  */
HAL_StatusTypeDef HAL_HSP_DcGPid(HSP_HandleTypeDef *hhsp, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                 hyp_dc_gpid_ctrl_t *pCfg);

/**
  * @brief This function is a proportional resonant
  * @param hhsp      HSP handle.
  * @param pSrc      Input A Buffer address
  * @param pSet      Input B Buffer address
  * @param pDst      Output Buffer address
  * @param pCfg      Config struct address
  * @param pState    State buffer
  * @retval          HAL status.
  */
HAL_StatusTypeDef HAL_HSP_DcPpr1(HSP_HandleTypeDef *hhsp, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                 hyp_dc_ppr1_ctrl_t *pCfg, hyp_dc_ppr1_sta_t *pState);

#endif // if 0
#endif // __HSP_DMA__

/************************ End Digital Control API  to be moved in MDW *******************************/
#endif // HYP_TOOLS



/// Matrix structure
typedef struct
{
  float32_t *addr; ///< Buffer address
  uint16_t nRows; ///< number of rows
  uint16_t nCols; ///< number of columns
} p60_matrix_t;

/*------------------------------------------------------------------------------
 * Variables
 *----------------------------------------------------------------------------*/

#ifdef ARM_COMPILE
extern float32_t hspTestDstExt4096[4096];
#else // ARM_COMPILE
#define hspTestDstExt4096 hspTestDst4096
#endif // ARM_COMPILE

/// Destination buffer used by all tests
extern float32_t chess_storage(hypDM:HYPSA_TEST_DST_ADDR) hspTestDst4096[8192];

/// Use to test error counter report
extern uint32_t _errorReportCount;

/// Return internal measure from last lib function called
extern volatile cycleu_t hspInternalMeasure;

/// Return ARM measure
extern cycleu_t _armMeasure;

/// Start cycle for perf
extern cycleu_t _startCycles;

/// Mailbox status
extern  uint32_t *_mbStatus;


/*------------------------------------------------------------------------------
 * Functions
 *----------------------------------------------------------------------------*/
#ifndef HYP_TOOLS
/**
 * @brief HSP API hw reset
 * @param[in] hhsp    HSP handle.
 * @retval            HAL status.
 */
void test_hw_reset(void);

HAL_StatusTypeDef HAL_HSP_ConfigureEOT(uint8_t taskNb, uint8_t taskCmpNb);
HAL_StatusTypeDef test_send_event(uint8_t event);
HAL_StatusTypeDef test_enable_event(uint8_t event);

hsp_core_status_t HSP_WriteCommand(uint32_t command);
void hst_test_HAL_HSP_Boot0(HSP_HandleTypeDef *hhsp, uint32_t timeout_ms);
void hst_test_HAL_HSP_Boot1(void);
void hst_test_enableCycleCount(uint32_t enableCycleCount);
void hst_test_HSP_CORE_Init(hsp_core_handle_t *hmw);
void hst_test_HSP_CORE_Init_NPlug(hsp_core_handle_t *hmw, uint32_t *pSrc, uint32_t length);
void hst_test_HSP_CORE_Init_NPlug3(hsp_core_handle_t *hmw, uint32_t *pSrc0, uint32_t l0,
                                   uint32_t *pSrc1, uint32_t l1, uint32_t *pSrc2, uint32_t l2);
void hst_test_HSP_CORE_Init_NPlugE(hsp_core_handle_t *hmw, uint32_t *pSrc, uint32_t length, uint32_t fwCsize);

/**
  * @brief Check 2 address: external memory, shared memory, peripheral
  * @param addr1     value address to check
  * @param addr2     value address to check
  * @param variant   type of memory address allowed
  * @param ouAddr1   value address to check
  * @param ouAddr2   value address to check
  * @param encoded   value address to check
  * @retval            HAL status.
  */
HAL_StatusTypeDef HSP_Check2Address(HSP_HandleTypeDef *hhsp, uint32_t addr1, uint32_t addr2, uint32_t variant,
                                    uint32_t *ouAddr1, uint32_t *ouAddr2, uint32_t *encoded);
/**
  * @brief Check 2 address: external memory, shared memory, peripheral
  * @param addr1     value address to check
  * @param addr2     value address to check
  * @param addr3     value address to check
  * @param variant   type of memory address allowed
  * @param ouAddr1   value address to check
  * @param ouAddr2   value address to check
  * @param ouAddr3   value address to check
  * @param encoded   value address to check
  * @retval            HAL status.
  */
HAL_StatusTypeDef HSP_Check3Address(HSP_HandleTypeDef *hhsp, uint32_t addr1, uint32_t addr2, uint32_t addr3,
                                    uint32_t variant,
                                    uint32_t *ouAddr1, uint32_t *ouAddr2, uint32_t *ouAddr3, uint32_t *encoded);

/**
  * @brief Translate address according type of address
  * @param addr    value address to check
  * @param ouAddr  address translated
  * @retval       Type of memory.
  */
uint32_t HSP_CheckAddress(HSP_HandleTypeDef *hhsp, uint32_t addr, uint32_t *ouAddr);

/**
  * @brief Check if address is in shared memory
  * @param addr    value address to check
  * @param ouAddr  address in HSP space
  * @retval            HAL status.
  */
HAL_StatusTypeDef HSP_CheckSharedAddress(HSP_HandleTypeDef *hhsp, uint32_t addr, uint32_t *ouAddr);

/**
  * @brief Check if address is out of HSP memory space
  * @param addr    value address to check
  * @param ouAddr  address in external space
  * @retval            HAL status.
  */
HAL_StatusTypeDef HSP_CheckExternalAddress(HSP_HandleTypeDef *hhsp, uint32_t addr, uint32_t *ouAddr);


#endif // HYP_TOOLS


/**
 * Compare data table with ref
 * data Input vector
 * ref Reference vector to compare
 * size Number of elements to compare
 * noCompare Flag to no compare data and ref but check _errorReportCount was set by P60
 * return number of check failed
 */
uint32_t compare_float(const char *testName, float32_t *data, float32_t *ref, uint32_t size, uint16_t noCompare);

/**
 * Compare data table with ref and print maximun difference
 * data Input vector
 * ref Reference vector to compare
 * size Number of elements to compare
 * noCompare Flag to no compare data and ref but check _errorReportCount was set by P60
 * return number of check failed
 */
uint32_t compare_max_diff_float(const char *testName, float32_t *data, float32_t *ref, uint32_t size, uint16_t noCompare);

/**
 * Compare data table with ref
 * data Input vector
 * ref Reference vector to compare
 * size Number of elements to compare
 * noCompare Flag to no compare data and ref but check _errorReportCount was set by Hyperion
 * return number of check failed
 */
uint32_t compare_int32(const char *testName, uint32_t *data, uint32_t *ref, uint32_t size, uint32_t noCompare);

/**
 * Compare data table with ref
 * data Input vector
 * ref Reference vector to compare
 * size Number of elements to compare
 * noCompare Flag to no compare data and ref but check _errorReportCount was set by Hyperion
 * return number of check failed
 */
uint32_t compare_int8(const char *testName, uint8_t *data, uint8_t *ref, uint32_t size, uint16_t noCompare);

/**
 * Compare data table with ref
 * eltInFormat Input vector
 * eltOuFormat Output vector
 * data Input vector
 * ref Reference vector to compare
 * size Number of elements to compare
 * return number of check failed
 */
void conv_vect_type(uint8_t eltInFormat, uint8_t eltOuFormat, uint32_t *pIn, uint32_t *pOu, uint32_t size);

/**
 * Compare data table with ref
 * eltOuFormat Output vector format
 * data Output vector
 * size Number of elements to compare
 */
void conv_vectf_type(uint8_t eltOuFormat, uint8_t dmaI2f, uint8_t *pIn, uint32_t *pOu, uint32_t size,
                     uint8_t iJump);

/**
 * Compare data table with ref
 * eltInFormat Input vector
 * data Input vector
 * ref Reference vector to compare
 * size Number of elements to compare
 * return number of check failed
 */
void conv_vect_type_jmp(uint8_t eltInFormat, uint8_t dmaI2f, uint8_t *pIn, uint32_t *pOu, uint32_t size,
                        uint8_t iJump, uint8_t oJump);

/**
 * Compare data table with ref
 * eltOuFormat Output vector
 * data Input vector
 * ref Reference vector to compare
 * size Number of elements to compare
 * return number of check failed
 */
void conv_vectf_type_jmp(uint8_t eltOuFormat, uint8_t dmaI2f, uint8_t *pIn, uint32_t *pOu, uint32_t size,
                         uint8_t oJump);

/**
 * Read input file fileName, get uint32_t data in asccii hexa format
 * nbElem is number of element read in file
 */
void read_input32(const char *fileName, uint32_t nbElem, uint32_t *data);

/**
 * Read input file fileName, get uint32_t data in asccii hexa format
 * return nbElem, number of element read in file
 */
uint32_t read_input_file32(const char *fileName, uint32_t *data);

/**
 * Read matrix from file fileName, get uint32_t data in asccii hexa format
 */
void get_matrix_file32(const char *fileName, p60_matrix_t *mat);

/**
 * Write data in file fileName in asccii hexa format
 * nbElem is number of element write in file
 */
void write_file32(const char *fileName, uint32_t nbElem, uint32_t *data);

/**
 * Write data in file fileName in asccii hexa format
 * nbElem is number of element write in file
 */
void write_cfile32(const char *fileName, uint32_t nbElem, uint32_t *data);

/**
 * Write data in file fileName in asccii hexa format + float format
 * nbElem is number of element write in file
 */
void write_file32xf(const char *fileName, uint32_t nbElem, uint32_t *data);

/**
 * HSP check status error and return 0 if OK, else 1
 */
uint32_t hsp_check_status(const char *testName, uint32_t status, uint32_t ref_sts);

/**
 * Load HSP data test in BRAM
 */
void load_hsp_data_bram(uint32_t *pSrc, uint32_t *pDst, uint32_t length);
/**
 * Fill HSP memory with value
 */
void fill_hsp_memory(uint32_t *pDst, uint32_t value, uint32_t length);

#ifdef ARM_COMPILE
/**
 * Fill HSP memory with value
 */
void fill_hsp_memory(uint32_t *pDst, uint32_t value, uint32_t length);

/**
 * Load HSP DRAM code
 */
void load_hsp_dram(uint32_t *addr);

/**
 * ARM compilation: Load HSP CRAM code
 */
void load_hsp_cram(uint32_t *addr);

void load_hsp_data_cram(uint32_t *pSrc, uint32_t offset, uint32_t length);

#ifdef ARM_LOAD_BRAM
/**
 * ARM compilation: Load HSP BRAM code
 */
void load_hsp_bram(void);
#endif // ARM_LOAD_BRAM

/**
 * Hsp test main function called by ARm HAL
 */
int hsp_test_main(void);
#else // ARM_COMPILE

/// Define to set main function in Hypsa world
//#define hsp_test_main main
int hsp_test_main(void);

void load_hsp_data_cram(uint32_t *pSrc, uint32_t offset, uint32_t length);

#endif // ARM_COMPILE


/**
 * Reset shared memory area
 * @param[in] addr   Start address of area to reset
 * @param[in] size   Size of area to reset
 * @param[in] data   Data to set to reset area
 */
void reset_hsp_shared_mem(uint32_t addr, uint32_t size, uint32_t data);

/**
 * Hypsa platform: Used for calling scheduler in hypsa platform
 * FPGA platform: Wait for HSP termination.
 */
void test_wait_for_hsp(void);

/**
 * Wait for HSP Global IT
 */
void test_wait_for_gbl_hsp(void);

#ifndef HYP_TOOLS

/**
 * @brief Enable and Send event to HSP
 * @param[in] hhsp    HSP handle.
 * @retval            HAL status.
 */
HAL_StatusTypeDef test_enable_and_send_event(uint8_t event);
#endif // HYP_TOOLS


/**
 * Start cycle counter
 */
void hsp_startcc();

/**
 * Stop cycle counter
 */
void hsp_stopcc(void);

#ifndef HYP_TOOLS
/**
 * @brief HSP API hw reset
 * @param[in] hhsp    HSP handle.
 * @retval            HAL status.
 */
HAL_StatusTypeDef HAL_HSP_HWReset(HSP_HandleTypeDef *hhsp);
#endif // HYP_TOOLS

/**
 * Add padding for CNN input
 * @param[in] pSrc   Input image to pad
 * @param[in] pDst   Output image padded
 * @param[in] nbCol  Input width
 * @param[in] nbLin  Input height
 * @param[in] nbLin  Input channels
 * @param[in] padX   Horizontal padding
 * @param[in] padY   Vertical padding
 * @param[in] padV   Padding value
 */
void gen_padding_img(uint8_t *pSrc, uint8_t *pDst, uint32_t nbCol, uint32_t nbLin, uint32_t nbChan, uint32_t padX,
                     uint32_t padY, uint32_t padV);


/**
 * Add padding for CNN input
 * @param[in] pSrc   Input image to pad
 * @param[in] pDst   Output image padded
 * @param[in] nbCol  Input width
 * @param[in] nbLin  Input height
 * @param[in] nbLin  Input channels
 * @param[in] padX   Horizontal padding
 * @param[in] padY   Vertical padding
 * @param[in] padV   Padding value
 */
void gen_padding_img2(uint8_t *pSrc, uint8_t *pDst, uint32_t nbCol, uint32_t nbLin, uint32_t nbChan, uint32_t padX0,
                      uint32_t padX1, uint32_t padY0, uint32_t padY1, uint32_t padV);


/**
 * Return HSP BRAM A address
 * @param[in] bramab  BRAMAB address to convert
 * @retval            Return BRAM A address
 */
uint32_t get_brama_addr(uint32_t bramab);

/**
 * Return HSP BRAM B address
 * @param[in] bramab  BRAMAB address to convert
 * @retval            Return BRAM B address
 */
uint32_t get_bramb_addr(uint32_t bramab);

/**
 * Reset external buffer area
 */
void reset_ebuff(uint32_t *tmpAddr, uint32_t size);

/**
 * Reset shared memory
 */
void reset_bram(uint32_t size);

/**
 * Print conv2D kernel type
 */
void print_conv2d_type(void);

/**
 * Print CC counter dbg info
 */
void print_dbgcc(uint32_t *p);


#ifndef HYP_TOOLS
#ifdef __HSP_DMA__
// HSP motor control and digital control MDW functions
hsp_core_status_t HSP_SEQ_McClarkeParkS16d(hsp_core_handle_t *hmw, int32_t *pTheta, HSP_IabTypeDef2 *pIab,
                                           HSP_VqdTypeDef2 *pIqd, uint32_t ioType);
hsp_core_status_t HSP_SEQ_McPiController(hsp_core_handle_t *hmw, float32_t *inABuff, int32_t *inBBuff,
                                         HSP_McPiControllerTypeDef *cfgBuff, float32_t *outBuff, uint32_t ioType);
hsp_core_status_t HSP_SEQ_McCircleLimitation(hsp_core_handle_t *hmw, HSP_VqdTypeDef2 *pVqd,
                                             HSP_McClmBuffTypeDef *pCfg, HSP_VqdTypeDef2 *pQd, uint32_t ioType);
hsp_core_status_t HSP_SEQ_McIParkS16d(hsp_core_handle_t *hmw, int32_t *pTheta, HSP_VqdTypeDef2 *pVqd,
                                      HSP_ValphabetaTypeDef2 *pVab, uint32_t ioType);
hsp_core_status_t HSP_SEQ_McPwmcSetPhaseVoltage(hsp_core_handle_t *hmw, HSP_ValphabetaTypeDef2 *pVab,
                                                HSP_McPwmcBuffTypeDef *pHandle, uint32_t ioType);
hsp_core_status_t HSP_SEQ_McUpdateFocVar(hsp_core_handle_t *hmw, HSP_McFocVarBuffTypeDef *pFocVar,
                                         HSP_VqdTypeDef2 *pIqd, HSP_VqdTypeDef2 *pVqd, uint32_t ioType);
hsp_core_status_t HSP_SEQ_McEncCalcAngle(hsp_core_handle_t *hmw, ENCODER_Handle_t *superBuff,
                                         uint32_t timCntAddr, uint32_t U32MAXdivPulseNumber, uint32_t ioType);
hsp_core_status_t HSP_SEQ_Ramp_f32(hsp_core_handle_t *hmw, uint32_t *pSts, hsp_dc_ramp_cfg_t *pCfg,
                                   float32_t *pDst, uint32_t ioType);
#endif // __HSP_DMA__
#endif // HYP_TOOLS

#endif // __HSP_TEST_COMMON_H__
