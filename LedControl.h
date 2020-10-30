#include "MKL25Z4.h"
// #define RED_LED 				18		//PortB Pin 18
// #define GREEN_LED 			19		//PortB Pin 19
// #define BLUE_LED 				1		  //PortD Pin 1
#define IN 0
#define OUT 1

/**
typedef enum{
	red,
	blue,
	green
}color_t;
**/

// Turn off the LED
void offAllGreenLed(void);
void offAllRedLed(void);

// update the LED to designated color
//color_t updateLEDColor(color_t color);

// initilise GPIO pins for LED
// void InitLED(void);

// set a specific pin of a specific port to GPIO and set to input/output
// ptName: [a,b,c,d,e] case-insensitive
// pin: pin number
// IO [IN, OUT] predefined in header
void setPortPinIO(char ptName, int pin, int IO);

// Init 16 gpio pins to power the LED strip
void initLedStrip(void);

void LightUpAllGreenLed(void);

void LightUpAllRedLed(void);

void stationaryLed(void);
	
void runningLed(void);

void BlinkAllGreenLed(void);
