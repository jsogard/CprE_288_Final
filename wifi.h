/*
 * wifi.h
 *
 *  Created on: Mar 22, 2017
 *      Author: sogard
 */

#ifndef WIFI_H_
#define WIFI_H_


void UART_init();
void UART_transmit(char sdata);
char UART_receive();
void UART_transmit_string(char* str);
void UART_handle_button(int button);
void WiFi_start();
void WiFi_stop();



#endif /* WIFI_H_ */
