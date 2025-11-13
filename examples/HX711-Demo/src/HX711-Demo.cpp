#include <Arduino.h>

#include <HX711.h>

HX711<5, 12> loadCellHX1;

void setup() 
{
  Serial.begin(250000);

  Serial.println("setup()");
  loadCellHX1.Init();
}

void loop() 
{
  int32_t reading = 0;
  if(loadCellHX1.GetReading(reading)) 
  {
    Serial.print(millis());
    Serial.print('\t');
    Serial.println(reading);
  }
}
