
#include "servo.h"
#include "ping.h"
#include "lcd.h"
#include "wifi.h"
#include "timer.h"
#include "adc.h"
#include <stdbool.h>
#include <stdlib.h>
#include "driverlib/interrupt.h"
#include "button.h"
#include "movement.h"
#include "math.h"
#include "utils.h"

//oi_t *sensor_data;

typedef struct object{
	uint32_t distance;
	uint32_t width;
	uint32_t l_degrees;
	uint32_t r_degrees;
} obstacle;

void command_look_up(char* command);


//int madddin() {
//    oi_t *sensor_data = oi_alloc();
//    oi_init(sensor_data);
//
//    int sum = 0;
//    oi_setWheels(500, 500); // move forward; full speed
//    while (sum < 1000) {
//        oi_update(sensor_data);
//        sum += sensor_data->distance;
//    }
//    oi_setWheels(0, 0); // stop
//
//    oi_free(sensor_data);
//    return 0;
//}

/**
 * Connects to PUTTY, takes basic commands and executes them
 * e.g servo 10 -> this will move the servo to 10
 */
int main(){
	lcd_init();


	TIMER1_init();
	timer_init();
	pulse_init();
	adc_init(); //TODO: uncomment this
	UART_init();
//	WiFi_start();
	state = LOW;

//	command_look_up("cservo 50");
	command_look_up("move 10");
//	command_look_up("escape 50");
	static char chr[100];
	char s_data;
	while(1){
		int num = 0;
		while(((s_data = UART_receive()) != '\r') && num < 20){
			if (s_data != 10)
				chr[num++] = s_data;
		}
		chr[num] = 0;
		lcd_init();
		lcd_puts(chr);
		num = 0;

		command_look_up(chr);
	}


	return 0;
}

void command_look_up(char* command){
	if (startsWith(command, "servo")){
		get_objects_sweep();
	}else if (startsWith(command, "move")){
		char* token = strtok(command, " ");
		token = strtok(NULL, " ");
		int dist = atoi(token);
		move(dist);
	}else if (startsWith(command, "turn")){
			char* token = strtok(command, " ");
			token = strtok(NULL, " ");
			int dist = atoi(token);
			turn(dist);
	}else if (startsWith(command, "song")){
		char* token = strtok(command, " ");
		token = strtok(NULL, " ");
		int dist = atoi(token);

	}else if (startsWith(command, "oservo")){
		char* token = strtok(command, " ");
		token = strtok(NULL, " ");
		int deg = atoi(token);
		move_servo_absolute(deg);
	}else{
		lcd_clear();
		UART_transmit_string("some bullshit\n");
		lcd_puts("Some bullshit\n");
	}
	UART_transmit_string(command);
	UART_transmit_string("\n\r");
}
