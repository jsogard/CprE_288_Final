#include "open_interface.h"


void move(oi_t *sensor, int centimeters);

void turn(oi_t *sensor, int degrees);
void escape(oi_t *sensor);

/*
	    90
		^
		|
180 <---+---> 0
		|
		v
	  270
*/

int abs_angle = 90;
float abs_position_x = 0;
float abs_position_y = 0;