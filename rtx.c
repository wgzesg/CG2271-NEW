/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/
 
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"
#include "LedControl.h"
#include "common.h"
#include "UART.h"
#include "motorControl.h"
#include "BuzzerControl.h"

#define MSG_COUNT 10

volatile char data = 0;
volatile char status = 0;
volatile char startOrEnd = 0;


osThreadId_t motorId;
osThreadId_t messagerId;
osThreadId_t buzzerId;
osThreadId_t ledId;

osMessageQueueId_t motorMsg;
  
typedef struct {
	uint8_t cmd;
} myDataPkt;

void motor_thread (void *argument) {
 
	myDataPkt myRxData;
	for (;;) {
		osMessageQueueGet(motorMsg, &myRxData, NULL, osWaitForever);
		if (myRxData.cmd == 0x01) {
			forward_move();
		} else if (myRxData.cmd == 0x02) {
			backward_move();
		} else if (myRxData.cmd == 0x03) {
			left_move();
		} else if (myRxData.cmd == 0x04) {
			right_move();
		} else if (myRxData.cmd == 0x00) {
			stop_move();
		}
	}
}

void led_thread(void *argument) {
	for(;;) {
		int flag = osThreadFlagsWait(0x0111, osFlagsWaitAny, osWaitForever);
		if (flag == 0x00000001) {
			// connect routine
			BlinkAllGreenLed();
			offAllGreenLed();
			offAllRedLed();
		} else if (flag == 0x00000010) {
			// end routine
			offAllGreenLed();
			offAllRedLed();
		} else {
			int i = 0;
			int arr[8] = {7, 3, 4,5, 6, 10, 11, 12};
			data = 0;
			while(status == 2){
				if (data == 0) {
					LightUpAllGreenLed();
					LightUpAllRedLed();
					for(int j = 0; j <10; j++) {
						if(data != 0) {
							break;
						}
						osDelay(200);
					}
					offAllRedLed();
					for(int j = 0; j <10; j++) {
						if(data != 0) {
							break;
						}
						osDelay(200);
					}
				} else {
					offAllGreenLed();
					i += 1;
					i %= 8;
					PTC->PDOR |= MASK(arr[i]);
					LightUpAllRedLed();
					for(int j = 0; j <10; j++) {
						if(data == 0) {
							break;
						}
						osDelay(100);
					}
					offAllRedLed();
					for(int j = 0; j <10; j++) {
						if(data == 0) {
							break;
						}
						osDelay(100);
					}
				}
			}
		}
	}
}

void messager_thread (void *argument) {
	myDataPkt myMessageData;
	
	for (;;) {
		// osWaitFlag();
		osThreadFlagsWait(0x0001, osFlagsWaitAll, osWaitForever);
		switch(data) {
			case 0x0007: // just connected 
				status = 1; // Connected not started
				startOrEnd = 1; // is start
			  osThreadFlagsSet(ledId, 0x0001);  // run connect routine
			  osThreadFlagsSet(buzzerId, 0x0001); // run connect routine
				break;
			case 0x0005: // starting challenge
				status = 2; // connected and started
				osThreadFlagsSet(ledId, 0x0100);  // run normal routine
			  osThreadFlagsSet(buzzerId, 0x0100); // run normal routine
				break;
			case 0x0006: // Ending challenge
				status = 1; // connected not started
				startOrEnd = 0; // is end
				osThreadFlagsSet(ledId, 0x0010); // ended challenge routine
			  osThreadFlagsSet(buzzerId, 0x0010); // ended challenge routine
				break;
		}
		myMessageData.cmd = data;
		osMessageQueuePut(motorMsg, &myMessageData, NULL, 0);
			
		}
}

void buzzer_thread (void *argument) {
	for(;;) {
		int flag = osThreadFlagsWait(0x0111, osFlagsWaitAny, osWaitForever);
		if (flag == 0x00000001) {
			// connect routine
			for(int i = 0; i <MUSCIAL_NOTE_CNT_JINGLEBELL; i++) {
				main_buzzer(i, 1);
			}
			main_buzzer(0, 0);
		} else if (flag == 0x00000010) {
			// End routine
			for(int i = 0; i <MUSCIAL_NOTE_CNT_OLDDONALD; i++) {
					main_buzzer(i, 3);
			}
			main_buzzer(0, 0);
		} else {
			int i = 0;
			while(status == 2) {
				main_buzzer(i, 2);
				i++;
				i = i % MUSCIAL_NOTE_CNT_HAPPYBIRTHDAY;
			}
			main_buzzer(0, 0);
		}
	}
}

void UART2_IRQHandler(void) {
	NVIC_ClearPendingIRQ(UART2_IRQn);
	if(UART2->S1 & UART_S1_RDRF_MASK) {
	 // receive a char
		data = (uint8_t)UART2->D;
		osThreadFlagsSet(messagerId, 0x0001);
	}
}
 
/*----------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/

int main (void) {
 
  // System Initialization
  SystemCoreClockUpdate();
	InitUART2(BAUD_RATE);  // Init for UART
	initPWM(); // Init for motor and buzzer
	initLedStrip(); // Init for two leds
	
  osKernelInitialize();                 // Initialize CMSIS-RTOSt
	
  motorMsg = osMessageQueueNew(MSG_COUNT, sizeof(myDataPkt), NULL); // msg queue for motor thread
	
	messagerId = osThreadNew(messager_thread, NULL, NULL);    // Create messager blinky
	
	motorId = osThreadNew(motor_thread, NULL, NULL);    // Create motor 
	
	buzzerId = osThreadNew(buzzer_thread, NULL, NULL);  // Create buzzer

	ledId = osThreadNew(led_thread, NULL, NULL);

	
  osKernelStart();                      // Start thread execution
  for (;;) {}
}

