#include "Network.h"
/* INTERRUPTS START */

ICACHE_RAM_ATTR void turnOffBuzzer()
{
  BuzzerState = 0; // Turns off buzzer
  IsSnoozed = true; // Snoozed to make sure the machine knows the user was notified
}

/* INTERRUPTS END */

/* FUNCTIONS START */

// Analog pin does not initialization
void init_Controls() 
{
  // No room for LED 
  // initialize the LED pin as an output:
//  pinMode(ledPin, OUTPUT);
//  digitalWrite(ledPin, HIGH);

  // https://www.youtube.com/watch?v=uBvnvf35YJ8
  // initialize the pushbutton pin as an input:
  pinMode(joyButtonPin, FUNCTION_3); // enable rx to be gpio
  pinMode(joyButtonPin, INPUT);

  // attach interrupt
  attachInterrupt(digitalPinToInterrupt(joyButtonPin), turnOffBuzzer, FALLING); 

  // init buzzer output pin 
//  debug output at boot, boot fails if pulled LOW
  pinMode(buzzerPin,OUTPUT);
}


// JOYSTICK LOGIC
// only analog signal is A0
void ReadAxis()
{
  //https://randomnerdtutorials.com/esp8266-adc-reading-analog-values-with-nodemcu/
  int sensorValue = 0;  // value read from the pot
  Xaxis = map(analogRead(Apin0), 0, 1023, 0, 255);
  if(Xaxis < 100) // Left orientation
  {
    CurrentState = AQIDisplay;
  }
  else if (Xaxis > 200) // Right orientation
  {
    CurrentState = TempDisplay;
  }
  // default is CurrentState remains the same
}

// BUZZER LOGIC TODO
void TestValues()
{
  if(AQI >= AQIThreshold && !IsSnoozed) BuzzerState = ON; // testing buzzer
  if(TempF >= TempFThreshold && !IsSnoozed) BuzzerState = ON; // testing 

  // test buzzer and output 
  if(BuzzerState) // if ON
  {
    // turn on buzzer, write to it
    digitalWrite(buzzerPin, HIGH); 
  }
  else
  {
    // turn it off, write digital 0 to S pin 
    digitalWrite(buzzerPin, LOW); 
  }
}
/* FUNCTIONS END */
