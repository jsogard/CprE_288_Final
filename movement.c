#include "open_interface.h"
#include "color.h"
#include "movement.h"
#include "bump.h"
#include <math.h>
int totalDistance = 0;

double RADIANS = 3.14159265 / 180.0;

/**
* void move_forward(int centimeters) Moves the bot forward the given number of centimeters while checking all of the sensors. If any of the sensors go off, then the bot stops. 
* @param centimeters	the amount of centimeters you want the bot to move forward
*/
void move_forward(int centimeters){

	int millimeters = centimeters * 10;

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    int sum = 0;
    oi_setWheels(100, 100); // move forward; full speed
    while (sum < millimeters) {
        oi_update(sensor_data);

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

/**
* void move_forward_absolute(int centimeters) Moves the bot forward without checking any sensors. in case you think you are on the black final part.
* @param centimeters	the amount of centimeters you want the bot to move forward
*/
void move_forward_absolute(int centimeters){

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

/**
* int checkSensors(oi_t *sensor) Checks the light bumpers, bumpers, and color sensors and returns a number greater than zero if any of the senors are tripped. Otherwise it returns 0.
* @param *sensor	the current open_interface sensor data.
* @return Integer value > 0 if any of the sensors have been tripped, else 0.
*/
int checkSensors(oi_t *sensor){

	int returner = 0;

	returner += checkColors(sensor);
	returner += checkBump(sensor);

	return returner;
}

/**
* void move_backward(int centimeters) Moves the bot backwards without checking any sensors. None of the sensors are on the back anyways.
* @param centimeters	the amount of centimeters you want the bot to move backward
*/
void move_backward(int centimeters){

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

	// update position
	abs_position_x += cos(abs_angle * RADIANS) * (float)sum/10.0;
	abs_position_y += sin(abs_angle * RADIANS) * (float)sum/10.0;

    oi_free(sensor_data);
}

/**
* void turn_clockwise(int degrees) Turn the bot clockwise the given number of degrees.
* @param centimeters	the amount of degress you want the bot to turn clockwise
*/
void turn_clockwise(int degrees){

	int angleChange = 0;

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    oi_setWheels(-200, 200); // turn

    while (angleChange > (degrees*-1) + 3) {
        oi_update(sensor_data);
        angleChange += sensor_data->angle;
    }
    oi_setWheels(0, 0); // stop

    //update angle
    abs_angle -= degrees;
    if(abs_angle < 0) abs_angle += 360;
    if(abs_angle > 360) abs_angle -= 360;

    oi_free(sensor_data);
}

/**
* void turn_counter_clockwise(int degrees) Turns the bot counter clockwise the given number of degrees. 
* @param centimeters	the amount of degress you want the bot to turn clockwise
*/
void turn_counter_clockwise(int degrees){

	int angleChange = 0;

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    oi_setWheels(200, -200); // turn

    while (angleChange < (degrees-3)) {
        oi_update(sensor_data);
        angleChange += sensor_data->angle;
    }
    oi_setWheels(0, 0); // stop

    //update angle
    abs_angle += degrees;
    if(abs_angle < 0) abs_angle += 360;
    if(abs_angle > 360) abs_angle -= 360;

    oi_free(sensor_data);
}

/**
* void move(int centimeters) Parses the given int and calls move_forward if it is positive, move_backward if it is negative. 
* @param centimeters	the amount of centimeters you want the bot to move
*/
void move(int centimeters){
	if (centimeters < 0)
		move_backward(centimeters * -1);
	else move_forward(centimeters);
}

/**
* void turn(int angle) Parses the given int and calls turn_clockwise if it is negative, and turn_counter_clockwise if it is positive.
* @param centimeters	the amount of degress you want the bot to turn
*/
void turn(int angle){
	if(angle < 0) turn_clockwise(angle*-1);
	else turn_counter_clockwise(angle);
}