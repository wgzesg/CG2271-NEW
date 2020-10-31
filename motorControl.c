#include "motorControl.h"
#include "common.h"


void left_move() {
	LF = RUNNING;
	RF = RUNNING;
	LB = STATIONARY;
	RB = STATIONARY;
}

void right_move() {
	LB = RUNNING;
	RB = RUNNING;
	LF = STATIONARY;
	RF = STATIONARY;
}

void forward_move() {
	LF = STATIONARY;
	RF = RUNNING;
	LB = RUNNING;
	RB = STATIONARY;
}

void backward_move() {
	LF = RUNNING;
	RF = STATIONARY;
	LB = STATIONARY;
	RB = RUNNING;
}

void stop_move() {
	LF = STATIONARY;
	RF = STATIONARY;
	LB = STATIONARY;
	RB = STATIONARY;
}

void main_motor(unsigned char direction){
	
	
	//TPM1_C0V = 0x0666; // 0x666 = 1638 (half of 3276) 50% Duty Cycle
	//TPM1_C0V = 0x0EA6; // 0x0EA6 = 3750 (half of 7500) 50% Duty Cycle
	//TPM0_C1V = 0x0EA6; 
	//TPM0_C2V = 0x0EA6;
		

		
		switch (direction) {
			case FORWARD: 
				forward_move();
			break;
			case BACKWARD: 
				backward_move();
			break;
			case LEFT: 
				left_move();
			break;
			case RIGHT: 
				right_move();
			break;
			default: 
				stop_move();
			break;
		}
		
}

