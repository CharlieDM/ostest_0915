
#include "bsp.h"

void bsp_init(void) 
{ 
 	delay_init();
    NVIC_Configuration();
    io_init();
    iic_init();
    adc_init();
    hc595_init();
	lcd12864_init(); 
}
