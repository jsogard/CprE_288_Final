/*
 * adc.h
 *
 *  Created on: Mar 22, 2017
 *      Author: sogard
 */

#ifndef ADC_H_
#define ADC_H_


void adc_init();
uint32_t ADC_read(char channel);
double adc_convert(uint32_t input);


#endif /* ADC_H_ */
