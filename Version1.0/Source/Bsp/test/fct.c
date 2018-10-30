
#include "bsp.h"
#include "data.h"
#include "fct.h" 

#define RES_100R		100
#define RES_1M			1000000

uint16_t fct_get_data(FCT_ADC_TYPE ftype)
{
	uint16_t adcx=0,res=0;
	float v=0;
	switch(ftype)
	{
		case FCT_ADC1_IN:
			
			break;

		case FCT_ADC2_IN:
			adcx = get_adc(ftype);
			v = adcx*ADC_VREF/ADC_RESOL;
			res = RES_1M*v/(ADC_VREF-v);
			break;

		case FCT_ADC3_IN:
			adcx = get_adc(ftype);
			v = adcx*ADC_VREF/ADC_RESOL; 
			if(v >= 3200) res = 0xFFFF;
			else if(v < 3200) res = RES_100R*v/(ADC_VREF-v);
			break;

		case FCT_ADC4_IN:
			break;
	}
	return res;
}

