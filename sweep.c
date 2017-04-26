
#include "servo.h"
#include "ping.h"
#include "lcd.h"
#include "wifi.h"
#include "timer.h"
#include "sweep.h"
#include "adc.h"
#include <stdbool.h>
#include "button.h"
#include <inc/tm4c123gh6pm.h>


#include "math.h"


typedef struct object{
	uint32_t distance;
	uint32_t width;
	uint32_t l_degrees;
	uint32_t r_degrees;
} obstacle;



/**
* int get_obj_length(int l_degrees, int r_degrees, int dist) given the left most point of an object, the right most point, and the ditance after a sweep, this function then computes the linear width of the object.
* @param l_degrees	the left most point of the object in the sweep
* @param r_degrees	the right most point of the object in the sweep
* @param dist 	the distance of the object
* @return Integer linear width of object.
*/
int get_obj_length(int l_degrees, int r_degrees, int dist){
	double rad = (3.14159 * (double)(l_degrees - r_degrees)) / 360.0;
	double width = ((double)dist * sin(rad)) / cos(rad);
	return width * 2;
}

/**
* void get_objects_sweep() This function sweeps the servo motor while scanning with the ping and ir sensors and prints out each object that it finds while sweeping.
*/
void get_objects_sweep(){
	state = LOW;

	int MAD_DIST = 100;

	//	configure_servo();
	obstacle obstacles[10];
	int o_index = 0;
	static uint32_t data[3][90];
	int data_index = 0;

	char cmap[81][40];
	int i, j, dx, dy;
	for(i = 0; i < 81; i++){
		for(j = 0; j < 40; j++){
			dx = i - 40;
			dy = 39 - j;
			if(i == 40 && j == 39) cmap[i][j] = 239;
			else if(dx*dx + dy*dy <= 1600) cmap[i][j] = 176;
			else cmap[i][j] = ' ';
		}
	}

	UART_transmit_string(" _____________________\n\r");
	UART_transmit_string("|Degrees|    IR| Sonar|\n\r");
	UART_transmit_string("|-------+------+------|\n\r");

	/* GATHER ANGLE, DISTANCE DATA */
	float degrees = 0;
	double ir;
	uint32_t sonar;
	int max_angle = 174;
	while(degrees < max_angle){
		ir = adc_convert(ADC_read(0));
		sonar = ping();
		static char res[50];

		sprintf(res, "|%7d| %5d| %5d|\n\r", (int)degrees,(int)ir,(int)sonar);
		data[0][data_index] = degrees;
		data[1][data_index] = ir;
		data[2][data_index++] = sonar;

		lcd_init();
		lcd_printf(res);
		UART_transmit_string(res);
		timer_waitMillis(5);
		degrees += 2;
		move_servo_absolute(degrees);
	}

	/* INTERPRET DATA FOR OBSTACLES */
	uint32_t prev_ir = 81, degree_length = 0, min_dist = 0, max_dist = 0;
	float avg_dist = 0;
	obstacle *smallest;
	int counting = 0;
	for(i = 0; i < max_angle/2 && o_index < 30; i++){
		if(counting && prev_ir < 80 && data[1][i] > 80){
			counting = 0;
			obstacles[o_index].distance = min_dist;
			obstacles[o_index].l_degrees = data[0][i];
			avg_dist /= (obstacles[o_index].l_degrees - obstacles[o_index].r_degrees)/2;
			obstacles[o_index].width = get_obj_length(obstacles[o_index].l_degrees, obstacles[o_index].r_degrees, avg_dist);
			if(obstacles[o_index].width < 5){
				continue;
			}

			double angle = (double)obstacles[o_index].r_degrees;
			double dist = (double)obstacles[o_index].distance;
			int width = obstacles[o_index].width;
			int x = cos(angle*3.1415926/180.0)*dist + 40;
			int y = 39 - sin(angle*3.1415926/180.0)*dist;
			for(i = x; i > x-width/2; i--)
				for(j = y; j > y-width/2; j--)
					if(x >= 0 && x < 81 && y >= 0 && y < 40 && cmap[x][y] != ' ') cmap[i][j] == 219;
				

			static char res[50];
			sprintf(res, "Object #%d:\n\rDist: %u\n\rWidth: %u\n\rSpan: %u - %u\n\r\n\r", o_index+1, obstacles[o_index].distance, obstacles[o_index].width , obstacles[o_index].r_degrees, obstacles[o_index].l_degrees);
			UART_transmit_string(res);

			if(o_index == 0 || obstacles[o_index].width < smallest->width){
				smallest = &obstacles[o_index];
			}

			o_index++;
			degree_length = 0;
			avg_dist = 0;
		}
		else if(!counting && data[1][i] < 80 && prev_ir > 80){
			counting = 1;
			obstacles[o_index].r_degrees = data[0][i];
			min_dist = data[2][i];
			avg_dist += data[2][i];
		}
		else if(counting){
			degree_length += 2;
			if(data[2][i] < min_dist)
				min_dist = data[2][i];
			if(data[2][i] > max_dist && data[2][i] < 80)
				max_dist = data[2][i];
			avg_dist += data[2][i];
		}
		prev_ir = data[1][i];

	}
	if(data[1][max_angle/2-1] < 80){
		obstacles[o_index].distance = min_dist;
		obstacles[o_index].l_degrees = data[0][i];
		obstacles[o_index].width = get_obj_length(obstacles[o_index].l_degrees, obstacles[o_index].r_degrees, max_dist);

		if(obstacles[o_index].width > 5){

			double angle = (double)obstacles[o_index].r_degrees;
			double dist = (double)obstacles[o_index].distance;
			int width = obstacles[o_index].width;
			int x = cos(angle*3.1415926/180.0)*dist + 40;
			int y = 39 - sin(angle*3.1415926/180.0)*dist;
			for(i = x; i > x-width/2; i--)
				for(j = y; j > y-width/2; j--)
					if(x >= 0 && x < 81 && y >= 0 && y < 40 && cmap[x][y] != ' ') cmap[i][j] == 219;


			static char res[50];
			sprintf(res, "Object #%d:\n\rDist: %u\n\rWidth: %u\n\rSpan: %u - %u\n\r\n\r", o_index+1, obstacles[o_index].distance, obstacles[o_index].width , obstacles[o_index].r_degrees, obstacles[o_index].l_degrees);
			UART_transmit_string(res);

			if(obstacles[o_index].width < smallest->width){
				smallest = &obstacles[o_index];
			}

		}
	}


	for(i = 0; i < 40; i++){
		for(j = 0; j < 81; j++){
			UART_transmit(cmap[j][i]);
		}
		UART_transmit_string("\r\n");
	}
}


