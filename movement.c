#include "open_interface.h"
#include "cliff.h"
#include "color.h"
#include "bump.h"
int totalDistance = 0;


void move_forward(int centimeters) {

	int millimeters = centimeters * 10;

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    int sum = 0;
    oi_setWheels(100, 100); // move forward; full speed
    while (sum < millimeters) {
        oi_update(sensor_data);


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

    oi_free(sensor_data);
}


void turn_clockwise(int degrees){

	int angleChange = degrees + 5;

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    oi_setWheels(-200, 200); // turn
    while (angleChange > 0) {
        oi_update(sensor_data);
        angleChange += sensor_data->angle;
    }
    oi_setWheels(0, 0); // stop

    oi_free(sensor_data);
}

void turn_counter_clockwise(int degrees){

	int angleChange = 0;

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    oi_setWheels(200, -200); // turn
    while (angleChange < (degrees-5)) {
        oi_update(sensor_data);
        angleChange += sensor_data->angle;
    }
    oi_setWheels(0, 0); // stop

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

void move(int centimeters){
	if (centimeters < 0)
		move_backward(centimeters * -1);
	else move_forward(centimeters);
}

void turn(int angle){
	if(angle > 0) turn_clockwise(angle);
	else turn_counter_clockwise(-1*angle);
}

//void main() {
//    oi_t *sensor_data = oi_alloc();
//    oi_init(sensor_data);
//
//	move_forward(sensor_data, 200);
//}
