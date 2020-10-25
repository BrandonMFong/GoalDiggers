#include "Display.h" // Seven segment display 
#include "FS.h"

int counter = 0;


//=======================================================================
//                    Power on setup
//=======================================================================
void setup()
{
  Serial.begin(115200);
  bootPrint();
//  Serial.begin(115200); // turn on when you are debugging for buzzer
  /* SEVEN SEGMENT */
  init_Display();

  /* BUZZER, JOY STICK, LED (control signals) */
  init_Controls();

  // initial values, good for testing display
  AQI = 444; 
  TempF = 444;
  BuzzerState = 1;
  /* NETWORK */
  init_Network();
}


//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop()
{

  // Network method, TODO Thomas


  Network(); // Get location & AQI/Temp
  TestValues(); // Compares AQI/Temp to threshold
  ReadAxis(); // Reads joystick
  Display(); // Displays AQI/Temp to SSD

  // Keep so we can use this to debug Buzzer
//  Serial.println(digitalRead(1));
}
