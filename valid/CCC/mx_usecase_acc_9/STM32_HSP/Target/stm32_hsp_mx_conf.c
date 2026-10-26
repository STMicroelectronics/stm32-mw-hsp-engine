/**
  ******************************************************************************
  * @file    MW/Src/stm32_hsp_mx_conf.c
  * @author  GPM Application Team
  * @brief   This example describes how to configure the STM32U3xx MW API.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hsp_mx_conf.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* HSP BRAM Static Allocation *********************************/
/* BRAM Data as variable */
float32_t my_var1_f32  __attribute__((section("HSP_DATA_BRAM"))) = 0.0f;
uint32_t  my_var2_u32  __attribute__((section("HSP_DATA_BRAM"))) = 0UL;
int32_t   my_var3_i32  __attribute__((section("HSP_DATA_BRAM"))) = 0;
uint16_t  my_var4_ui16 __attribute__((section("HSP_DATA_BRAM"))) = 0U;
int16_t   my_var5_i16  __attribute__((section("HSP_DATA_BRAM"))) = 0;
int8_t    my_var6_i8   __attribute__((section("HSP_DATA_BRAM"))) = 0;

/* BRAM Data as buffer with unique init value */
float32_t my_buffer1_f32[MY_BUFFER1_F32_SIZE]   __attribute__((section("HSP_DATA_BRAM"))) = {0.0f};
uint32_t  my_buffer2_u32[MY_BUFFER2_U32_SIZE]   __attribute__((section("HSP_DATA_BRAM"))) = {0UL};
int32_t   my_buffer3_i32[MY_BUFFER3_I32_SIZE]   __attribute__((section("HSP_DATA_BRAM"))) = {0};
uint16_t  my_buffer4_ui16[MY_BUFFER4_UI16_SIZE] __attribute__((section("HSP_DATA_BRAM"))) = {0U};
int16_t   my_buffer5_i16[MY_BUFFER5_I16_SIZE]   __attribute__((section("HSP_DATA_BRAM"))) = {0};
int8_t    my_buffer6_i8[MY_BUFFER6_I8_SIZE]     __attribute__((section("HSP_DATA_BRAM"))) = {0};

/* BRAM Data as buffer with init values array */
float32_t my_buffer8_f32[MY_BUFFER8_F32_SIZE]     __attribute__((section("HSP_DATA_BRAM"))) = {0.0f, 1.2f, -0.2f, -1000.0f};
uint32_t  my_buffer9_u32[MY_BUFFER9_U32_SIZE]     __attribute__((section("HSP_DATA_BRAM"))) = {0UL, 10UL, 12UL, 1025UL, 8UL};
int32_t   my_buffer10_i32[MY_BUFFER10_I32_SIZE]   __attribute__((section("HSP_DATA_BRAM"))) = {-3505, 13450};
uint16_t  my_buffer11_ui16[MY_BUFFER11_UI16_SIZE] __attribute__((section("HSP_DATA_BRAM"))) = {0U, 1U, 2U, 3U, 4U};
int16_t   my_buffer12_i16[MY_BUFFER12_I16_SIZE]   __attribute__((section("HSP_DATA_BRAM"))) = {-5, -3, 0, 10, 85, -10, -54, 9, 63, -99, 875, 326};
int8_t    my_buffer13_i8[MY_BUFFER13_I8_SIZE]     __attribute__((section("HSP_DATA_BRAM"))) = {-2, 127, -47};

/* BRAM Data as Pointer of Pointer */
float32_t *my_pop1_f32  __attribute__((section("HSP_DATA_BRAM"))) = &my_var1_f32;
uint32_t  *my_var2_u32  __attribute__((section("HSP_DATA_BRAM"))) = &my_buffer2_u32;
int32_t   *my_var3_i32  __attribute__((section("HSP_DATA_BRAM"))) = &my_var3_i32;
uint16_t  *my_var4_ui16 __attribute__((section("HSP_DATA_BRAM"))) = &my_var4_ui16;
int16_t   *my_var5_i16  __attribute__((section("HSP_DATA_BRAM"))) = &my_buffer12_i16;
int8_t    *my_var6_i8   __attribute__((section("HSP_DATA_BRAM"))) = &my_buffer13_i8;

/* Private function prototypes -----------------------------------------------*/
extern void Error_Handler(void);
