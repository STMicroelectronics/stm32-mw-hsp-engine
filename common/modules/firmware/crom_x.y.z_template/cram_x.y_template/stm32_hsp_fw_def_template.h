/**
  ******************************************************************************
  * @file    stm32u3xx_hsp_fw_def.h
  * @author  MCD Application Team
  * @brief   Header file of Hyperion command.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#ifndef STM32U3xx_HSP_FW_DEF_H
#define STM32U3xx_HSP_FW_DEF_H

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
/*
  HSP command for PL init decode
 _______________________________________________________________________________________________________________________________________________________________
| 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 | 23 | 22 | 21 | 20 | 19 | 18 | 17 | 16 | 15 | 14 | 13 | 12 | 11 | 10 | 09 | 08 | 07 | 06 | 05 | 04 | 03 | 02 | 01 | 00 |
|_______________________________________________________________________________________________________________________________________________________________|
|    |    |    |Im  |Pre | SE | DE |     HYP_PLG_IDX             | s2 | s1 | s0 |    HYP_KERNEL_INIT_TYPE_MSK           |       HYP_KERNEL_ID_MSK               |
|_______________________________________________________________________________________________________________________________________________________________|
|    |    |    |Im  |STI | DMA ext |    Plugin index counter     | STI !encoded |  init function + ker param struct ID  |   unique  enum command                |
|_______________________________________________________________________________________________________________________________________________________________|
*/

// DefinesBalise: start here to copy defines in HAL header file
/** @addtogroup HSP_ENGINE
  * @{
  */
/** @addtogroup HSP_Private_Constants
  * @{
  */
/** @defgroup HSP_MEMORY_Constants HSP Memory Constants
  * @{
 */
/** HSP side: HSP memory base address */
#define HSP_SHARED_MEMORY_BASE_ADDR (0x40000 * 4)

/** HSP CC DRAM addr for the moment in DRAM: TBM */
#define HSP_DRAM_CC_ADDR 0x8

/** Direct command start address */
#define HSP_DC_START 0x280 // TBM for ROM: (0x250 * 4)

/**
  * @}
  */

/** @defgroup HSP_Command_Fields_Constants HSP Command Constants
  * @{
  */
/** Kernels list enumeration */
enum HSP_KernelNameDef
{
  /* Do not modify order nor add or suppress definition */

  /* Filter related functions */
  HSP_KER_FIR = 0, /**< FIR filter nb taps >= 7 and not modulo4 */
  HSP_KER_FIR_LESS7TAPS, /**< FIR filter nosimd for nb taps < 7 */
  HSP_KER_FIR_MODULO4TAPS, /**< FIR filter for modulo 4 taps + size even */
  HSP_KER_FIR_1SAMPLE, /**< FIR filter 1 sample (all taps supported) */
  HSP_KER_FIRDEC, /**< FIR filter, with decimation */
  HSP_KER_FIRDEC_1TAP, /**< FIR filter, with decimation for 1 tap */
  HSP_KER_FIRDEC_SPEC, /**< FIR filter, with decimation and special size: nb taps >= size and other conditions */
  HSP_KER_LMS, /**< filter, with adaptive LMS algorithm. */
  HSP_KER_BQ_CAS_DF1, /**< IIR biquad cascade DF1 filter */
  HSP_KER_BQ_CAS_DF2T, /**< IIR biquad cascade DF2T filter */
  HSP_KER_IIR_DF1, /**< IIR DF1 filter */
  HSP_KER_IIR_3P3Z_1S, /**< IIR 3p3z for 1 sample filter */
  HSP_KER_IIR_2P2Z_1S, /**< IIR 2p2z for 1 sample filter */
  HSP_KER_IIR_LATTICE, /**< IIR lattice filter */
  HSP_KER_CONV, /**< Convolution */
  HSP_KER_CORR, /**< Correlation */
  HSP_KER_WINSYM, /**< Window symmetric kernel */
  /* Vector related functions */
  HSP_KER_VEC_ADD, /**< Element-wise summation of a vector */
  HSP_KER_VEC_SUB, /**< Element-wise subtraction of a vector */
  HSP_KER_VEC_MUL, /**< Element-wise multiplication of a vector */
  HSP_KER_VEC_DIV, /**< Element-wise division of a vector */
  HSP_KER_VEC_SQRT, /**< Calculates the sum of the */
  HSP_KER_VEC_ABS, /**< Element-wise absolute value of a vector */
  HSP_KER_VEC_AVG, /**< Compute the average value of a vector */
  HSP_KER_VEC_RMS, /**< Compute the RMS value of a vector */
  HSP_KER_VEC_SCALE, /**< Multiply each vector element by a scalar */
  HSP_KER_VEC_OFFSET, /**< Add to each vector element a scalar */
  HSP_KER_VEC_MAX, /**< Search for value and position of the biggest element of a vector */
  HSP_KER_VEC_ABSMAX, /**< Search for value and position of the absolute biggest element of a vector */
  HSP_KER_VEC_MIN, /**< Search for value and position of the smallest element of a vector */
  HSP_KER_VEC_COPY, /**< Performs the copy of a vector (can be used for debug) */
  HSP_KER_VEC_SET, /**< Add kernel function pointer and parameters according to user command */
  HSP_KER_VEC_DOTPROD, /**< Calculates the dot prod of the input vectors */
  HSP_KER_VEC_COS, /**< Element-wise cosine value of a vector */
  HSP_KER_VEC_SIN, /**< Element-wise sine value of a vector */
  HSP_KER_VEC_SINCOS, /**< Element-wise sine cosine value of a vector */
  HSP_KER_VEC_F2I, /**< Element-wise float32 to integer 32bits conversion */
  HSP_KER_VEC_I2F, /**< Element-wise integer 32bits to float32 conversion */
  HSP_KER_VEC_24S2F, /**< Element-wise integer 24bits signed to float32 conversion */
  HSP_KER_VEC_F2U, /**< Element-wise float32 to unsigned integer 32bits conversion */
  HSP_KER_VEC_U2F, /**< Element-wise unsigned integer 32bits to float32 conversion */
  HSP_KER_VEC_DECIM, /**< Decimation */
  HSP_KER_VEC_ZINS, /**< Zero insertion */
  HSP_KER_VEC_ATAN2, /**< ATAN2 computation */
  HSP_KER_VEC_LN, /**< LN computation */
  HSP_KER_VEC_LOG10, /**< LOG10 computation */
  HSP_KER_VEC_EXP, /**< Exponential computation */
  HSP_KER_VEC_EXP10, /**< Exponential base 10 computation */
  HSP_KER_VEC_MUL_COS, /**< Compute the multiplication of one vector and cos ROM */
  HSP_KER_VEC_MUL_SIN, /**< Compute the multiplication of one vector and sin ROM */
  HSP_KER_VEC_SCALE_I, /**< Multiply each vector element by an immediate scalar */
  HSP_KER_VEC_OFFSET_I, /**< Add to each vector element an immediate scalar */
  HSP_KER_VEC_SET_I, /**< Set each vector element with an immediate scalar */
  HSP_KER_VEC_F2Q31, /**< Element-wise float32 to Q31 conversion */
  HSP_KER_VEC_Q312F, /**< Element-wise Q31 to float32 conversion */
  HSP_KER_VEC_F2Q15, /**< Element-wise float32 to Q15 conversion */
  HSP_KER_VEC_Q152F, /**< Element-wise Q15 to float32 conversion */
  /* Scalar related functions */
  HSP_KER_SCA_ABS, /**< Absolute value of an element */
  HSP_KER_SCA_ADD, /**< Summation of 2 scalars */
  HSP_KER_SCA_ATAN2, /**< ATAN2 of a scalar */
  HSP_KER_SCA_COS, /**< Cos */
  HSP_KER_SCA_DIV,
  HSP_KER_SCA_EXP, /**< Exponential computation */
  HSP_KER_SCA_EXP10,/**< Exponential base 10 computation */
  HSP_KER_SCA_F2I,
  HSP_KER_SCA_I2F,
  HSP_KER_SCA_24S2F,
  HSP_KER_SCA_F2U,
  HSP_KER_SCA_U2F,
  HSP_KER_SCA_F2Q31, /**< float32 to Q31 conversion */
  HSP_KER_SCA_Q312F, /**< Q31 to float32 conversion */
  HSP_KER_SCA_LN, /**< LN computation */
  HSP_KER_SCA_LOG10,/**< LOG10 computation */
  HSP_KER_SCA_MUL,
  HSP_KER_SCA_SIN, /**< Sin */
  HSP_KER_SCA_SINCOS, /**< Cos */
  HSP_KER_SCA_SET,
  HSP_KER_SCA_SQRT, /**< Square-root of an element */
  HSP_KER_SCA_SUB,
  HSP_KER_SCA_CLARKE, /**< Clarke */
  HSP_KER_SCA_PARK, /**< Park */
  HSP_KER_SCA_ICLARKE, /**< Iclarke */
  HSP_KER_SCA_IPARK, /**< IPark */
  HSP_KER_SCA_PID, /**< Pid */
  HSP_KER_SCA_FCOS, /**< FCos */
  HSP_KER_SCA_FSIN, /**< FSin */
  HSP_KER_SCA_FATAN2, /**< FAtan2 */
  /* Matrix related functions */
  HSP_KER_MAT_MUL, /**< Multiplication of two matrix */
  HSP_KER_MAT_TRANS, /**< Transposition of a matrix */
  HSP_KER_MAT_INV, /**< Matrix inversion */
  HSP_KER_M2V, /**< mat 2 vect kernel copy */
  HSP_KER_V2M, /**< vect 2 mat kernel copy */
  /* Transformation related funcons */
  HSP_KER_FFT, /**< Performs the fast Fourier transform of an input vector */
  HSP_KER_RFFT, /**< Performs the fast Fourier transform of an real input vector */
  HSP_KER_DCT, /**< Performs the discrete cosine transform of an input vector */
  HSP_KER_IDCT, /**< Performs the inverse discrete cosine transform of an input vector */
  /* Complex functions */
  HSP_KER_CMPLX_CONJ, /**< Compute the conjugate of each vector element */
  HSP_KER_CMPLX_DOTPROD, /**< Computes the dot product of two complex vectors */
  HSP_KER_CMPLX_MAG, /**< Vector Floating-point complex magnitude */
  HSP_KER_CMPLX_MAGSQUARED, /**< Vector Floating-point complex magnitude squared */
  HSP_KER_CMPLX_MUL, /**< Compute the complex multiplication of 2 complex vector */
  HSP_KER_CMPLX_RMUL, /**< Compute the multiplication of a complex vector by a real vector and generates a result */
  HSP_KER_CMPLX_MUL_EXP, /**< Compute the complex multiplication of one complex vector and exp ROM */
  HSP_KER_CMPLX_CMSIS_DOTPROD, /**< Computes the dot product of two complex vectors with 2 out real and imaginary */
  /* Specific functions */
  HSP_KER_FLTBANK, /**< Mel filter */
  /* Event kernel */
  HSP_KER_SEND_EVT, /**< Send EVT */
  HSP_KER_SET_FLAG, /**< Set KERF flag */
  HSP_KER_SET_TRGO, /**< TRGO kernel: generate a trigger pulse on one of the hsp_trg_out */
  /* conditional branch kernel */
  HSP_KER_CMPB, /**< Compare and send cond EVT to schedule conditional list */
  HSP_KER_CMPCNT, /**< Compare and send cond EVT to schedule conditional list */
  HSP_KER_RAMP, /**< Performs a linear Ramp-up or Ramp-down */
  HSP_KER_SCA2VECT, /**< Write a scalar value into a vector in order to build a vector */
  HSP_KER_SAT, /**< Perform a saturation to each vector element, using a programmable value */
  HSP_KER_CHK_BITS, /**< Checks the content of a bit field to a reference value and activates PL */
  HSP_KER_SET_BITS, /**< Set the specified bitfield of a scalar to the specified value */
  HSP_KER_SET_GPO, /**< Set the GPO field bit */
  HSP_KER_WAIT_COND, /**< Checks the content of a bit field to a reference value and waits until the condition */
  /* Motor control */
  /* State kernels */
  HSP_RESET_STATE, /**< hyp_reset_state */
  HSP_SET_STATE_CR2L, /**< hyp_set_state_cr2l */
  HSP_SET_STATE_CL2, /**< hyp_set_state_cl2r */
  HSP_SET_STATE_L2R, /**< hyp_set_state_cl2r */
  HSP_GET_STATE_CR2L, /**< hyp_get_state_cr2l */
  HSP_GET_STATE_CL2, /**< hyp_get_state_cl2r */
  HSP_GET_STATE_L2R, /**< hyp_get_state_cl2r */
  HSP_KER_CNT, /**< Counter kernel */
  /* CRC kernel */
  HSP_KER_CRC32, /**< hyp_crc32 */
  HSP_CLR_FWERR, /**< Clear FWERR register */
  /* CNN convolution kernels */
  HSP_CNN_CONV2D, /**< CNN 2D convolution */
  HSP_CNN_CONVDW, /**< CNN Depthwise convolution */
  HSP_CNN_CONVPW, /**< CNN pointwise */
  HSP_CNN_FC, /**< CNN fully connected */
  HSP_CNN_POOL, /**< CNN pooling functions */
  HSP_VECT_MB2A, /**< copy of a vector from MEMB to MEMA */
  /* Integer functions */
  HSP_INT32_ADD_I, /**< Integer scalar addition with constant */
  HSP_INT32_MUL_I, /**< Integer scalar multiplication with constant */
  /* End of kernels in hyp_ram_ker_list */
  HSP_NB_DRAM_KERNELS, /**< Number of kernels in DRAM (in ::hyp_ram_ker_list) */
  /* Starting here some enum for kernels which are not in hyp_ram_ker_list table but used in processing list process */
  /* Comparison kernels */
  HSP_KER_IFE_CNT, /**< ife count kernel comparison */
  HSP_KER_IFE_LOOP, /**< ife loop kernel comparison */
  HSP_KER_IFE, /**< ife kernel comparison */
  /* loop kernel */
  HSP_KER_LOOP, /**< loop kernel */
  /* End of all kernels */
  HSP_MAX_NB_KERNELS, /**< Put in last enum position the define for the number of kernels ID */
};

/* Command group init specific */
#define HSP_KER_IO_INIT       0x0000 /**< Kernel with 1 input and 1 output */
#define HSP_KER_IOS_INIT      0x0100 /**< Kernel with 1 input and 1 output + size */
#define HSP_KER_IIO_INIT      0x0200 /**< Kernel with 2 inputs and 1 output */
#define HSP_KER_IIOS_INIT     0x0300 /**< Kernel with 2 inputs and 1 output + size */
#define HSP_KER_IIOSS_INIT    0x0400 /**< Kernel with 2 inputs and 1 output + sizeA + sizeB */
#define HSP_KER_FLT_INIT       0x0500 /**< Kernel for filtering */
#define HSP_KER_FFT_INIT      0x0600 /**< Kernel for fft */
#define HSP_MAT_IIO_INIT      0x0700 /**< Kernel for matrix */
#define HSP_KER_VAL_INIT      0x0800 /**< Kernels for one value */
#define HSP_KER_COND_INIT     0x0900 /**< Kernels with conditional event and flag generation */
#define HSP_KER_REG_INIT      0x0c00 /**< Kernels for register bit manipulation */
#define HSP_KER_IIIOSS_INIT   0x0d00 /**< Kernel with 3 inputs and 1 output + 2 params */
#define HSP_KER_FIRDEC_INIT   0x0e00 /**< Kernel with 3 inputs and 1 output + 2 params */
#define HSP_KER_PLG_INIT      0x1000 /**< Plugin kernel init */
#define HSP_KER_IFE_INIT      0x1100 /**< Comparison (if, else, endif) kernel init */
#define HSP_MAT_CONV_INIT     0x1200 /**< Kernel for matrix 1D conversion */
#define HSP_KER_LOOP_INIT     0x1300 /**< Kernel for loop */

/* Specify some kernel size at 0x0000f000 of kernelID */
#define HSP_KER_STIA_MSK 0x00000000 /**< Kernel STI encoded mask for all allowed external buffer */
#define HSP_KER_STI0_MSK 0x00010000 /**< Kernel STI encoded mask for forbidden external buffer */
#define HSP_KER_STI1_MSK 0x00020000 /**< Kernel STI encoded mask for forbidden external buffer */
#define HSP_KER_STI2_MSK 0x00040000 /**< Kernel STI encoded mask for forbidden external buffer */
#define HSP_KER_STIN_MSK 0x00070000 /**< Kernel STI encoded mask for forbidden external buffer */
#define HSP_KER_STI_SHIFT 16 /**< Kernel STI encoded shift for allowed external buffer */

/* Plugin init index 0xf80000 */
#define HSP_KER_PLG           0x8000 /**< Plugin kernel */
#define HSP_KER_PLG_IDX_MSK   0x01f80000 /**< Mask for plugin init index */
#define HSP_KER_PLG_IDX_SHIFT 19 /**< Shift for plugin init index */

/* Specify preload info */
#define HSP_KER_PRE_MSK   0x08000000 /**< KernelID mask for preload possibility of first input when external buffer */
#define HSP_KER_PRE_SHIFT 27 /**< KernelID shift to get preload field */


/* Specify immediate value */
#define HSP_KER_IMM_MASK 0x10000000 /**< KernelID mask for immediate value */
#define HSP_KER_IMM_SHIFT 28 /**< KernelID shift for immediate value */

/**
  * @}
  */

/** @defgroup HSP_PLCommand_Constants HSP Processing list Command Constants
  * @{
  */

/* FW command */
#define HSP_CMD_FW_START            0x84000000 /**< After boot, FW is waiting for ::HSP_CMD_FW_START */

/* Processing list configuration command for supervisor mode */
#define HSP_CMD_PRO_CFG_START 0x81000000 /**< Start create PL: supervisor mode blocking no wfe until end PL creation */
#define HSP_CMD_PRO_CFG_END   0x82000000 /**< Close the started processing list creation and go back to wfe */
#define HSP_CMD_PL_RESET      0x83000000 /**< In supervisor mode: Reset all processing lists and go back to wfe */

/* Filter related functions */
/** FIR filter (all other cases) */
#define HSP_CMD_FIR         (HSP_KER_FIR | HSP_KER_FLT_INIT | HSP_KER_STIA_MSK | HSP_KER_PRE_MSK)
/** FIR filter, with decimation (more efficient function for (nb taps < nb samples) and
    ((nb samples - nb taps) > (2*decimator))) */
#define HSP_CMD_FIRDEC      (HSP_KER_FIRDEC | HSP_KER_FIRDEC_INIT | HSP_KER_STIA_MSK)
/** FIR filter, with adaptive LMS algorithm. */
#define HSP_CMD_LMS         (HSP_KER_LMS | HSP_KER_FLT_INIT | HSP_KER_STIA_MSK)
/** IIR biquad cascade DF1 filter */
#define HSP_CMD_BQ_CAS_DF1  (HSP_KER_BQ_CAS_DF1 | HSP_KER_FLT_INIT | HSP_KER_STIA_MSK | HSP_KER_PRE_MSK)
/** IIR biquad cascade DF2T filter */
#define HSP_CMD_BQ_CAS_DF2T (HSP_KER_BQ_CAS_DF2T | HSP_KER_FLT_INIT | HSP_KER_STIA_MSK | HSP_KER_PRE_MSK)
/** IIR DF1 filter */
#define HSP_CMD_IIR_DF1     (HSP_KER_IIR_DF1 | HSP_KER_FLT_INIT | HSP_KER_STIA_MSK)
/** IIR 3p3z for 1 sample filter */
#define HSP_CMD_IIR_3P3Z_1S (HSP_KER_IIR_3P3Z_1S | HSP_KER_FLT_INIT | HSP_KER_STIA_MSK)
/** IIR 2p2z for 1 sample filter */
#define HSP_CMD_IIR_2P2Z_1S (HSP_KER_IIR_2P2Z_1S | HSP_KER_FLT_INIT | HSP_KER_STIA_MSK)
/** IIR Lattice filter */
#define HSP_CMD_IIR_LATTICE (HSP_KER_IIR_LATTICE | HSP_KER_FLT_INIT | HSP_KER_STIA_MSK)
/** Convolution */
#define HSP_CMD_CONV        (HSP_KER_CONV | HSP_KER_IIOSS_INIT | HSP_KER_STIA_MSK)
/** Correlation */
#define HSP_CMD_CORR        (HSP_KER_CORR | HSP_KER_IIOSS_INIT | HSP_KER_STIA_MSK)
/** Window symmetric kernel */
#define HSP_CMD_WINSYM      (HSP_KER_WINSYM | HSP_KER_IIOSS_INIT | HSP_KER_STIA_MSK)
/** FLTBANK filter */
#define HSP_CMD_FLTBANK     (HSP_KER_FLTBANK | HSP_KER_FLT_INIT | HSP_KER_STIN_MSK)


/* Vector related functions */
/** Element-wise summation of a vector */
#define HSP_CMD_VEC_ADD        (HSP_KER_VEC_ADD | HSP_KER_IIOS_INIT | HSP_KER_STIA_MSK | HSP_KER_PRE_MSK)
/** Element-wise subtraction of a vector */
#define HSP_CMD_VEC_SUB        (HSP_KER_VEC_SUB | HSP_KER_IIOS_INIT | HSP_KER_STIA_MSK | HSP_KER_PRE_MSK)
/** Element-wise multiplication of a vector */
#define HSP_CMD_VEC_MUL        (HSP_KER_VEC_MUL | HSP_KER_IIOS_INIT | HSP_KER_STIA_MSK | HSP_KER_PRE_MSK)
/** Element-wise division of a vector */
#define HSP_CMD_VEC_DIV        (HSP_KER_VEC_DIV | HSP_KER_IIOS_INIT | HSP_KER_STIA_MSK | HSP_KER_PRE_MSK)
/** Element-wise square-root of a vector */
#define HSP_CMD_VEC_SQRT       (HSP_KER_VEC_SQRT | HSP_KER_IOS_INIT | HSP_KER_STI2_MSK | HSP_KER_PRE_MSK)
/** Element-wise absolute value of a vector */
#define HSP_CMD_VEC_ABS        (HSP_KER_VEC_ABS | HSP_KER_IOS_INIT | HSP_KER_STI2_MSK | HSP_KER_PRE_MSK)
/** Compute the average value of a vector */
#define HSP_CMD_VEC_AVG        (HSP_KER_VEC_AVG | HSP_KER_IOS_INIT | HSP_KER_STI2_MSK | HSP_KER_PRE_MSK)
/** Compute the RMS value of a vector */
#define HSP_CMD_VEC_RMS        (HSP_KER_VEC_RMS | HSP_KER_IOS_INIT | HSP_KER_STI2_MSK | HSP_KER_PRE_MSK)
/** Multiply each vector element by a scalar */
#define HSP_CMD_VEC_SCALE      (HSP_KER_VEC_SCALE | HSP_KER_IIOS_INIT | HSP_KER_STIA_MSK | HSP_KER_PRE_MSK)
/** Add to each vector element a scalar */
#define HSP_CMD_VEC_OFFSET     (HSP_KER_VEC_OFFSET | HSP_KER_IIOS_INIT | HSP_KER_STIA_MSK | HSP_KER_PRE_MSK)
/** Search for value and position of the absolute biggest element of a vector */
#define HSP_CMD_VEC_ABSMAX     (HSP_KER_VEC_ABSMAX | HSP_KER_IIOS_INIT | HSP_KER_STIA_MSK | HSP_KER_PRE_MSK)
/** Search for value and position of the biggest element of a vector */
#define HSP_CMD_VEC_MAX        (HSP_KER_VEC_MAX | HSP_KER_IIOS_INIT | HSP_KER_STIA_MSK | HSP_KER_PRE_MSK)
/** Search for value and position of the smallest element of a vector */
#define HSP_CMD_VEC_MIN        (HSP_KER_VEC_MIN | HSP_KER_IIOS_INIT | HSP_KER_STIA_MSK | HSP_KER_PRE_MSK)
/** Performs the copy of a vector (can be used for debug) */
#define HSP_CMD_VEC_COPY       (HSP_KER_VEC_COPY | HSP_KER_IOS_INIT | HSP_KER_STI2_MSK | HSP_KER_PRE_MSK)
/** Add kernel function pointer and parameters according to user command */
#define HSP_CMD_VEC_SET        (HSP_KER_VEC_SET | HSP_KER_IOS_INIT | HSP_KER_STI2_MSK)
/** Calculates the dot prod of the input vectors */
#define HSP_CMD_VEC_DOTPROD    (HSP_KER_VEC_DOTPROD | HSP_KER_IIOS_INIT | HSP_KER_STIA_MSK | HSP_KER_PRE_MSK)
/** Element-wise cosine value of a vector */
#define HSP_CMD_VEC_COS        (HSP_KER_VEC_COS | HSP_KER_IOS_INIT | HSP_KER_STI2_MSK | HSP_KER_PRE_MSK)
/** Element-wise sine value of a vector */
#define HSP_CMD_VEC_SIN        (HSP_KER_VEC_SIN | HSP_KER_IOS_INIT | HSP_KER_STI2_MSK | HSP_KER_PRE_MSK)
/** Element-wise sine and cosine value of a vector */
#define HSP_CMD_VEC_SINCOS     (HSP_KER_VEC_SINCOS | HSP_KER_IOS_INIT | HSP_KER_STI2_MSK | HSP_KER_PRE_MSK)
/** Element-wise float32 to integer 32bits conversion */
#define HSP_CMD_VEC_F2I        (HSP_KER_VEC_F2I | HSP_KER_IOS_INIT | HSP_KER_STI2_MSK | HSP_KER_PRE_MSK)
/** Element-wise integer 32bits to float32 conversion */
#define HSP_CMD_VEC_I2F        (HSP_KER_VEC_I2F | HSP_KER_IOS_INIT | HSP_KER_STI2_MSK | HSP_KER_PRE_MSK)
/** Element-wise integer 24bits signed to float32 conversion */
#define HSP_CMD_VEC_24S2F      (HSP_KER_VEC_24S2F | HSP_KER_IOS_INIT | HSP_KER_STI2_MSK | HSP_KER_PRE_MSK)
/** Element-wise float32 to unsigned integer 32bits conversion */
#define HSP_CMD_VEC_F2U        (HSP_KER_VEC_F2U | HSP_KER_IOS_INIT | HSP_KER_STI2_MSK | HSP_KER_PRE_MSK)
/** Element-wise unsigned integer 32bits to float32 conversion */
#define HSP_CMD_VEC_U2F        (HSP_KER_VEC_U2F | HSP_KER_IOS_INIT | HSP_KER_STI2_MSK | HSP_KER_PRE_MSK)
/** Vector decimation */
#define HSP_CMD_VEC_DECIM      (HSP_KER_VEC_DECIM | HSP_KER_IIOS_INIT | HSP_KER_STI1_MSK)
/** Vector zero insertion */
#define HSP_CMD_VEC_ZINS       (HSP_KER_VEC_ZINS | HSP_KER_IIOS_INIT | HSP_KER_STI1_MSK | HSP_KER_PRE_MSK)
/** Element-wise Atan2 computation of a vector */
#define HSP_CMD_VEC_ATAN2      (HSP_KER_VEC_ATAN2 | HSP_KER_IIOS_INIT | HSP_KER_STIA_MSK | HSP_KER_PRE_MSK)
/** Element-wise Logarithm neperien computation of a vector */
#define HSP_CMD_VEC_LN         (HSP_KER_VEC_LN | HSP_KER_IOS_INIT | HSP_KER_STI2_MSK | HSP_KER_PRE_MSK)
/** Element-wise Logarithm base 10 computation of a vector */
#define HSP_CMD_VEC_LOG10      (HSP_KER_VEC_LOG10 | HSP_KER_IOS_INIT | HSP_KER_STI2_MSK | HSP_KER_PRE_MSK)
/** Element-wise Exponential computation of a vector */
#define HSP_CMD_VEC_EXP        (HSP_KER_VEC_EXP | HSP_KER_IOS_INIT | HSP_KER_STI2_MSK | HSP_KER_PRE_MSK)
/** Element-wise Exponential base 10 computation of a vector */
#define HSP_CMD_VEC_EXP10      (HSP_KER_VEC_EXP10 | HSP_KER_IOS_INIT | HSP_KER_STI2_MSK | HSP_KER_PRE_MSK)
/** Compute the multiplication of one vector and cos ROM */
#define HSP_CMD_VEC_MUL_COS    (HSP_KER_VEC_MUL_COS | HSP_KER_IIOSS_INIT | HSP_KER_STIA_MSK | HSP_KER_PRE_MSK)
/** Compute the multiplication of one vector and sin ROM */
#define HSP_CMD_VEC_MUL_SIN    (HSP_KER_VEC_MUL_SIN | HSP_KER_IIOSS_INIT | HSP_KER_STIA_MSK | HSP_KER_PRE_MSK)
/** Multiply each vector element by an immediate scalar */
#define HSP_CMD_VEC_SCALE_I    (HSP_KER_VEC_SCALE_I | HSP_KER_IIOS_INIT | HSP_KER_STI1_MSK | HSP_KER_PRE_MSK)
/** Add to each vector element by an immediate scalar */
#define HSP_CMD_VEC_OFFSET_I   (HSP_KER_VEC_OFFSET_I | HSP_KER_IIOS_INIT | HSP_KER_STI1_MSK | HSP_KER_PRE_MSK)
/** Set each vector element with an immediate scalar */
#define HSP_CMD_VEC_SET_I      (HSP_KER_VEC_SET_I | HSP_KER_IIOS_INIT | HSP_KER_STI2_MSK | HSP_KER_PRE_MSK)
/** Element-wise float32 to Q31 conversion of a vector */
#define HSP_CMD_VEC_F2Q31      (HSP_KER_VEC_F2Q31 | HSP_KER_IOS_INIT | HSP_KER_STI2_MSK | HSP_KER_PRE_MSK)
/** Element-wise Q31 to float32 conversion of a vector */
#define HSP_CMD_VEC_Q312F      (HSP_KER_VEC_Q312F | HSP_KER_IOS_INIT | HSP_KER_STI2_MSK | HSP_KER_PRE_MSK)
/** Element-wise float32 to Q15 conversion of a vector */
#define HSP_CMD_VEC_F2Q15      (HSP_KER_VEC_F2Q15 | HSP_KER_IOS_INIT | HSP_KER_STI2_MSK | HSP_KER_PRE_MSK)
/** Element-wise Q15 to float32 conversion of a vector */
#define HSP_CMD_VEC_Q152F      (HSP_KER_VEC_Q152F | HSP_KER_IOS_INIT | HSP_KER_STI2_MSK | HSP_KER_PRE_MSK)

/* Scalar related functions */
/** Absolute value of an element */
#define HSP_CMD_SCA_ABS      (HSP_KER_SCA_ABS | HSP_KER_IO_INIT | HSP_KER_STI2_MSK)
/** Scalar addition */
#define HSP_CMD_SCA_ADD      (HSP_KER_SCA_ADD | HSP_KER_IIO_INIT | HSP_KER_STIA_MSK)
/** Scalar atan2 */
#define HSP_CMD_SCA_ATAN2    (HSP_KER_SCA_ATAN2 | HSP_KER_IIO_INIT | HSP_KER_STIA_MSK)
/** Scalar cosinus */
#define HSP_CMD_SCA_COS      (HSP_KER_SCA_COS | HSP_KER_IO_INIT | HSP_KER_STI2_MSK)
/** Scalar division */
#define HSP_CMD_SCA_DIV      (HSP_KER_SCA_DIV | HSP_KER_IIO_INIT | HSP_KER_STIA_MSK)
/** Scalar exponential neperien */
#define HSP_CMD_SCA_EXP      (HSP_KER_SCA_EXP | HSP_KER_IO_INIT | HSP_KER_STI2_MSK)
/** Scalar exponential base 10 */
#define HSP_CMD_SCA_EXP10    (HSP_KER_SCA_EXP10 | HSP_KER_IO_INIT | HSP_KER_STI2_MSK)
/** Scalar float32 to integer 32bits conversion */
#define HSP_CMD_SCA_F2I      (HSP_KER_SCA_F2I | HSP_KER_IO_INIT | HSP_KER_STI2_MSK)
/** Scalar integer 32bits to float32 conversion */
#define HSP_CMD_SCA_I2F      (HSP_KER_SCA_I2F | HSP_KER_IO_INIT | HSP_KER_STI2_MSK)
/** Scalar integer 24bits signed to float32 conversion */
#define HSP_CMD_SCA_24S2F    (HSP_KER_SCA_24S2F | HSP_KER_IO_INIT | HSP_KER_STI2_MSK)
/** Scalar float32 to unsigned integer 32bits conversion */
#define HSP_CMD_SCA_F2U      (HSP_KER_SCA_F2U | HSP_KER_IO_INIT | HSP_KER_STI2_MSK)
/** Scalar unsigned integer 32bits to float32 conversion */
#define HSP_CMD_SCA_U2F      (HSP_KER_SCA_U2F | HSP_KER_IO_INIT | HSP_KER_STI2_MSK)
/** Scalar float32 to Q31 conversion */
#define HSP_CMD_SCA_F2Q31    (HSP_KER_SCA_F2Q31 | HSP_KER_IO_INIT | HSP_KER_STI2_MSK)
/** Scalar Q31 to float32 conversion */
#define HSP_CMD_SCA_Q312F    (HSP_KER_SCA_Q312F | HSP_KER_IO_INIT | HSP_KER_STI2_MSK)
/** Scalar logarithm neperien */
#define HSP_CMD_SCA_LN       (HSP_KER_SCA_LN | HSP_KER_IO_INIT | HSP_KER_STI2_MSK)
/** Scalar logarithm base 10 */
#define HSP_CMD_SCA_LOG10    (HSP_KER_SCA_LOG10 | HSP_KER_IO_INIT | HSP_KER_STI2_MSK)
/** Scalar multiplication */
#define HSP_CMD_SCA_MUL      (HSP_KER_SCA_MUL | HSP_KER_IIO_INIT | HSP_KER_STIA_MSK)
/** Saturation of an element to a given value */
#define HSP_CMD_SCA_SAT      (HSP_KER_SCA_SAT | HSP_KER_IIO_INIT | HSP_KER_STIA_MSK)
/** Scalar Sinus */
#define HSP_CMD_SCA_SIN      (HSP_KER_SCA_SIN | HSP_KER_IO_INIT | HSP_KER_STI2_MSK)
/** Scalar Sinus and Cosinus */
#define HSP_CMD_SCA_SINCOS   (HSP_KER_SCA_SINCOS | HSP_KER_IO_INIT | HSP_KER_STI2_MSK)
/** Scalar set */
#define HSP_CMD_SCA_SET      (HSP_KER_SCA_SET | HSP_KER_IO_INIT | HSP_KER_STI2_MSK)
/** Square-root of an element */
#define HSP_CMD_SCA_SQRT     (HSP_KER_SCA_SQRT | HSP_KER_IO_INIT | HSP_KER_STI2_MSK)
/** Scalar subtraction */
#define HSP_CMD_SCA_SUB      (HSP_KER_SCA_SUB | HSP_KER_IIO_INIT | HSP_KER_STIA_MSK)
/** Scalar Clarke transform (#hyp_sca_clarke) */
#define HSP_CMD_SCA_CLARKE   (HSP_KER_SCA_CLARKE | HSP_KER_IO_INIT | HSP_KER_STI2_MSK)
/** Scalar Park transform (#hyp_sca_park) */
#define HSP_CMD_SCA_PARK     (HSP_KER_SCA_PARK | HSP_KER_IIO_INIT | HSP_KER_STIA_MSK)
/** Scalar Iclarke transform (#hyp_sca_iclarke) */
#define HSP_CMD_SCA_ICLARKE  (HSP_KER_SCA_ICLARKE | HSP_KER_IO_INIT | HSP_KER_STI2_MSK)
/** Scalar IPark transform (#hyp_sca_ipark) */
#define HSP_CMD_SCA_IPARK    (HSP_KER_SCA_IPARK | HSP_KER_IIO_INIT | HSP_KER_STIA_MSK)
/** Scalar PID */
#define HSP_CMD_SCA_PID      (HSP_KER_SCA_PID | HSP_KER_IIIOSS_INIT | HSP_KER_STIA_MSK)
/** Scalar fast Cosinus */
#define HSP_CMD_SCA_FCOS     (HSP_KER_SCA_FCOS | HSP_KER_IO_INIT | HSP_KER_STI2_MSK)
/** Scalar fast Sinus */
#define HSP_CMD_SCA_FSIN     (HSP_KER_SCA_FSIN | HSP_KER_IO_INIT | HSP_KER_STI2_MSK)
/** Scalar fast FAtan2 */
#define HSP_CMD_SCA_FATAN2   (HSP_KER_SCA_FATAN2 | HSP_KER_IIO_INIT | HSP_KER_STIA_MSK)

/* Matrix related functions */
/** Multiplication of two matrix */
#define HSP_CMD_MAT_MUL     (HSP_KER_MAT_MUL | HSP_MAT_IIO_INIT | HSP_KER_STIA_MSK)
/** Transposition of a matrix */
#define HSP_CMD_MAT_TRANS   (HSP_KER_MAT_TRANS | HSP_MAT_IIO_INIT | HSP_KER_STIA_MSK)
/** Matrix inversion */
#define HSP_CMD_MAT_INV     (HSP_KER_MAT_INV | HSP_MAT_IIO_INIT | HSP_KER_STIA_MSK)
/** Matrix to column vector kernel copy */
#define HSP_CMD_M2V         (HSP_KER_M2V | HSP_MAT_CONV_INIT | HSP_KER_STIA_MSK)
/** Vector to column matrix kernel copy */
#define HSP_CMD_V2M         (HSP_KER_V2M | HSP_MAT_CONV_INIT | HSP_KER_STIA_MSK | HSP_KER_PRE_MSK)

/* Transformation related funcons */
/** Performs the complex fast Fourier transform of an input vector */
#define HSP_CMD_FFT   (HSP_KER_FFT | HSP_KER_FFT_INIT | HSP_KER_STIN_MSK)
/** Performs the real fast Fourier transform of an input vector */
#define HSP_CMD_RFFT  (HSP_KER_RFFT | HSP_KER_FFT_INIT | HSP_KER_STIN_MSK)
/** Performs the discrete cosine transform of an input vector */
#define HSP_CMD_DCT   (HSP_KER_DCT | HSP_KER_FFT_INIT | HSP_KER_STIN_MSK)
/** Performs the inverse discrete cosine transform of an input vector */
#define HSP_CMD_IDCT  (HSP_KER_IDCT | HSP_KER_FFT_INIT | HSP_KER_STIN_MSK)

/* Complex functions */
/** Compute the conjugate of each vector element */
#define HSP_CMD_CMPLX_CONJ       (HSP_KER_CMPLX_CONJ | HSP_KER_IOS_INIT | HSP_KER_STI2_MSK | HSP_KER_PRE_MSK)
/** Computes the dot product of two complex vectors */
#define HSP_CMD_CMPLX_DOTPROD    (HSP_KER_CMPLX_DOTPROD | HSP_KER_IIOS_INIT | HSP_KER_STIA_MSK | HSP_KER_PRE_MSK)
/** Vector Floating-point complex magnitude */
#define HSP_CMD_CMPLX_MAG        (HSP_KER_CMPLX_MAG | HSP_KER_IOS_INIT | HSP_KER_STI2_MSK | HSP_KER_PRE_MSK)
/** Vector Floating-point complex magnitude squared */
#define HSP_CMD_CMPLX_MAGSQUARED (HSP_KER_CMPLX_MAGSQUARED | HSP_KER_IOS_INIT | HSP_KER_STI2_MSK | HSP_KER_PRE_MSK)
/** Compute the complex multiplication of 2 complex vector */
#define HSP_CMD_CMPLX_MUL        (HSP_KER_CMPLX_MUL | HSP_KER_IIOS_INIT | HSP_KER_STIA_MSK | HSP_KER_PRE_MSK)
/** Compute the multiplication of a complex vector by a real vector and generates a complex result */
#define HSP_CMD_CMPLX_RMUL       (HSP_KER_CMPLX_RMUL | HSP_KER_IIOS_INIT |  HSP_KER_STIA_MSK |  HSP_KER_PRE_MSK)
/** Compute the complex multiplication of one complex vector and exp ROM */
#define HSP_CMD_CMPLX_MUL_EXP    (HSP_KER_CMPLX_MUL_EXP | HSP_KER_IIOSS_INIT | HSP_KER_STIA_MSK | HSP_KER_PRE_MSK)

/* Counter function */
/** Global counter kernel (use DRAM counter in order to use HSP_CMD_IFE_CNT) */
#define HSP_CMD_COUNT (HSP_KER_CNT | HSP_KER_IO_INIT)

/* CRC function */
/** CRC32 calculation */
#define HSP_CMD_CRC32 (HSP_KER_CRC32 | HSP_KER_IIIOSS_INIT | HSP_KER_STIA_MSK)

/* Integer functions */
/** Integer scalar addition with constant */
#define HSP_CMD_INT32_ADD_I    (HSP_INT32_ADD_I | HSP_KER_IIO_INIT | HSP_KER_STI1_MSK)
/** Integer scalar multiplication with constant */
#define HSP_CMD_INT32_MUL_I    (HSP_INT32_MUL_I | HSP_KER_IIO_INIT | HSP_KER_STI1_MSK)

/* Comparison functions */
/** if kernel comparison */
#define HSP_CMD_IFE      (HSP_KER_IFE | HSP_KER_IFE_INIT | HSP_KER_STIN_MSK)
/** if kernel comparison */
#define HSP_CMD_IFE_LOOP (HSP_KER_IFE_LOOP | HSP_KER_IFE_INIT | HSP_KER_STIN_MSK)
/** if kernel comparison for global counters */
#define HSP_CMD_IFE_CNT  (HSP_KER_IFE_CNT | HSP_KER_IFE_INIT | HSP_KER_STIN_MSK)

/* Loop function */
/** loop kernel comparison */
#define HSP_CMD_LOOP (HSP_KER_LOOP | HSP_KER_LOOP_INIT | HSP_KER_STIN_MSK)

/* Kernels with conditional event and flag generation */
/** Comparison of an input vector to two thresholds (LOTH, HITH) with branch option */
#define HSP_CMD_CMPB      (HSP_KER_CMPB | HSP_KER_COND_INIT | HSP_KER_STIN_MSK)
/** Comparison of an input vector to two thresholds (LOTH, HITH) with branch option */
#define HSP_CMD_CMPCNT    (HSP_KER_CMPCNT | HSP_KER_COND_INIT | HSP_KER_STIN_MSK)
/** Performs a linear Ramp-up or Ramp-down */
#define HSP_CMD_RAMP      (HSP_KER_RAMP | HSP_KER_COND_INIT | HSP_KER_STIN_MSK)
/** Performs a linear Ramp-up or Ramp-down */
#define HSP_CMD_SCA2VECT  (HSP_KER_SCA2VECT | HSP_KER_COND_INIT | HSP_KER_STIN_MSK)
/** Perform a saturation to each vector element, using a programmable value */
#define HSP_CMD_SAT       (HSP_KER_SAT | HSP_KER_COND_INIT | HSP_KER_STIN_MSK)
/** Checks the content of a bit field to a reference value and activates PL */
#define HSP_CMD_CHK_BITS  (HSP_KER_CHK_BITS | HSP_KER_COND_INIT | HSP_KER_STIN_MSK)
/** Set the specified bitfield of a scalar to the specified value */
#define HSP_CMD_SET_BITS  (HSP_KER_SET_BITS | HSP_KER_REG_INIT | HSP_KER_STI1_MSK)
/** Set the GPO bitfield */
#define HSP_CMD_SET_GPO   (HSP_KER_SET_GPO | HSP_KER_REG_INIT | HSP_KER_STIN_MSK)
/** Checks the content of a bit field to a reference value and waits until the condition */
#define HSP_CMD_WAIT_COND (HSP_KER_WAIT_COND | HSP_KER_REG_INIT | HSP_KER_STI1_MSK)


/* Memory transfer related functions */
/** Send event */
#define HSP_CMD_SEND_EVT (HSP_KER_SEND_EVT | HSP_KER_VAL_INIT)
/** Set KERF flag */
#define HSP_CMD_SET_FLAG (HSP_KER_SET_FLAG | HSP_KER_VAL_INIT)
/** TRGO kernel: generate a trigger pulse on one of the hsp_trg_out */
#define HSP_CMD_SET_TRGO (HSP_KER_SET_TRGO | HSP_KER_VAL_INIT)

/**
  * @}
  */

/** @defgroup HSP_DCommand_Constants HSP Direct Command Constants
  * @{
  */

/* Filter related functions */
/** FIR filter */
#define HSP_DIRECT_CMD_FIR                 ((HSP_DC_START + ((HSP_KER_FIR) * 2)) * 4)
/** FIR filter */
#define HSP_DIRECT_CMD_FIR_LESS7TAPS       ((HSP_DC_START + ((HSP_KER_FIR_LESS7TAPS) * 2)) * 4)
/** FIR filter */
#define HSP_DIRECT_CMD_FIR_MODULO4TAPS     ((HSP_DC_START + ((HSP_KER_FIR_MODULO4TAPS) * 2)) * 4)
/** FIR filter */
#define HSP_DIRECT_CMD_FIR_1SAMPLE         ((HSP_DC_START + ((HSP_KER_FIR_1SAMPLE) * 2)) * 4)
/** FIR filter, with decimation */
#define HSP_DIRECT_CMD_FIRDEC              ((HSP_DC_START + ((HSP_KER_FIRDEC) * 2)) * 4)
/** FIR filter, with decimation */
#define HSP_DIRECT_CMD_FIRDEC_1TAP         ((HSP_DC_START + ((HSP_KER_FIRDEC_1TAP) * 2)) * 4)
/** FIR filter, with decimation */
#define HSP_DIRECT_CMD_FIRDEC_SPEC         ((HSP_DC_START + ((HSP_KER_FIRDEC_SPEC) * 2)) * 4)
/** FIR filter, with adaptive LMS algorithm. */
#define HSP_DIRECT_CMD_LMS                 ((HSP_DC_START + ((HSP_KER_LMS) * 2)) * 4)
/** IIR biquad cascade DF1 filter */
#define HSP_DIRECT_CMD_BIQUAD_CASCADE_DF1  ((HSP_DC_START + ((HSP_KER_BQ_CAS_DF1) * 2)) * 4)
/** IIR biquad cascade DF2T filter */
#define HSP_DIRECT_CMD_BIQUAD_CASCADE_DF2T ((HSP_DC_START + ((HSP_KER_BQ_CAS_DF2T) * 2)) * 4)
/** IIR DF1 filter */
#define HSP_DIRECT_CMD_IIR_DF1             ((HSP_DC_START + ((HSP_KER_IIR_DF1) * 2)) * 4)
/** Only define to generate FW error. IIR 3p3z for 1 sample filter */
#define HSP_DIRECT_CMD_IIR_3P3Z_1S         ((HSP_DC_START + ((HSP_KER_IIR_3P3Z_1S) * 2)) * 4)
/** Only define to generate FW error. IIR 2p2z for 1 sample filter */
#define HSP_DIRECT_CMD_IIR_2P2Z_1S         ((HSP_DC_START + ((HSP_KER_IIR_2P2Z_1S) * 2)) * 4)
/** IIR Lattice */
#define HSP_DIRECT_CMD_IIR_LATTICE         ((HSP_DC_START + ((HSP_KER_IIR_LATTICE) * 2)) * 4)
/** Convolution */
#define HSP_DIRECT_CMD_CONV                ((HSP_DC_START + ((HSP_KER_CONV) * 2)) * 4)
/** Correlation */
#define HSP_DIRECT_CMD_CORR                ((HSP_DC_START + ((HSP_KER_CORR) * 2)) * 4)
/** FLTBANK filter */
#define HSP_DIRECT_CMD_FLTBANK             ((HSP_DC_START + ((HSP_KER_FLTBANK) * 2)) * 4)
/** FLTBANK filter with external coeffs */
#define HSP_DIRECT_CMD_FLTBANK_EXTC        ((HSP_DC_START + ((HSP_KER_FLTBANK_EXTC) * 2)) * 4)

/* State buffer functions */
/** Reset filter state */
#define HSP_DIRECT_CMD_RESET_STATE       ((HSP_DC_START + ((HSP_RESET_STATE) * 2)) * 4)
/** Set circular filter state from right to left */
#define HSP_DIRECT_CMD_SET_STATE_CR2L    ((HSP_DC_START + ((HSP_SET_STATE_CR2L) * 2)) * 4)
/** Set circular filter state from left to right */
#define HSP_DIRECT_CMD_SET_STATE_CL2R    ((HSP_DC_START + ((HSP_SET_STATE_CL2) * 2)) * 4)
/** Set linear filter state from left to right */
#define HSP_DIRECT_CMD_SET_STATE_L2R     ((HSP_DC_START + ((HSP_SET_STATE_L2R) * 2)) * 4)
/** Get circular filter state from right to left */
#define HSP_DIRECT_CMD_GET_STATE_CR2L    ((HSP_DC_START + ((HSP_GET_STATE_CR2L) * 2)) * 4)
/** Get circular filter state from left to right */
#define HSP_DIRECT_CMD_GET_STATE_CL2R    ((HSP_DC_START + ((HSP_GET_STATE_CL2)* 2)) * 4)
/** Get linear filter state from left to right */
#define HSP_DIRECT_CMD_GET_STATE_L2R     ((HSP_DC_START + ((HSP_GET_STATE_L2R) * 2)) * 4)

/* Vector related functions */
/** Element-wise summation of a vector */
#define HSP_DIRECT_CMD_VEC_ADD        ((HSP_DC_START + ((HSP_KER_VEC_ADD) * 2)) * 4)
/** Element-wise subtraction of a vector */
#define HSP_DIRECT_CMD_VEC_SUB        ((HSP_DC_START + ((HSP_KER_VEC_SUB) * 2)) * 4)
/** Element-wise multiplication of a vector */
#define HSP_DIRECT_CMD_VEC_MUL        ((HSP_DC_START + ((HSP_KER_VEC_MUL) * 2)) * 4)
/** Element-wise division of a vector */
#define HSP_DIRECT_CMD_VEC_DIV        ((HSP_DC_START + ((HSP_KER_VEC_DIV) * 2)) * 4)
/** Calculates the sum of the */
#define HSP_DIRECT_CMD_VEC_SQRT       ((HSP_DC_START + ((HSP_KER_VEC_SQRT) * 2)) * 4)
/** Element-wise absolute value of a vector */
#define HSP_DIRECT_CMD_VEC_ABS        ((HSP_DC_START + ((HSP_KER_VEC_ABS) * 2)) * 4)
/** Compute the average value of a vector */
#define HSP_DIRECT_CMD_VEC_AVG        ((HSP_DC_START + ((HSP_KER_VEC_AVG) * 2)) * 4)
/** Compute the RMS value of a vector */
#define HSP_DIRECT_CMD_VEC_RMS        ((HSP_DC_START + ((HSP_KER_VEC_RMS) * 2)) * 4)
/** Multiply each vector element by a scalar */
#define HSP_DIRECT_CMD_VEC_SCALE      ((HSP_DC_START + ((HSP_KER_VEC_SCALE) * 2)) * 4)
/** Add to each vector element a scalar */
#define HSP_DIRECT_CMD_VEC_OFFSET     ((HSP_DC_START + ((HSP_KER_VEC_OFFSET) * 2)) * 4)
/** Search for value and position of the biggest element of a vector */
#define HSP_DIRECT_CMD_VEC_ABSMAX     ((HSP_DC_START + ((HSP_KER_VEC_ABSMAX) * 2)) * 4)
/** Search for value and position of the biggest element of a vector */
#define HSP_DIRECT_CMD_VEC_MAX        ((HSP_DC_START + ((HSP_KER_VEC_MAX) * 2)) * 4)
/** Search for value and position of the smallest element of a vector */
#define HSP_DIRECT_CMD_VEC_MIN        ((HSP_DC_START + ((HSP_KER_VEC_MIN) * 2)) * 4)
/** Performs the copy of a vector (can be used for debug) */
#define HSP_DIRECT_CMD_VEC_COPY       ((HSP_DC_START + ((HSP_KER_VEC_COPY) * 2)) * 4)
/** Add kernel function pointer and parameters according to user command */
#define HSP_DIRECT_CMD_VEC_SET        ((HSP_DC_START + ((HSP_KER_VEC_SET) * 2)) * 4)
/** Calculates the dot prod of the input vectors */
#define HSP_DIRECT_CMD_VEC_DOTPROD    ((HSP_DC_START + ((HSP_KER_VEC_DOTPROD) * 2)) * 4)
/** Element-wise cosine value of a vector */
#define HSP_DIRECT_CMD_VEC_COS        ((HSP_DC_START + ((HSP_KER_VEC_COS) * 2)) * 4)
/** Element-wise sine value of a vector */
#define HSP_DIRECT_CMD_VEC_SIN        ((HSP_DC_START + ((HSP_KER_VEC_SIN) * 2)) * 4)
/** Element-wise sine cosine value of a vector */
#define HSP_DIRECT_CMD_VEC_SINCOS     ((HSP_DC_START + ((HSP_KER_VEC_SINCOS) * 2)) * 4)
/** Element-wise float32 to integer 32bits conversion */
#define HSP_DIRECT_CMD_VEC_F2I        ((HSP_DC_START + ((HSP_KER_VEC_F2I) * 2)) * 4)
/** Element-wise integer 32bits to float32 conversion */
#define HSP_DIRECT_CMD_VEC_I2F        ((HSP_DC_START + ((HSP_KER_VEC_I2F) * 2)) * 4)
/** Element-wise integer 24bits signed to float32 conversion */
#define HSP_DIRECT_CMD_VEC_24S2F      ((HSP_DC_START + ((HSP_KER_VEC_24S2F) * 2)) * 4)
/** Element-wise float32 to unsigned integer 32bits conversion */
#define HSP_DIRECT_CMD_VEC_F2U        ((HSP_DC_START + ((HSP_KER_VEC_F2U) * 2)) * 4)
/** Element-wise unsigned integer 32bits to float32 conversion */
#define HSP_DIRECT_CMD_VEC_U2F        ((HSP_DC_START + ((HSP_KER_VEC_U2F) * 2)) * 4)
/** Decimation */
#define HSP_DIRECT_CMD_VEC_DECIM      ((HSP_DC_START + ((HSP_KER_VEC_DECIM) * 2)) * 4)
/** Zero insertion */
#define HSP_DIRECT_CMD_VEC_ZINS       ((HSP_DC_START + ((HSP_KER_VEC_ZINS) * 2)) * 4)
/** Atan2 computation */
#define HSP_DIRECT_CMD_VEC_ATAN2      ((HSP_DC_START + ((HSP_KER_VEC_ATAN2) * 2)) * 4)
/** Logarithm neperien computation */
#define HSP_DIRECT_CMD_VEC_LN         ((HSP_DC_START + ((HSP_KER_VEC_LN) * 2)) * 4)
/** Logarithm base 10 computation */
#define HSP_DIRECT_CMD_VEC_LOG10      ((HSP_DC_START + ((HSP_KER_VEC_LOG10) * 2)) * 4)
/** Exponential computation */
#define HSP_DIRECT_CMD_VEC_EXP        ((HSP_DC_START + ((HSP_KER_VEC_EXP) * 2)) * 4)
/** Exponential base 10 computation */
#define HSP_DIRECT_CMD_VEC_EXP10      ((HSP_DC_START + ((HSP_KER_VEC_EXP10) * 2)) * 4)
/** Compute the multiplication of one vector and cos ROM */
#define HSP_DIRECT_CMD_VEC_MUL_COS    ((HSP_DC_START + ((HSP_KER_VEC_MUL_COS) * 2)) * 4)
/** Compute the multiplication of one vector and sin ROM */
#define HSP_DIRECT_CMD_VEC_MUL_SIN    ((HSP_DC_START + ((HSP_KER_VEC_MUL_SIN) * 2)) * 4)
/** Multiply each vector element by a scalar */
#define HSP_DIRECT_CMD_VEC_SCALE_I    ((HSP_DC_START + ((HSP_KER_VEC_SCALE_I) * 2)) * 4)
/** Add to each vector element a scalar */
#define HSP_DIRECT_CMD_VEC_OFFSET_I   ((HSP_DC_START + ((HSP_KER_VEC_OFFSET_I) * 2)) * 4)
/** Set each vector element with an immediate scalar */
#define HSP_DIRECT_CMD_VEC_SET_I      ((HSP_DC_START + ((HSP_KER_VEC_SET_I) * 2)) * 4)
/** Element-wise float32 to Q31 conversion */
#define HSP_DIRECT_CMD_VEC_F2Q31      ((HSP_DC_START + ((HSP_KER_VEC_F2Q31) * 2)) * 4)
/** Element-wise Q31 to float32 conversion */
#define HSP_DIRECT_CMD_VEC_Q312F      ((HSP_DC_START + ((HSP_KER_VEC_Q312F) * 2)) * 4)
/** Element-wise float32 to Q15 conversion */
#define HSP_DIRECT_CMD_VEC_F2Q15      ((HSP_DC_START + ((HSP_KER_VEC_F2Q15) * 2)) * 4)
/** Element-wise Q15 to float32 conversion */
#define HSP_DIRECT_CMD_VEC_Q152F      ((HSP_DC_START + ((HSP_KER_VEC_Q152F) * 2)) * 4)

/* Matrix related functions */
/** Multiplication of two matrix */
#define HSP_DIRECT_CMD_MAT_MUL         ((HSP_DC_START  + ((HSP_KER_MAT_MUL) * 2)) * 4)
/** Transposition of a matrix */
#define HSP_DIRECT_CMD_MAT_TRANS       ((HSP_DC_START  + ((HSP_KER_MAT_TRANS) * 2)) * 4)
/** Matrix inversion */
#define HSP_DIRECT_CMD_MAT_INV         ((HSP_DC_START + ((HSP_KER_MAT_INV) * 2)) * 4)

/* Transformation related funcons */
/** Performs the fast Fourier transform of an input vector */
#define HSP_DIRECT_CMD_FFT             ((HSP_DC_START  + ((HSP_KER_FFT) * 2)) * 4)
/** Performs the fast Fourier transform of an input vector */
#define HSP_DIRECT_CMD_RFFT            ((HSP_DC_START  + ((HSP_KER_RFFT) * 2)) * 4)
/** Performs the discrete cosine transform of an input vector */
#define HSP_DIRECT_CMD_DCT             ((HSP_DC_START  + ((HSP_KER_DCT) * 2)) * 4)
/** Performs the inverse discrete cosine transform of an input vector */
#define HSP_DIRECT_CMD_IDCT            ((HSP_DC_START  + ((HSP_KER_IDCT) * 2)) * 4)

/* Complex functions */
/** Compute the conjugate of each vector element */
#define HSP_DIRECT_CMD_CMPLX_CONJ          ((HSP_DC_START + ((HSP_KER_CMPLX_CONJ) * 2)) * 4)
/** Computes the dot product of two complex vectors */
#define HSP_DIRECT_CMD_CMPLX_DOTPROD       ((HSP_DC_START + ((HSP_KER_CMPLX_DOTPROD) * 2)) * 4)
/** Vector Floating-point complex magnitude */
#define HSP_DIRECT_CMD_CMPLX_MAG           ((HSP_DC_START + ((HSP_KER_CMPLX_MAG) * 2)) * 4)
/** Vector Floating-point complex magnitude squared */
#define HSP_DIRECT_CMD_CMPLX_MAGSQUARED    ((HSP_DC_START + ((HSP_KER_CMPLX_MAGSQUARED) * 2)) * 4)
/** Compute the complex multiplication of 2 complex vector */
#define HSP_DIRECT_CMD_CMPLX_MUL           ((HSP_DC_START + ((HSP_KER_CMPLX_MUL) * 2)) * 4)
/** Compute the multiplication of a complex vector by a real vector and generates a complex result */
#define HSP_DIRECT_CMD_CMPLX_RMUL          ((HSP_DC_START + ((HSP_KER_CMPLX_RMUL) * 2)) * 4)
/** Compute the complex multiplication of one complex vector and exp ROM */
#define HSP_DIRECT_CMD_CMPLX_MUL_EXP       ((HSP_DC_START + ((HSP_KER_CMPLX_MUL_EXP) * 2)) * 4)
/** Compute the dot product of two complex vectors */
#define HSP_DIRECT_CMD_CMPLX_CMSIS_DOTPROD ((HSP_DC_START + ((HSP_KER_CMPLX_CMSIS_DOTPROD) * 2)) * 4)


/* Counter function */
/** Direct Global counter kernel to set counter value */
#define HSP_DIRECT_CMD_COUNT ((HSP_DC_START + ((HSP_KER_CNT) * 2)) * 4)

/* CRC32 function */
/** CRC32 */
#define HSP_DIRECT_CMD_CRC32  ((HSP_DC_START + ((HSP_KER_CRC32) * 2)) * 4)

/* Clear FWERR register function */
/** Clear FWERR register */
#define HSP_DIRECT_CMD_CLR_FWERR  ((HSP_DC_START + ((HSP_CLR_FWERR) * 2)) * 4)

/* Convolution function */
/** CNN conv 2D kernel */
#define HSP_DIRECT_CMD_CNN_CONV2D  ((HSP_DC_START + ((HSP_CNN_CONV2D) * 2)) * 4)
/** CNN conv deptwise kernel */
#define HSP_DIRECT_CMD_CNN_CONVDW  ((HSP_DC_START + ((HSP_CNN_CONVDW) * 2)) * 4)
/** CNN conv pointwise kernel */
#define HSP_DIRECT_CMD_CNN_CONVPW  ((HSP_DC_START + ((HSP_CNN_CONVPW) * 2)) * 4)
/** CNN conv fully connected kernel */
#define HSP_DIRECT_CMD_CNN_FC      ((HSP_DC_START + ((HSP_CNN_FC) * 2)) * 4)
/** CNN pooling kernel */
#define HSP_DIRECT_CMD_CNN_POOL    ((HSP_DC_START + ((HSP_CNN_POOL) * 2)) * 4)
/** Copy of a vector from MEMB to MEMA kernel */
#define HSP_DIRECT_CMD_MB2A        ((HSP_DC_START + ((HSP_VECT_MB2A) * 2)) * 4)
/* End direct commands */
/**
  * @}
  */

/** @defgroup HSP_Command_Fields_Constants HSP Command Fields Constants
  * @brief    HSP command fields description\n
  * @{
  */
/* plugin functions */
/** DRAM Kernel table size */
#define HSP_NB_DRAM_KERNELS_SIZE (HSP_NB_DRAM_KERNELS*2)
/** Define for Plug ID start offset */
#define HSP_DIRECT_CMD_PLUG_ID_OFFSET ((HSP_DC_START + (HSP_NB_DRAM_KERNELS_SIZE + 1)) * 4)
#define HSP_DIRECT_CMD_PLUG_ID_SCALE 12 /**< Direct command for plugin scaling factor for DC ID */

#define HSP_CNN_CFG_MODE_MASK    0x0000000f  /**< mask for convolution mode */
#define HSP_CNN_CFG_NB_LINE_MASK 0x00003fff  /**< mask for in/out nb line */
#define HSP_CNN_CFG_NB_IN_LINE_SHIFT  4  /**< Shift for nb input lines in buffer */
#define HSP_CNN_CFG_NB_OU_LINE_SHIFT  18 /**< Shift for nb output lines in buffer */
#define HSP_CNN_CFG_MODE_0STEP        0  /**< Mode 0 step for conv */
#define HSP_CNN_CFG_MODE_1STEP        1  /**< Mode 1 step for conv */
#define HSP_CNN_CFG_MODE_2STEP        2  /**< Mode 2 steps for conv */
#define HSP_CNN_CFG_MODE_3STEP        4  /**< Mode 3 steps for conv */
#define HSP_CNN_CFG_MODE_PCIRC        1  /**< Circular mode for pooling */
#define HSP_CNN_CFG_MODE_FCPP         1  /**< Ping pong mode for fully connected */

/* IOTYPE for pointer on pointer */
#define HSP_IOTYPE_POP  0x70 /**< One of parameter pointer is a pointer on pointer */
#define HSP_IOTYPE_POP0 0x10 /**< First pointer address is a pointer on pointer */
#define HSP_IOTYPE_POP1 0x20 /**< Second pointer address is a pointer on pointer */
#define HSP_IOTYPE_POP2 0x40 /**< Third pointer address is a pointer on pointer */


#ifndef __HSP_DMA__
/* TBR, should use ipxact define for reset value */
#define HSP_HWCFGR1_RESET_VAL         0x140C0020
#define HSP_HWCFGR1_RESET_MSK         0xFFFFFFFF
#endif /* __HSP_DMA__ */

/* BUFFx registers offset addresses */
#define HSP_REG_SPE_BUFF0DR           0x002010F8
#define HSP_REG_SPE_BUFF1DR           0x002010FC
#define HSP_REG_SPE_BUFF2DR           0x00201100
#define HSP_REG_SPE_BUFF3DR           0x00201104

/**
  * @}
  */

/** @defgroup HSP_BSTAT_Constants HSP State Constants
  * @brief    HSP State constant description\n
  * @{
  */
#ifndef HSP_SPE_CR_BSTAT_Pos
/** Define BSTAT position if not yet defined */
#define HSP_SPE_CR_BSTAT_Pos HSP_CR_BSTAT_Pos
#endif  /* HSP_SPE_CR_BSTAT_Pos */

#define HSP_BSTAT_RESETV   (0x0 << HSP_SPE_CR_BSTAT_Pos) /**< RESETV state: reset value */
#define HSP_BSTAT_BOOTOK   (0x1 << HSP_SPE_CR_BSTAT_Pos) /**< BOOTOK state: wait for init command */
#define HSP_BSTAT_WAICMD   (0x2 << HSP_SPE_CR_BSTAT_Pos) /**< WAICMD state: wait for first command */
#define HSP_BSTAT_PROCFG   (0x3 << HSP_SPE_CR_BSTAT_Pos) /**< PROCFG state: processing list configuration */
#define HSP_BSTAT_RST_PL   (0x4 << HSP_SPE_CR_BSTAT_Pos) /**< Reset PL: reset all Processing list */
#define HSP_BSTAT_ERROR    (0x6 << HSP_SPE_CR_BSTAT_Pos) /**< Bad init command */
#define HSP_BSTAT_ADD_PG   (0x7 << HSP_SPE_CR_BSTAT_Pos) /**< Add plugin */
#define HSP_BSTAT_ERR_CROM (0x8 << HSP_SPE_CR_BSTAT_Pos) /**< CROM ID error, not in lign with CRAM */

/**
  * @}
  */

/** @defgroup HSP_EVENT_Constants HSP Event Constants
  * @{
  */
/** Event to switch in supervisor mode */
#define HSP_EVENT_SUPERVISOR 37

/** Event to switch in direct command */
#define HSP_EVENT_DIRECT_COMMAND 38
/**
  * @}
  */

/** @defgroup HSP_COND_Constants HSP Conditional Constants
  * @{
  */
/** Type for data type of variable condition for conditional command */
#define HSP_COND_TYPE_UINT32 1 /**< 32 bit unsigned integer */
#define HSP_COND_TYPE_INT32  2 /**< 32 bit signed integer */
#define HSP_COND_TYPE_FLOAT  3 /**< 32 bit float */
#define HSP_COND_TYPE_CONSTANT_UINT32 ((0x1 << 2)| HSP_COND_TYPE_UINT32) /**< 32 bit unsigned int immediate value */
#define HSP_COND_TYPE_CONSTANT_INT32  ((0x1 << 2) | HSP_COND_TYPE_INT32) /**< 32 bit signed int immediate value */
#define HSP_COND_TYPE_CONSTANT_FLOAT  ((0x1 << 2) | HSP_COND_TYPE_FLOAT) /**< 32 bit float immediate value */

/**
  * @}
  */
/**
  * @}
  */
/* End of private constants --------------------------------------------------*/

/** @addtogroup HSP_Exported_Constants
  * @{
  */
/** @addtogroup HSP_Transform_Constants HSP Transform Constants
  * @{
  */
#define HAL_HSP_FFT_COMPLEX   0  /**< CFFT: identify a complex FFT */
#define HAL_HSP_RFFT_TYPE_1   1  /**< RFFT: identify a real FFT with out[0]=in[0]+in[1] and out[1]=0 */
#define HAL_HSP_RFFT_TYPE_2   2  /**< RFFT: identify a real FFT CMSIS-like */
#define HAL_HSP_RFFT_TYPE_3   3  /**< RFFT: identify a real FFT with n+1 elements with out[n]=in[0]+in[1] */
/**
  * @}
  */

/** @defgroup HSP_Conditional_Expr_Constants HSP Conditional expression Constants
  * @{
  */
#define HAL_HSP_CMP_IFEQ      0 /**< if kernel comparison equal */
#define HAL_HSP_CMP_IFNE      1 /**< if kernel comparison not equal */
#define HAL_HSP_CMP_IFGT      2 /**< if kernel comparison greater than */
#define HAL_HSP_CMP_IFLT      3 /**< if kernel comparison less than */
#define HAL_HSP_CMP_IFGE      4 /**< if kernel comparison greater or equal */
#define HAL_HSP_CMP_IFLE      5 /**< if kernel comparison less or equal */
#define HAL_HSP_CMP_IFELSE    6 /**< if kernel comparison else */
#define HAL_HSP_CMP_IFENDIF   7 /**< if kernel comparison endif */
#define HAL_HSP_CMP_IFODD     8 /**< if kernel comparison odd value */
#define HAL_HSP_CMP_IFEVEN    9 /**< if kernel comparison even value */
#define HAL_HSP_CMP_LOOPSTART 0 /**< loop kernel start loop */
#define HAL_HSP_CMP_LOOPEND   1 /**< loop kernel end loop */

/** Maximum number of nested if */
#define HAL_HSP_MAX_NB_IF 15

/** Maximum number of nested loop */
#define HAL_HSP_MAX_NB_LOOP 5
/**
  * @}
  */

/** @defgroup HSP_Command_Status_Constants HSP Command status Constants
  * @{
  */
/* Command status return in FWERR or mailbox status register */
#define HAL_HSP_CMD_STATUS_MSK                    0x000000ff /**< Mask for command status */
#define HAL_HSP_CMD_STATUS_OK                     0x0000 /**< User command completed with success */
#define HAL_HSP_CMD_STATUS_ERROR_CMDL_MEM_ALLOC   0x0001 /**< Kernel cfg failed to alloc memory (CRAM) for PL */
#define HAL_HSP_CMD_STATUS_ERROR_KERNEL_MEM_ALLOC 0x0002 /**< Kernel cfg failed to alloc memory (DRAM) */
#define HAL_HSP_CMD_STATUS_ERROR_SUPER_CMD        0x0003 /**< Error: bad supervisor command */
#define HAL_HSP_CMD_STATUS_ERROR_INI_CMD          0x0004 /**< Error: bad command, waiting for init command */
#define HAL_HSP_CMD_STATUS_ERROR_KERNEL_ID        0x0005 /**< Kernel configuration failed: Bad kernel ID */
#define HAL_HSP_CMD_STATUS_ERROR_EMPTY_PL         0x0006 /**< Empty processing list scheduled */
#define HAL_HSP_CMD_STATUS_ERROR_FLTBANK_DMA_SIZE 0x0007 /**< Error, bad FLTBANK command size */
#define HAL_HSP_CMD_STATUS_ERROR_FATAL            0x0008 /**< Fatal error: PL supervisor/direct/error alloc failed */
#define HAL_HSP_CMD_STATUS_ERROR_DIR_EXTB         0x0009 /**< Error: bad external io detected in direct command */
#define HAL_HSP_CMD_STATUS_ERROR_DIR_CMD          0x000a /**< Error: bad command in direct command */
#define HAL_HSP_CMD_STATUS_ERROR_TSKOFF           0x000b /**< Error: tskoff address too high for TSKOFF0R size */
#define HAL_HSP_CMD_STATUS_ERROR_MAT_INV_SINGULAR 0x000c /**< Error: Matinv input matrix is singular: non-invertible */
#define HAL_HSP_CMD_STATUS_ERROR_PLUGIN_D_ALLOC   0x000d /**< Error: DRAM memory allocation failed to add plugin */
#define HAL_HSP_CMD_STATUS_ERROR_BGND_CHAN        0x000e /**< Error: bad background channel number */
#define HAL_HSP_CMD_STATUS_ERROR_BGND_CMD         0x000f /**< Error: bad background command suspend, resume, stop */
#define HAL_HSP_CMD_STATUS_ERROR_IFE_CMD          0x0010 /**< Error: bad command ife */
#define HAL_HSP_CMD_STATUS_ERROR_IFE_MAX_IF       0x0011 /**< Error: maximum number of nested <if-else> is reached */
#define HAL_HSP_CMD_STATUS_ERROR_IFE_UNCLOSED_IF  0x0012 /**< Error: unclosed <if-else> */
#define HAL_HSP_CMD_STATUS_ERROR_MAX_LOOP         0x0013 /**< Error: max loop reached */
#define HAL_HSP_CMD_STATUS_ERROR_LOOP_UNCLOSED    0x0014 /**< Error: unclosed /loop/ */
#define HAL_HSP_CMD_STATUS_ERROR_NO_LOOP          0x0015 /**< Error: not in /loop/ statement */
#define HAL_HSP_CMD_STATUS_ERROR_PLUGIN_INST      0x0016 /**< Error: bad instruction in plugin */
#define HAL_HSP_CMD_STATUS_ERROR_CNN_CONV2D       0x0017 /**< Error: bad CNN conv2d parameters */

/**
  * @}
  */

/** @defgroup HSP_Command_CountMode HSP Counter Command mode Constants
  * @{
  */
/* Command status return in FWERR or mailbox status register */
#define HAL_HSP_CMD_COUNT_MODE_SET 0 /**< Counter command mode set */
#define HAL_HSP_CMD_COUNT_MODE_ADD 1 /**< Counter command mode add */
/**
  * @}
  */
/** @defgroup HSP_Command_CountNb HSP Counter Command max number of counters Constants
  * @{
  */
/** Maximum number of countif */
#define HAL_HSP_CMD_COUNT_MAX_NB_COUNTIF 15
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* STM32U3xx_HAL_HSP_FW_DEF_H */
