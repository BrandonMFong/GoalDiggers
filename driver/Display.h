

//https://lastminuteengineers.com/esp8266-nodemcu-arduino-tutorial/

// Define prototypes 
void init_7SegmentDisplay();  
void SetSevenSegmentDisplay(int value);
void Display();

/* IMPORTANT VARIALBLES START */
int CurrentState = 0;
const uint8_t AQIDisplay = 0;
const uint8_t TempDisplay = 1;
int ledPin = 12;
int test_AQI = 0;

volatile uint8_t SSDState;

// From left to right
// SSD3, SSD2, SSD1, SSD0
const uint8_t ssd0 = 0x00;
const uint8_t ssd1 = 0x01;
const uint8_t ssd2 = 0x02;
const uint8_t ssd3 = 0x03;
/* IMPORTANT VARIALBLES END */

// INIT
void init_7SegmentDisplay()
{
  pinMode(ledPin, OUTPUT);
  SSDState = 0x00; // init the value of the state 
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

  // set state to next 
  switch(SSDState)
  {
    case ssd0: 
      SSDState = ssd1;
      break;
    case ssd0: 
      SSDState = ssd2;
      break;
    case ssd0: 
      SSDState = ssd3;
      break;
    case ssd0: 
      SSDState = ssd0;
      break;
    default:
      SSDState = ssd0; // going to let it keep lighting up the right most segment 
      break;
  }
  
}
