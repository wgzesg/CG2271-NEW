#include "MKL25Z4.h"


#define PTB0_Pin 0 // Timer1 ch0 checked Buzzer
#define PTB1_Pin 1 // Timer1 ch1 checked Left Forward
#define PTA1_Pin 1 // Timer2 ch0 checked Left Back
#define PTA2_Pin 2 // Timer2 ch1 checked Right Forward
#define PTA5_Pin 5 // Timer0 ch1 checked Right Back

#define MASK(x) 				( 1 << (x))

void initPWM(void);

void delay_mult100(volatile uint32_t nof);

void delay(volatile uint32_t nof);


