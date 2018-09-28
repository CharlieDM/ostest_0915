
#include "adc.h"
#include "res.h"

u16 res_value(void)
{	
	u16 adcx;
	adcx=get_adc(ADC_T1_CHANNEL);				
	return adcx;
}

u16 res_max_value(void)
{	
	u16 adcx;
	adcx=get_adc(ADC_T2_CHANNEL);				
	return adcx;
}

