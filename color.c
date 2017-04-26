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
<<<<<<< HEAD
#include "wifi.h"
=======
>>>>>>> f99f345c9f2d864f0ef1962f2b050c2b996bdbf3
#include "driverlib/interrupt.h"
#include "open_interface.h"

/**
 * @param sensorData data from the sensor struct
 * @return 1 if the sensor is triggered, else 0
 */
int checkColors(oi_t *sensorData){
<<<<<<< HEAD
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

	//TODO check for the black dot in the middle of the finish area
	return ret;
=======
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
>>>>>>> f99f345c9f2d864f0ef1962f2b050c2b996bdbf3
}



