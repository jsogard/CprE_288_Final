#include "math.h"
#include <inc/tm4c123gh6pm.h>
#include "lcd.h"
#include "timer.h"
#include "button.h"
#include "adc.h"



//
//int main(){
//	adc_init();
//	lcd_init();
//
//	uint32_t input;
//	double distance;
//	while(1){
//		//TODO: Do average of 5 inputs
//		input = ADC_read(0);
//		distance = adc_convert(input);
//		timer_waitMillis(1000);
//		lcd_printf("%d Value \n %02lf Distance cm", input, distance);
//
//	}
//}

void adc_init(){
	//enable ADC 0 module on port D
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
	//enable clock for ADC
	SYSCTL_RCGCADC_R |= 0x1;
	//enable port D pin 0 to work as alternate functions
	GPIO_PORTB_AFSEL_R |= 0x01;
	//set pin to input - 0
	GPIO_PORTB_DEN_R &= 0b11111110;
	//disable analog isolation for the pin
	GPIO_PORTB_AMSEL_R |= 0x01;
	//initialize the port trigger source as processor (default)
	GPIO_PORTB_ADCCTL_R = 0x00;
	//disable SS0 sample sequencer to configure it
	ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN0;
	//initialize the ADC trigger source as processor (default)
	ADC0_EMUX_R = ADC_EMUX_EM0_PROCESSOR;
	//set 1st sample to use the AIN10 ADC pin
	ADC0_SSMUX0_R |= 0x000A;
	//enable raw interrupt
	ADC0_SSCTL0_R |= (ADC_SSCTL0_IE0 | ADC_SSCTL0_END0);
	//enable oversampling to average
	ADC0_SAC_R |= ADC_SAC_AVG_64X;
	//re-enable ADC0 SS0
	ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;

}

uint32_t ADC_read(char channel){ // channel 0
	//disable ADC0SS0 sample sequencer to configure it
	ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN0;
	//set 1st sample to use the channel ADC pin
	ADC0_SSMUX0_R |= channel;
	//re-enable ADC0 SS0
	ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;
	//initiate SS0 conversion
	ADC0_PSSI_R=ADC_PSSI_SS0;
	//wait for ADC conversion to be complete
	while((ADC0_RIS_R & ADC_RIS_INR0) == 0){}
	//clear interrupt
	ADC0_ISC_R=ADC_ISC_IN0;
	return ADC0_SSFIFO0_R;
}

double adc_convert(uint32_t input){
	return 94654 * pow((double)input, -1.155);
}


