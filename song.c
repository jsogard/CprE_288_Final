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
 * @param sensor_data Sensor data struct from robot
 * @return 1 if there is a cliff, else 0
 */
void loadSong(){
		unsigned char mario[] = {55,60,64,67,72,76,79,76,56,60,63,68,72,75,80,75,58,62,65,70,74,77,82,82,82,82,84};

<<<<<<< HEAD
		unsigned char marioDuration[] = {8,8,8,8,8,8,24,24,8,8,8,8,8,8,24,24,8,8,8,8,8,8,24,8,8,8,48};
=======
		unsigned char marioDuration[] = {133,133,133,133,133,133,400,400,133,133,133,133,133,133,400,400,133,133,133,133,133,133,400,133,133,133,800};
>>>>>>> f99f345c9f2d864f0ef1962f2b050c2b996bdbf3

		oi_loadSong(0, 27, mario, marioDuration);
}

void playSong(){
<<<<<<< HEAD
	oi_play_song(0);
=======
	oi_playSong(0);
>>>>>>> f99f345c9f2d864f0ef1962f2b050c2b996bdbf3
}
