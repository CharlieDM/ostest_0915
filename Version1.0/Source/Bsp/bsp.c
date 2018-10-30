
#include "bsp.h"

u16 res = 0;
void bsp_init(void) 
{ 
 	delay_init();
    NVIC_Configuration();
    io_init();
    iic_init();
    adc_init();
    hc595_init();    
    spi3_init();
    tm7705_io_config();
    tm7705_init(CHIP0);
    TIM_Int_Init();
    uart_init(115200);
    lcd12864_init();     
    PWR24V_CTR(OUTPUT_OFF, OFF);
    fct_swtich(FCT_OFF); 
    isolate_switch(ISOLATE_OFF); 
    read_param(); 
    
//    fct_swtich(FCT_4W_EN5);
//    
//    switch_testpoint(TPA,1);
//    switch_testpoint(TPB,5);
//    
//    while(1)
//    {

//        data1 = tm7705_read_data(CHIP0,CHANNEL0);
//        delay_ms(100);
//        data2 = tm7705_read_data(CHIP0,CHANNEL1);
//        delay_ms(100);
//    }
//    fct_swtich(FCT_100R_EN3);
//    
//    switch_testpoint(TPA,1);
//    switch_testpoint(TPB,5);
//    
//    while(1)
//    {
//        res = fct_get_data(FCT_ADC3_IN);
//        delay_ms(100);
//    }

}
