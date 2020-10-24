// Your First C++ Program

#include <iostream>
#include "Header.h"

void setup()
{
	init_7SegmentDisplay();

}

// This is the MAIN thread
void loop()
{
	Display();
}
int main() {

	setup();
	while (1)
	{
		loop();
		//Sleep(10);
	}
    return 0;
}