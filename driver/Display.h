

//https://lastminuteengineers.com/esp8266-nodemcu-arduino-tutorial/

// Define prototypes 
void init_7SegmentDisplay();  
void SetSevenSegmentDisplay(int value);
void Display();
void AssignSeg(uint8_t val);
void AssignVal(uint8_t val);
void GetOutputValue(uint8_t val);
int [] ExtractSegmentValues(uint8_t val);

/* IMPORTANT VARIALBLES START */
int test_AQI = 0; // temp
int CurrentState = 0;
const uint8_t AQIDisplay = 0;
const uint8_t TempDisplay = 1;

// Segment control 
int pinD1 = 10; // GPIO10
int pinD2 = 16; // GPIO16
int pinD3 = 5;  // GPIO5
int pinD4 = 4;  // GPIO4

// LED segment control
int pinA = 14;  // GPIO14
int pinB = 0;   // GPIO0
int pinC = 8;   // GPIO8
int pinD = 7;   // GPIO7
int pinE = 6;   // GPIO6
int pinF = 2;   // GPIO2

volatile uint8_t ssdReg;

/* IMPORTANT VARIALBLES END */

// INIT
void init_7SegmentDisplay()
{
  // init segment output pin 
  pinMode(pinD1, OUTPUT);
  pinMode(pinD2, OUTPUT);
  pinMode(pinD3, OUTPUT);
  pinMode(pinD4, OUTPUT);
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  
  ssdReg = 0x00; // init the value of the state 
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
  AssignSeg(ssdReg); // turn the segment on 

  AssignVal(value);
}

// do I need to invert the bits? 
// this assigns one of the 4 segments
void AssignSeg(uint8_t val)
{
  // shifting the bits left
  if(ssdReg == 0x08)ssdReg = 0x01;
  else ssdReg = ssdReg << 1;
  
  // only one of these segments should be on 
  // shift the bits to index 0 and AND it to get the value for the pin
  // bits -> xxxx <pinD4><pinD3><pinD2><pin1>
  uint8_t var0 = (val >> 0) & 0x01;
  digitalWrite(pinD1, GetOutputValue(var0));   // D1
  uint8_t var1 = (val >> 1) & 0x01;
  digitalWrite(pinD2, GetOutputValue(var1));   // D2
  uint8_t var2 = (val >> 2) & 0x01;
  digitalWrite(pinD3, GetOutputValue(var2));   // D3
  uint8_t var3 = (val >> 3) & 0x01;
  digitalWrite(pinD4, GetOutputValue(var3));   // D4
}

// translates value to the arduino board digital values
uint8_t GetOutputValue(uint8_t val)
{
  return (val == 0) ? LOW : HIGH;
}

int SegmentValArr [4] = {0,0,0,0};
// say a number is 4 digits long, like WXYZ 
// WXYZ % 10 => Z
// WXYZ * 0.1 => WXY.Z
// int(WXY.Z) => WXY
// then repeat
void AssignVal(uint8_t val)
{
  // modulo 10
  
}
int [] ExtractSegmentValues(uint8_t val)
{
  
}
