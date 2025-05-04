
#include "MCP23017_ARD.hpp"

/**
 * @brief Construct a new GPIO::GPIO object
 * #@details This is constructor of the GPIO class
 *           This constructor does the initialization of the
 *           MCP23017 IO Expander
 * @author Shreyas D
 *
 */
GPIO::GPIO()
{
    // Constructor
    /**
     * 1. Put the all ports in INPUT mode
     * 2. Configure the interrupts pin in open drain mode.
     */
    Wire.begin();
    this->Port_A.Value = 0x00;
    this->Port_B.Value = 0x00;

    // Set Port-A as Input
    Wire.beginTransmission(DEV_ADDR);
    Wire.write(IODIRA_ADDR); // IODIRA register
    Wire.write(PORT_IN);     // set entire PORT A to input
    Wire.endTransmission();

    // Set Port-B as Input
    Wire.beginTransmission(DEV_ADDR);
    Wire.write(IODIRB_ADDR);
    Wire.write(PORT_IN);
    Wire.endTransmission();
}

/**
 * @brief Set single pin direction
 *
 * @param PIN : Pin Number
 * @param DIR : Directyion(Input/Output)
 */
void GPIO::pinMode(uint8_t pin, bool dir)
{
    uint8_t iVal = 0;
    if (pin < 8)
    {
        Wire.beginTransmission(DEV_ADDR);
        Wire.write(IODIRA_ADDR);
        Wire.endTransmission();
        Wire.requestFrom(DEV_ADDR, 1);
        iVal = Wire.read();

        (dir == INPUT) ? iVal |= (INPUT << pin) : iVal &= (!(1 << pin));

        Wire.beginTransmission(DEV_ADDR);
        Wire.write(IODIRA_ADDR);
        Wire.write(iVal);
        Wire.endTransmission();
    }
    else
    {
        Wire.beginTransmission(DEV_ADDR);
        Wire.write(IODIRB_ADDR);
        Wire.endTransmission();
        Wire.requestFrom(DEV_ADDR, 1);
        iVal = Wire.read();

        (dir == INPUT) ? iVal |= (INPUT << (pin - 8)) : iVal &= (!(1 << (pin - 8)));
    }
}

/**
 * @brief Write binary value on specified pin
 *
 * @param PIN : GPIO pin number
 * @param val : Binary value to be written on the gpio pin
 */
void GPIO::digitalWrite(uint8_t PIN, bool val)
{

    if (PIN < 8)
    {
        this->Port_A.Value = 0x00;
        this->Temp_A = 0x00;
        // Port-A
        Wire.beginTransmission(DEV_ADDR);
        Wire.write(PORTA_ADDR);         // address port A
        Wire.write(this->Port_A.Value); // value to send
        Wire.endTransmission();
    }
    else
    {
        // Port-B
        this->Port_B.Value = 0x00;
        this->Temp_B = 0x00;
        Wire.beginTransmission(DEV_ADDR);
        Wire.write(PORTB_ADDR);
        Wire.write(this->Port_B.Value);
        Wire.endTransmission();
    }
}

/**
 * @brief Read the binary value from specified gpio pin
 *
 * @param PIN  : GPIO pin number to be read
 * @return true : If spcefied port pin is HIGH
 * @return false: If specified port pin is LOW
 */
bool GPIO::digitalRead(uint8_t pin)
{
    uint8_t iVal = 0;

    if (pin < 8)
    {
        // Port-A
        Wire.beginTransmission(DEV_ADDR);
        Wire.write(PORTA_ADDR);
        Wire.endTransmission();
        Wire.requestFrom(DEV_ADDR, 1);
        iVal = Wire.read();

        return ((iVal & (1 << pin)));
    }
    else
    {
        // Port-B
        Wire.beginTransmission(DEV_ADDR);
        Wire.write(PORTB_ADDR);
        Wire.endTransmission();
        Wire.requestFrom(DEV_ADDR, 1);
        iVal = Wire.read();

        return ((iVal & (1 << pin)));
    }
}

/**
 * @brief Set the direction of the entire port
 *
 * @param PORT : Port of which direction to be changed
 * @param DIR  : Port Direction (Input/Output)
 */
void GPIO::portMode(uint8_t Port, uint8_t dir)
{
    if (Port == PORT_A)
    {
        // Direction Control of Port A

        if (dir == INPUT)
        {

            //  Set Port-A as Input
            Wire.beginTransmission(DEV_ADDR);
            Wire.write(IODIRA_ADDR); // IODIRA register
            Wire.write(PORT_IN);     // set entire PORT A to input
            Wire.endTransmission();
        }
        else
        {
            // Port-A Dirtection set to OUTPUT
            Wire.beginTransmission(DEV_ADDR);
            Wire.write(IODIRA_ADDR); // IODIRA register
            Wire.write(PORT_OUT);    // set entire PORT A to output
            Wire.endTransmission();
        }
    }
    else
    {
        // Direction Control of Port B
        if (dir == INPUT)
        {

            // Set Port-B as Input
            Wire.beginTransmission(DEV_ADDR);
            Wire.write(IODIRB_ADDR);
            Wire.write(PORT_IN);
            Wire.endTransmission();
        }
        else
        {
            // Port-B Direction set to OUTPUT
            Wire.beginTransmission(DEV_ADDR);
            Wire.write(IODIRB_ADDR); // IODIRB register
            Wire.write(PORT_OUT);    // set entire PORT B to output
            Wire.endTransmission();
        }
    }
}

/**
 * @brief Write 8-bit value on to spwecified port
 *
 * @param Port : Port Number
 * @param iVAL : Value to be written on the port
 */

void GPIO::porWrite(uint8_t Port, uint8_t iVAL)
{
    if (Port == PORT_A)
    {
        // Write value to Port-A
        Wire.beginTransmission(DEV_ADDR);
        Wire.write(PORTA_ADDR);
        Wire.write(iVAL);
        Wire.endTransmission();
    }
    else
    {
        // Write value to Port-B
        Wire.beginTransmission(DEV_ADDR);
        Wire.write(PORTB_ADDR);
        Wire.write(iVAL);
        Wire.endTransmission();
    }
}

/**
 * @brief Read the 8-bit value from the port
 *
 * @param Port : Port to be read from
 * @return uint8_t : Value read from port
 */

uint8_t GPIO::portRead(uint8_t Port)
{
    uint8_t iVal = 0; // local variable to store the port read value

    if (Port == PORT_A)
    {
        // Read Port-A
        Wire.beginTransmission(DEV_ADDR);
        Wire.write(PORTA_ADDR);
        Wire.endTransmission();
        Wire.requestFrom(DEV_ADDR, 1);
        iVal = Wire.read();
    }
    else
    {
        // Read Port-B
        Wire.beginTransmission(DEV_ADDR);
        Wire.write(PORTB_ADDR);
        Wire.endTransmission();
        Wire.requestFrom(DEV_ADDR, 1);
        iVal = Wire.read();
    }
    return iVal;
}
