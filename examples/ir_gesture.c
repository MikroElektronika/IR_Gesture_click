/*******************************************************************************
* Title                 :   IR Gesture Example
* Filename              :   MikroC_ARM_M3.c
* Author                :   RBL
* Origin Date           :   15/01/2016
* Notes                 :   None
*******************************************************************************/
/*************** MODULE REVISION LOG ******************************************
*
*    Date    Software Version    Initials   Description
*  15/01/16           .1         RBL        Module Created.
*
*******************************************************************************/
/** 
 * @file MikroC_ARM_M3.c.c
 * @brief This module contains the
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include <stdbool.h>
#include "ir_gesture_hw.h"
#include "resources.h"
#include "gesture.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define PROX_INT_HIGH   50 // Proximity level for interrupt
#define PROX_INT_LOW    0  // No far interrupt

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
static volatile bool isr_flag;

unsigned int TFT_DataPort at GPIOE_ODR;
sbit TFT_RST at GPIOE_ODR.B8;
sbit TFT_RS at GPIOE_ODR.B12;
sbit TFT_CS at GPIOE_ODR.B15;
sbit TFT_RD at GPIOE_ODR.B10;
sbit TFT_WR at GPIOE_ODR.B11;
sbit TFT_BLED at GPIOE_ODR.B9;

sbit APDS9960_INT at GPIOD_IDR.B10;
#if defined( DEBUG )
sbit Mmc_Chip_Select at GPIOD_ODR.B3;
#endif
/******************************************************************************
* Function Prototypes
*******************************************************************************/
/**
 * @brief Initialize Display
 */
static void display_init( void );

/**
 * @brief Process Incoming Gesture
 */
static void process_gesture( void );

/**
 * @brief Initialize System Peripherials
 */
static int system_init( void );

/******************************************************************************
* Function Definitions
*******************************************************************************/
static void display_init()
{
    TFT_Init_ILI9341_8bit( 320, 240 );
    TFT_Set_Font( TFT_defaultFont, CL_WHITE, FO_HORIZONTAL );
    TFT_Fill_Screen( CL_WHITE );
    TFT_Set_Brush(1, CL_WHITE , 0, 0, 0, 0);
    TFT_Set_Pen( CL_BLUE, 1 );
    TFT_Line( 20, 220, 300, 220 );
    TFT_LIne( 20,  40, 300,  40 );
    TFT_Set_Pen( CL_WHITE, 1 );
    TFT_Set_Font( &HandelGothic_BT21x22_Regular, CL_BLUE, FO_HORIZONTAL );
    TFT_Write_Text( "IR Gesture click", 90, 10 );
    TFT_Set_Font( &Verdana12x13_Regular, CL_BLUE, FO_HORIZONTAL );
    TFT_Write_Text( "EasyMx PRO v7 for STM32", 19, 223 );
    TFT_Set_Font( &Verdana12x13_Regular, CL_RED, FO_HORIZONTAL );
    TFT_Write_Text( "www.mikroe.com", 200, 223 );
    TFT_Set_Font( &TFT_defaultFont, CL_RED, FO_HORIZONTAL );
    TFT_Rectangle( 80, 60, 300, 200 );
    TFT_Write_Text( "Please wait...", 100, 110 );
}

static void process_gesture()
{
    if ( ir_gesture_available() )
    {
        TFT_Set_Font( &TFT_defaultFont, CL_RED, FO_HORIZONTAL );
        TFT_Rectangle( 80, 60, 300, 180 );
        switch ( ir_gesture_read_gesture() )
        {
          case DIR_UP:
            TFT_Image(110,80, touch_up_bmp, 1);
            break;
          case DIR_DOWN:
            TFT_Image(110,80, touch_down_bmp, 1);
            break;
          case DIR_LEFT:
            TFT_Image(110,80, touch_left_bmp, 1);
            break;
          case DIR_RIGHT:
            TFT_Image(110,80, touch_right_bmp, 1);
            break;
          case DIR_NEAR:
            TFT_Write_Text("NEAR", 100, 110 );
            break;
          case DIR_FAR:
            TFT_Write_Text("FAR", 100, 110 );
            break;
          default:
            TFT_Write_Text("NONE", 100, 110 );
        }
    }
}

static int system_init()
{
    DisableInterrupts();
    // Set interrupt pin as input
    GPIO_Digital_Input( &GPIOD_BASE, _GPIO_PINMASK_10 );
    //RCC_APB2ENR.AFIOEN = 1;         // Enable clock for alternate pin functions
    //                   AFIO_EXTICR3 = 0x0300;
    EXTI_FTSR |= ( 1 << TR10 );      // Set interrupt on Rising edge
    EXTI_IMR |= ( 1 << MR10 );       // Set mask
    NVIC_IntEnable( IVT_INT_EXTI15_10 );// Enable External interrupt
    
    I2C1_Init_Advanced( 400000, &_GPIO_MODULE_I2C1_PB67 );
    delay_ms( 100 );
    
    // Initialize APDS-9960 (configure I2C and initial values)
    ir_gesture_init( APDS9960_I2C_ADDR );
    ir_gesture_enable_gesture_sensor( true );
    
    display_init();

    EnableInterrupts();
    return 0;
}

void main()
{
    if( system_init() )
        return;

    while (1)
    {
        if( isr_flag )
        {
            DisableInterrupts();
            process_gesture();
            isr_flag = false;
            EnableInterrupts();
        }
    }
}

void gesture_ISR() iv IVT_INT_EXTI15_10 ics ICS_AUTO
{
    EXTI_PR |= ( 1 << PR10 );
    
    if( ir_gesture_is_interrupted( INT_GESTURE ) )
    {
        isr_flag = true;
    }
}