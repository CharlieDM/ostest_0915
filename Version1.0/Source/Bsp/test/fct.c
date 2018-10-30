
#include "bsp.h"
#include "data.h"
#include "fct.h" 

#define RES_100R		100
#define RES_999R		999
#define RES_1M			1000
#define RES_20M			20000

uint16_t fct_get_data(FCT_ADC_TYPE ftype)
{
	uint16_t adcx=0,res=0;
    uint32_t restmp=0;
	switch(ftype)
	{
		case FCT_ADC1_IN:
			
			break;

		case FCT_ADC2_IN:
			adcx = get_adc(ftype);
			restmp = RES_1M*adcx/(ADC_RESOL-adcx);
            if(restmp>RES_20M) res = RES_20M;
			break;

		case FCT_ADC3_IN:
			adcx = get_adc(ftype);
            restmp = (RES_100R*adcx)/(ADC_RESOL - adcx) - RES_100R;
            if(restmp>RES_999R) res = RES_999R;
			break;

		case FCT_ADC4_IN:
			break;
	}
	return res;
}

