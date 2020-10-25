#include "Display.h" // Seven segment display 
#include "FS.h"

//=======================================================================
//                    Power on setup
//=======================================================================
void setup()
{
  /* NETWORK */
  init_Network();
  
  /* SEVEN SEGMENT */
  init_Display();

  /* BUZZER, JOY STICK, LED (control signals) */
  init_Controls();

  bootPrint();
  
  // initial values, good for testing display
  AQI = 444; 
  TempF = 444;
}


//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop()
{
  Network(); // Get location & AQI/Temp
  TestValues(); // Compares AQI/Temp to threshold
  ReadAxis(); // Reads joystick
  Display(); // Displays AQI/Temp to SSD

  // Keep so we can use this to debug Buzzer
//  Serial.println(digitalRead(1));
}
