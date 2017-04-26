

#include "lcd.h"
#include "timer.h"
#include "adc.h"
#include <stdbool.h>
#include "driverlib/interrupt.h"
#include "button.h"
#include "servo.h"

#include "math.h"


float curr_angle;
bool clockwise = true;
uint32_t pulse_period = 0x4E200; // pulse period in cycles\

float cybot_m = 150;
float cybot_b = 8200;



void TIMER1_init()
{
	//***set GPIO PB5, turn on clk, alt. function, output, enable***
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
	GPIO_PORTB_AFSEL_R |= BIT5;
	GPIO_PORTB_DIR_R |= BIT5;
	GPIO_PORTB_DEN_R |= BIT5;
	GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB5_T1CCP1;//T1CCP1
	uint32_t mid_width = 0x19C80;
	SYSCTL_RCGCTIMER_R |= 0x2; //turn on clk for TIMER1
	TIMER1_CTL_R &= ~TIMER_CTL_TBEN; //disable timer to config

	TIMER1_TBMR_R |= 0xA; //periodic and PWM enable
	TIMER1_CFG_R |= 0x4; //set size of timer to 16
	TIMER1_TBILR_R = pulse_period & 0xFFFF; //lower 16 bits of the interval
	TIMER1_TBPR_R = (pulse_period >> 16) & 0xFF; //set the upper 8 bits of the interval
//	GPTMTAMATCHR0 = mid_width;
	TIMER1_TBMATCHR_R = mid_width; // if you want to move serv to the middle
	TIMER1_CTL_R |= TIMER_CTL_TBEN; //enable timer
	move_servo_absolute(0);
}

void move_servo_absolute(float degree)
{
	if(degree > 180)
		degree = 180;
	else if(degree < 0)
		degree = 0;
	unsigned int pulse_width = cybot_m * degree + cybot_b; // pulse width in cycles
	TIMER1_TBMATCHR_R = (pulse_period - pulse_width) & 0xFFFF;
	TIMER1_TBPMR_R = ((pulse_period - pulse_width) >> 16) & 0xFF;
	// calculate pulse width in cycles
//	TIMER1_TBMATCHR_R = period_width - pulse_width; // set pulse width
	// you need to call timer_waitMillis( ) here to enforce a delay for the servo to
	// move to the position
	timer_waitMillis(5);
	curr_angle = degree;
}

void move_servo_relative(float degree)
{
	move_servo_absolute(curr_angle + degree);
}

void configure_servo()
{
	int i;
	for(i = 0; i < 100; i += 10){
		move_servo_absolute(i);
		timer_waitMillis(500);
	}
}

