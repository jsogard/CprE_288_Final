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

void cliff_init(){

	oi_t *sensorData = oi_alloc();
	oi_init(sensorData);
	checkCliffs(sensorData)

}

int checkCliffs(oi_t *sensorData){
	if(sensorData -> cliffLeft){
		//move backwards
		//uart_transmit("Cliff on Left")
		return 1;
	}
	if(sensorData -> cliffRight){
		//move backwards
		//uart_transmit("Cliff on Right")
		return 1;
	}
	if(sensorData -> cliffFrontLeft){
		//move backwards
		//uart_transmit("Cliff on Front Left")
		return 1;
	}
	if(sensorData -> cliffFrontRight){
		//move backwards
		//uart_transmit("Cliff on Front Right")
		return 1;
	}
}


