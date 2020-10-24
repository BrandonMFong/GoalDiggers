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
//  digitalWrite(pinD1, HIGH);
//  digitalWrite(pinA, LOW);
//  digitalWrite(pinB, LOW);
//  digitalWrite(pinC, LOW);
////  digitalWrite(pinD, HIGH);
//  digitalWrite(pinE, LOW);  
//  digitalWrite(pinF, LOW);  
//  digitalWrite(pinF, LOW);  
}
