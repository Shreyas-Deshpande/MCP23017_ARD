#ifndef MCP23017_ARD_H
#define MCP23017_ARD_H

#include<Arduino.h>
#include <Wire.h>

#define DEV_ADDR 0x20

/**
 * @brief These are the internal Register addresses of the MCP23017
 *
 */
#define IODIRA_ADDR     0x00
#define IODIRB_ADDR     0x01
#define IPOLA_ADDR      0x02
#define IPOLB_ADDR      0x03
#define GPINTENA_ADDR   0x04
#define GPINTENB_ADDR   0x05
#define DEFVALA_ADDR    0x06
#define DEFVALB_ADDR    0x07
#define INTCONA_ADDR    0x08
#define INTCONB_ADDR    0x09
#define IOCONA_ADDR     0x0A
#define IOCONB_ADDR     0x0B
#define GPPUA_ADDR      0x0C
#define GPPUB_ADDR      0x0D
#define INTFA_ADDR      0x0E
#define INTFB_ADDR      0x0F
#define INTCAPA_ADDR    0x10
#define INTCAPB_ADDR    0x11
#define PORTA_ADDR      0x12
#define PORTB_ADDR      0x13
#define OLATA_ADDR      0x14
#define OLATB_ADDR      0x15


/*
*    Port Direction Macros
*/
#define PORT_OUT    0x00
#define PORT_IN     0xFF

typedef struct gpio
    {
        uint8_t pin_0 : 1;
        uint8_t pin_1 : 1;
        uint8_t pin_2 : 1;
        uint8_t pin_3 : 1;
        uint8_t pin_4 : 1;
        uint8_t pin_5 : 1;
        uint8_t pin_6 : 1;
        uint8_t pin_7 : 1;

    } gpio_t;

    typedef union Register
    {
        uint8_t Value;
        gpio_t PINS;
    } Reg_t;


typedef class GPIO
{
private:
    /**
     * Port Structure
     */
    
    Reg_t Port_A;
    Reg_t Port_B;
    uint8_t Temp_A;
    uint8_t Temp_B;

public:
    
    void pinMode(uint8_t PIN, bool DIR);
    void digitalWrite(uint8_t PIN, bool val);
    bool digitalRead(uint8_t PIN);
}PORT;

#endif
