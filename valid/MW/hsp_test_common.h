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
#endif // ARM_COMPILE
#ifndef GCC_COMPILE
#include "hyp_mmap.h"
#include "hsp_test_mmap.h"
#endif // GCC_COMPILE

#ifdef STM32H7P5xx
#include "stm32_hal.h"
#include "stm32h7pxx_hal_rcc.h"
#endif


#ifndef HYP_TOOLS
// #include "hsp_hal.h"
// #include "hal_hsp.h"

// #include "stm32_hsp.h"
// #include "stm32_hsp_def.h"
// #include "hsp_hw_if.h"
#ifdef HYPSA_SIMU
#include "hal_hsp.h"
#endif /* HYPSA_SIMU */
#include "hsp_hw_if.h"
#include "hsp_def.h"

#endif // HYP_TOOLS 
//#include "hsp_hal.h"


#ifdef HYPSA_SIMU
#define HSP_MEMA_BASE_ADDR (0x08000 * 4)           /**< BRAM A addr */
#define HSP_MEMB_BASE_ADDR (0x24000 * 4)           /**< BRAM B addr */
#define uint8_mema_t uint8_t chess_storage(DMbA)   /**< uint8_t in BRAM MEMA */
#define int8_mema_t int8_t chess_storage(DMbA)     /**< int8_t in BRAM MEMA */
#define uint8_memb_t uint8_t chess_storage(DMbB)   /**< uint8_t in BRAM MEMB */
#define int8_memb_t int8_t chess_storage(DMbB)     /**< int8_t in BRAM MEMB */
#define uint32_mema_t uint32_t chess_storage(DMbA) /**< uint32_t in BRAM MEMA */
#define int32_mema_t int32_t chess_storage(DMbA)   /**< int32_t in BRAM MEMA */
#define uint32_memb_t uint32_t chess_storage(DMbB) /**< uint32_t in BRAM MEMB */
#define int32_memb_t int32_t chess_storage(DMbB)   /**< int32_t in BRAM MEMB */
#endif


/*------------------------------------------------------------------------------
 * Defines
 *----------------------------------------------------------------------------*/
// Address  of coverage memory: HSP base addr  + size MEMAB + offset memory ????
//#define TEST_ADDR_MEM_COVERAGE  (0x410EA000)
#define TEST_ADDR_MEM_COVERAGE  (HYPSA_SHARED_MEM_BASE_ADDR + HSP_MEM_BRAMAB_SIZE)

// Filter state allocation define: add parameter to slect allcoation area: persistent or default
/* ------------------------ */
/* Allocation Filter State  */ 
/* ------------------------ */

#define  HSP_BRAM_MallocStateBuffer_Fir(hmw, nbTaps, nbSamples)\
HSP_BRAM_MallocStateBuffer_Fir(hmw, nbTaps, nbSamples)

#define  HSP_BRAM_MallocStateBuffer_FirDecimate(hmw, nbTaps, nbSamples, decimFactor)\
  HSP_BRAM_MallocStateBuffer_FirDecimate(hmw, nbTaps, nbSamples, decimFactor)

#define  HSP_BRAM_MallocStateBuffer_BiquadCascadeDf1(hmw, nbStages)\
  HSP_BRAM_MallocStateBuffer_BiquadCascadeDf1(hmw, nbStages)

#define  HSP_BRAM_MallocStateBuffer_BiquadCascadeDf2t(hmw, nbStages)\
  HSP_BRAM_MallocStateBuffer_BiquadCascadeDf2t(hmw, nbStages)

#define  HSP_BRAM_MallocStateBuffer_Lms(hmw, nbTaps)\
  HSP_BRAM_MallocStateBuffer_Lms(hmw, nbTaps)

#define  HSP_BRAM_MallocStateBuffer_IirLattice(hmw, nbStages)\
  HSP_BRAM_MallocStateBuffer_IirLattice(hmw, nbStages)

#define  HSP_BRAM_MallocStateBuffer_IirDf1(hmw, nbStages)\
  HSP_BRAM_MallocStateBuffer_IirDf1(hmw, nbStages)

#define  HSP_BRAM_MallocStateBuffer_Iir3p3z(hmw)\
  HSP_BRAM_MallocStateBuffer_Iir3p3z(hmw)

#define  HSP_BRAM_MallocStateBuffer_Iir2p2z(hmw)\
  HSP_BRAM_MallocStateBuffer_Iir2p2z(hmw)


// CNN define for pad4 merge function, in order to not modify tests
/* ------------------------ */
/* CONV2D                   */ 
/* ------------------------ */
/* TO DO 0 STEP CONV2D */
#define HAL_HSP_Direct_Cnn_Conv2D0StepPad(hmw, in_w, in_h, in_c, k_w, k_h, ou_w, ou_h, ou_c, stridex, stridey,\
                                       pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale, offIn, offOu, satMin, satMax, padx, pady)\
  HSP_DIRECT_CNN_Conv2D0StepPad4_s8(hmw, in_w, in_h, in_c, k_w, k_h, ou_w, ou_h, ou_c, stridex, stridey,\
                                       pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale, offIn, offOu, satMin, satMax, padx, pady, padx, pady)

#define HAL_HSP_Direct_Cnn_Conv2D0Step(hmw,\
                                       in_w, in_h, in_c,\
                                       k_w, k_h,\
                                       ou_w, ou_h, ou_c,\
                                       stridex, stridey,\
                                       pIn, pKe, pOu,\
                                       pBi, in_scale, out_scale, p_wt_scale,\
                                       offIn, offOu, satMin, satMax)\
  HSP_DIRECT_CNN_Conv2D0StepPad4_s8(hmw,\
                                       in_w, in_h, in_c,\
                                       k_w, k_h,\
                                       ou_w, ou_h, ou_c,\
                                       stridex, stridey,\
                                       pIn, pKe, pOu,\
                                       pBi, in_scale, out_scale, p_wt_scale,\
                                       offIn, offOu, satMin, satMax,\
                                       0, 0, 0, 0)									
									
									
#define HAL_HSP_Direct_Cnn_Conv2D1Step(hhsp, in_w, in_h, in_c, k_w, k_h, ou_w, ou_h, ou_c, stridex, stridey, \
                                       pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale, offIn, offOu, satMin, satMax, nbLouM2) \
  HSP_DIRECT_CNN_Conv2D1StepPad4_s8(hhsp, in_w, in_h, in_c, k_w, k_h, ou_w, ou_h, ou_c, stridex, stridey, pIn, pKe, \
                                     pOu, pBi, in_scale, out_scale, p_wt_scale, offIn, offOu, satMin, satMax, 0, 0, 0, 0, nbLouM2)

#define HAL_HSP_Direct_Cnn_Conv2D1StepPad(hhsp, in_w, in_h, in_c, k_w, k_h, ou_w, ou_h, ou_c, stridex, stridey, \
                                          pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale, offIn, offOu, satMin, satMax, padx, pady, nbLouM2) \
  HSP_DIRECT_CNN_Conv2D1StepPad4_s8(hhsp, in_w, in_h, in_c, k_w, k_h, ou_w, ou_h, ou_c, stridex, stridey, pIn, pKe, \
                                     pOu, pBi, in_scale, out_scale, p_wt_scale, offIn, offOu, satMin, satMax, padx, padx, pady, pady, nbLouM2)

#define HAL_HSP_Direct_Cnn_Conv2D3Step(hhsp, in_w, in_h, in_c, k_w, k_h, ou_w, ou_h, ou_c, stridex, stridey, \
                                       pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale, offIn, offOu, satMin, satMax, nbLouM2) \
HSP_DIRECT_CNN_Conv2D3StepPad4_s8(hhsp, in_w, in_h, in_c, k_w, k_h, ou_w, ou_h, ou_c, stridex, stridey, pIn, pKe, \
                                   pOu, pBi, in_scale, out_scale, p_wt_scale, offIn, offOu, satMin, satMax, 0, 0, 0, 0, nbLouM2)

#define HAL_HSP_Direct_Cnn_Conv2D3StepPad(hhsp, in_w, in_h, in_c, k_w, k_h, ou_w, ou_h, ou_c, stridex, stridey, \
                                          pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale, offIn, offOu, satMin, satMax, padx, pady, nbLouM2) \
  HSP_DIRECT_CNN_Conv2D3StepPad4_s8(hhsp, in_w, in_h, in_c, k_w, k_h, ou_w, ou_h, ou_c, stridex, stridey, pIn, pKe, \
                                     pOu, pBi, in_scale, out_scale, p_wt_scale, offIn, offOu, satMin, satMax, padx, padx, pady, pady, nbLouM2)

#define HAL_HSP_Direct_Cnn_Conv2D2Step(hhsp, in_w, in_h, in_c, k_w, k_h, ou_w, ou_h, ou_c, stridex, stridey, \
                                       pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale, offIn, offOu, satMin, satMax, nbLouM2) \
HSP_DIRECT_CNN_Conv2D2StepPad4_s8(hhsp, in_w, in_h, in_c, k_w, k_h, ou_w, ou_h, ou_c, stridex, stridey, pIn, pKe, \
                                   pOu, pBi, in_scale, out_scale, p_wt_scale, offIn, offOu, satMin, satMax, 0, 0, 0, 0, nbLouM2)

#define HAL_HSP_Direct_Cnn_Conv2D2StepPad(hhsp, in_w, in_h, in_c, k_w, k_h, ou_w, ou_h, ou_c, stridex, stridey, \
                                          pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale, offIn, offOu, satMin, satMax, padx, pady, nbLouM2) \
  HSP_DIRECT_CNN_Conv2D2StepPad4_s8(hhsp, in_w, in_h, in_c, k_w, k_h, ou_w, ou_h, ou_c, stridex, stridey, pIn, pKe, \
                                   pOu, pBi, in_scale, out_scale, p_wt_scale, offIn, offOu, satMin, satMax, padx, padx, pady, pady, nbLouM2)

/* ------------------------ */
/* POINTWISE                */ 
/* ------------------------ */
#define HAL_HSP_Direct_Cnn_Pointwise0Step(hhsp, in_w, in_h, in_c,\
                            ou_w, ou_h, ou_c, stridex, stridey,\
                            p_input_data, p_filter_data, p_output_data, p_bias_data,\
                            in_scale, out_scale, p_wt_scale,\
                            off_in, off_ou, sat_min, sat_max)\
  HSP_DIRECT_CNN_Pointwise0Step_s8(hhsp, in_w, in_h, in_c,\
                            ou_w, ou_h, ou_c, stridex, stridey,\
                            p_input_data, p_filter_data, p_output_data, p_bias_data,\
                            in_scale, out_scale, p_wt_scale,\
                            off_in, off_ou, sat_min, sat_max)
							
#define HAL_HSP_Direct_Cnn_Pointwise1Step(hhsp, in_w, in_h, in_c,\
                            ou_w, ou_h, ou_c, stridex, stridey,\
                            p_input_data, p_filter_data, p_output_data, p_bias_data,\
                            in_scale, out_scale, p_wt_scale,\
                            off_in, off_ou, sat_min, sat_max)\
   HSP_DIRECT_CNN_Pointwise1Step_s8(hhsp, in_w, in_h, in_c,\
                            ou_w, ou_h, ou_c, stridex, stridey,\
                            p_input_data, p_filter_data, p_output_data, p_bias_data,\
                            in_scale, out_scale, p_wt_scale,\
                            off_in, off_ou, sat_min, sat_max)
							
#define HAL_HSP_Direct_Cnn_Pointwise2Step(hhsp, in_w, in_h, in_c,\
                            ou_w, ou_h, ou_c, stridex, stridey,\
                            p_input_data, p_filter_data, p_output_data, p_bias_data,\
                            in_scale, out_scale, p_wt_scale,\
                            off_in, off_ou, sat_min, sat_max, nb_line_per_blocks)\
  HSP_DIRECT_CNN_Pointwise2Step_s8(hhsp, in_w, in_h, in_c,\
                            ou_w, ou_h, ou_c, stridex, stridey,\
                            p_input_data, p_filter_data, p_output_data, p_bias_data,\
                            in_scale, out_scale, p_wt_scale,\
                            off_in, off_ou, sat_min, sat_max, nb_line_per_blocks)
							
#define HAL_HSP_Direct_Cnn_Pointwise3Step(hhsp, in_w, in_h, in_c,\
                            ou_w, ou_h, ou_c, stridex, stridey,\
                            p_input_data, p_filter_data, p_output_data, p_bias_data,\
                            in_scale, out_scale, p_wt_scale,\
                            off_in, off_ou, sat_min, sat_max, nb_line_per_blocks)\
  HSP_DIRECT_CNN_Pointwise3Step_s8(hhsp, in_w, in_h, in_c,\
                            ou_w, ou_h, ou_c, stridex, stridey,\
                            p_input_data, p_filter_data, p_output_data, p_bias_data,\
                            in_scale, out_scale, p_wt_scale,\
                            off_in, off_ou, sat_min, sat_max, nb_line_per_blocks)
/* ------------------------ */
/* DEPTHWISE                */ 
/* ------------------------ */
#define HAL_HSP_Direct_Cnn_Depthwise1Step(hmw, in_w,  in_h, in_c,\
                                 k_w,  k_h, ou_w,  ou_h, ou_c, stridex, stridey,\
                                 pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale,\
                                 offIn, offOu, satMin, satMax) \
  HSP_DIRECT_CNN_Depthwise1StepPad4_s8(hmw, in_w,  in_h, in_c,\
                                 k_w,  k_h, ou_w,  ou_h, ou_c, stridex, stridey,\
                                 pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale,\
                                 offIn, offOu, satMin, satMax, 0, 0, 0, 0)

#define HAL_HSP_Direct_Cnn_Depthwise1StepPad4(hmw, in_w,  in_h, in_c,\
                                 k_w,  k_h, ou_w,  ou_h, ou_c, stridex, stridey,\
                                 pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale,\
                                 offIn, offOu, satMin, satMax, padx0, padx1, pady0, pady1) \
  HSP_DIRECT_CNN_Depthwise1StepPad4_s8(hmw, in_w,  in_h, in_c,\
                                 k_w,  k_h, ou_w,  ou_h, ou_c, stridex, stridey,\
                                 pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale,\
                                 offIn, offOu, satMin, satMax, padx0, padx1, pady0, pady1)

#define HAL_HSP_Direct_Cnn_Depthwise2StepPad4(hmw, in_w,  in_h, in_c,\
                                 k_w,  k_h, ou_w,  ou_h, ou_c, stridex, stridey,\
                                 pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale,\
                                 offIn, offOu, satMin, satMax, padx0, padx1, pady0, pady1, nboutline) \
  HSP_DIRECT_CNN_Depthwise2StepPad4_s8(hmw, in_w,  in_h, in_c,\
                                 k_w,  k_h, ou_w,  ou_h, ou_c, stridex, stridey,\
                                 pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale,\
                                 offIn, offOu, satMin, satMax, padx0, padx1, pady0, pady1, nboutline)

#define HAL_HSP_Direct_Cnn_Depthwise3StepPad4(hmw, in_w,  in_h, in_c,\
                                 k_w,  k_h, ou_w,  ou_h, ou_c, stridex, stridey,\
                                 pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale,\
                                 offIn, offOu, satMin, satMax, padx0, padx1, pady0, pady1, nboutline) \
  HSP_DIRECT_CNN_Depthwise3StepPad4_s8(hmw, in_w,  in_h, in_c,\
                                 k_w,  k_h, ou_w,  ou_h, ou_c, stridex, stridey,\
                                 pIn, pKe, pOu, pBi, in_scale, out_scale, p_wt_scale,\
                                 offIn, offOu, satMin, satMax, padx0, padx1, pady0, pady1, nboutline)
								 
/* ------------------------ */
/* MAX/AVG POOL             */ 
/* ------------------------ */
#define HAL_HSP_Direct_Cnn_PoolCioPad(hhsp, in_w, in_h, in_c, k_w, k_h, ou_w, ou_h, ou_c, stridex, stridey, pIn, pOu, \
                                      satMin, satMax, nbOlines, padx, pady) \
  HSP_DIRECT_CNN_Pool1StepPad4_s8(hhsp, in_w, in_h, in_c, k_w, k_h, ou_w, ou_h, ou_c, stridex, stridey, pIn, pOu, \
                                 satMin, satMax, padx, padx, pady, pady, 0, nbOlines)
			
#define HAL_HSP_Direct_Cnn_PoolCio(hhsp, in_w, in_h, in_c, k_w, k_h, ou_w,  ou_h,  ou_c, stridex,  stridey,\
                                pIn, pOu, satMin, satMax, nbOlines, type)\
  HSP_DIRECT_CNN_Pool1StepPad4_s8(hhsp, in_w, in_h, in_c, k_w, k_h, ou_w, ou_h, ou_c, stridex, stridey, pIn, pOu, \
                                 satMin, satMax, 0, 0, 0, 0, type, nbOlines)
							
#define HAL_HSP_Direct_Cnn_Pool(hmw, INP_W, INP_H, IN_C, K_W, K_H, OU_W, OU_H, OU_C, STRIDEX, STRIDEY,\
                            pIn, pOu, satMin, satMax, type)\
  HSP_DIRECT_CNN_Pool0Step_s8(hmw, INP_W, INP_H, IN_C, K_W, K_H, OU_W, OU_H, OU_C, STRIDEX, STRIDEY, pIn, pOu, satMin,  satMax, type)
							
/* ------------------------ */
/* FULLY CONNECTED POOL     */ 
/* ------------------------ */
#define HAL_HSP_Direct_Cnn_Fc(hmw, in_c, ou_c, pIn, pKe, pOu, pBi, in_scale, out_scale, wt_scale, offIn, offOu, satMin, satMax)\
  HSP_DIRECT_CNN_FullyConnected0Step_s8(hmw, in_c, ou_c,pIn, pKe, pOu, pBi, in_scale, out_scale, wt_scale, offIn, offOu, satMin, satMax)

#define  HAL_HSP_Direct_Cnn_Fc2(hmw, in_c, ou_c, pIn, pKe, pOu, pBi, in_scale, out_scale, wt_scale, offIn, offOu, satMin, satMax)\
  HSP_DIRECT_CNN_FullyConnected1Step_s8(hmw, in_c, ou_c, pIn, pKe, pOu, pBi, in_scale, out_scale, wt_scale, offIn, offOu, satMin, satMax)
				
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
// #include "hsp_hal.h"
// #include "stm32u3xx_hal_def.h"
extern void hypsa_post_command();
typedef HAL_HSP_HandleTypeDef HSP_HandleTypeDef ;

// typedef struct 
// {
  // HSP_TypeDef               *instance;     /*!< Register base address  */

  // HAL_HSP_StateTypeDef global_state;  /*!< HSP peripheral state  */

  // uint32_t last_error_codes;  /*!< Errors limited to the last process
                                        // This parameter can be a combination of @ref HSP_HAL_Error_Codes */
  // uint32_t fw_error_code;     /*!< Firmware Error code
                                        // This parameter can be a value of @ref HSP_Firmware_Error_Codes  */
  // uint32_t *cram_address_for_plugin;  /*!< CRAM Address to load the next plugin */
// } HSP_HandleTypeDef;

HAL_StatusTypeDef test_send_event(HSP_HandleTypeDef *hhsp, uint8_t event);
HAL_StatusTypeDef test_enable_event(HSP_HandleTypeDef *hhsp, uint8_t event);

#endif

#else
typedef HAL_HSP_HandleTypeDef HSP_HandleTypeDef ;
HAL_StatusTypeDef test_send_event(HSP_HandleTypeDef *hhsp, uint8_t event);
HAL_StatusTypeDef test_enable_event(HSP_HandleTypeDef *hhsp, uint8_t event);
void hsp_startcc(void);
void hsp_stopcc(void);

#define getARMCycle() (0xFFFFFF - SysTick->VAL)
#endif

#ifndef ARM_COMPILE
#define hspInternalMeasure hypInternalMeasure
#endif // ARM_COMPILE

/*------------------------------------------------------------------------------
 * Variables
 *----------------------------------------------------------------------------*/
#ifndef HYP_TOOLS
/// Global HSP handler variable 
// extern HSP_HandleTypeDef HSPHandle;
HAL_StatusTypeDef HAL_HSP_SPE_ConfigAndEnableEvent(HSP_HandleTypeDef *hhsp, uint8_t event);

// FOR MDW
 extern hsp_core_handle_t hmw;
 extern hw_hsp_if_handle_t h_hw_hsp_if[];
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
void test_hw_reset(HSP_HandleTypeDef *hhsp);

HAL_StatusTypeDef HAL_HSP_ConfigureEOT(HSP_HandleTypeDef *hhsp, uint8_t taskNb, uint8_t taskCmpNb);

/** @defgroup HSP_Private_Functions HSP Private Functions
  * @{
  */
/**
  * @brief HAL Write 32-bit value in mailbox dedicated command register
  * @param value 32-bit value to be write in command register
  * @retval            HAL status.
  */
HAL_StatusTypeDef HSP_WriteCommand(HSP_HandleTypeDef *hhsp, uint32_t command);
 
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
uint32_t compare_int32(const char *testName, uint32_t *data, uint32_t *ref, uint32_t size, uint16_t noCompare);

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
void load_hsp_dram(void);

/**
 * ARM compilation: Load HSP CRAM code
 */
void load_hsp_cram(void);

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
 * @brief Send event to HSP
 * @param[in] hhsp    HSP handle.
 * @retval            HAL status.
 */
HAL_StatusTypeDef HAL_HSP_SendEvent(HSP_HandleTypeDef *hhsp, uint8_t event);

/**
 * @brief Enable and Send event to HSP
 * @param[in] hhsp    HSP handle.
 * @retval            HAL status.
 */
HAL_StatusTypeDef test_enable_and_send_event(HSP_HandleTypeDef *hhsp, uint8_t event);
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

#endif // __HSP_TEST_COMMON_H__
