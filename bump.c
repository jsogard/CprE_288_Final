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
 * @return 1 if a sensor is triggered
 */
int checkBump(oi_t *sensorData){
<<<<<<< HEAD
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
	return ret;
=======
	if(sensorData->lightBumpLeftSignal > 650){
		//stop
		//uart_transmit("Boulder on left")
		return 1;
	}
	if(sensorData->lightBumpFrontLeftSignal > 650){
		//stop
		//uart_transmit("Boulder on front left")
		return 3;
	}
	if(sensorData->lightBumpCenterLeftSignal > 650){
		//stop
		//uart_transmit("boulder on center left")
		return 5;
	}
	if(sensorData->lightBumpCenterRightSignal > 650){
		//stop
		//uart_transmit("boulder on center right")
		return 6;
	}
	if(sensorData->lightBumpFrontRightSignal > 650){
		//stop
		//uart_transmit("boulder on front right")
		return 4;
	}
	if(sensorData->lightBumpRightSignal > 650){
		//stop
		//uart_transmit("boulder on right")
		return 2;
	}
	return 0;
>>>>>>> f99f345c9f2d864f0ef1962f2b050c2b996bdbf3
}

