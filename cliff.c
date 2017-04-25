/*
 * cliff.c
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
 * @param sensor_data Sensor data struct from robot
 * @return 1 if there is a cliff, else 0
 */
int checkCliffs(oi_t *sensorData){
	if(sensorData -> cliffLeft){
		//move backwards
		//uart_transmit("Cliff on Left")
		return 1;
	}
	if(sensorData -> cliffRight){
		//move backwards
		//uart_transmit("Cliff on Right")
		return 2;
	}
	if(sensorData -> cliffFrontLeft){
		//move backwards
		//uart_transmit("Cliff on Front Left")
		return 3;
	}
	if(sensorData -> cliffFrontRight){
		//move backwards
		//uart_transmit("Cliff on Front Right")
		return 4;
	}
	return 0;
}


