


void init_7SegmentDisplay();  
void SetSevenSegmentDisplay(int value);
void Display();

int CurrentState = 0;
int ledPin = 12;

// INIT
void init_7SegmentDisplay()
{
  pinMode(ledPin, OUTPUT);
}

// DISPLAY
void Display()
{
  
}

// SEVEN SEG LOGIC
// http://acoptex.com/project/95/basics-project-018b-4-digit-7-segment-display-modules-5641ah-or-3461bs-timer-at-acoptexcom/#sthash.iBBeEE1f.dpbs 
void SetSevenSegmentDisplay(int value)
{
 // will need to know if there is multithreading 
  // https://www.circuitbasics.com/arduino-7-segment-display-tutorial/ 
}
