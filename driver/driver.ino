#include "Display.h" // Seven segment display 

int counter = 0;
void setup()
{
	init_7SegmentDisplay();
  AQI = 0;
}

// This is the MAIN thread
void loop()
{
  if(counter == 100)
  {
    counter = 0;
    if(AQI > 900) AQI = 0; 
    else AQI++;
  }
  else counter++;
  
	Display(); 
  // can I save volatile variables to the eeprom?
}
