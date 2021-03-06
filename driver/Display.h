#include "Controls.h"

//https://lastminuteengineers.com/esp8266-nodemcu-arduino-tutorial/
//https://tttapa.github.io/ESP8266/Chap04%20-%20Microcontroller.html
/* FUNCTIONS START */
// INIT
void init_Display()
{
  Serial.println("Initializing IO pins");
  
//https://electronics.stackexchange.com/questions/30238/how-to-invert-a-digital-signal/117087
  pinMode(1, FUNCTION_3); // enable tx to be gpio
//  pinMode(1, OUTPUT); // FAILS if low
  
  // init segment output pin 
  pinMode(pinD1, OUTPUT);
  pinMode(pinD2, OUTPUT);
  pinMode(pinD3, OUTPUT);
//  pinMode(pinD4, OUTPUT);
  pinMode(pinA, OUTPUT); // good
  pinMode(pinB, OUTPUT); // good
  pinMode(pinC, OUTPUT); // good

  // using tx
  pinMode(pinD, FUNCTION_3); // enable tx to be gpio
  pinMode(pinD, OUTPUT); // good
  
  pinMode(pinE, OUTPUT); // good
  pinMode(pinF, OUTPUT); // good
  pinMode(pinG, OUTPUT); // good
  
  ssdReg = 0x01; // init the value of the state 
  CurrentState = 0x00;
}

// DISPLAY
void Display()
{
  switch(CurrentState) // driven by Controls.h
  {
    case AQIDisplay: 
      SetSevenSegmentDisplay(AQI); // test value
      break;
    case TempDisplay: 
      SetSevenSegmentDisplay(TempF);
      break;
  }
  delay(10); // multiplexing the 3 segments by 5ms intervals
}

// SEVEN SEG LOGIC
void SetSevenSegmentDisplay(int value)
{
  AssignSeg(); // turn the segment on 
  AssignVal(value);
}

// do I need to invert the bits? 
// this assigns one of the 4 segments
// Display
// <D4><D3><D2><D1>
void AssignSeg()
{
  
  // only one of these segments should be on 
  // shift the bits to index 0 and AND it to get the value for the pin
  // bits -> xxxx <pinD4><pinD3><pinD2><pin1>
  uint8_t forD1 = (ssdReg >> 0) & 0x01;
  digitalWrite(pinD1, GetOutputValue(forD1));   // D1
  uint8_t forD2 = (ssdReg >> 1) & 0x01;
  digitalWrite(pinD2, GetOutputValue(forD2));   // D2
  uint8_t forD3 = (ssdReg >> 2) & 0x01;
  digitalWrite(pinD3, GetOutputValue(forD3));   // D3
//  uint8_t forD4 = (ssdReg >> 0) & 0x01;
//  digitalWrite(pinD4, GetOutputValue(forD4));   // D4

  // since the segment register only contains one bit (assuming the register isn't complimented 
  // i can use the position of that bit to determine with segment should be on 
  // 1000 = 8, log2(8) = 3 
  // therefore SegmentValArr[3] will give me the digit for the 4 segment (the left most segment)
  idx = (log(ssdReg) / log(2)); // Get the log base 2
  
  // shifting the bits left
  if(ssdReg == 0x04)ssdReg = 0x01;
  else ssdReg = ssdReg << 1;
}

// translates value to the arduino board digital values
int GetOutputValue(uint8_t val)
{
  return (val == 0) ? LOW : HIGH;
}

int SegmentValArr [4] = {0,0,0,0}; // array 
// say a number is 4 digits long, like WXYZ 
// modulo 10
// WXYZ % 10 => Z
// WXYZ * 0.1 => WXY.Z
// int(WXY.Z) => WXY
// then repeat
void AssignVal(int val)
{
//  SegmentValArr = {0,0,0,0}; // reset 
  int ArrSize = sizeof(SegmentValArr)/sizeof(SegmentValArr[0]);
  for(int i = 0; i < ArrSize; i++)
  {
    SegmentValArr[i] = 0;
  }
  
  ExtractSegmentValues(val,0,GetNumberOfDigits(val)); // separates WXYZ into {Z,Y,X,W}

  // Set value 
  SetSegmentValue(SegmentValArr[idx]);
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
void ExtractSegmentValues(int val,int index_inner, int MAX)
{
  int temp = val % 10;
  SegmentValArr[index_inner] = temp;

  // int(val*0.1) shifts the number to the right
  if(index_inner < MAX) ExtractSegmentValues(int(val*0.1),index_inner+1,MAX); // recurse into function if we still have some of the number left 
}

// let 1'b xxxx xxxx 
// map them to pin variables 
// so 1'b xABC DEFG
uint8_t SSDValue [10] = 
{
  ~0x7E, // 0111 1110 = 0 
  ~0x30, // 0011 0000 = 1
  ~0x6D, // 0110 1101 = 2
  ~0x79, // 0111 1001 = 3
  ~0x33, // 0011 0011 = 4
  ~0x5B, // 0101 1011 = 5
  ~0x5F, // 0101 1111 = 6 
  ~0x70, // 0111 0000 = 7
  ~0x7F, // 0111 1111 = 8
  ~0x73 // 0111 0011 = 9 
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
  uint8_t forF = (val >> 1) & 0x01;
  digitalWrite(pinF, GetOutputValue(forF));   // G
  uint8_t forE = (val >> 2) & 0x01;
  digitalWrite(pinE, GetOutputValue(forE));   // G
  uint8_t forD = (val >> 3) & 0x01;
  digitalWrite(pinD, GetOutputValue(forD));   // G
  uint8_t forC = (val >> 4) & 0x01;
  digitalWrite(pinC, GetOutputValue(forC));   // G
  uint8_t forB = (val >> 5) & 0x01;
  digitalWrite(pinB, GetOutputValue(forB));   // G
  uint8_t forA = (val >> 6) & 0x01;
  digitalWrite(pinA, GetOutputValue(forA));   // G
}
/* FUNCTIONS END */
