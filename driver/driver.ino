#include "Display.h" // Seven segment display 
#include "FS.h"

int counter = 0;


//=======================================================================
//                    Power on setup
//=======================================================================
void setup()
{
  Serial.begin(115200);
//  Serial.begin(115200); // turn on when you are debugging for buzzer
  /* SEVEN SEGMENT */
	init_Display();

  /* BUZZER, JOY STICK, LED (control signals) */
  init_Controls();

  // Test values
  AQI = 205; // put a value above AQIThreshold to init ON for buzzer
  TempF = 50;

  /* NETWORK */
//  init_Network();
  
  // if(!SPIFFS.begin()){
  //   Serial.println("An Error has occurred while mounting SPIFFS");
  //   return;
  // }
  
  // File file = SPIFFS.open("/test.txt", "r");
  // if(!file){
  //   Serial.println("Failed to open file for reading");
  //   return;
  // }
  
  // Serial.println();
  // Serial.println("File Content:");
  // while(file.available()){
  //   Serial.write(file.read());
  // }
  // file.close();
}


//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop()
{
  // Network method, TODO Thomas


//    Network(); // Get location & AQI/Temp
  TestValues(); // Compares AQI/Temp to threshold
  ReadAxis(); // Reads joystick
	Display(); // Displays AQI/Temp to SSD

  // Keep so we can use this to debug Buzzer
//  Serial.println(BuzzerState);
}
