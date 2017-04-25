//#include "move.h"
//#include "wifi.h"
//#include "sweep.h"
//
//oi_t *oi_sensor;
//
//void init_all(){
//	oi_sensor = oi_alloc();
////	oi_init(oi_sensor);
//	lcd_init();
//	UART_init();
//	WiFi_start();
//	TIMER1_init();
//	timer_init();
//	pulse_init();
//	adc_init();
//}
//
//int extract_number(char* str){
//	char *i = str;
//	int dig = 0, no = 0;
//	while(*i){
//		if(*i >= '0' && *i <= '9'){
//			dig = 1;
//			no = no * 10 + (int)(*i - '0');
//		}
//		else if(dig){
//			return no;
//		}
//
//		i++;
//	}
//	return no;
//}
//
//void print_oi_status(){
//	char str[80];
//	sprintf(str, "OI STATUS:\n\
//				  ----------\n\
//				  Position: (%+4d, %+4d)\n\
//				  Angle: %3d\n", (int)abs_position_x, (int)abs_position_y, abs_angle);
//	UART_transmit_string(str);
//}
//
//void interpret(char* command){
//	int amt = extract_number(command);
//	char msg[30];
//	switch(command[0]){
//		case 'w':
//			move(oi_sensor, amt);
//			sprintf(msg,
//				"Moving forward %dcm.\n", amt);
//			break;
//		case 'a':
//			turn(oi_sensor, amt);
//			sprintf(msg,
//				"Turning left %dd.\n", amt);
//			break;
//		case 'd':
//			turn(oi_sensor, -1*amt);
//			sprintf(msg,
//				"Turning right %dd.\n", amt);
//			break;
//		case 's':
//			if(command[1] == ' '){
//				move(oi_sensor, -1*amt);
//				sprintf(msg,
//					"Moving backward %dcm.\n", amt);
//			}
//			else if(strncmp(command, "scan", 4) == 0){
//				get_objects_sweep();
//				sprintf(msg,
//					"Room scanned.\n");
//			}
//			break;
//		default:
//			sprintf(msg,
//				"Invalid command.\n");
//	}
//	UART_transmit_string(msg);
//	print_oi_status();
//}
//
//
//
//int main(){
//	init_all();
//
//	while(1){
//		interpret(UART_receive());
//	}
//
//	return 0;
//}
