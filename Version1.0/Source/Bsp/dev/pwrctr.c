#include "pwrctr.h"
#include "74HC595.h"
#include "gpio.h"

#define	SW_1D8V			SW_1D8V_PORT, SW_1D8V_PIN
#define SW_3D3V			SW_3D3V_PORT, SW_3D3V_PIN
#define SW_5V			SW_5V_PORT, SW_5V_PIN 

uint8_t PWR_OUT_Status = 0;

void PWR24V_CTR(uint8_t output)
{
	PWR_OUT_Status &= output;
	HC595SendData(PWR_OUT, PWR_OUT_Status);
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




