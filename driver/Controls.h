#include "Network.h"
/* INTERRUPTS START */

ICACHE_RAM_ATTR void turnOffBuzzer()
{
  BuzzerState = 0; // Turns off buzzer

  // snoozing both for good measure
  IsSnoozed_TempF = true; // Snoozed to make sure the machine knows the user was notified
  IsSnoozed_AQI = true; // Snoozed to make sure the machine knows the user was notified
}

/* INTERRUPTS END */

/* FUNCTIONS START */

// Analog pin does not initialization
void init_Controls() 
{
  Serial.println("Initializing Controls");
  // No room for LED 
  // initialize the LED pin as an output:
//  pinMode(ledPin, OUTPUT);
//  digitalWrite(ledPin, HIGH);

  // https://www.youtube.com/watch?v=uBvnvf35YJ8
  // initialize the pushbutton pin as an input:
  Serial.println("  init Joystick Button [INPUT]");
  Serial.println("  init Joystick x Axis [INPUT]");
  pinMode(joyButtonPin, FUNCTION_3); // enable rx to be gpio
  pinMode(joyButtonPin, INPUT);

  // attach interrupt
  Serial.println("    applying interrupt");
  attachInterrupt(digitalPinToInterrupt(joyButtonPin), turnOffBuzzer, FALLING); 

  // init buzzer output pin 
  Serial.println("  init Buzzer [OUTPUT]");
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
  if(AQI >= AQIThreshold)
  {
    if(!IsSnoozed_AQI) BuzzerState = ON; // testing buzzer
  }
  else
  {
    BuzzerState = OFF;
    IsSnoozed_AQI = false;
  }
  if(TempF >= TempFThreshold) 
  {
    if(!IsSnoozed_TempF) BuzzerState = ON; // testing 
  }
  else
  {
    BuzzerState = OFF;
    IsSnoozed_TempF = false;
  }

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
