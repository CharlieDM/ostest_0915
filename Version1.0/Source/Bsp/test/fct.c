
#include "bsp.h"
#include "data.h"
#include "fct.h" 

uint16_t fct_get_data(FCT_ADC_TYPE ftype)
{
    return get_adc(ftype);
}
