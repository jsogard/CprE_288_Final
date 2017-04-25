/*
 * light.c
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
 * @return 1 if a sensor is triggered
 */
int checkLight(oi_t *sensorData){
	if(sensorData->lightBumpLeftSignal > 650){
		//stop
		//uart_transmit("Boulder on left")
		return 1;
	}
	if(sensorData->lightBumpFrontLeftSignal > 650){
		//stop
		//uart_transmit("Boulder on front left")
		return 1;
	}
	if(sensorData->lightBumpCenterLeftSignal > 650){
		//stop
		//uart_transmit("boulder on center left")
		return 1;
	}
	if(sensorData->lightBumpCenterRightSignal > 650){
		//stop
		//uart_transmit("boulder on center right")
		return 1;
	}
	if(sensorData->lightBumpFrontRightSignal > 650){
		//stop
		//uart_transmit("boulder on front right")
		return 1;
	}
	if(sensorData->lightBumpRightSignal > 650){
		//stop
		//uart_transmit("boulder on right")
		return 1;
	}
	return 0;
}

