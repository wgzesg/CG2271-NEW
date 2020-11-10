#include "LedControl.h"
#include "common.h"
#include "cmsis_os2.h"

void LightUpAllGreenLed(void){
	PTC->PDOR |= (MASK(7) | MASK(3) | MASK(4) | MASK(5) 
		| MASK(6) | MASK(10) | MASK(11) | MASK(12));
}

void LightUpAllRedLed(void){
	PTE->PDOR |= (MASK(30) | MASK(29) | MASK(22) | MASK(21) 
		| MASK(20) | MASK(5) | MASK(4) | MASK(3)) ;
}

void setPortPinIO(char ptName, int pin, int IO){
	PORT_Type *port;
	GPIO_Type *gpio;
	switch(ptName){
		case 'A': case 'a':
			port = PORTA;
			gpio = PTA;
			break;
		case 'B': case 'b':
			port = PORTB;
			gpio = PTB;
			break;
		case 'C': case 'c':
			port = PORTC;
			gpio = PTC;
			break;
		case 'D': case 'd':
			port = PORTD;
			gpio = PTD;
			break;
		case 'E': case 'e':
			port = PORTE;
			gpio = PTE;
			break;
	}
	port->PCR[pin] &= ~PORT_PCR_MUX_MASK;
	port->PCR[pin] |= PORT_PCR_MUX(1);
	
	if(IO == OUT){
		gpio->PDDR |= MASK(pin);
	}
	else{
		gpio->PDDR &= ~MASK(pin);
	}
	
	
}

void initLedStrip() {
	SIM->SCGC5 |= (SIM_SCGC5_PORTE_MASK);
	// Red Led
	setPortPinIO('E', 30, OUT);
	setPortPinIO('E', 29, OUT);
	setPortPinIO('E', 22, OUT);
	setPortPinIO('E', 21, OUT);
	setPortPinIO('E', 20, OUT);
	setPortPinIO('E', 5, OUT);
	setPortPinIO('E', 4, OUT);
	setPortPinIO('E', 3, OUT);
	
	SIM->SCGC5 |= (SIM_SCGC5_PORTC_MASK);
	// Green Led
	setPortPinIO('C', 7, OUT);
	setPortPinIO('C', 3, OUT);
	setPortPinIO('C', 4, OUT);
	setPortPinIO('C', 5, OUT);
	setPortPinIO('C', 6, OUT);
	setPortPinIO('C', 10, OUT);
	setPortPinIO('C', 11, OUT);
	setPortPinIO('C', 12, OUT);
}

void stationaryLed() {
	LightUpAllGreenLed();
	while(1) {
		LightUpAllRedLed();
		osDelay(2000); // 500ms
		offAllRedLed();
		osDelay(2000);
	}
}

void BlinkAllGreenLed() {
	for(int i = 0; i < 3; i++){
		LightUpAllGreenLed();
		osDelay(100);
		offAllGreenLed();
		osDelay(100);
	}
}

void offAllRedLed() {
	PTE->PDOR &= ~(MASK(30) | MASK(29) | MASK(22) | MASK(21) 
	| MASK(20) | MASK(5) | MASK(4) | MASK(3));
}

void offAllGreenLed() {
	PTC->PDOR &= ~( MASK(7) | MASK(3) | MASK(4) | MASK(5) 
	| MASK(6) | MASK(10) | MASK(11) | MASK(12));
	
}
