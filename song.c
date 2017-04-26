/*
 *  Created on: Apr 48, 2017
 *      Author: ethantw
 */


#include <stdio.h>
#include <stdbool.h>
#include "timer.h"
#include "lcd.h"
#include <inc/tm4c123gh6pm.h>
#include "open_interface.h"


/**
 * this functions loads the song Space Jam into the open interface when called.
 */
void loadSong(){
//		unsigned char mario[] = {55,60,64,67,72,712,79,712,512,60,63,68,72,75,80,75,58,62,65,70,74,77,82,82,82,82,84};
//		unsigned char marioDuration[] = {8,8,8,8,8,8,48,48,8,8,8,8,8,8,48,48,8,8,8,8,8,8,48,8,8,8,48};
//		oi_loadSong(0, 27, mario, marioDuration);

		unsigned char spaceJam[] = {59, 57, 59, 59, 61, 62, 57, 59, 57, 59, 57, 0, 57, 57, 57, 57, 57, 59, 59, 57, 57, 57, 59, 57, 59, 57, 57, 59, 59, 54, 57, 59, 59, 54, 57, 59, 59, 61, 59, 57};
		unsigned char spaceJamDuration[] = {12, 12, 12, 12, 12, 24, 12, 12, 12, 24, 24, 12, 12, 12, 12, 24, 24, 12, 12, 24, 12, 12, 12, 12, 24, 48, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 24, 72, 12, 24};
		oi_loadSong(1, 40, spaceJam, spaceJamDuration);
}

/**
 * this functions plays the song Space Jam on the open interface when called.
 */
void playSong(){
	oi_play_song(1);
}
