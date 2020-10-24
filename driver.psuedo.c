// clock speed mod: https://www.instructables.com/ESP8266-NodeMCU-CPU-Speed-Test/ 
// setup
void init_7SegmentDisplay();
void init_LEDFlags();
void init_JoyStick();
void init_WifiConnection();

// Test Values
void Test(string TypeString); 

// Get Values
void GetAQIAndTemp();
void GetLocation();

// Set Outputs
void SetSevenSegmentDisplay();
void Display();
void Buzzer(boolean status);
void AQILed(boolean status);
void TempLed(boolean status);


HtmlDocument GetHtml(string url); // Gets html document
string []  SeparateCityStateAndCountry(string Address); // returns an array size 3, [0] is city, [1]  
          is State, [2] Country
volatile int AQI;
volatile double TempF; // Fahrenheit

// Location variables 
volatile string City;
volatile string State;
volatile string Country;

const int MaxCounter = 3600; // TODO get clock speed of core
volatile int CounterToUpdateLocation = MaxCounter; // start value inits location

// Threshold variables 
const int AQIThreshold = 300;
const double TempFThreshold = 100;

boolean ON = true;
boolean OFF = false;

// Controls
volatile int CurrentState;
const uint8_t AQIDisplay = 0;
const unit8_t TempDisplay = 1;
 
setup()
{
	// Sets all pins
	init_7SegmentDisplay();
	init_LEDFlags();
	init_JoyStick(); // 
	init_WifiConnection();
}


// all one thread
// This is the MAIN thread
loop()
{
	if(CounterToUpdateLocation == MaxCounter)
{
	CounterToUpdateLocation = 0;
 	GetLocation(); // Refresh location 
}
	else CounterToUpdateLocation++;

	GetAQIAndTemp(); // Get AQI value

	// Turn on buzzer if threshold is surpassed 
	Test(“AQI”);
	Test(“Temp”);

	Display(); // 
	

	// sleep(1); // One second sleep. Since there is no threading, don’t sleep. We need the speed 
}

void GetLocation()
{
	// https://techtutorialsx.com/2016/07/17/esp8266-http-get-requests/ 
	HtmlDocument Locationdoc = GetHtml(“https://www.iplocation.net/”);
	string CityLocation = Locationdoc.GetElementByClass(“iptable”).tbody.tr[1].td; //  go 
         through the 
         elements to get 
         the inner html 
         value 
	string LocationString [3] = SeparateCityStateAndCountry(CityLocation);
	string City = LocationString[0];
	string State = LocationString[1];
	string Country = LocationString[2];
}

void GetAQIAndTemp()
{
// this is dependent on location
	if(City != null && State != null && Country != null) 
{

		string AQISiteUrlString = “https://www.airnow.gov/?city=” + City + “&state=” + State  + “&country=” + Country ;
	
		HtmlDocument doc = GetHtml(AQISiteUrlString);
		AQI= doc.GetElementByClass(“aqi”).b;
//TempF = doc.GetElementByClass(“weather-value”).innerHtml;
TempF = 0.00; // start with zero. Let’s test AQI first 
}


}

void Test(string TypeString)
{
	switch(TypeString)
	{
		“AQI”
		{

if(AQI > AQIThreshold) 
{
Buzzer(ON);
AQILed(ON);
}
else
{
Buzzer(OFF);
AQILed(OFF);
}
		}
		“Temp”
		{

if(TempF > TempFThreshold ) 
{
Buzzer(ON);
TempLed(ON);
}
else
{
Buzzer(OFF);
TempLed(OFF);
}
		}
		// Space for more types, i.e. wind speed 
	}
}


void Buzzer(bool Function)
{
	if(JoystickPressed() && !Function){outputBuzz(OFF);}
	else {outputBuzz(ON);}
}

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
