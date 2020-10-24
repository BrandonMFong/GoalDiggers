

// http://acoptex.com/project/95/basics-project-018b-4-digit-7-segment-display-modules-5641ah-or-3461bs-timer-at-acoptexcom/#sthash.iBBeEE1f.dpbs 
void SetSevenSegmentDisplay(int value)
{
 // will need to know if there is multithreading 
  // https://www.circuitbasics.com/arduino-7-segment-display-tutorial/ 
}

void Display()
{
  // First test to see if the user wants to change
  if(JoystickPosition(Left)){CurrentState = AQIDisplay ;}
  if(JoystickPosition(Right)){CurrentState = TempDisplay ;}
  
  switch(CurrentState)
  {
    AQIDisplay :
    {
      SetSevenSegmentDisplay(AQI);
    }
    TempDisplay :
    {
      SetSevenSegmentDisplay(TempF);
    }
  }
}
