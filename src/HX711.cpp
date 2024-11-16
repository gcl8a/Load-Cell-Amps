#include <HX711.h>
#include <FastGPIO.h>

bool HX711::Init(void)
{
    SerialUSB.println("HX711::Init()");

    pinMode(dataPin, INPUT);
    pinMode(clkPin, OUTPUT);

    SerialUSB.println("/HX711::Init()");

    return true;
}

/**
 * This is blocking code, but note that there are no delays, so we're talking
 * a few microseconds.
 */
int32_t HX711::ReadMeasurementAndCmdNextReading(void)
{
    int32_t value = 0;
    
    for(uint8_t i = 31; i >= 8; i--)
    {
        digitalWrite(clkPin, HIGH);
        digitalWrite(clkPin, LOW);
        if(digitalRead(dataPin)) value |= (1ul << i);
    }
    // command the next reading - HARDCODED FOR 1 PULSE -> Gain = 128 on CH A
    digitalWrite(clkPin, HIGH);
    digitalWrite(clkPin, LOW);

    return value / 256;
}
