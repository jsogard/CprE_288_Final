#include "open_interface.h"

int totalDistance = 0;


void move_forward(oi_t *sensor, int centimeters) {

	int millimeters = centimeters * 10;

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    int sum = 0;
    oi_setWheels(500, 500); // move forward; full speed
    while (sum < millimeters) {
        oi_update(sensor_data);
        if (sensor_data->bumpLeft || sensor_data->bumpRight) {
        	oi_setWheels(0, 0); // stop
        	totalDistance += sum;
        	maneuver(sensor_data);
        }
        sum += sensor_data->distance;
    }
    oi_setWheels(0, 0); // stop

    oi_free(sensor_data);
}

void move_backward(oi_t *sensor, int centimeters) {

	int millimeters = (centimeters / 10) * -1;

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    int sum = 0;
    oi_setWheels(-500, -500); // move forward; full speed
    while (sum > millimeters) {
        oi_update(sensor_data);
        sum += sensor_data->distance;
    }
    oi_setWheels(0, 0); // stop

    oi_free(sensor_data);
}


void turn_clockwise(oi_t *sensor, int degrees){

	int angleChange = 0;

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    oi_setWheels(-250, 250); // turn
    while (angleChange > (degrees+5)) {
        oi_update(sensor_data);
        angleChange += sensor_data->angle;
    }
    oi_setWheels(0, 0); // stop

    oi_free(sensor_data);
}

void turn_counter_clockwise(oi_t *sensor, int degrees){

	int angleChange = 0;

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    oi_setWheels(250, -250); // turn
    while (angleChange < (degrees-5)) {
        oi_update(sensor_data);
        angleChange += sensor_data->angle;
    }
    oi_setWheels(0, 0); // stop

    oi_free(sensor_data);
}

void maneuver(oi_t *sensor_data){

	if(sensor_data->bumpLeft && sensor_data->bumpRight)
	{
		move_backward(sensor_data, 15);
		turn_clockwise(sensor_data, -90);
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
}

void main() {
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

	move_forward(sensor_data, 200);
}
