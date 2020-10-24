#define OFF 0
#define ON 1
#define AQIThreshold 300
#define TempFThreshold 100

/******** PINS *****************/

// Segment control 
int pinD1 = 10; // GPIO10
int pinD2 = 16; // GPIO16
int pinD3 = 5;  // GPIO5
//int pinD4 = 4;  // GPIO4

// LED segment control
int pinA = 14;  // GPIO14
int pinB = 0;   // GPIO0
int pinC = 13;   // GPIO13
int pinD = 1;   // GPIO1 tx
int pinE = 12;   // GPIO12
int pinF = 2;   // GPIO2
int pinG = 15;   // GPIO15

const int buzzerPin = 4; // GPIO4

const int joyButtonPin = 3;     // the number of the pushbutton pin, note the button is active high

/************** DISPLAY MOD ******************/
/* PROTOTYPES START */
void init_Display();  
void SetSevenSegmentDisplay(int value);
void Display();
void AssignSeg();
void AssignVal(int val);
int GetOutputValue(uint8_t val);
void ExtractSegmentValues(int val,int index_inner, int MAX);
void SetSegmentValue(int val);
void SSDTranslation(uint8_t val);
int GetNumberOfDigits(int num);
/* PROTOTYPES END */

/* IMPORTANT VARIALBLES START */
volatile int AQI;
volatile double TempF; // Fahrenheit

const uint8_t AQIDisplay = 0x00;
const uint8_t TempDisplay = 0x01;
volatile int CurrentState; // test value


volatile uint8_t ssdReg; // IMPORTANT
volatile int idx; // IMPORTANT

/* IMPORTANT VARIALBLES END */

/************** CONTROLS MOD ******************/
/* PROTOTYPES START */
void init_Buzzer();
void ReadAxis();
void button_ISR();
void TestValues();
void Buzzer();
/* PROTOTYPES END */

/* IMPORTANT VARIALBLES START */
//const int ledPin =  13;      // the number of the LED pin

// variables will change:
volatile int buttonState = 0;         // variable for reading the pushbutton status

// Define: AQI when Xaxis<144 and Temp when Xaxis>=144
volatile int Xaxis = 0; // safe value
const int Apin0 = A0;

volatile uint8_t BuzzerState = OFF; // BUZZER STATE
volatile bool IsSnoozed = false;
volatile bool CriticalAQI = false; // for LED
volatile bool CriticalTempF = false; // for LED
/* IMPORTANT VARIALBLES END */

/******************* NETWORKS MOD *****************/
void init_Network();
void Network();
