/*
 * adc.h
 *
 * Created: 
 *  Author: jlb
 */ 


#ifndef adc_H_
#define adc_H_
void init_adc_withINT(void);
void init_adc_withoutINT(void);
uint16_t read_adc(void);
#endif /* adc_H_ */