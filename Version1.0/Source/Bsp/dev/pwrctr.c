#include "pwrctr.h"
#include "74HC595.h"
#include "io.h"

#define	SW_1D8V			SW_1D8V_PORT, SW_1D8V_PIN
#define SW_3D3V			SW_3D3V_PORT, SW_3D3V_PIN
#define SW_5V			SW_5V_PORT, SW_5V_PIN 

#define	FCT_EN1			TEST_EN1_PORT, TEST_EN1_PIN
#define FCT_EN2			TEST_EN2_PORT, TEST_EN2_PIN
#define FCT_EN3			TEST_EN3_PORT, TEST_EN3_PIN
#define FCT_EN4			TEST_EN4_PORT, TEST_EN4_PIN
#define FCT_EN5			AD_EN_PORT, AD_EN_PIN


void PWR24V_CTR(uint8_t output, uint8_t state)
{
    static uint8_t PWR_OUT_Status = 0;
    if(state == ON)
        PWR_OUT_Status |= output;
    else
        PWR_OUT_Status &= output;
	HC595SendData(PWR_OUT, PWR_OUT_Status);
}

void isolate_switch(uint8_t point)
{
    HC595SendData(SW_OTHER, point);
}

void SW_3D3V_Out(SW_PWROUT_TYPE PWRout)
{
	if(PWRout == PWR_1D8V_ON)		GPIO_SetBits(SW_1D8V);		
	else if(PWRout == PWR_1D8V_OFF)	GPIO_ResetBits(SW_1D8V);		
	else if(PWRout == PWR_3D3V_ON)	GPIO_SetBits(SW_3D3V);		
	else if(PWRout == PWR_3D3V_OFF)	GPIO_ResetBits(SW_3D3V);			
	else if(PWRout == PWR_5V_ON)	GPIO_SetBits(SW_5V);		
	else if(PWRout == PWR_5V_OFF)	GPIO_ResetBits(SW_5V);		
	else if(PWRout == NONE_PWR)
	{
		GPIO_ResetBits(SW_1D8V);
		GPIO_ResetBits(SW_3D3V);
		GPIO_ResetBits(SW_5V);		
	}
}

void fct_swtich(FCT_EN_TYPE ftype)
{
    if(ftype == FCT_100R_EN1)		
        {GPIO_SetBits(FCT_EN1);	GPIO_ResetBits(FCT_EN2); GPIO_ResetBits(FCT_EN3); GPIO_ResetBits(FCT_EN4); GPIO_ResetBits(FCT_EN5);}
	else if(ftype == FCT_1M_EN2)	
        {GPIO_SetBits(FCT_EN2); GPIO_ResetBits(FCT_EN1); GPIO_ResetBits(FCT_EN3); GPIO_ResetBits(FCT_EN4); GPIO_ResetBits(FCT_EN5);}	
	else if(ftype == FCT_100R_EN3)	
        {GPIO_SetBits(FCT_EN3);	GPIO_ResetBits(FCT_EN1); GPIO_ResetBits(FCT_EN2); GPIO_ResetBits(FCT_EN4); GPIO_ResetBits(FCT_EN5);}
	else if(ftype == FCT_100R_EN4)	
        {GPIO_SetBits(FCT_EN4); GPIO_ResetBits(FCT_EN1); GPIO_ResetBits(FCT_EN2); GPIO_ResetBits(FCT_EN3); GPIO_ResetBits(FCT_EN5);}	        
    else if(ftype == FCT_4W_EN5)	
        {GPIO_SetBits(FCT_EN5); GPIO_ResetBits(FCT_EN1); GPIO_ResetBits(FCT_EN2); GPIO_ResetBits(FCT_EN3); GPIO_ResetBits(FCT_EN4);}	
    else if(ftype == FCT_OFF)	    
        { GPIO_ResetBits(FCT_EN1); GPIO_ResetBits(FCT_EN2); GPIO_ResetBits(FCT_EN3);GPIO_ResetBits(FCT_EN4); GPIO_ResetBits(FCT_EN5);}  
}



