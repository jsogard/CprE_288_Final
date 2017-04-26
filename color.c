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
#include "wifi.h"
#include "driverlib/interrupt.h"
#include "open_interface.h"

/**
 * int checkColors(oi_t *sensorData) Takes in the current open_interface sensor data and checks eachs color sensor to see if there's 
 * 1) a cliff
 * 2) a white line
 * 3) any black
 * It then sends to putty anything that was detected and returns 1 if anything was detected, otherwise it returns 0.
 * @param sensorData data from the sensor struct
 * @return 1 if the sensor is triggered, else 0
 */
int checkColors(oi_t *sensorData){
	int ret = 0;

	if(sensorData->cliffRightSignal > 2700){
		//return white line on right
		UART_transmit_string("White Line on Right\r\n");
		ret = 1;

//	else if(sensorData->cliffRightSignal > 1600){
//		//normal ground
////		UART_transmit_string("Right's good, move on brother!");
	}else if(sensorData->cliffRightSignal > 400 && sensorData->cliffRightSignal < 1200){
		//black square
		UART_transmit_string("Black on Right\r\n");
		ret = 1;
	}else if(sensorData->cliffRightSignal < 400){
		//cliff
		UART_transmit_string("Cliff on Right\r\n");
		ret = 1;
	}

	if(sensorData->cliffLeftSignal > 2600){
		//white line on let
		UART_transmit_string("White Line on Left\r\n");
		ret = 1;

//	else if(sensorData->cliffLeftSignal > 1600){
//		//normal ground
////		UART_transmit_string("Left's good, move on brother!");
	}else if(sensorData->cliffLeftSignal > 400 && sensorData->cliffLeftSignal < 1200){
		//black square
		UART_transmit_string("Black on Left\r\n");
		ret = 1;
	}else if(sensorData->cliffLeftSignal < 400){
		//cliff
		UART_transmit_string("Cliff on Left\r\n");
		ret = 1;
	}

	if(sensorData->cliffFrontLeftSignal > 2600){
		//white line front left
		UART_transmit_string("White Line on Front Left\r\n");
		ret = 1;
//	else if(sensorData->cliffFrontLeftSignal > 1600){
//		//normal ground
////		UART_transmit_string("Front Left's good, move on brother!");
	}else if(sensorData->cliffFrontLeftSignal > 400 && sensorData->cliffFrontLeftSignal < 1200){
		//black square
		UART_transmit_string("Black Line on Front Left\r\n");
		ret = 1;
	}else if(sensorData->cliffFrontLeftSignal < 400){
		//cliff
		UART_transmit_string("Cliff Line on Front Left\r\n");
		ret = 1;
	}

	if(sensorData->cliffFrontRightSignal > 2600){
		//white line front right
		UART_transmit_string("White Line on Front Right\r\n");
		ret = 1;
//	else if(sensorData->cliffFrontRightSignal > 1600){
//		//normal ground
////		UART_transmit_string("Front Right's good, move on brother!");
	}else if(sensorData->cliffFrontRightSignal > 400 && sensorData->cliffFrontRightSignal < 1200){
		//black square
		UART_transmit_string("Black Line on Front Right\r\n");
		ret = 1;
	}else if(sensorData->cliffFrontRightSignal < 400){
		//cliff
		UART_transmit_string("Cliff on Front Right\r\n");
		ret = 1;
	}
	return ret;
}



