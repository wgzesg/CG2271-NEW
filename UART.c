#include "UART.h"

/**
void InitGPIO(void){
	// Clock to PORTB and PORTD
	SIM->SCGC5 |= ((SIM_SCGC5_PORTB_MASK) | (SIM_SCGC5_PORTD_MASK));
	
	//Configure MUX settings to make all 3 pins GPIO
	
	PORTB->PCR[RED_LED] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED] |= PORT_PCR_MUX(1);
	
	PORTB->PCR[GREEN_LED] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED] |= PORT_PCR_MUX(1);
	
	PORTD->PCR[BLUE_LED] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED] |= PORT_PCR_MUX(1);
	
	//Set Data Direction Registers for PortB and PortD
	PTB->PDDR |= (MASK(RED_LED)) | (MASK(GREEN_LED));
	PTD->PDDR |= (MASK(BLUE_LED));
}
**/

/* Init UART2 */
void InitUART2(uint32_t baud_rate) {
	uint32_t divisor, bus_clock;
	
	SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	PORTE->PCR[UART_TX_PORTE22] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[UART_TX_PORTE22] |= PORT_PCR_MUX(4);
	
	PORTE->PCR[UART_RX_PORTE23] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[UART_RX_PORTE23] |= PORT_PCR_MUX(4);
	
	UART2->C2 &= ~((UART_C2_TE_MASK) | (UART_C2_RE_MASK));
	
	bus_clock = (DEFAULT_SYSTEM_CLOCK)/2;
	divisor = bus_clock / (baud_rate * 16);
	UART2->BDH = UART_BDH_SBR(divisor >> 8);
	UART2->BDL = UART_BDL_SBR(divisor);

	UART2->C1 = 0;
	UART2->S2 = 0;
	UART2->C3 = 0;
	
	UART2->C2 |= ((UART_C2_TE_MASK) | (UART_C2_RE_MASK));
	
	NVIC_SetPriority(UART2_IRQn, 128);
	NVIC_ClearPendingIRQ(UART2_IRQn);
	NVIC_EnableIRQ(UART2_IRQn);
 
	// enable transmit and receive interrupt
	UART2->C2 |= UART_C2_RIE_MASK | UART_C2_TE_MASK;
	
}

/*
// UART2 Transmit Poll
void UART2_Transmit_Poll(uint8_t data) {
	while(!(UART2->S1 & UART_S1_TDRE_MASK));
	UART2->D = data;

}

// UART2 Receive Poll
uint8_t UART2_Receive_Poll(void) {
	while(!(UART2->S1 & UART_S1_RDRF_MASK));
	return (UART2->D);
}
*/

/**
volatile unsigned char command;
**/
/*MAIN function */
/*
void UART_main(void) {
	
	SystemCoreClockUpdate();
	InitGPIO();
	PTD->PCOR = MASK(BLUE_LED);
	InitUART2(BAUD_RATE);
	initPWM();
	
	
	while(1) {
		// Rx and Tx 
		// UART2_Transmit_Poll(0x69);
		unsigned char direction = command;
		main_motor(direction);
	}
}
*/

