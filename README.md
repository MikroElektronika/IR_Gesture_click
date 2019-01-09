![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# IR_Gesture Click

- **CIC Prefix**  : IRGESTURE
- **Author**      : Nenad Filipovic
- **Verison**     : 1.0.0
- **Date**        : Aug 2018.

---

### Software Support

We provide a library for the IR_Gesture Click on our [LibStock](https://libstock.mikroe.com/projects/view/1703/ir-gesture-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

The library covers all the necessary functions to control IR Gesture Click board.
IR_Gesture click communicates with the target board via I2C protocol. 
This library contains drivers for write to and read data from APDS-9960 IC sensor,
set default configuration, enable/disable gesture/ambient light/proximity sensor,
set configuration, read proximity, read ambient light data, 
read red, green or blue color data, detectin gesture, etc. 

Key functions :

- ``` void irgesture_defaultConfiguration()``` -Default configuration function
- ``` void irgesture_enableGestureSensor() ``` - Starts the gesture recognition engine function
- ``` uint8_t irgesture_detectGesture() ``` - Function decode a gesture event function

**Examples Description**

The application is composed of three sections :

- System Initialization - Initializes GPIO, I2C and LOG structures, set INT pin as input.
- Application Initialization - Initialization driver enable's - I2C,
     set default configuration, enable geasture sensor and start write log.
- Application Task - (code snippet) This is a example which demonstrates the use of IR Gesture Click board.
     IR Gesture Click communicates with register via I2C by write to register and read from register,
     dececting gesture and write log.
     Results are being sent to the Usart Terminal where you can track their changes.
     All data logs write on usb uart changes for every 1 sec.


```.c

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

```


The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/1703/ir-gesture-click) page.

Other mikroE Libraries used in the example:

- I2C
- UART


**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
