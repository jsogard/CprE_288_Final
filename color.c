/*
 * color.c
 *
 *  Created on: Apr 24, 2017
 *      Author: ethantw
 */



#include <stdio.h>
#include <stdbool.h>
#include "timer.h"
#include "lcd.h"
#include "driverlib/interrupt.h"
#include "open_interface.h"

/**
 * @param sensorData data from the sensor struct
 * @return 1 if the sensor is triggered, else 0
 */
int checkColors(oi_t *sensorData){
	if(sensorData->cliffRightSignal > 2600){
		//white line on right
		return 1;
	}
	if(sensorData->cliffLeftSignal > 2600){
		//white line on let
		return 2;
	}
	if(sensorData->cliffFrontLeftSignal > 2600){
		//white line front left
		return 3;
	}
	if(sensorData->cliffFrontRightSignal > 2600){
		//white line front right
		return 4;
	}
	//TODO check for the black dot in the middle of the finish area
	return 0;
}



