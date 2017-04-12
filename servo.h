/*
 * servo.h
 *
 *  Created on: Mar 22, 2017
 *      Author: sogard
 */

#ifndef SERVO_H_
#define SERVO_H_


void TIMER1_init();
void move_servo_absolute(float degree);
void move_servo_relative(float degree);

void servo_move_relative(float degree);
void move_servo_absolute(float degree);

void configure_servo(void);


#endif /* SERVO_H_ */
