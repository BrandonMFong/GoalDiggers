


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
  digitalWrite(ledPin, LOW);   // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(1000);                      // Wait for a second
  digitalWrite(ledPin, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);   
}

// SEVEN SEG LOGIC
// http://acoptex.com/project/95/basics-project-018b-4-digit-7-segment-display-modules-5641ah-or-3461bs-timer-at-acoptexcom/#sthash.iBBeEE1f.dpbs 
void SetSevenSegmentDisplay(int value)
{
 // will need to know if there is multithreading 
  // https://www.circuitbasics.com/arduino-7-segment-display-tutorial/ 
}
