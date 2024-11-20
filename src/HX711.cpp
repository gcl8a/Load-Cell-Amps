#include <HX711.h>

int32_t HX711::ReadMeasurementAndCmdNextReading(void)
{   
    // 32-bit manipulation is slow, so use three bytes to collect data
    uint8_t highByte = 0;
    uint8_t medByte = 0;
    uint8_t lowByte = 0;

    for(uint8_t i = 0; i < 8; i++)
    {
        FastGPIO::Pin<clk>::setOutputValueHigh();

        // add a little stretch to the HIGH signal -- datasheet says minimum of 0.2 us
        // (4) nop's is ~250ns, plus the pin call puts us well over the minimum
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");

        FastGPIO::Pin<clk>::setOutputValueLow();

        highByte <<= 1;
        if(FastGPIO::Pin<dat>::isInputHigh()) highByte++;
    }

    for(uint8_t i = 0; i < 8; i++)
    {
        FastGPIO::Pin<clk>::setOutputValueHigh();

        // add a little stretch to the HIGH signal
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");

        FastGPIO::Pin<clk>::setOutputValueLow();

        medByte <<= 1;
        if(FastGPIO::Pin<dat>::isInputHigh()) medByte++;
    }

    for(uint8_t i = 0; i < 8; i++)
    {
        FastGPIO::Pin<clk>::setOutputValueHigh();

        // add a little stretch to the HIGH signal
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");

        FastGPIO::Pin<clk>::setOutputValueLow();

        lowByte <<= 1;
        if(FastGPIO::Pin<dat>::isInputHigh()) lowByte++;
    }

    // command the next reading -- see datasheet for how gain is set
    for(uint8_t i = 0; i < gain; i++)
    {
        FastGPIO::Pin<clk>::setOutputHigh();
        FastGPIO::Pin<clk>::setOutputLow();
    }

    /**
     * Now assemble the result. Put into a 32-bit variable, _left aligned_ to maintain
     * sign. Then divide by 256, also to maintain sign.
     */
    int32_t value = ((uint32_t)highByte << 24) | ((uint32_t)medByte << 16) | ((uint32_t)lowByte << 8); 
    return value / 256;
}
