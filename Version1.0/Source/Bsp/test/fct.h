#ifndef __FCT_H
#define __FCT_H

#include "sys.h"
#include "adc.h"

typedef enum
{
    FCT_ADC1_IN = ADC_Channel_13,
    FCT_ADC2_IN = ADC_Channel_12,
    FCT_ADC3_IN = ADC_Channel_11,
    FCT_ADC4_IN = ADC_Channel_10,
}FCT_ADC_TYPE;


uint16_t fct_get_data(FCT_ADC_TYPE ftype);

#endif
