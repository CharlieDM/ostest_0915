#include "din.h"
#include "io.h"

uint8_t Din_Status(DATA_IN_STATUS din)
{
	if(din == DIN1)
		return GPIO_ReadInputDataBit(IN0_PORT, IN0_PIN);
	else if(din == DIN2)
		return GPIO_ReadInputDataBit(IN1_PORT, IN1_PIN);	
	else if(din == DIN3)
		return GPIO_ReadInputDataBit(IN2_PORT, IN2_PIN);	
	else if(din == DIN4)
		return GPIO_ReadInputDataBit(IN3_PORT, IN3_PIN);	
	else if(din == DIN5)
		return GPIO_ReadInputDataBit(IN4_PORT, IN4_PIN);	
	else if(din == DIN6)
		return GPIO_ReadInputDataBit(IN5_PORT, IN5_PIN);	
	else if(din == DIN7)
		return GPIO_ReadInputDataBit(IN6_PORT, IN6_PIN);	
	else if(din == DIN8)
		return GPIO_ReadInputDataBit(IN7_PORT, IN7_PIN);		
}

