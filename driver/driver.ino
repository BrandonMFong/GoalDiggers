#include "Display.h" // Seven segment display 

int counter = 0;


void setup()
{
  Serial.begin(115200); // turn on when you are debugging for buzzer
  /* SEVEN SEGMENT */
	init_Display();

  /* BUZZER, JOY STICK, LED (control signals) */
  init_Controls();

  // Test values
  AQI = 837;
  TempF = 80;
//https://electronics.stackexchange.com/questions/30238/how-to-invert-a-digital-signal/117087
//  pinMode(1, FUNCTION_3); // enable rx to be gpio
//  pinMode(1, OUTPUT);
//  digitalWrite(1,LOW); // FAILS if low
}

// This is the MAIN thread
void loop()
{
  // Network method, TODO Thomas
  TestValues(); // Compares AQI/Temp to threshold
  ReadAxis(); // Reads joystick
	Display(); 

  // Keep so we can use this to debug Buzzer
//  int state = digitalRead(1);
//  Serial.println(state);
//  Serial.println(BuzzerState);
}
