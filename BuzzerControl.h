#include "MKL25Z4.h"						// Device header
/* Default Core Clk Frequency is 20.97152MHz
	 #include CLOCK_SETUP 1 in <system_MKL2574.h> to change it to Core Clk Freq to 48MHz */
/*
PTB18 -> TM2 CH0
PTB19 -> TM2 CH1
*/
#define MUSICAL_NOTE_CNT_JINGLEBELL 22
#define MUSICAL_NOTE_CNT_HAPPYBIRTHDAY 50
#define MUSICAL_NOTE_CNT_OLDDONALD 30
#define MUSICAL_NOTE_CNT_BRAWLSTARS_BEGIN 14

#define FREQ_2_MOD(x) (375000 / x)
#define MASK(x) 				( 1 << (x))

// TONES
//Period = 375,000*(1/frequency)
//letter=note #=octave b=flat
//       note,  frequency. 
#define  d3     147
#define  c4     261
#define  d4b    277 
#define  d4     294 
#define  e4b    311 
#define  e4     329 
#define  f4     349
#define  g4b    370
#define  g4     392
#define  a4b    415
#define  a4     440
#define  b4b    466
#define  b4     493
#define  c5     523
#define  d5b    554
#define  d5     587
#define  e5b    622
#define  e5     659
#define  f5     698
#define  g5b    740
#define  g5     784
#define  a5b    831
#define  a5     880
#define  b5b    932
#define  b5     988
#define  d6     1175 
//A special note, 'R', to represent a rest
#define  R      0
#define beat 200
#define pause 40

void main_buzzer(char i, char song);
