#include "MKL25Z4.h"						// Device header
/* Default Core Clk Frequency is 20.97152MHz
	 #include CLOCK_SETUP 1 in <system_MKL2574.h> to change it to Core Clk Freq to 48MHz */


// #define RB TPM0_C1V // pta4 transfer to buzzer
#define RB TPM1_C0V // ptb0
#define RF TPM1_C1V // pta2 change to ptb1
#define LB TPM2_C0V // pta1
#define LF TPM2_C1V // ptb1 change to pta2

#define FORWARD  0x01
#define BACKWARD 0x02
#define LEFT     0x03
#define RIGHT    0x04
#define STOP     0x00

#define RUNNING     3500
#define STATIONARY  0

void forward_move(void);
void backward_move(void);
void left_move(void);
void right_move(void);
void stop_move(void);
void stop_turning(void);

void main_motor(unsigned char);



