
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

void GPIO::pinMode(uint8_t PIN, bool DIR)
{
    if (DIR == INPUT)
    {
    }
    else // DIR = OUTPUT
    {
    }
}

void GPIO::digitalWrite(uint8_t PIN, bool val)
{
    

    if (PIN < 8)
    {
        this->Port_A.Value = 0x00;
        this->Temp_A = 0x00;
        // Port-A
        Wire.beginTransmission(DEV_ADDR);
        Wire.write(PORTA_ADDR); // address port A
        Wire.write(this->Port_A.Value);    // value to send
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

bool GPIO::digitalRead(uint8_t PIN)
{
    if (PIN < 8)
    {
        // Port-A
    }
    else
    {
        // Port-B
    }
}
