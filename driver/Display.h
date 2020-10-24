

//https://lastminuteengineers.com/esp8266-nodemcu-arduino-tutorial/

// Define prototypes 
void init_7SegmentDisplay();  
void SetSevenSegmentDisplay(int value);
void Display();
void AssignSeg(uint8_t val);

/* IMPORTANT VARIALBLES START */
int CurrentState = 0;
const uint8_t AQIDisplay = 0;
const uint8_t TempDisplay = 1;
int ledPin = 12;
int test_AQI = 0;

volatile uint8_t ssdReg;

// From left to right
// SSD3, SSD2, SSD1, SSD0
//const uint8_t ssd0 = 0x00;
//const uint8_t ssd1 = 0x01;
//const uint8_t ssd2 = 0x02;
//const uint8_t ssd3 = 0x03;

  
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
void SetSevenSegmentDisplay(int value)
{
  // shifting the bits left
  if(ssdReg == 0x08)ssdReg = 0x01;
  else ssdReg = ssdReg << 1;
}

void AssignSeg(uint8_t val)
{
  // do I need to invert the bits? 
  
}
