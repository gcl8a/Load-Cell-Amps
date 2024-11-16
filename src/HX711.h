/**
 * A library for the HX711 load cell amplifier.
 * 
 * https://cdn.sparkfun.com/assets/b/f/5/a/e/hx711F_EN.pdf
 */
#pragma once

#include <LoadCell.h>

class HX711 : public LoadCellAmp
{
private:
    /**
     * Though the chip has clock and data pins, it is not using I2C. You can use most 
     * any pin for connections.
     */
    // The clock pin is used to clock out data
    const uint8_t clkPin = -1;

    // The data pin both indicates a new reading and is used to read data
    uint8_t dataPin = -1;

public:
    HX711(uint8_t clk, uint8_t data) : clkPin(clk), dataPin(data) {}
    virtual bool Init(void);

    bool GetReading(int32_t& reading)
    {
        bool retVal = false;
        if(!digitalRead(dataPin)) // LOW on the data line indicates new reading available
        {
            reading = ReadMeasurementAndCmdNextReading();
            retVal = true;
        }

        return retVal;
    }
    
    void Sleep(void);
    void Wakeup(void);

private:
    int32_t ReadMeasurementAndCmdNextReading(void);
};
