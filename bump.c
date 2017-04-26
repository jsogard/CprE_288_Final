/*
 * bump.c
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
#include "bump.h"


/**
 * int checkBump(oi_t *sensorData) Checks the current open_interface sensor data for the light bumpers, and the actual bumpers to see if anything is detected to prevent moving objects, and to ensure the bot stops when something is detected. 
 * @param oi_t *sensorData the current open_interface sensor data
 * @return 1 if a sensor is triggered
 */
int checkBump(oi_t *sensorData){
	static char msg[40];
	int ret = 0;
	if(sensorData->lightBumpLeftSignal > 150){
		sprintf(msg, "Light Bump on Left: %d \r\n", sensorData->lightBumpLeftSignal);
		UART_transmit_string(msg);
		ret = 1;
	}
	if(sensorData->lightBumpFrontLeftSignal > 150){
		sprintf(msg, "Light Bump on Front Left: %d \r\n", sensorData->lightBumpFrontLeftSignal);
		UART_transmit_string(msg);
		ret = 1;
	}
	if(sensorData->lightBumpCenterLeftSignal > 150){
		sprintf(msg, "Light Bump on Center Left: %d \r\n", sensorData->lightBumpCenterLeftSignal);
		UART_transmit_string(msg);
		ret = 1;
	}
	if(sensorData->lightBumpCenterRightSignal > 150){
		sprintf(msg, "Light Bump on Center Right: %d \r\n", sensorData->lightBumpCenterRightSignal);
		UART_transmit_string(msg);
		ret = 1;
	}
	if(sensorData->lightBumpFrontRightSignal > 150){
		sprintf(msg, "Light Bump on Front Right: %d \r\n", sensorData->lightBumpFrontRightSignal);
		UART_transmit_string(msg);
		ret = 1;
	}
	if(sensorData->lightBumpRightSignal > 150){
		sprintf(msg, "Light Bump on Right: %d \r\n", sensorData->lightBumpRightSignal);
		UART_transmit_string(msg);
		ret = 1;
	}
	if(sensorDta->bumpLeft){
		UART_transmit_string("Left Bumper Triggered");
		ret = 1;
	}
	if(sensorData->bumpRight){
		UART_transmit_string("Right Bumper Triggered");
		ret = 1;
	}
	return ret;
}

