#include <ZSC31014.h>
#include <FastGPIO.h>

bool HX711::Init(void)
{
    SerialUSB.println("HX711::Init()");

    pinMode(dataPin, INPUT);
    pinMode(clkPin, OUTPUT);

    SerialUSB.println("/HX711::Init()");

    return true;
}

int32_t HX711::ReadMeasurementAndCmdNextReading(void)
{
    int32_t value = 0;
    
    for(uint8_t i = 31; i >= 8; i--)
    {
        digitalWrite(clkPin, HIGH);
        digitalWrite(clkPin, LOW);
        if(digitalRead(dataPin)) value |= (1ul << i);
    }
    // command the next reading
    digitalWrite(clkPin, HIGH);
    digitalWrite(clkPin, LOW);

    return value / 256;
}
