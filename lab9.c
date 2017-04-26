
#include "servo.h"
#include "ping.h"
#include "lcd.h"
#include "wifi.h"
#include "bump.h"
#include "color.h"
#include "timer.h"
#include "adc.h"
#include <stdbool.h>
#include <stdlib.h>
#include "driverlib/interrupt.h"
#include "open_interface.h"
#include "button.h"
#include "movement.h"
#include "math.h"
#include "utils.h"
#include "song.h"

//oi_t *sensor_data;

typedef struct object{
	uint32_t distance;
	uint32_t width;
	uint32_t l_degrees;
	uint32_t r_degrees;
} obstacle;



void command_look_up(char* command);

void print_oi_status(){
	char str[80];
	sprintf(str, "OI STATUS:\r\n\
				  ----------\r\n\
				  Position: (%+4d, %+4d)\r\n\
				  Angle: %3d\r\n" ,(int)abs_position_x, (int)abs_position_y, abs_angle );
	UART_transmit_string(str);
}


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

	WiFi_start();
	state = LOW;

	/*
	 *
115200 speed (baud)
8 Data bits
No Parity
1 Stop bits
No flow control
Host Name: 192.168.1.1
Port: 42880
Connection type: Raw
	 *
	 */


//    oi_t *sensor_data = oi_alloc();
//    oi_init(sensor_data);
//
//	while(1){
//		static char msg[40];
//		oi_update(sensor_data);
//		sprintf(msg, "CLiff %d cliffLeftSignal\r\n", sensor_data->lightBumpLeftSignal);
//		UART_transmit_string(msg);
//		sprintf(msg, "CLiff %d cliffFrontLeftSignal\r\n", sensor_data->lightBumpFrontLeftSignal);
//		UART_transmit_string(msg);
//		sprintf(msg, "CLiff %d cliffFrontRightSignal\r\n", sensor_data->lightBumpCenterLeftSignal);
//		UART_transmit_string(msg);
//		sprintf(msg, "CLiff %d cliffLeftSignal\r\n", sensor_data->lightBumpRightSignal);
//		UART_transmit_string(msg);
//		sprintf(msg, "CLiff %d cliffFrontLeftSignal\r\n", sensor_data->lightBumpFrontRightSignal);
//		UART_transmit_string(msg);
//		sprintf(msg, "CLiff %d cliffFrontRightSignal\r\n", sensor_data->lightBumpCenterRightSignal);
//		UART_transmit_string(msg);
//		timer_waitMillis(3000);
//	}
//
//
//	oi_free(sensor_data);


	abs_angle = 90;
	abs_position_x = 0;
	abs_position_y = 0;

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
		print_oi_status();
	}else if (startsWith(command, "Fmove")){
		char* token = strtok(command, " ");
		token = strtok(NULL, " ");
		int dist = atoi(token);
		move_forward_absolute(dist);
		print_oi_status();
	}else if (startsWith(command, "turn")){
		char* token = strtok(command, " ");
		token = strtok(NULL, " ");
		int dist = atoi(token);
		turn(dist);
		print_oi_status();
	}else if (startsWith(command, "song")){
		oi_t *sensor_data = oi_alloc();
		oi_init(sensor_data);
		loadSong();
		playSong();
		oi_free(sensor_data);
		// dat song ish
	}else{
		lcd_clear();
		UART_transmit_string("some bullshit\n");
		lcd_puts("Some bullshit\n");
	}
	UART_transmit_string(command);
	UART_transmit_string("\n\r");
}
