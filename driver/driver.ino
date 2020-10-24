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
}

// This is the MAIN thread
void loop()
{
  // Network method, TODO Thomas
  TestValues(); // Compares AQI/Temp to threshold
  ReadAxis(); // Reads joystick
	Display(); 

  // Keep so we can use this to debug Buzzer
  Serial.println(BuzzerState);
}
