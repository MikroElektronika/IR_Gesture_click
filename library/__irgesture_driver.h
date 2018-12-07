/*
    __irgesture_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __irgesture_driver.h
@brief    IR_Gesture Driver
@mainpage IR_Gesture Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   IRGESTURE
@brief      IR_Gesture Click Driver
@{

| Global Library Prefix | **IRGESTURE** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Aug 2018.**      |
| Developer             | **Nenad Filipovic**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _IRGESTURE_H_
#define _IRGESTURE_H_

/** 
 * @macro T_IRGESTURE_P
 * @brief Driver Abstract type 
 */
#define T_IRGESTURE_P    const uint8_t*

/** @defgroup IRGESTURE_COMPILE Compilation Config */              /** @{ */

//  #define   __IRGESTURE_DRV_SPI__                            /**<     @macro __IRGESTURE_DRV_SPI__  @brief SPI driver selector */
   #define   __IRGESTURE_DRV_I2C__                            /**<     @macro __IRGESTURE_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __IRGESTURE_DRV_UART__                           /**<     @macro __IRGESTURE_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup IRGESTURE_VAR Variables */                           /** @{ */

/* APDS-9960 I2C address */
extern const uint8_t  _IRGESTURE_I2C_ADDR;
/* APDS-9960 register addresses */
extern const uint8_t _IRGESTURE_ENABLE;
extern const uint8_t _IRGESTURE_ATIME;
extern const uint8_t _IRGESTURE_WTIME;
extern const uint8_t _IRGESTURE_AILTL;
extern const uint8_t _IRGESTURE_AILTH;
extern const uint8_t _IRGESTURE_AIHTL;
extern const uint8_t _IRGESTURE_AIHTH;
extern const uint8_t _IRGESTURE_PILT;
extern const uint8_t _IRGESTURE_PIHT;
extern const uint8_t _IRGESTURE_PERS;
extern const uint8_t _IRGESTURE_CONFIG1;
extern const uint8_t _IRGESTURE_PPULSE;
extern const uint8_t _IRGESTURE_CONTROL;
extern const uint8_t _IRGESTURE_CONFIG2;
extern const uint8_t _IRGESTURE_ID;
extern const uint8_t _IRGESTURE_STATUS;
extern const uint8_t _IRGESTURE_CDATAL;
extern const uint8_t _IRGESTURE_CDATAH;
extern const uint8_t _IRGESTURE_RDATAL;
extern const uint8_t _IRGESTURE_RDATAH;
extern const uint8_t _IRGESTURE_GDATAL;
extern const uint8_t _IRGESTURE_GDATAH;
extern const uint8_t _IRGESTURE_BDATAL;
extern const uint8_t _IRGESTURE_BDATAH;
extern const uint8_t _IRGESTURE_PDATA;
extern const uint8_t _IRGESTURE_POFFSET_UR;
extern const uint8_t _IRGESTURE_POFFSET_DL;
extern const uint8_t _IRGESTURE_CONFIG3;
extern const uint8_t _IRGESTURE_GPENTH;
extern const uint8_t _IRGESTURE_GEXTH;
extern const uint8_t _IRGESTURE_GCONF1;
extern const uint8_t _IRGESTURE_GCONF2;
extern const uint8_t _IRGESTURE_GOFFSET_U;
extern const uint8_t _IRGESTURE_GOFFSET_D;
extern const uint8_t _IRGESTURE_GOFFSET_L;
extern const uint8_t _IRGESTURE_GOFFSET_R;
extern const uint8_t _IRGESTURE_GPULSE;
extern const uint8_t _IRGESTURE_GCONF3;
extern const uint8_t _IRGESTURE_GCONF4;
extern const uint8_t _IRGESTURE_GFLVL;
extern const uint8_t _IRGESTURE_GSTATUS;
extern const uint8_t _IRGESTURE_IFORCE;
extern const uint8_t _IRGESTURE_PICLEAR;
extern const uint8_t _IRGESTURE_CICLEAR;
extern const uint8_t _IRGESTURE_AICLEAR;
extern const uint8_t _IRGESTURE_GFIFO_U;
extern const uint8_t _IRGESTURE_GFIFO_D;
extern const uint8_t _IRGESTURE_GFIFO_L;
extern const uint8_t _IRGESTURE_GFIFO_R;

/* Default values */
extern const uint8_t  DEFAULT_ATIME;
extern const uint8_t  DEFAULT_WTIME;
extern const uint8_t  DEFAULT_PROX_PPULSE;
extern const uint8_t  DEFAULT_GESTURE_PPULSE;
extern const uint8_t  DEFAULT_POFFSET_UR;
extern const uint8_t  DEFAULT_POFFSET_DL;
extern const uint8_t  DEFAULT_CONFIG1;
extern const uint8_t  DEFAULT_LDRIVE;
extern const uint8_t  DEFAULT_PGAIN;
extern const uint8_t  DEFAULT_AGAIN;
extern const uint8_t  DEFAULT_PILT;
extern const uint8_t  DEFAULT_PIHT;
extern const uint16_t DEFAULT_AILT;
extern const uint8_t  DEFAULT_AIHT;
extern const uint8_t  DEFAULT_PERS;
extern const uint8_t  DEFAULT_CONFIG2;
extern const uint8_t  DEFAULT_CONFIG3;
extern const uint8_t  DEFAULT_GPENTH;
extern const uint8_t  DEFAULT_GEXTH;
extern const uint8_t  DEFAULT_GCONF1;
extern const uint8_t  DEFAULT_GGAIN;
extern const uint8_t  DEFAULT_GLDRIVE;
extern const uint8_t  DEFAULT_GWTIME;
extern const uint8_t  DEFAULT_GOFFSET;
extern const uint8_t  DEFAULT_GPULSE;
extern const uint8_t  DEFAULT_GCONF3;
extern const uint8_t  DEFAULT_GIEN;

/* Bit fields */
extern const uint8_t _IRGESTURE_PON;
extern const uint8_t _IRGESTURE_AEN;
extern const uint8_t _IRGESTURE_PEN;
extern const uint8_t _IRGESTURE_WEN;
extern const uint8_t _IRGESTURE_AIEN;
extern const uint8_t _IRGESTURE_PIEN;
extern const uint8_t _IRGESTURE_GEN;
extern const uint8_t _IRGESTURE_GVALID;

/* Geasture results */
extern const uint8_t _IRGESTURE_FAR;
extern const uint8_t _IRGESTURE_RIGHT;
extern const uint8_t _IRGESTURE_LEFT;
extern const uint8_t _IRGESTURE_UP;
extern const uint8_t _IRGESTURE_DOWN;
extern const uint8_t _IRGESTURE_NEAR;

/* Error code for returned values */
extern const uint8_t  DEFAULT_ERROR;

                                                                       /** @} */
/** @defgroup IRGESTURE_TYPES Types */                             /** @{ */

typedef enum
{
    NA_STATE,
    NEAR_STATE,
    FAR_STATE,
    ALL_STATE
} gesture_prox_t;

/* Direction definitions */
typedef enum
{
    DIR_NONE,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP,
    DIR_DOWN,
    DIR_NEAR,
    DIR_FAR,
    DIR_ALL
} gesture_dir_t;

/* Container for gesture data */
typedef struct
{
    uint8_t u_data[32];
    uint8_t d_data[32];
    uint8_t l_data[32];
    uint8_t r_data[32];
    uint8_t index;
    uint8_t total_gestures;
    uint8_t in_threshold;
    uint8_t out_threshold;
    uint16_t ud_delta;
    uint16_t lr_delta;
    uint16_t ud_count;
    uint16_t lr_count;
    uint16_t near_count;
    uint16_t far_count;
    gesture_prox_t state;
    gesture_dir_t motion;
} gesture_data_t;



                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup IRGESTURE_INIT Driver Initialization */              /** @{ */

#ifdef   __IRGESTURE_DRV_SPI__
void irgesture_spiDriverInit(T_IRGESTURE_P gpioObj, T_IRGESTURE_P spiObj);
#endif
#ifdef   __IRGESTURE_DRV_I2C__
void irgesture_i2cDriverInit(T_IRGESTURE_P gpioObj, T_IRGESTURE_P i2cObj, uint8_t slave);
#endif
#ifdef   __IRGESTURE_DRV_UART__
void irgesture_uartDriverInit(T_IRGESTURE_P gpioObj, T_IRGESTURE_P uartObj);
#endif


/** @defgroup IRGESTURE_FUNC Driver Functions */                   /** @{ */

/**
 * @brief Generic write byte of data function
 *
 * @param[in] regAddress                Register address
 *
 * @param[in] writeData                 Byte of data to write
 *
 * Function write the 8-bit of data to the
 * target 8-bit register address of APDS-9960 IC sensor 
 * on IR Gesture Click.
 */
void irgesture_writeData( uint8_t regAddress, uint8_t writeData );

/**
 * @brief Generic read byte of data function
 *
 * @param[in] regAddress                Register address
 *
 * @return
 * 8-bit read data
 *
 * Function read the 8-bit of data from the
 * target 8-bit register address of 
 * APDS-9960 IC sensor on IR Gesture Click.
 */
uint8_t irgesture_readData( uint8_t regAddress );

/**
 * @brief Get state of interrupt pin function
 *
 * @return state of INT pin
 * - 0: not active;
 * - 1: active;
 *
 * Function get state of interrupt ( INT ) pin.
 */
uint8_t irgesture_getInterrupt();

/**
 * @brief Default configuration function
 *
 * Function set default configuration to the 
 * APDS-9960 IC sensor on IR Gesture Click.
 */
void irgesture_defaultConfiguration();

/**
 * @brief Starts the gesture recognition engine function
 *
 * Function starts the gesture recognition engine on the 
 * APDS-9960 IC on IR Gesture Click.
 */
void irgesture_enableGestureSensor();

/**
 * @brief Disable the gesture recognition engine function
 *
 * Function disable the gesture recognition engine on the
 * APDS-9960 IC on IR Gesture Click.
 */
void irgesture_disableGestureSensor();

/**
 * @brief Determines if there is a gesture available function
 *
 * @return
 * - 1 : TRUE;
 * - 0 : FALSE;
 *
 * Function determines if there is a gesture available 
 * for reading from target 8-bit register address of
 * APDS-9960 IC sensor on IR Gesture Click.
 */
uint8_t irgesture_available();

/**
 * @brief Set gain for gesture function
 *
 * @param[in] gainVal                  8-bit gain data
 *
 * Function set gain for gesture on the target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
void irgesture_setGestureGain( uint8_t gainVal );

/**
 * @brief Get gain for gesture function
 *
 * @return
 * 8-bit gain data
 *
 * Function get gain for gesture from the target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
uint8_t irgesture_getGestureGain();

/**
 * @brief Processes a gesture event function
 *
 * @return gesture_dir_t
 * - Number corresponding to gesture.
 * - or -1 on error.
 *
 * Function processes a gesture event and returns best guessed gesture
 * engine on the APDS-9960 IC on IR Gesture Click.
 */
gesture_dir_t irgesture_gestureReadGesture();

/**
 * @brief Sets the gesture mode function
 *
 * Function set the gesture mode engine on the
 * APDS-9960 IC on IR Gesture Click.
 */
void irgesture_setGestureMode();

/**
 * @brief Enable power sensor function
 *
 * Function enable power sensor engine on the
 * APDS-9960 IC on IR Gesture Click.
 */
void irgesture_enablePower();

/**
 * @brief Disable power sensor function
 *
 * Function disable power sensor engine on the
 * APDS-9960 IC on IR Gesture Click.
 */
void irgesture_disablePower();

/**
 * @brief Set gain for ambient light function
 *
 * @param[in] gainVal                8-bit gain data
 *
 * Function set gain for ambient light on the target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
void irgesture_setAmbientLightGain( uint8_t gainVal );

/**
 * @brief Get gain for ambient light function
 *
 * @return
 * 8-bit gain data
 *
 * Function get gain for ambient light from the target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
uint8_t irgesture_getAmbientLightGain();

/**
 * @brief Enable specific ambient light sensors function
 *
 * Function enable specific ambient light sensors
 * and set default gain on the
 * APDS-9960 IC on IR Gesture Click.
 */
void irgesture_enableLightSensor();

/**
 * @brief Disable specific ambient light sensors function
 *
 * Function disable specific ambient light sensors on the
 * APDS-9960 IC on IR Gesture Click.
 */
void irgesture_disableLightSensor();

/**
 * @brief Read ambient light data function
 *
 * @return
 * 16-bit read ambient light data
 *
 * Function read ambient light data from the two target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
uint16_t irgesture_readAmbientLight();

/**
 * @brief Read RED light data function
 *
 * @return
 * 16-bit read RED light data
 *
 * Function read red light data from the two target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
uint16_t irgesture_readRedLight();

/**
 * @brief Read GREEN light data function
 *
 * @return
 * 16-bit read GREEN light data
 *
 * Function read green light data from the two target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
uint16_t irgesture_readGreenLight();

/**
 * @brief Read BLUE light data function
 *
 * @return
 * 16-bit read BLUE light data
 *
 * Function read blue light data from the two target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
uint16_t irgesture_readBlueLight();

/**
 * @brief Sets the LED current boost value function
 *
 * @param[in] boost value (0-3)
 *  - 0 :       100%;
 *  - 1 :       150%;
 *  - 2 :       200%;
 *  - 3 :       300%;
 *
 * Function set the LED current boost value to the target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
void irgesture_setLedBoost( uint8_t boost );

/**
 * @brief Gets the LED current boost value function
 *
 * @return boost value (0-3)
 *  - 0 :       100%;
 *  - 1 :       150%;
 *  - 2 :       200%;
 *  - 3 :       300%;
 *
 * Function get the LED current boost value to the target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
uint8_t irgesture_getLedBoost();

/**
 * @brief Function decode a gesture event function
 *
 * @return
 * 8-bit position of decode gesture
 *
 * Function processes a gesture event and returns best guessed position
 * engine on the APDS-9960 IC on IR Gesture Click.
 */
uint8_t irgesture_detectGesture();

/**
 * @brief Set gain for proximity function
 *
 * @param[in] gainVal                8-bit gain proximity data
 *
 * Function set gain for proximity on the target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
void irgesture_setProximityGain( uint8_t gainVal );

/**
 * @brief Get gain for proximity function
 *
 * @return
 * 8-bit gain proximity data
 *
 * Function get gain for proximity from the target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
uint8_t irgesture_getProximityGain();

/**
 * @brief Enable specific proximity sensors function
 *
 * Function enable specific proximity sensors
 * and set default gain on the
 * APDS-9960 IC on IR Gesture Click.
 */
void irgesture_enableProximitySensor();

/**
 * @brief Disable specific proximity sensors function
 *
 * Function disable specific proximity sensors
 * and set default gain on the
 * APDS-9960 IC on IR Gesture Click.
 */
void irgesture_disableProximitySensor();

/**
 * @brief Get the current mask for enabled/disabled proximity photodiodes function
 *
 * @return
 * 8-bit photo mask data
 *  - 1     : disabled;
 *  - 0     : enabled;
 *  - Bit 3 : UP;
 *  - Bit 2 : DOWN;
 *  - Bit 1 : LEFT;
 *  - Bit 0 : RIGHT;
 *
 * Function get the current mask for enabled/disabled 
 * proximity photodiodes to the target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
uint8_t irgesture_getProxyPhotoMask();

/**
 * @brief Get the current mask for enabled/disabled proximity photodiodes function
 *
 * @param[in] mask
 *  - 1     : disabled;
 *  - 0     : enabled;
 *  - Bit 3 : UP;
 *  - Bit 2 : DOWN;
 *  - Bit 1 : LEFT;
 *  - Bit 0 : RIGHT;
 *
 * Function get the current mask for enabled/disabled
 * proximity photodiodes to the target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
void irgesture_setProxyPhotoMask( uint8_t mask );

/**
 * @brief Read proximity data function
 *
 * @return
 * 8-bit read proximity data
 *
 * Function read proximity data from the two target
 * register address of APDS-9960 IC on IR Gesture Click.
 */
uint8_t irgesture_readProximityData();


                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_IR_Gesture_STM.c
    @example Click_IR_Gesture_TIVA.c
    @example Click_IR_Gesture_CEC.c
    @example Click_IR_Gesture_KINETIS.c
    @example Click_IR_Gesture_MSP.c
    @example Click_IR_Gesture_PIC.c
    @example Click_IR_Gesture_PIC32.c
    @example Click_IR_Gesture_DSPIC.c
    @example Click_IR_Gesture_AVR.c
    @example Click_IR_Gesture_FT90x.c
    @example Click_IR_Gesture_STM.mbas
    @example Click_IR_Gesture_TIVA.mbas
    @example Click_IR_Gesture_CEC.mbas
    @example Click_IR_Gesture_KINETIS.mbas
    @example Click_IR_Gesture_MSP.mbas
    @example Click_IR_Gesture_PIC.mbas
    @example Click_IR_Gesture_PIC32.mbas
    @example Click_IR_Gesture_DSPIC.mbas
    @example Click_IR_Gesture_AVR.mbas
    @example Click_IR_Gesture_FT90x.mbas
    @example Click_IR_Gesture_STM.mpas
    @example Click_IR_Gesture_TIVA.mpas
    @example Click_IR_Gesture_CEC.mpas
    @example Click_IR_Gesture_KINETIS.mpas
    @example Click_IR_Gesture_MSP.mpas
    @example Click_IR_Gesture_PIC.mpas
    @example Click_IR_Gesture_PIC32.mpas
    @example Click_IR_Gesture_DSPIC.mpas
    @example Click_IR_Gesture_AVR.mpas
    @example Click_IR_Gesture_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __irgesture_driver.h

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */