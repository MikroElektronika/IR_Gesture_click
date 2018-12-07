/*
Example for IR_Gesture Click

    Date          : Aug 2018.
    Author        : Nenad Filipovic

Test configuration PIC32 :
    
    MCU                : P32MX795F512L
    Dev. Board         : EasyPIC Fusion v7
    PIC32 Compiler ver : v4.0.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes GPIO, I2C and LOG structures, set INT pin as input.
- Application Initialization - Initialization driver enable's - I2C,
     set default configuration, enable geasture sensor and start write log.
- Application Task - (code snippet) This is a example which demonstrates the use of IR Gesture Click board.
     IR Gesture Click communicates with register via I2C by write to register and read from register,
     dececting gesture and write log.
     Results are being sent to the Usart Terminal where you can track their changes.
     All data logs write on usb uart changes for every 1 sec.

*/

#include "Click_IR_Gesture_types.h"
#include "Click_IR_Gesture_config.h"


uint8_t position;
uint8_t positionOld = 0xFF;

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_INPUT );

    mikrobus_i2cInit( _MIKROBUS1, &_IRGESTURE_I2C_CFG[0] );

    mikrobus_logInit( _LOG_USBUART_A, 9600 );

    Delay_100ms();
}

void applicationInit()
{
    irgesture_i2cDriverInit( (T_IRGESTURE_P)&_MIKROBUS1_GPIO, (T_IRGESTURE_P)&_MIKROBUS1_I2C, _IRGESTURE_I2C_ADDR );

    irgesture_defaultConfiguration();

    irgesture_enableGestureSensor();

    mikrobus_logWrite( "--------------------", _LOG_LINE );
    mikrobus_logWrite( "  IR Gesture Click  ", _LOG_LINE );
    mikrobus_logWrite( "--------------------", _LOG_LINE );

    Delay_100ms();
}

void applicationTask()
{
    position = irgesture_detectGesture();

    if ( positionOld != position )
    {
        if ( position == _IRGESTURE_FAR )
            mikrobus_logWrite( "       F A R        ", _LOG_LINE );

        if ( position == _IRGESTURE_RIGHT )
            mikrobus_logWrite( "     R I G H T      ", _LOG_LINE );

        if ( position == _IRGESTURE_LEFT )
            mikrobus_logWrite( "      L E F T       ", _LOG_LINE );

        if ( position == _IRGESTURE_UP )
            mikrobus_logWrite( "        U P         ", _LOG_LINE );

        if ( position == _IRGESTURE_DOWN )
            mikrobus_logWrite( "      D O W N       ", _LOG_LINE );

        if ( position == _IRGESTURE_NEAR )
            mikrobus_logWrite( "      N E A R       ", _LOG_LINE );

        positionOld = position;

        mikrobus_logWrite( "--------------------", _LOG_LINE );

        Delay_1sec();
    }
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}