/*
    __irgesture_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__irgesture_driver.h"
#include "__irgesture_hal.c"

/* ------------------------------------------------------------------- MACROS */





/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __IRGESTURE_DRV_I2C__
static uint8_t _slaveAddress;
#endif

/* APDS-9960 I2C address */
const uint8_t  _IRGESTURE_I2C_ADDR      = 0x39;

/* APDS-9960 register addresses */
const uint8_t _IRGESTURE_ENABLE         = 0x80;
const uint8_t _IRGESTURE_ATIME          = 0x81;
const uint8_t _IRGESTURE_WTIME          = 0x83;
const uint8_t _IRGESTURE_AILTL          = 0x84;
const uint8_t _IRGESTURE_AILTH          = 0x85;
const uint8_t _IRGESTURE_AIHTL          = 0x86;
const uint8_t _IRGESTURE_AIHTH          = 0x87;
const uint8_t _IRGESTURE_PILT           = 0x89;
const uint8_t _IRGESTURE_PIHT           = 0x8B;
const uint8_t _IRGESTURE_PERS           = 0x8C;
const uint8_t _IRGESTURE_CONFIG1        = 0x8D;
const uint8_t _IRGESTURE_PPULSE         = 0x8E;
const uint8_t _IRGESTURE_CONTROL        = 0x8F;
const uint8_t _IRGESTURE_CONFIG2        = 0x90;
const uint8_t _IRGESTURE_ID             = 0x92;
const uint8_t _IRGESTURE_STATUS         = 0x93;
const uint8_t _IRGESTURE_CDATAL         = 0x94;
const uint8_t _IRGESTURE_CDATAH         = 0x95;
const uint8_t _IRGESTURE_RDATAL         = 0x96;
const uint8_t _IRGESTURE_RDATAH         = 0x97;
const uint8_t _IRGESTURE_GDATAL         = 0x98;
const uint8_t _IRGESTURE_GDATAH         = 0x99;
const uint8_t _IRGESTURE_BDATAL         = 0x9A;
const uint8_t _IRGESTURE_BDATAH         = 0x9B;
const uint8_t _IRGESTURE_PDATA          = 0x9C;
const uint8_t _IRGESTURE_POFFSET_UR     = 0x9D;
const uint8_t _IRGESTURE_POFFSET_DL     = 0x9E;
const uint8_t _IRGESTURE_CONFIG3        = 0x9F;
const uint8_t _IRGESTURE_GPENTH         = 0xA0;
const uint8_t _IRGESTURE_GEXTH          = 0xA1;
const uint8_t _IRGESTURE_GCONF1         = 0xA2;
const uint8_t _IRGESTURE_GCONF2         = 0xA3;
const uint8_t _IRGESTURE_GOFFSET_U      = 0xA4;
const uint8_t _IRGESTURE_GOFFSET_D      = 0xA5;
const uint8_t _IRGESTURE_GOFFSET_L      = 0xA7;
const uint8_t _IRGESTURE_GOFFSET_R      = 0xA9;
const uint8_t _IRGESTURE_GPULSE         = 0xA6;
const uint8_t _IRGESTURE_GCONF3         = 0xAA;
const uint8_t _IRGESTURE_GCONF4         = 0xAB;
const uint8_t _IRGESTURE_GFLVL          = 0xAE;
const uint8_t _IRGESTURE_GSTATUS        = 0xAF;
const uint8_t _IRGESTURE_IFORCE         = 0xE4;
const uint8_t _IRGESTURE_PICLEAR        = 0xE5;
const uint8_t _IRGESTURE_CICLEAR        = 0xE6;
const uint8_t _IRGESTURE_AICLEAR        = 0xE7;
const uint8_t _IRGESTURE_GFIFO_U        = 0xFC;
const uint8_t _IRGESTURE_GFIFO_D        = 0xFD;
const uint8_t _IRGESTURE_GFIFO_L        = 0xFE;
const uint8_t _IRGESTURE_GFIFO_R        = 0xFF;

/* Default values */
const uint8_t  DEFAULT_ATIME           = 219;     // 103ms
const uint8_t  DEFAULT_WTIME           = 246;     // 27ms
const uint8_t  DEFAULT_PROX_PPULSE     = 0x87;    // 16us, 8 pulses
const uint8_t  DEFAULT_GESTURE_PPULSE  = 0x89;    // 16us, 10 pulses
const uint8_t  DEFAULT_POFFSET_UR      = 0;       // 0 offset
const uint8_t  DEFAULT_POFFSET_DL      = 0;       // 0 offset
const uint8_t  DEFAULT_CONFIG1         = 0x60;    // No 12x wait (WTIME) factor
const uint8_t  DEFAULT_LDRIVE          = 0;       // LED_DRIVE_100MA
const uint8_t  DEFAULT_PGAIN           = 2;       // PGAIN_4X
const uint8_t  DEFAULT_AGAIN           = 1;       // AGAIN_4X
const uint8_t  DEFAULT_PILT            = 0;       // Low proximity threshold
const uint8_t  DEFAULT_PIHT            = 50;      // High proximity threshold
const uint16_t DEFAULT_AILT            = 0xFFFF;  // Force interrupt for calibration
const uint8_t  DEFAULT_AIHT            = 0;
const uint8_t  DEFAULT_PERS            = 0x11;    // 2 consecutive prox or ALS for int.
const uint8_t  DEFAULT_CONFIG2         = 0x01;    // No saturation interrupts or LED boost
const uint8_t  DEFAULT_CONFIG3         = 0;       // Enable all photodiodes, no SAI
const uint8_t  DEFAULT_GPENTH          = 40;      // Threshold for entering gesture mode
const uint8_t  DEFAULT_GEXTH           = 30;      // Threshold for exiting gesture mode
const uint8_t  DEFAULT_GCONF1          = 0x40;    // 4 gesture events for int., 1 for exit
const uint8_t  DEFAULT_GGAIN           = 2;       // GGAIN_4X
const uint8_t  DEFAULT_GLDRIVE         = 0;       // LED_DRIVE_100MA
const uint8_t  DEFAULT_GWTIME          = 1;       // GWTIME_2_8MS
const uint8_t  DEFAULT_GOFFSET         = 0;       // No offset scaling for gesture mode
const uint8_t  DEFAULT_GPULSE          = 0xC9;    // 32us, 10 pulses
const uint8_t  DEFAULT_GCONF3          = 0;       // All photodiodes active during gesture
const uint8_t  DEFAULT_GIEN            = 0;       // Disable gesture interrupts

/* Bit fields */
const uint8_t _IRGESTURE_PON            = 0b00000001;
const uint8_t _IRGESTURE_AEN            = 0b00000010;
const uint8_t _IRGESTURE_PEN            = 0b00000100;
const uint8_t _IRGESTURE_WEN            = 0b00001000;
const uint8_t _IRGESTURE_AIEN           = 0b00010000;
const uint8_t _IRGESTURE_PIEN           = 0b00100000;
const uint8_t _IRGESTURE_GEN            = 0b01000000;
const uint8_t _IRGESTURE_GVALID         = 0b00000001;

/* Geasture results */
const uint8_t _IRGESTURE_FAR            = 0x00;
const uint8_t _IRGESTURE_RIGHT          = 0x01;
const uint8_t _IRGESTURE_LEFT           = 0x02;
const uint8_t _IRGESTURE_UP             = 0x03;
const uint8_t _IRGESTURE_DOWN           = 0x04;
const uint8_t _IRGESTURE_NEAR           = 0x05;

/* Error code for returned values */
const uint8_t  DEFAULT_ERROR           = 0xFF;



/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */

/**
 * @brief Compare input data
 *
 * @param[in] 8-bit data 1
 *
 * @param[in] 8-bit data 2
 *
 * @param[in] 8-bit data 3
 *
 * @param[in] 8-bit data 4
 *
 * @return
 * byte of data - position of gesture
 *
 */
static uint8_t _compareData( uint8_t value0, uint8_t value1, uint8_t value2, uint8_t value3 );

/**
 * @brief Reads and returns the contents of the ENABLE register
 *
 * @return Contents of the ENABLE register. 0xFF if error.
 *
 */
static uint8_t _getMode();

/**
 * @brief Enables or disables a feature in the APDS-9960
 *
 * @param[in] mode which feature to enable
 *
 * @param[in] enable true or false
 *
 */
static void _setMode( uint8_t mode, uint8_t _enable );

/**
 * @brief Processes the raw gesture data to determine swipe direction
 *
 * @return 1 if near or far state seen. 0 otherwise.
 *
 */
static uint8_t _processGestureData( gesture_data_t *gesture_data );

/**
 * @brief Determines swipe direction or near/far state
 *
 * @return 1 if near/far event. 0 otherwise.
 *
 */
static uint8_t _decodeGesture( gesture_data_t *gesture_data );

/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */

static uint8_t _compareData( uint8_t value0, uint8_t value1, uint8_t value2, uint8_t value3 )
{
    uint8_t maxData;
    uint16_t sumData;
    uint8_t result;
    uint8_t cnt;
    uint8_t temp[ 4 ];
    temp[ 0 ] = value0;
    temp[ 1 ] = value1;
    temp[ 2 ] = value2;
    temp[ 3 ] = value3;
    
    maxData = value0;
    sumData = 0;
    result = 1;
    
    for ( cnt = 0; cnt < 4; cnt++ )
    {
        if ( maxData < temp [ cnt ] )
        {
            maxData = temp[ cnt ];
            result = cnt + 1;
        }
        
        sumData += temp[ cnt ];
    }

    if ( sumData > 1000 )
        result = 5;
    
    if ( maxData < 16 )
        result = 0;

    return result;
}

static uint8_t _getMode()
{
    uint8_t enable_value;

    enable_value = irgesture_readData( _IRGESTURE_ENABLE );

    return enable_value;
}

static void _setMode( uint8_t mode, uint8_t _enable )
{
    uint8_t reg_val = _getMode();

    if ( reg_val == DEFAULT_ERROR )
        return;

    if ( mode == 0x07 )
    {
        reg_val = 0x00;

        if ( _enable )
            reg_val = 0x7F;
    } 
    else 
    {
        reg_val &= ~( 1 << mode );

        if( _enable )
            reg_val |= ( 1 << mode );
    }

    irgesture_writeData( _IRGESTURE_ENABLE, reg_val );
}

static uint8_t _processGestureData( gesture_data_t *gesture_data )
{
    uint8_t u_first = 0;
    uint8_t d_first = 0;
    uint8_t l_first = 0;
    uint8_t r_first = 0;
    uint8_t u_last = 0;
    uint8_t d_last = 0;
    uint8_t l_last = 0;
    uint8_t r_last = 0;
    uint16_t ud_ratio_first;
    uint16_t lr_ratio_first;
    uint16_t ud_ratio_last;
    uint16_t lr_ratio_last;
    uint16_t ud_delta;
    uint16_t lr_delta;
    uint16_t i;

    if( gesture_data->total_gestures <= 4 )
        return -1;

    if( ( gesture_data->total_gestures <= 32 ) && ( gesture_data->total_gestures > 0 ) )
    {
        for ( i = 0; i < gesture_data->total_gestures; i++ )
        {
            if ( ( gesture_data->u_data[i] > 10 ) && ( gesture_data->d_data[i] > 10 ) && ( gesture_data->l_data[i] > 10 ) && ( gesture_data->r_data[i] > 10 ) )
            {
                u_first = gesture_data->u_data[i];
                d_first = gesture_data->d_data[i];
                l_first = gesture_data->l_data[i];
                r_first = gesture_data->r_data[i];
                break;
            }
        }

        if ( ( u_first == 0 ) || 
             ( d_first == 0 ) ||
             ( l_first == 0 ) || 
             ( r_first == 0 ) )
            return -1;
            
        for ( i = gesture_data->total_gestures - 1; i >= 0; i-- )
        {
            if( ( gesture_data->u_data[i] > 10 ) && ( gesture_data->d_data[i] > 10 ) && ( gesture_data->l_data[i] > 10 ) && ( gesture_data->r_data[i] > 10 ) )
            {
                u_last = gesture_data->u_data[i];
                d_last = gesture_data->d_data[i];
                l_last = gesture_data->l_data[i];
                r_last = gesture_data->r_data[i];
                break;
            }
        }
    }

    ud_ratio_first = ( ( u_first - d_first ) * 100 ) / ( u_first + d_first );
    lr_ratio_first = ( ( l_first - r_first ) * 100 ) / ( l_first + r_first );
    ud_ratio_last = ( ( u_last - d_last ) * 100 ) / ( u_last + d_last );
    lr_ratio_last = ( ( l_last - r_last ) * 100 ) / ( l_last + r_last );

    ud_delta = ud_ratio_last - ud_ratio_first;
    lr_delta = lr_ratio_last - lr_ratio_first;

    gesture_data->ud_delta += ud_delta;
    gesture_data->lr_delta += lr_delta;

    if ( gesture_data->ud_delta >= 50 )
        gesture_data->ud_count = 1;
    else 
        if ( gesture_data->ud_delta <= -50 )
            gesture_data->ud_count = -1;
        else
            gesture_data->ud_count = 0;

    if ( gesture_data->lr_delta >= 50 )
        gesture_data->lr_count = 1;
    else 
        if ( gesture_data->lr_delta <= -50 )
            gesture_data->lr_count = -1;
        else
            gesture_data->lr_count = 0;

    if ( ( gesture_data->ud_count == 0 ) && ( gesture_data->lr_count == 0 ) )
    {
        if ( ( ud_delta  < 20 ) && ( lr_delta < 20 ) )
        {
            if ( ( ud_delta == 0 ) && ( lr_delta == 0 ) )
                gesture_data->near_count++;
            else 
                if ( ( ud_delta != 0 ) || ( lr_delta != 0 ) )
                    gesture_data->far_count++;

            if ( ( gesture_data->near_count >= 10 ) && ( gesture_data->far_count >= 2 ) )
            {
                if ( ( ud_delta == 0 ) && ( lr_delta == 0 ) )
                    gesture_data->state = NEAR_STATE;
                else 
                    if ( ( ud_delta != 0 ) && ( lr_delta != 0 ) )
                        gesture_data->state = FAR_STATE;
                
                return 0;
            }
        }
    } 
    else 
    {
        if ( (  ud_delta < 20 ) && ( lr_delta < 20 ) )
        {
            if( ( ud_delta == 0 ) && ( lr_delta == 0 ) )
                gesture_data->near_count++;

            if( gesture_data->near_count >= 10 )
            {
                gesture_data->ud_count = 0;
                gesture_data->lr_count = 0;
                gesture_data->ud_delta = 0;
                gesture_data->lr_delta = 0;
            }
        }
    }
    return -1;
}


static uint8_t _decodeGesture( gesture_data_t *gesture_data )
{
    if ( gesture_data->state == NEAR_STATE )
    {
        gesture_data->motion = DIR_NEAR;
        return 0;
    } 
    else if ( gesture_data->state == FAR_STATE )
    {
         gesture_data->motion = DIR_FAR;
         return 0;
    }

    if ( ( gesture_data->ud_count == -1 ) && ( gesture_data->lr_count == 0 ) )
        gesture_data->motion = DIR_UP;
    else if ( ( gesture_data->ud_count == 1 ) && ( gesture_data->lr_count == 0) )
            gesture_data->motion = DIR_DOWN;
    else if ( ( gesture_data->ud_count == 0 ) && ( gesture_data->lr_count == 1) )
            gesture_data->motion = DIR_RIGHT;
    else if ( ( gesture_data->ud_count == 0 ) && ( gesture_data->lr_count == -1) )
            gesture_data->motion = DIR_LEFT;
    else if ( ( gesture_data->ud_count == -1 ) && ( gesture_data->lr_count == 1) )
    {
        if ( gesture_data->ud_delta > gesture_data->lr_delta )
            gesture_data->motion = DIR_UP;
        else
            gesture_data->motion = DIR_RIGHT;
    }
    else if ( ( gesture_data->ud_count == 1 ) && ( gesture_data->lr_count == -1) )
        {
            if ( gesture_data->ud_delta > gesture_data->lr_delta )
                gesture_data->motion = DIR_DOWN;
            else
                gesture_data->motion = DIR_LEFT;
        }
    else if ( ( gesture_data->ud_count == -1 ) && ( gesture_data->lr_count == -1) )
         {
             if ( gesture_data->ud_delta > gesture_data->lr_delta )
                 gesture_data->motion = DIR_UP;
             else
                 gesture_data->motion = DIR_LEFT;
         }
    else if ( ( gesture_data->ud_count == 1 ) && ( gesture_data->lr_count == 1) )
    {
        if ( gesture_data->ud_delta > gesture_data->lr_delta )
            gesture_data->motion = DIR_DOWN;
        else
            gesture_data->motion = DIR_RIGHT;
    }
    else
        return -1;

    return 0;
}

/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __IRGESTURE_DRV_SPI__

void irgesture_spiDriverInit(T_IRGESTURE_P gpioObj, T_IRGESTURE_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __IRGESTURE_DRV_I2C__

void irgesture_i2cDriverInit(T_IRGESTURE_P gpioObj, T_IRGESTURE_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __IRGESTURE_DRV_UART__

void irgesture_uartDriverInit(T_IRGESTURE_P gpioObj, T_IRGESTURE_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif



/* ----------------------------------------------------------- IMPLEMENTATION */


/* Generic write data function */
void irgesture_writeData( uint8_t regAddress, uint8_t writeData )
{
    uint8_t buffer[2];
    buffer[ 0 ] = regAddress;
    buffer[ 1 ] = writeData;

    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, buffer, 2, END_MODE_STOP );
}

/* Generic read data function */
uint8_t irgesture_readData( uint8_t regAddress )
{
    uint8_t writeReg[ 1 ];
    uint8_t readReg[ 1 ];

    writeReg[ 0 ] = regAddress;

    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, writeReg, 1, END_MODE_RESTART );
    Delay_10ms();
    hal_i2cRead( _slaveAddress, readReg, 1, END_MODE_STOP );
    Delay_10ms();

    return readReg[0];
}

/* Get interrupt function */
uint8_t irgesture_getInterrupt()
{
    return hal_gpio_intGet();
}

/* Default configuration function */
void irgesture_defaultConfiguration()
{
    uint8_t val;
    uint8_t drive;

    irgesture_writeData( _IRGESTURE_ATIME, DEFAULT_ATIME );

    irgesture_writeData( _IRGESTURE_WTIME, DEFAULT_WTIME );

    irgesture_writeData( _IRGESTURE_PPULSE, DEFAULT_PROX_PPULSE );

    irgesture_writeData( _IRGESTURE_POFFSET_UR, DEFAULT_POFFSET_UR );

    irgesture_writeData( _IRGESTURE_POFFSET_DL, DEFAULT_POFFSET_DL );

    irgesture_writeData( _IRGESTURE_CONFIG1, DEFAULT_CONFIG1 );

    irgesture_writeData( _IRGESTURE_CONFIG1, DEFAULT_CONFIG1 );

    val = irgesture_readData( _IRGESTURE_CONTROL );
    drive = 0x00;
    drive &= 0x03;
    drive = drive << 6;
    val &= 0x3F;
    val |= drive;

    irgesture_writeData( _IRGESTURE_CONTROL, val );

    val = irgesture_readData( _IRGESTURE_CONTROL );
    drive = 0x02;
    drive &= 0x03;
    drive = drive << 2;
    val &= 0xF3;
    val |= drive;

    irgesture_writeData( _IRGESTURE_CONTROL, val );

    val = irgesture_readData( _IRGESTURE_CONTROL );
    drive = 0x01;
    drive &= 0x03;
    val &= 0xFC;
    val |= drive;

    irgesture_writeData( _IRGESTURE_CONTROL, val );

    irgesture_writeData( _IRGESTURE_PILT, 0x00 );

    irgesture_writeData( _IRGESTURE_PIHT, 0x32 );

    irgesture_writeData( _IRGESTURE_AILTL, 0xFF );

    irgesture_writeData( _IRGESTURE_AILTH, 0x00 );

    irgesture_writeData( _IRGESTURE_AIHTL, 0xFF );

    irgesture_writeData( _IRGESTURE_AILTH, 0x00 );

    irgesture_writeData( _IRGESTURE_PERS, 0x11 );

    irgesture_writeData( _IRGESTURE_CONFIG2, 0x01 );

    irgesture_writeData( _IRGESTURE_CONFIG3, 0x00 );

    irgesture_writeData( _IRGESTURE_GPENTH, 0x28 );

    irgesture_writeData( _IRGESTURE_GEXTH, 0x1E );

    irgesture_writeData( _IRGESTURE_GCONF1,  0x40 );

    irgesture_writeData( _IRGESTURE_GCONF1,  0x40 );

    val = irgesture_readData( _IRGESTURE_GCONF2 );
    val &= 0x9F;
    val |= 0x40;
    irgesture_writeData( _IRGESTURE_GCONF2, val );

    val = irgesture_readData( _IRGESTURE_GCONF2 );
    val &= 0xE7;
    val |= 0x08;
    irgesture_writeData( _IRGESTURE_GCONF2, val );

    val = irgesture_readData( _IRGESTURE_GCONF2 );
    val &= 0xF8;
    val |= 0x01;
    irgesture_writeData( _IRGESTURE_GCONF2, val );

    irgesture_writeData( _IRGESTURE_GOFFSET_U,  0x00 );

    irgesture_writeData( _IRGESTURE_GOFFSET_D,  0x00 );

    irgesture_writeData( _IRGESTURE_GOFFSET_L,  0x00 );

    irgesture_writeData( _IRGESTURE_GOFFSET_R,  0x00 );

    irgesture_writeData( _IRGESTURE_GPULSE,  0xC9 );

    irgesture_writeData( _IRGESTURE_GCONF3,  0x00 );

    val = irgesture_readData( _IRGESTURE_GCONF4 );
    val &= 0xFD;
    val |= 0x02;
    irgesture_writeData( _IRGESTURE_GCONF2, val );
}

/* Processes a gesture event function */
gesture_dir_t irgesture_gestureReadGesture()
{
    uint8_t fifo_count;
    gesture_data_t gesture_data;
    uint8_t fifo_data[ 132 ];
    uint8_t fifo_addr[ 1 ];
    uint16_t i;
    
    fifo_count = 0;
    fifo_addr[ 0 ] = _IRGESTURE_GFIFO_U;

    if( !irgesture_available() || !( _getMode() & 0x41 ) )
    {
        return DIR_NONE;
    }

    while( 1 )
    {
        Delay_100ms();

        if( irgesture_available() )
        {
            fifo_count = irgesture_readData( _IRGESTURE_GFLVL );

            if( fifo_count > 0 )
            {
                hal_i2cStart();
                hal_i2cWrite( _slaveAddress, fifo_addr, 1, END_MODE_RESTART );
                hal_i2cRead( _slaveAddress, fifo_data, fifo_count * 4, END_MODE_STOP );

                for( i = 0; i < fifo_count; i += 4 )
                {
                    gesture_data.u_data[gesture_data.index] = fifo_data[i];
                    gesture_data.d_data[gesture_data.index] = fifo_data[i + 1];
                    gesture_data.l_data[gesture_data.index] = fifo_data[i + 2];
                    gesture_data.r_data[gesture_data.index] = fifo_data[i + 3];
                    gesture_data.index++;
                    gesture_data.total_gestures++;
                }

                if( !_processGestureData( &gesture_data ) )
                {
                    if( !_decodeGesture( &gesture_data ) )
                    {

                    }
                }

                gesture_data.index = 0;
                gesture_data.total_gestures = 0;
            }
        } 
        else 
        {
            Delay_100ms();
            _decodeGesture( &gesture_data );

            return gesture_data.motion;
        }
    }
}

/* Sets gesture mode function */
void irgesture_setGestureMode()
{
    uint8_t val;

    val = irgesture_readData( _IRGESTURE_GCONF4 );

    val &= ~( 1 << 0 );

    val |= ( 1 << 0 );

    irgesture_writeData( _IRGESTURE_GCONF4, val );
}

/* Enable power sensor function */
void irgesture_enablePower()
{
    _setMode( 0x00, 1 );
}

/* Disable power sensor function */
void irgesture_disablePower()
{
    _setMode( 0x00, 0 );
}

/* Set gain for ambient light function */
void irgesture_setAmbientLightGain( uint8_t gainVal )
{
    uint8_t val;
    
    val = 0;

    val = irgesture_readData( _IRGESTURE_CONTROL );

    val &= ~( 1 << 0 ) | ( 1 << 1 );
    gainVal |= val;

    irgesture_writeData( _IRGESTURE_CONTROL, gainVal );
}

/* Get gain for ambient light function */
uint8_t irgesture_getAmbientLightGain()
{
    uint8_t val;

    val = 0;

    val = irgesture_readData( _IRGESTURE_CONTROL );

    val &= 0x03;

    return val;
}

/* Enable specific light sensors function */
void irgesture_enableLightSensor()
{
    irgesture_setAmbientLightGain( DEFAULT_AGAIN );

    irgesture_enablePower();
    
    _setMode( 0x01, 1 );
}

/* Disable specific light sensors function */
void irgesture_disableLightSensor()
{
    irgesture_enablePower();

    _setMode( 0x01, 0 );
}

/* Read ambient light data function */
uint16_t irgesture_readAmbientLight()
{
    uint8_t buffer[ 2 ];
    uint16_t result;

    buffer[ 0 ] = irgesture_readData( _IRGESTURE_CDATAH );
    buffer[ 1 ] = irgesture_readData( _IRGESTURE_CDATAL );
    
    result = buffer[ 0 ];
    result <<= 8;
    result |= buffer[ 1 ];

    return result;
}

/* Read RED light data function */
uint16_t irgesture_readRedLight()
{
    uint8_t buffer[ 2 ];
    uint16_t result;

    buffer[ 0 ] = irgesture_readData( _IRGESTURE_RDATAH );
    buffer[ 1 ] = irgesture_readData( _IRGESTURE_RDATAL );
    
    result = buffer[ 0 ];
    result <<= 8;
    result |= buffer[ 1 ];

    return result;
}

/* Read GREEN light data function */
uint16_t irgesture_readGreenLight()
{
    uint8_t buffer[ 2 ];
    uint16_t result;

    buffer[ 0 ] = irgesture_readData( _IRGESTURE_GDATAH );
    buffer[ 1 ] = irgesture_readData( _IRGESTURE_GDATAL );

    result = buffer[ 0 ];
    result <<= 8;
    result |= buffer[ 1 ];

    return result;
}

/* Read BLUE light data function */
uint16_t irgesture_readBlueLight()
{
    uint8_t buffer[ 2 ];
    uint16_t result;

    buffer[ 0 ] = irgesture_readData( _IRGESTURE_BDATAH );
    buffer[ 1 ] = irgesture_readData( _IRGESTURE_BDATAL );

    result = buffer[ 0 ];
    result <<= 8;
    result |= buffer[ 1 ];

    return result;
}

/* Sets the LED current boost value function */
void irgesture_setLedBoost( uint8_t boost )
{
    uint8_t val;

    val = 0;

    val = irgesture_readData( _IRGESTURE_CONFIG2 );

    val &= ~( 1 << 4 ) | ( 1 << 5 );
    
    boost = ( boost << 4 ) | val;

    irgesture_writeData( _IRGESTURE_CONFIG2, boost );
}

/* Gets the LED current boost value function */
uint8_t irgesture_getLedBoost()
{
    uint8_t val;

    val = irgesture_readData( _IRGESTURE_CONFIG2 );

    val = ( val >> 4 ) & 0x03;

    return val;
}

/* Determines if there is a gesture available function */
uint8_t irgesture_available()
{
    uint8_t val;

    val = 0;

    val = irgesture_readData( _IRGESTURE_GSTATUS );

    val &= _IRGESTURE_GVALID;

    return ( val == 1 ) ? 1 : 0;
}

/* Set gain for gesture function */
void irgesture_setGestureGain( uint8_t gainVal )
{
    uint8_t val;

    val = 0;

    val = irgesture_readData( _IRGESTURE_GCONF2 );

    val &= ~( 1 << 5 ) | ( 1 << 6 );

    gainVal = ( gainVal << 5 ) | val;

    irgesture_writeData( _IRGESTURE_GCONF2, gainVal );
}

/* Get gain for gesture function */
uint8_t irgesture_getGestureGain()
{
    uint8_t val;

    val = 0;

    val = irgesture_readData( _IRGESTURE_GCONF2 );

    val = ( val >> 5 ) & 0x03;

    return val;
}

/* Starts the gesture recognition engine function */
void irgesture_enableGestureSensor()
{
    uint8_t temp;
    uint8_t val;
    
    temp = 0xFF;
    val = 0;
    
    irgesture_writeData( _IRGESTURE_WTIME, 0xFF );
    
    temp = DEFAULT_GESTURE_PPULSE;
    
    irgesture_writeData( _IRGESTURE_PPULSE, 0xFF );

    val = irgesture_readData( _IRGESTURE_GCONF4 );

    val &= ~( 1 << 1 );

    val |= ( 1 << 1 );

    irgesture_writeData( _IRGESTURE_GCONF4, val );

    irgesture_setGestureMode();
    
    irgesture_enablePower();
    
    _setMode( 0x03, 1 );
    _setMode( 0x02, 1 );
    _setMode( 0x06, 1 );
}

/* Disable the gesture recognition engine function */
void irgesture_disableGestureSensor()
{
    uint8_t val;
    
    val = 0;
    
    val = irgesture_readData( _IRGESTURE_GCONF4 );

    val &= ~( 1 << 0 );

    irgesture_writeData( _IRGESTURE_GCONF4, val );
    
    _setMode( 0x06, 0 );
}

/* Function decode a gesture event function */
uint8_t irgesture_detectGesture()
{
    uint8_t dataRight;
    uint8_t dataLeft;
    uint8_t dataUp;
    uint8_t dataDown;
    uint8_t cnt;
    uint8_t result;
    
    dataRight = irgesture_readData( _IRGESTURE_GFIFO_R );
    dataLeft = irgesture_readData( _IRGESTURE_GFIFO_L );
    dataUp = irgesture_readData( _IRGESTURE_GFIFO_U );
    dataDown = irgesture_readData( _IRGESTURE_GFIFO_D );
    
    result = _compareData( dataRight, dataLeft, dataUp, dataDown );
    
    return result;
}

/* Set gain for proximity function */
void irgesture_setProximityGain( uint8_t gainVal )
{
    uint8_t val;
    
    val = 0;

    val = irgesture_readData( _IRGESTURE_CONTROL );

    val &= ~( 1 << 2 ) | ( 1 << 3 );
    gainVal = ( gainVal << 2 ) | val;

    irgesture_writeData( _IRGESTURE_CONTROL, gainVal );
}

/* Get gain for proximity function */
uint8_t irgesture_getProximityGain()
{
    uint8_t result;

    result = 0;

    result = irgesture_readData( _IRGESTURE_CONTROL );

    result = ( result >> 2 ) & 0x03;

    return result;
}

/* Enable specific proximity sensors function */
void irgesture_enableProximitySensor()
{
    /* Set default gain, LED, interrupts, enable power, and enable sensor */
    irgesture_setProximityGain( DEFAULT_PGAIN );

    irgesture_enablePower();
    
    _setMode( 0x02, 1 );
}

/* Disable specific proximity sensors function */
void irgesture_disableProximitySensor()
{
    irgesture_enablePower();

    _setMode( 0x02, 0 );
}

/* Get the current mask for enabled/disabled proximity photodiodes function */
uint8_t irgesture_getProxyPhotoMask()
{
    uint8_t result;

    result = 0;

    result = irgesture_readData( _IRGESTURE_CONFIG3 );

    result &= 0x0f;

    return result;
}

/* Sets the mask for enabling/disabling proximity photodiodes function */
void irgesture_setProxyPhotoMask( uint8_t mask )
{
    uint8_t val;

    val = 0;

    val = irgesture_readData( _IRGESTURE_CONFIG3 );

    val &= ~( 1 << 0 ) | ( 1 << 1 )| ( 1 << 2 )| ( 1 << 3 );
    mask |= val;

    irgesture_writeData( _IRGESTURE_CONFIG3, mask );
}

/* Read proximity data function */
uint8_t irgesture_readProximityData()
{
    uint8_t result;

    result = 0;

    result = irgesture_readData( _IRGESTURE_PDATA );

    return result;
}


/* -------------------------------------------------------------------------- */
/*
  __irgesture_driver.c

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