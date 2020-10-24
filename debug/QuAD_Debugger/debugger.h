#pragma once

const int OUTPUT = 1;
const int INPUT = 0;
const int LOW = 0;
const int HIGH = 1;
using namespace std;
void pinMode(int pin, int value)
{
	cout << "Initializing\n";
	cout << pin << " : " << value << endl;
}


void digitalWrite(int pin, int value)
{
	cout << "Writing\n";
	cout << "pin " << pin << " : " << "value " << value << endl;
}