<<<<<<< HEAD
=======
 *  Created on: Apr 24, 2017
 *      Author: ethantw
 */

>>>>>>> f99f345c9f2d864f0ef1962f2b050c2b996bdbf3
#include <stdio.h>
#include <stdbool.h>
#include "timer.h"
#include "lcd.h"
#include "driverlib/interrupt.h"
#include "open_interface.h"


/**
 * this functions loads the song Space Jam into the open interface when called.
 */
void loadSong(){
//		unsigned char mario[] = {55,60,64,67,72,76,79,76,56,60,63,68,72,75,80,75,58,62,65,70,74,77,82,82,82,82,84};
//		unsigned char marioDuration[] = {8,8,8,8,8,8,24,24,8,8,8,8,8,8,24,24,8,8,8,8,8,8,24,8,8,8,48};
//		oi_loadSong(0, 27, mario, marioDuration);

		unsigned char spaceJam[] = {47, 45, 47, 47, 49, 50, 45, 47, 45, 47, 45, 0, 45, 45, 45, 45, 45, 47, 47, 45, 45, 45, 47, 45, 47, 45, 45, 47, 47, 42, 45, 47, 47, 42, 45, 47, 47, 49, 47, 45}
		unsigned char spaceJamDuration[] = {6, 6, 6, 6, 6, 12, 6, 6, 6, 12, 12, 6, 6, 6, 6, 12, 12, 6, 6, 12, 6, 6, 6, 6, 12, 24, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 12, 36, 6, 12}
		oi_loadSong(1, 40, spaceJam, spaceJamDuration);
}

/**
 * this functions plays the song Space Jam on the open interface when called.
 */
void playSong(){
	oi_play_song(1);
}
