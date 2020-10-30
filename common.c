#include "common.h"

void delay_mult100(volatile uint32_t nof){
	for(int i = 0; i<100;i++){
		delay(nof);
	}
}

void delay(volatile uint32_t nof){
	while(nof!= 0){
		__ASM("NOP");    // no operation,  stop the processor, but the clock is still running.
		nof--;           // each nof take 1/clockFrequency
	}
}

void initPWM(void){
	// enable clock for PortB
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
	// enable clock for PortA
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	
	//Configure Mode3 for the PWM pin operation
	PORTB->PCR[PTB0_Pin] &= ~PORT_PCR_MUX_MASK;  //ptb0 is the TPM1_CH0 under alternative 3 mux
	PORTB->PCR[PTB0_Pin] |= PORT_PCR_MUX(3);
	
	PORTB->PCR[PTB1_Pin] &= ~PORT_PCR_MUX_MASK;  //ptb1 is the TPM1_CH1 under alternative 3 mux
	PORTB->PCR[PTB1_Pin] |= PORT_PCR_MUX(3);
	
	PORTA->PCR[PTA1_Pin] &= ~PORT_PCR_MUX_MASK;  //pta1 is the TPM2_CH0 under alternative 3 mux
	PORTA->PCR[PTA1_Pin] |= PORT_PCR_MUX(3);
	
	PORTA->PCR[PTA2_Pin] &= ~PORT_PCR_MUX_MASK;  //pta2 is the TPM2_CH1 under alternative 3 mux
	PORTA->PCR[PTA2_Pin] |= PORT_PCR_MUX(3);
	
	PORTA->PCR[PTA5_Pin] &= ~PORT_PCR_MUX_MASK;  //pta5 is the TPM0_CH2 under alternative 3 mux
	PORTA->PCR[PTA5_Pin] |= PORT_PCR_MUX(3);

	//Enable Clock Gating for Timer0
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	
	//Enable Clock Gating for Timer1
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
	
	//Enable Clock Gating for Timer2
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;
	
	// Select clock for TPM module
	SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1); // MCGFLLCLK or MCGPLLCLK/2	
	
	//Set Modulo Value 20971520/ 128 = 163840 /3276 = 50Hz
	TPM1->MOD = 7500;
	
	//Set Modulo Value 48000000 /128 = 375000 / 7500 = 50Hz
	TPM2->MOD = 7500;
	
	TPM0->MOD = 0;
	
	/* Edge-Aligned PWM*/
	//Update Snc register: CMOD = 01, PS=111(128)
	TPM0->SC &= ~((TPM_SC_CMOD_MASK)|(TPM_SC_PS_MASK));
	TPM0->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(7)); // LPTPM counter increments on every LPTPM counter clock + 128 prescaler
	TPM0->SC &= ~(TPM_SC_CPWMS_MASK);
	/**/
	
	//Enable PWM on TPM1 Channel 0 -> PTB0
	TPM0_C0SC &= ~((TPM_CnSC_ELSB_MASK)|(TPM_CnSC_ELSA_MASK)|(TPM_CnSC_MSB_MASK)|(TPM_CnSC_MSA_MASK));
	TPM0_C0SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));  // assign 10 to C0SC, edge aligned pwm & high-true pules
	
	//Enable PWM on TPM0 Channel 2 -> PTA5
	TPM0_C2SC &= ~((TPM_CnSC_ELSB_MASK)|(TPM_CnSC_ELSA_MASK)|(TPM_CnSC_MSB_MASK)|(TPM_CnSC_MSA_MASK));
	TPM0_C2SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));  // assign 10 to C1SC, edge aligned pwm & high-true pules
	
	//Update Snc register: CMOD = 01, PS=111(128)
	TPM1->SC &= ~((TPM_SC_CMOD_MASK)|(TPM_SC_PS_MASK));
	TPM1->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(7)); // LPTPM counter increments on every LPTPM counter clock + 128 prescaler
	TPM1->SC &= ~(TPM_SC_CPWMS_MASK);
	/**/
	
	//Enable PWM on TPM1 Channel 0 -> PTB0
	TPM1_C0SC &= ~((TPM_CnSC_ELSB_MASK)|(TPM_CnSC_ELSA_MASK)|(TPM_CnSC_MSB_MASK)|(TPM_CnSC_MSA_MASK));
	TPM1_C0SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));  // assign 10 to C0SC, edge aligned pwm & high-true pules
	
	//Enable PWM on TPM1 Channel 1 -> PTB1
	TPM1_C1SC &= ~((TPM_CnSC_ELSB_MASK)|(TPM_CnSC_ELSA_MASK)|(TPM_CnSC_MSB_MASK)|(TPM_CnSC_MSA_MASK));
	TPM1_C1SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));  // assign 10 to C1SC, edge aligned pwm & high-true pules
	
	/* Edge-Aligned PWM*/
	//Update Snc register: CMOD = 01, PS=111(128)
	TPM2->SC &= ~((TPM_SC_CMOD_MASK)|(TPM_SC_PS_MASK));
	TPM2->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(7)); // LPTPM counter increments on every LPTPM counter clock + 128 prescaler
	TPM2->SC &= ~(TPM_SC_CPWMS_MASK);
	/**/
	
	//Enable PWM on TPM2 Channel 0 -> PTA1
	TPM2_C0SC &= ~((TPM_CnSC_ELSB_MASK)|(TPM_CnSC_ELSA_MASK)|(TPM_CnSC_MSB_MASK)|(TPM_CnSC_MSA_MASK));
	TPM2_C0SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));  // assign 10 to C0SC, edge aligned pwm & high-true pules
	
	//Enable PWM on TPM2 Channel 1 -> PTA2
	TPM2_C1SC &= ~((TPM_CnSC_ELSB_MASK)|(TPM_CnSC_ELSA_MASK)|(TPM_CnSC_MSB_MASK)|(TPM_CnSC_MSA_MASK));
	TPM2_C1SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));  // assign 10 to C1SC, edge aligned pwm & high-true pules
	
}

