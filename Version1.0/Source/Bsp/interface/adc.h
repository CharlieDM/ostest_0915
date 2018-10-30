#ifndef __ADC_H
#define __ADC_H	

#include "sys.h"
#include "stm32f10x_adc.h"

#define ADC_T1_CHANNEL        (ADC_Channel_12)
#define ADC_T2_CHANNEL        (ADC_Channel_13)

#define	ADC_VREF			(3300.0)
#define ADC_RESOL			(4096)

void adc_init(void);				 
u16  get_adc(u8 ch); 				  
u16  get_adc_avg(u8 ch,u8 times); 

#endif 
