#include "Display.h"
 
void setup()
{
	// Sets all pins
	init_7SegmentDisplay();
}


// all one thread
// This is the MAIN thread
void loop()
{
	Display(); // Display
}
