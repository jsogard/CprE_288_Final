#include "open_interface.h"
<<<<<<< HEAD
#include "color.h"
#include "movement.h"
#include "bump.h"
#include <math.h>
int totalDistance = 0;


double RADIANS = 3.14159265 / 180.0;

=======
#include "cliff.h"
#include "color.h"
#include "bump.h"
int totalDistance = 0;


>>>>>>> f99f345c9f2d864f0ef1962f2b050c2b996bdbf3
void move_forward(int centimeters) {

	int millimeters = centimeters * 10;

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    int sum = 0;
    oi_setWheels(100, 100); // move forward; full speed
    while (sum < millimeters) {
        oi_update(sensor_data);

<<<<<<< HEAD
        sum += sensor_data->distance;

        //if any of the sensors go off, stop the robot immediately by breaking out of the while loop
        if(checkSensors(sensor_data)){
        	break;
        }
    }

    oi_setWheels(0, 0); // stop

	// update position
	abs_position_x += cos(abs_angle * RADIANS) * (float)sum/10.0;
	abs_position_y += sin(abs_angle * RADIANS) * (float)sum/10.0;

    oi_free(sensor_data);
}

void move_forward_absolute(int centimeters) {

	int millimeters = centimeters * 10;

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    int sum = 0;
    oi_setWheels(100, 100); // move forward; full speed
    while (sum < millimeters) {
        oi_update(sensor_data);

        sum += sensor_data->distance;
    }

    oi_setWheels(0, 0); // stop

	// update position
	abs_position_x += cos(abs_angle * RADIANS) * (float)sum/10.0;
	abs_position_y += sin(abs_angle * RADIANS) * (float)sum/10.0;

    oi_free(sensor_data);
}

int checkSensors(oi_t *sensor){

	int returner = 0;

	returner += checkColors(sensor);
	returner += checkBump(sensor);

	return returner;
}

=======

        sum += sensor_data->distance;

		if(0 &&  checkSensors() != 0){
			// emergency stop
			oi_setWheels(0,0);

			// tell the driver
			int emergencyCode;
			if(emergencyCode = checkCliffs(sensor_data)){
				UART_transmit_string("Cliff detected!");
				handle_emergency(emergencyCode);
			}
			if(emergencyCode = checkColors(sensor_data)){
				UART_transmit_string("Color detected!");
				handle_emergency(emergencyCode);
			}
			if(emergencyCode = checkBump(sensor_data)){
				UART_transmit_string("Light detected!");
				handle_emergency(emergencyCode);
			}

			//stop going forward. emergency readjustment left to driver.
			break;
		}

    }
    oi_setWheels(0, 0); // stop

    oi_free(sensor_data);
}

>>>>>>> f99f345c9f2d864f0ef1962f2b050c2b996bdbf3
void move_backward(int centimeters) {

	//int millimeters = (centimeters / 10) * -1;
	int millimeters = centimeters * -10;

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    int sum = 0;
    oi_setWheels(-100, -100); // move forward; full speed
    while (sum > millimeters) {
        oi_update(sensor_data);
        sum += sensor_data->distance;
    }
    oi_setWheels(0, 0); // stop

<<<<<<< HEAD
	// update position
	abs_position_x += cos(abs_angle * RADIANS) * (float)sum/10.0;
	abs_position_y += sin(abs_angle * RADIANS) * (float)sum/10.0;


=======
>>>>>>> f99f345c9f2d864f0ef1962f2b050c2b996bdbf3
    oi_free(sensor_data);
}


void turn_clockwise(int degrees){

<<<<<<< HEAD
	int angleChange = 0;
=======
	int angleChange = degrees + 5;
>>>>>>> f99f345c9f2d864f0ef1962f2b050c2b996bdbf3

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    oi_setWheels(-200, 200); // turn
<<<<<<< HEAD
    while (angleChange > (degrees*-1) + 3) {
=======
    while (angleChange > 0) {
>>>>>>> f99f345c9f2d864f0ef1962f2b050c2b996bdbf3
        oi_update(sensor_data);
        angleChange += sensor_data->angle;
    }
    oi_setWheels(0, 0); // stop

<<<<<<< HEAD
    //update angle
    abs_angle -= degrees;
    if(abs_angle < 0) abs_angle += 360;
    if(abs_angle > 360) abs_angle -= 360;

=======
>>>>>>> f99f345c9f2d864f0ef1962f2b050c2b996bdbf3
    oi_free(sensor_data);
}

void turn_counter_clockwise(int degrees){

	int angleChange = 0;

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    oi_setWheels(200, -200); // turn
<<<<<<< HEAD
    while (angleChange < (degrees-3)) {
=======
    while (angleChange < (degrees-5)) {
>>>>>>> f99f345c9f2d864f0ef1962f2b050c2b996bdbf3
        oi_update(sensor_data);
        angleChange += sensor_data->angle;
    }
    oi_setWheels(0, 0); // stop

<<<<<<< HEAD
    //update angle
    abs_angle += degrees;
    if(abs_angle < 0) abs_angle += 360;
    if(abs_angle > 360) abs_angle -= 360;

    oi_free(sensor_data);
}

=======
    oi_free(sensor_data);
}

/*void maneuver(oi_t *sensor_data){

	if(sensor_data->bumpLeft && sensor_data->bumpRight)
	{
		move_backward(15);
		turn_clockwise( -90);
		move_forward(sensor_data, 25);
		turn_counter_clockwise(sensor_data, 90);
		move_forward(sensor_data, (200 - (totalDistance / 10)));
	}

	if(sensor_data->bumpLeft)
	{
		move_backward(sensor_data, 15);
		turn_clockwise(sensor_data, -90);
		move_forward(sensor_data, 25);
		turn_counter_clockwise(sensor_data, 90);
		move_forward(sensor_data, (200 - (totalDistance / 10)));

	}

	if(sensor_data->bumpRight)
	{
		move_backward(sensor_data, 15);
		turn_counter_clockwise(sensor_data, 90);
		move_forward(sensor_data, 25);
		turn_clockwise(sensor_data, -90);
		move_forward(sensor_data, (200 - (totalDistance / 10)));

	}
}*/

>>>>>>> f99f345c9f2d864f0ef1962f2b050c2b996bdbf3
void move(int centimeters){
	if (centimeters < 0)
		move_backward(centimeters * -1);
	else move_forward(centimeters);
}

void turn(int angle){
	if(angle > 0) turn_clockwise(angle);
	else turn_counter_clockwise(-1*angle);
}
<<<<<<< HEAD
=======

//void main() {
//    oi_t *sensor_data = oi_alloc();
//    oi_init(sensor_data);
//
//	move_forward(sensor_data, 200);
//}
>>>>>>> f99f345c9f2d864f0ef1962f2b050c2b996bdbf3
