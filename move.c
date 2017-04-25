#include "move.h"
#include <math.h>
#include "cliff.h"
#include "color.h"
#include "bump.h"
#include "wifi.h"


double RADIANS = 3.14159265 / 180.0;

void handle_emergency(int code){
	switch(code){
		case 1:
			UART_transmit_string("<<Emergency on left>>");
			break;
		case 2:
			UART_transmit_string("<<Emergency on right>>");
			break;
		case 3:
			UART_transmit_string("<<Emergency on front left>>");
			break;
		case 4:
			UART_transmit_string("<<Emergency on front right>>");
			break;
		case 5:
			UART_transmit_string("<<Emergency on center left>>");
			break;
		case 6:
			UART_transmit_string("<<Emergency on center right>>");
			break;
	}
	UART_transmit_string("\n\r");
}


void mov_______e(oi_t *sensor, int centimeters){
	if(centimeters == 0) return;

	int dist = 0;
	if(centimeters < 0)
		oi_setWheels(-300,-300);
	else
		oi_setWheels(300,300);

	while((centimeters < 0 && dist > centimeters) || (centimeters > 0 && dist < centimeters))
	{
		oi_update(sensor);
		dist += sensor->distance;
		

//		if(checkSensors() != 0){
//			// emergency stop
//			oi_setWheels(0,0);
//
//			// tell the driver
//			int emergencyCode;
//			if(emergencyCode = checkCliffs(sensor)){
//				UART_transmit_string("Cliff detected!");
//				handle_emergency(emergencyCode);
//			}
//			if(emergencyCode = checkColors(sensor)){
//				UART_transmit_string("Color detected!");
//				handle_emergency(emergencyCode);
//			}
//			if(emergencyCode = checkBump(sensor)){
//				UART_transmit_string("Light detected!");
//				handle_emergency(emergencyCode);
//			}
//
//			//stop going forward. emergency readjustment left to driver.
//			break;
//		}
	}
	oi_setWheels(0,0);

	// update position
	abs_position_x += cos(abs_angle * RADIANS) * (float)dist;
	abs_position_y += sin(abs_angle * RADIANS) * (float)dist;

	
}

void turn_____(oi_t *sensor, int degrees){
	if(degrees == 0) return;

	int angle = 0;
	if(degrees > 0)
		oi_setWheels(-200,200); // turn left
	else
		oi_setWheels(200,-200); // turn right

	while((degrees > 0 && angle > -degrees) || (degrees < 0 && angle < -degrees))
	{
		oi_update(sensor);
		angle += sensor->angle;
	}

	abs_angle += angle;
	if(abs_angle >= 360) abs_angle -= 360;
	if(abs_angle < 0) abs_angle += 360;

	oi_setWheels(0,0);
}

void escape(oi_t *sensor)
{
	move(sensor,-15);

	turn(sensor,-90);
	move(sensor,25);

	turn(sensor,-90);
	move(sensor,15);
}

int checkSensors(oi_t *sensor){

	int returner = 0;
	returner += checkCliffs(sensor);
//	returner += checkColors(sensor);
//	returner += checkBump(sensor);

	return returner;
}
