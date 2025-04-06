#include <Arduino.h>

#include <ZSC31014.h>

ZSC31014 loadCellHX1(2, 3);

void setup() 
{
  Serial.begin(250000);
  while(!Serial) {}

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
