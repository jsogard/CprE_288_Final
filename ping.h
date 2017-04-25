/*
 * ping.h
 *
 *  Created on: Mar 22, 2017
 *      Author: sogard
 */

#ifndef PING_H_
#define PING_H_

volatile enum {LOW, HIGH, DONE} state;
float ping();
void TIMER3B_Handler(void);
void send_pulse();
unsigned int ping_read();
unsigned int time2dist(unsigned int time);
//void IntRegister(int interrupt_num, void (*handler)(void));
void pulse_init();
void timer_init();

#endif /* PING_H_ */
