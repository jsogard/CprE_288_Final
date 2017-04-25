
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
#include "move.h"
#include "math.h"
#include "utils.h"

oi_t *sensor_data;

typedef struct object{
	uint32_t distance;
	uint32_t width;
	uint32_t l_degrees;
	uint32_t r_degrees;
} obstacle;

float ping(){
	uint32_t avg_time = 0, dist_mm;
	send_pulse();
	avg_time += ping_read();
	timer_waitMillis(20);
	send_pulse();
	avg_time += ping_read();
	timer_waitMillis(20);
	send_pulse();
	avg_time += ping_read();
	avg_time /= 3;

	dist_mm = time2dist(avg_time);
	return ((float)dist_mm)/10.0;
}

/**
 * Executes a commad on the robot
 */
void command_look_up(char* command){
	if (startsWith(command, "servo")){
		char* token = strtok(command, " ");
		token = strtok(NULL, " ");
		int deg = atoi(token);
		move_servo_absolute(deg);

	}else if (startsWith(command, "move")){
		char* token = strtok(command, " ");
		token = strtok(NULL, " ");
		int dist = atoi(token);
		move(sensor_data, dist);
	}else if (startsWith(command, "escape")){
		char* token = strtok(command, " ");
		token = strtok(NULL, " ");
		int dist = atoi(token);
		escape(sensor_data);
	}else{
		lcd_clear();
		UART_transmit_string("some bullshit\n");
		lcd_puts("Some bullshit\n");
	}
	UART_transmit_string(command);
	UART_transmit_string("\n\r");
}

/**
 * Connects to PUTTY, takes basic commands and executes them
 * e.g servo 10 -> this will move the servo to 10
 */
int main(){
	lcd_init();

	oi_t *sensor_data = oi_alloc();
	oi_init(sensor_data);
	TIMER1_init();
	timer_init();
	pulse_init();
//	adc_init(); //TODO: uncomment this
	UART_init();
//	WiFi_start();
	state = LOW;


	command_look_up("servo 50");
//	command_look_up("move 50");
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
//	int MAD_DIST = 100;
//
//
////	configure_servo();
//
//	obstacle obstacles[30];
//	int o_index = 0;
//	static uint32_t data[3][90];
//	int data_index = 0;
//
//	UART_transmit_string("Degrees\tIR   \tSonar\n\r");
//
//	/* GATHER ANGLE, DISTANCE DATA */
//
//	float degrees = 0;
//	double ir;
//	uint32_t sonar;
//	int max_angle = 174;
//	while(degrees < max_angle){
//		ir = adc_convert(ADC_read(0));
//		sonar = ping();
//		static char res[50];
//		sprintf(res, "%7d\t%5d\t%5d\n\r", (int)degrees,(int)ir,(int)sonar);
//		data[0][data_index] = degrees;
//		data[1][data_index] = ir;
//		data[2][data_index++] = sonar;
//
//		lcd_init();
//		lcd_printf(res);
//		UART_transmit_string(res);
//		timer_waitMillis(50);
//		degrees += 2;
//		move_servo_absolute(degrees);
//	}
//
//	/* INTERPRET DATA FOR OBSTACLES */
//
//	uint32_t i, prev_ir = 81, degree_length = 0, min_dist = 0, max_dist = 0;
//	float avg_dist = 0;
//	obstacle *smallest;
//	int counting = 0;
//	for(i = 0; i < max_angle/2 && o_index < 30; i++){
//		if(counting && prev_ir < 80 && data[1][i] > 80){
//			counting = 0;
//			obstacles[o_index].distance = min_dist;
//			obstacles[o_index].l_degrees = data[0][i];
//			avg_dist /= (obstacles[o_index].l_degrees - obstacles[o_index].r_degrees)/2;
//			obstacles[o_index].width = get_obj_length(obstacles[o_index].l_degrees, obstacles[o_index].r_degrees, avg_dist);
//			if(obstacles[o_index].width < 5){
//				continue;
//			}
//
//
//			static char res[50];
//			sprintf(res, "Object #%d:\n\rDist: %u\n\rWidth: %u\n\rSpan: %u - %u\n\r\n\r", o_index+1, obstacles[o_index].distance, obstacles[o_index].width , obstacles[o_index].r_degrees, obstacles[o_index].l_degrees);
//			UART_transmit_string(res);
//
//			if(o_index == 0 || obstacles[o_index].width < smallest->width){
//				smallest = &obstacles[o_index];
//			}
//
//			o_index++;
//			degree_length = 0;
//			avg_dist = 0;
//		}
//		else if(!counting && data[1][i] < 80 && prev_ir > 80){
//			counting = 1;
//			obstacles[o_index].r_degrees = data[0][i];
//			min_dist = data[2][i];
//			avg_dist += data[2][i];
//		}
//		else if(counting){
//			degree_length += 2;
//			if(data[2][i] < min_dist)
//				min_dist = data[2][i];
//			if(data[2][i] > max_dist && data[2][i] < 80)
//				max_dist = data[2][i];
//			avg_dist += data[2][i];
//		}
//		prev_ir = data[1][i];
//
//	}
//	if(data[1][max_angle/2-1] < 80){
//		obstacles[o_index].distance = min_dist;
//		obstacles[o_index].l_degrees = data[0][i];
//		obstacles[o_index].width = get_obj_length(obstacles[o_index].l_degrees, obstacles[o_index].r_degrees, max_dist);
//
//		if(obstacles[o_index].width > 5){
//
//
//		static char res[50];
//		sprintf(res, "Object #%d:\n\rDist: %u\n\rWidth: %u\n\rSpan: %u - %u\n\r\n\r", o_index+1, obstacles[o_index].distance, obstacles[o_index].width , obstacles[o_index].r_degrees, obstacles[o_index].l_degrees);
//		UART_transmit_string(res);
//
//		if(obstacles[o_index].width < smallest->width){
//			smallest = &obstacles[o_index];
//		}
//
//		}
//	}
//
//
//	/* POINT TO SMALLEST OBJECT */
//
//	int moveTo = (smallest->l_degrees - smallest->r_degrees)/2 + smallest->r_degrees;
//	static char res[50];
//	sprintf(res, "Moving to angle %u\n\r\n\r", moveTo);
//	UART_transmit_string(res);


	return 0;
}


