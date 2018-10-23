#ifndef __PWRCTR_H
#define __PWRCTR_H
#include "sys.h"

#define OUTPUT_OFF		0x00
#define OUTPUT1_ON		0x01
#define OUTPUT2_ON		0x02
#define OUTPUT3_ON		0x04
#define OUTPUT4_ON		0x08
#define OUTPUT5_ON		0x10
#define OUTPUT6_ON		0x20
#define OUTPUT7_ON		0x40
#define OUTPUT8_ON		0x80
#define OUTPUT1_OFF		(~OUTPUT1_ON)
#define OUTPUT2_OFF		(~OUTPUT2_ON)
#define OUTPUT3_OFF		(~OUTPUT3_ON)
#define OUTPUT4_OFF		(~OUTPUT4_ON)
#define OUTPUT5_OFF		(~OUTPUT5_ON)
#define OUTPUT6_OFF		(~OUTPUT6_ON)
#define OUTPUT7_OFF		(~OUTPUT7_ON)
#define OUTPUT8_OFF		(~OUTPUT8_ON)

typedef enum
{
	NONE_PWR = 0,
	PWR_1D8V_ON,		//可控1.8V输出
	PWR_3D3V_ON,		//可控3.3V输出
	PWR_5V_ON,			//可控5V输出
	PWR_1D8V_OFF,		//可控1.8V输出关闭
	PWR_3D3V_OFF,		//可控3.3V输出关闭
	PWR_5V_OFF,			//可控5V输出关闭
} SW_PWROUT_TYPE;

void SW_3D3V_Out(SW_PWROUT_TYPE PWRout);
void PWR24V_CTR(uint8_t output);

#endif
