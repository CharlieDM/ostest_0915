
#include "bsp.h"


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
    
//    while(1)
//    {
//        uart_puts(UART4,&data,1);
//        delay_ms(1000);
//    }
    
    
//    PWR24V_CTR(CYLINDER_3_ON, ON);
//    delay_ms(200);
//    PWR24V_CTR(CYLINDER_1_ON, ON); 
//    delay_ms(200);
//    PWR24V_CTR(CYLINDER_2_ON, ON); 
//    PWR24V_CTR(CYLINDER_3_OFF, OFF);
//    
//    fct_swtich(FCT_100R_EN3);
//    switch_testpoint(TPA,85);
//    switch_testpoint(TPB,66);
//    
//    data1 =  fct_get_data(FCT_ADC3_IN);
        
//    isolate_switch(ISOLATE_1);
//    isolate_switch(ISOLATE_2);
//    
//    SW_3D3V_Out(PWR_1D8V_ON);
//    fct_swtich(FCT_4W_EN5);
    
    
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
