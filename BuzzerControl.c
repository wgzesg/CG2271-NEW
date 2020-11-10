#include "BuzzerControl.h"						// Device header
#include "cmsis_os2.h"

int score_jingle_bell[MUSICAL_NOTE_CNT_JINGLEBELL] = {
 e4,R,e4,R,e4,R,
 e4,R,e4,R,e4,R,
 e4,R,g4,R,c4,R,d4,R,
 e4,R
 };
 

 int duration_jingle_bell[MUSICAL_NOTE_CNT_JINGLEBELL] = {
	 beat,pause, beat,pause, beat*2, pause,
   beat,pause, beat,pause, beat*2, pause,
   beat,pause, beat,pause, beat*1.5,pause, beat/2, pause,
	 beat * 4, pause
 };

int score_brawl_stars_begin[MUSICAL_NOTE_CNT_BRAWLSTARS_BEGIN] = {
	b5,R,a5,R,b5,R,d6,R,g5b,R,a5,R,b5,R 
};

int duration_brawl_stars_begin[MUSICAL_NOTE_CNT_BRAWLSTARS_BEGIN] = {
	beat,pause,beat,pause,beat,pause,beat,pause*2,
	beat,pause,beat,pause,beat,pause*2
};
 
 int score_old_donald[MUSICAL_NOTE_CNT_OLDDONALD] = {
	 g4,R,g4,R,g4,R,d4,R,
	 e4,R,e4,R,d4,R,b4,R,b4,R,a4,R,a4,R,g4,R
 };
 
 int duration_old_donald[MUSICAL_NOTE_CNT_OLDDONALD] = {
	 beat,pause,beat,pause, beat,pause,beat,pause,
	 beat,pause,beat,pause,beat*2,pause, 
	 beat,pause,beat,pause,beat,pause,beat,pause,beat,pause,
 };
 
 int score_happy_birthday[MUSICAL_NOTE_CNT_HAPPYBIRTHDAY] = {
	 g4,R,g4,R,a5,R,g4,R,c5,R,b5,R,
	 g4,R,g4,R,a5,R,g4,R,d5,R,c5,R,
	 g4,R,g4,R,g4,R,e4,R,c4,R,b4,R,a4,R,
	 f5,R,f5,R,e5,R,c5,R,d5,R,c5,R
 };
 
 int duration_happy_birthday[MUSICAL_NOTE_CNT_HAPPYBIRTHDAY] = {
	 beat/2,pause,beat/2,pause,beat,pause,beat,pause,beat,pause,beat*2,pause,
	 beat/2,pause,beat/2,pause,beat,pause,beat,pause,beat,pause,beat*2,pause,
	 beat/2,pause,beat/2,pause,beat,pause,beat,pause,beat,pause,beat*2,pause,beat,pause,
	 beat/2,pause,beat/2,pause,beat,pause,beat,pause,beat,pause,beat*2,pause
 };
 
 int test_music_note[30] = {
	 c4,R,d4b,R,d4,R,e4b,R,
	 e4,R,f4,R,g4b,R,g4,R,
	 a4b,R,a4,R,b4b,R,b4,R,
	 c5,R,d5b,R,d5,R
 };

 
void main_buzzer(char i, char song){
	
	switch(song) {
		case 1:
			TPM0->MOD = FREQ_2_MOD(score_brawl_stars_begin[i]);
			TPM0_C2V = (FREQ_2_MOD(score_brawl_stars_begin[i]))/10;
			osDelay(duration_brawl_stars_begin[i]);
			break;
		case 2:
			TPM0->MOD = FREQ_2_MOD(score_jingle_bell[i]);
			TPM0_C2V = (FREQ_2_MOD(score_jingle_bell[i]))/10;
			osDelay(duration_jingle_bell[i]);
			break;
		case 3:
			TPM0->MOD = FREQ_2_MOD(score_old_donald[i]);
			TPM0_C2V = (FREQ_2_MOD(score_old_donald[i]))/10;
			osDelay(duration_old_donald[i]);
			break;
		default:
			TPM0->MOD = 0;
			TPM0_C2V = 0;
			break;
	}
}

