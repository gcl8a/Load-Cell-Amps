/**
 * A library for the HX711 load cell amplifier.
 * 
 * https://cdn.sparkfun.com/assets/b/f/5/a/e/hx711F_EN.pdf
 */
#pragma once

#include <Arduino.h>
#include <LoadCell.h>
#include <FastGPIO.h>

/**
 * Though the chip has clock and data pins, it is not using I2C. You can use most 
 * any pin for connections. We use a template so we can use Pololu's FastGPIO library.
 */

template <uint8_t clk, uint8_t dat> class HX711 : public LoadCellAmp
{
private:

    // For keeping track of the gain settings
    #define GAIN_A128   1
    #define GAIN_B32    2
    #define GAIN_A64    3

    uint8_t gain = GAIN_A128;

public:
    HX711(void) {}
    
    virtual bool Init(void) 
    {
        FastGPIO::Pin<clk>::setOutputLow();
        FastGPIO::Pin<dat>::setInput();

        return true;
    }

    uint8_t SetGain(uint8_t g) { if(g >= 1 && g <= 3) gain = g; return gain; }

    bool GetReading(int32_t& reading)
    {
        bool retVal = false;
        if(!FastGPIO::Pin<dat>::isInputHigh()) // LOW on the data line indicates new reading available
        {
            reading = ReadMeasurementAndCmdNextReading();
            retVal = true;
        }

        return retVal;
    }
    
    // The chip has simple sleep and wakeup protocols
    void Sleep(void)    { FastGPIO::Pin<clk>::setOutputValueHigh(); }
    void Wakeup(void)   { FastGPIO::Pin<clk>::setOutputValueLow(); }

private:
    /**
     * ReadMeasurementAndCmdNextReading is blocking, but writing wo/blocking would 
     * require setting up a timer and interrupts and it's not worth it for ~20us.
     */
    int32_t ReadMeasurementAndCmdNextReading(void);
};
