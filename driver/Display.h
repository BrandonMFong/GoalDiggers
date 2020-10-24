

//https://lastminuteengineers.com/esp8266-nodemcu-arduino-tutorial/

// Define prototypes 
void init_7SegmentDisplay();  
void SetSevenSegmentDisplay(int value);
void Display();
void AssignSeg();
void AssignVal(uint8_t val);
void GetOutputValue(uint8_t val);
void ExtractSegmentValues(int val,int index, int MAX);
void SetSegmentValue(int val);
void SSDTranslation(uint8_t val);
int GetNumberOfDigits(int num);

/* IMPORTANT VARIALBLES START */
volatile int AQI;
volatile double TempF; // Fahrenheit

const uint8_t AQIDisplay = 0;
const uint8_t TempDisplay = 1;
volatile int CurrentState = AQIDisplay; // test value

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
int pinG = 9;   // GPIO9

volatile uint8_t ssdReg; // IMPORTANT

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
  pinMode(pinG, OUTPUT);
  
  ssdReg = 0x00; // init the value of the state 
}

// DISPLAY
void Display()
{
  switch(CurrentState)
  {
    case AQIDisplay: SetSevenSegmentDisplay(100); // test value
    case TempDisplay: SetSevenSegmentDisplay(100);
  }
}

// SEVEN SEG LOGIC
void SetSevenSegmentDisplay(int value)
{
  AssignSeg(); // turn the segment on 
  AssignVal(value);
}

// do I need to invert the bits? 
// this assigns one of the 4 segments
void AssignSeg()
{
  // shifting the bits left
  if(ssdReg == 0x08)ssdReg = 0x01;
  else ssdReg = ssdReg << 1;
  
  // only one of these segments should be on 
  // shift the bits to index 0 and AND it to get the value for the pin
  // bits -> xxxx <pinD4><pinD3><pinD2><pin1>
  uint8_t forD1 = (ssdReg >> 0) & 0x01;
  digitalWrite(pinD1, GetOutputValue(forD1));   // D1
  uint8_t forD2 = (ssdReg >> 1) & 0x01;
  digitalWrite(pinD2, GetOutputValue(forD2));   // D2
  uint8_t forD3 = (ssdReg >> 2) & 0x01;
  digitalWrite(pinD3, GetOutputValue(forD3));   // D3
  uint8_t forD4 = (ssdReg >> 3) & 0x01;
  digitalWrite(pinD4, GetOutputValue(forD4));   // D4
}

// translates value to the arduino board digital values
uint8_t GetOutputValue(uint8_t val)
{
  return (val == 0) ? LOW : HIGH;
}

int SegmentValArr [4] = {0,0,0,0}; // array 
// say a number is 4 digits long, like WXYZ 
// WXYZ % 10 => Z
// WXYZ * 0.1 => WXY.Z
// int(WXY.Z) => WXY
// then repeat
void AssignVal(uint8_t val)
{
  // modulo 10
  SegmentValArr = {0,0,0,0}; // reset 
  ExtractSegmentValues(val,0,GetNumberOfDigits(int(val))); // separates WXYZ into {Z,Y,X,W}

  // since the segment register only contains one bit (assuming the register isn't complimented 
  // i can use the position of that bit to determine with segment should be on 
  // 1000 = 8, log2(8) = 3 
  // therefore SegmentValArr[3] will give me the digit for the 4 segment (the left most segment)
  int index = log(ssdReg)/log(2); // Get the log base 2

  // Set value 
  SetSegmentValue(SegmentValArr[index]);
}

int GetNumberOfDigits(int num)
{
    int count = 0; 
    while (num != 0) 
    { 
      num = num / 10; 
      ++count; 
    }
    return count; 
}

// assume val is int
// result should be in SegmentValArr array 
// recurses based on the MAX number of digits
void ExtractSegmentValues(int val,int index, int MAX)
{
  int temp = val % 10;
  SegmentValArr[index] = temp;

  // int(val*0.1) shifts the number to the right
  if(index < MAX) ExtractSegmentValues(int(val*0.1),index+1); // recurse into function if we still have some of the number left 
}

// let 1'b xxxx xxxx 
// map them to pin variables 
// so 1'b xABC DEFG
uint8_t SSDValue [10] = 
{
  0x7E, // 0111 1110 = 0 
  0x60, // 0110 0000 = 1
  0x6D, // 0110 1101 = 2
  0x79, // 0111 1001 = 3
  0x33, // 0011 0011 = 4
  0x5B, // 0101 1011 = 5
  0x5F, // 0101 1111 = 6 
  0x70, // 0111 0000 = 7
  0x7F, // 0111 1111 = 8
  0x73 // 0111 0011 = 9 
};
// assuming the val is less then 10
// that means its in between 0 .. 9
// we can use this to index the array 
void SetSegmentValue(int val) 
{
  if(val < 10)
  {
    SSDTranslation(SSDValue[val]);
  }
  else 
  {
    // default setting 
    SSDTranslation(SSDValue[0]); // output zero
  }
}

// actual translation being written 
void SSDTranslation(uint8_t val)
{
  uint8_t forG = (val >> 0) & 0x01;
  digitalWrite(pinG, GetOutputValue(forG));   // G
  uint8_t forF = (val >> 0) & 0x01;
  digitalWrite(pinF, GetOutputValue(forF));   // G
  uint8_t forE = (val >> 0) & 0x01;
  digitalWrite(pinE, GetOutputValue(forE));   // G
  uint8_t forD = (val >> 0) & 0x01;
  digitalWrite(pinD, GetOutputValue(forD));   // G
  uint8_t forC = (val >> 0) & 0x01;
  digitalWrite(pinC, GetOutputValue(forC));   // G
  uint8_t forB = (val >> 0) & 0x01;
  digitalWrite(pinB, GetOutputValue(forB));   // G
  uint8_t forA = (val >> 0) & 0x01;
  digitalWrite(pinA, GetOutputValue(forA));   // G
}
