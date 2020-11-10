#include "MKL25Z4.h"
#define IN 0
#define OUT 1

// Turn off the LED
void offAllGreenLed(void);
void offAllRedLed(void);

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
	
void BlinkAllGreenLed(void);
