/**
 * A library for the ZSC31014 load cell amplifier, as found on, for example, the ...
 */

#pragma once

#include <Arduino.h>

class LoadCellAmp
{
private:
    uint8_t address = 0x28; // Default address; can be changed

public:
    LoadCellAmp(void) {}
    virtual bool Init(void) { return false; }

};

class HX711 : public LoadCellAmp
{
private:
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
        if(!digitalRead(dataPin))
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
