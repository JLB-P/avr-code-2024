/*
 * adc.h
 *
 * Created: 5/5/2024 9:42:15 PM
 * Author: jlb
 */ 


#ifndef ADC_H_
#define ADC_H_
#include <avr/io.h>

void adc_init();
uint16_t read_adc(uint8_t ch);

#endif /* ADC_H_ */