
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
    
    PWR24V_CTR(CYLINDER_1_ON, ON);
    PWR24V_CTR(CYLINDER_2_ON, ON);
    PWR24V_CTR(CYLINDER_3_ON, ON);
    PWR24V_CTR(LED_ON, ON);
    PWR24V_CTR(OUTPUT_OFF, OFF);
}
