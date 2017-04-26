

#include "lcd.h"
#include "timer.h"
#include "button.h"
#include "wifi.h"

/**
* void UART_init() Initializes all of the correct registers and ports for using wifi.
*/
void UART_init(){
	//enable clock to GPIO, R1 = port B
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;

	//enable clock to UART1, R1 = UART1. ***Must be done before setting Rx and Tx (SeeDataSheet)
	SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1;

	//enable alternate functions on port b pins 0 and 1
	GPIO_PORTB_AFSEL_R |= (BIT0 | BIT1);

	//enable Rx and Tx on port B on pins 0 and 1
	GPIO_PORTB_PCTL_R |= 0x00000011;

	//set pin 0 and 1 to digital
	//TODO: READ THIS We had to add BIT2 fo wifi
	GPIO_PORTB_DEN_R |= (BIT0 | BIT2|BIT1);

	//set pin 0 to Rx or input
	GPIO_PORTB_DIR_R &= ~BIT0;

	//set pin 1 to Tx or output
	//TODO: READ THIS We had to add BIT2 fo wifi
	GPIO_PORTB_DIR_R |= BIT1 | BIT2;


	//calculate baudrate
	uint16_t iBRD = 8 ;//use equations
	uint16_t fBRD = 44;//use equations

	//turn off uart1 while we set it up
	UART1_CTL_R &= ~(UART_CTL_UARTEN);

	//set baud rate
	UART1_IBRD_R = iBRD;
	UART1_FBRD_R = fBRD;

	//set frame, 8 data bits, 1 stop bit, no parity, no FIFO
	UART1_LCRH_R = UART_LCRH_WLEN_8 ;

	//use system clock as source
	UART1_CC_R = UART_CC_CS_SYSCLK;

	//re-enable enable RX, TX, and uart1
	UART1_CTL_R = (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);

}

/**
* void UART_transmit_string(char* str) sends the inputted character array to the computer over wifi.
* @param sdata The character array to send.
*/
void UART_transmit_string(char* str){
	//lcd_init();
	while(UART1_FR_R & 0x20);

	while(*str != 0){
		UART1_DR_R = *str;
		str++;
		timer_waitMillis(1);
	}
}

/**
* void UART_transmit(char sdata) sends the inputted character to the computer over wifi.
* @param sdata The character to send.
*/
void UART_transmit(char sdata){

	while(UART1_FR_R & 0x20);

	if(sdata == '\r'){
		UART1_DR_R = '\n';
		UART1_DR_R = '\r';
		return;
	}

	UART1_DR_R = sdata;
}

/**
* char UART_receive() waits to receive data over wifi, then returns that data.
* @return char data received over wifi
*/
char UART_receive(){
	char data = 0;

	while(UART1_FR_R & UART_FR_RXFE);

	data = (char)(UART1_DR_R & 0xFF);

	return data;
}

void wifi_init(){
	GPIO_PORTB_DEN_R |= 0x4;
	//direction

}

/**
* void WiFi_start() Starts the wifi service on the robot, allowing the computer to connect. 
*/
void WiFi_start(){
	GPIO_PORTB_DATA_R |= 0x4; //Enter command mode

	int WIFI_START_COMMAND = 0;
	char* WIFI_PSK = "12345678";
	
	UART_transmit(WIFI_START_COMMAND); //Send command

	UART_transmit_string(WIFI_PSK); //Send WiFi PSK

	UART_transmit(0x00); //NULL terminator

	int response = UART_receive(); //Wait for response

	GPIO_PORTB_DATA_R &= 0b11111011;

	if(response != 0) {
	//An error occurred…
		lcd_puts("Something went wrong!");
	}
}

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

 /**
 * void WiFi_stop() stops the wifi service.
 */
void WiFi_stop(){
	GPIO_PORTB_DATA_R |= 0x4; //Enter command mode//Enter command mode

	int WIFI_STOP_COMMAND = 1;

	UART_transmit(WIFI_STOP_COMMAND); //Send command

	int response = UART_receive(); //Wait for response

	GPIO_PORTB_DATA_R &= 0b11111011;//Leave command mode

	if(response != 0) {
	//An error occurred…
	}
}





