#include "motorControl.h"
#include "common.h"

int temp_LF;
int temp_RF;
int temp_LB;
int temp_RB;

void forward_move() {
	temp_LF = LF = RUNNING;
	temp_RF = RF = RUNNING;
	temp_LB = LB = STATIONARY;
	temp_RB = RB = STATIONARY;
}

void backward_move() {
	temp_LB = LB = RUNNING;
	temp_RB = RB = RUNNING;
	temp_LF = LF = STATIONARY;
	temp_RF = RF = STATIONARY;
}

void left_move() {
	temp_LF = LF;
	temp_RF = RF;
	temp_LB = LB;
	temp_RB = RB;
	LF = LF * 0;
	RF = RF;
	LB = LB * 0;
	RB = RB;
}

void right_move() {
	temp_LF = LF;
	temp_RF = RF;
	temp_LB = LB;
	temp_RB = RB;
	LF = LF;
	RF = RF * 0;
	LB = LB;
	RB = RB * 0;
}

void stop_turning() {
	LF = temp_LF;
	RF = temp_RF;
	LB = temp_LB;
	RB = temp_RB;
}

void stop_move() {
	LF = STATIONARY;
	RF = STATIONARY;
	LB = STATIONARY;
	RB = STATIONARY;
	temp_LB = 0;
	temp_RB = 0;
	temp_LF = 0;
	temp_RF = 0;
}

void main_motor(unsigned char direction){
		
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

