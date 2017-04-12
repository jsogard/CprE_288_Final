

#include "lcd.h"
#include "timer.h"
#include "button.h"
#include "wifi.h"

//int main(){
//	lcd_init();
//	UART_init();
//	button_init();
//	uint8_t num = 0;
//	char s_data, chr[21];
//	chr[20] = '\0';
//	uint8_t prev = -1, button;
//
//	WiFi_start();
//	while(1){
//
//
//		button = button_getButton();
//		if(prev != button){
//			UART_handle_button(button);
//			//timer_waitMillis(100);
//			prev = button;
//		}
//		WiFi_stop();
//
//
//		/* PART 2
//		s_data = UART_receive();
//		lcd_putc(s_data);
//		UART_transmit(s_data);
//		 */
//
//		/*	PART 1
//		while(((s_data = UART_receive()) != '\r') && num < 20){
//			chr[num] = s_data;
//			//lcd_putc(chr[num]);
//			num++;
//		}
//		chr[num] = 0;
//		lcd_init();
//		lcd_puts(chr);
//		num = 0;
//	*/
//	}
//}

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

void UART_handle_button(int button){
	if(button == 0)
		return;

	char* str;

	switch(button){
	case 6:
		str = "Yes";
		break;
	case 5:
		str = "No";
		break;
	case 4:
		str =  "Blue, no green, Ahhhhh!!!";
		break;
	case 3:
		str = "This is button 3";
		break;
	case 2:
		str = "2 two ";
		break;
	case 1:
		str = "number 1";
		break;
	}

	UART_transmit_string(str);

}

void UART_transmit_string(char* str){
	//lcd_init();
	while(UART1_FR_R & 0x20);

	while(*str != 0){
		UART1_DR_R = *str;
		str++;
		timer_waitMillis(1);
	}
}

void UART_transmit(char sdata){

	while(UART1_FR_R & 0x20);

	if(sdata == '\r'){
		UART1_DR_R = '\n';
		UART1_DR_R = '\r';
		return;
	}

	UART1_DR_R = sdata;
}

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

void WiFi_start(){
	GPIO_PORTB_DATA_R |= 0x4; //Enter command mode

	int WIFI_START_COMMAND = 0;
	char* WIFI_PSK = "easilyTheWorstp@sswd";
	// all under is pseudo and wrong
//	uart_sendChar(WIFI_START_COMMAND); //Send command
	UART_transmit(WIFI_START_COMMAND); //Send command

	UART_transmit_string(WIFI_PSK); //Send WiFi PSK

	UART_transmit(0x00); //NULL terminator

	int response = UART_receive(); //Wait for response

//	commandPin = 0; //Leave command mode
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





