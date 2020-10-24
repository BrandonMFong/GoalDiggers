

//https://lastminuteengineers.com/esp8266-nodemcu-arduino-tutorial/

// Define prototypes 
void init_7SegmentDisplay();  
void SetSevenSegmentDisplay(int value);
void Display();

int CurrentState = 0;
const uint8_t AQIDisplay = 0;
const uint8_t TempDisplay = 1;
int ledPin = 12;
int test_AQI = 0;

// INIT
void init_7SegmentDisplay()
{
  pinMode(ledPin, OUTPUT);
}

// DISPLAY
void Display()
{
  switch(CurrentState)
  {
    case AQIDisplay: SetSevenSegmentDisplay(test_AQI);
    case TempDisplay: SetSevenSegmentDisplay(test_AQI);
  }
}

// SEVEN SEG LOGIC
// http://acoptex.com/project/95/basics-project-018b-4-digit-7-segment-display-modules-5641ah-or-3461bs-timer-at-acoptexcom/#sthash.iBBeEE1f.dpbs 
void SetSevenSegmentDisplay(int value)
{
  // will need to know if there is multithreading 
  // https://www.circuitbasics.com/arduino-7-segment-display-tutorial/ 
  
  
}
