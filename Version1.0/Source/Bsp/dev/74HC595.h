#ifndef __74HC595_H
#define __74HC595_H
#include "stdint.h"

#define PIN_OFF			1
#define PIN_ON			0
#define PIN_ALL_OFF		0

typedef enum
{
	NONE_IC = 0,
	SW1_A,		//开关板1TEST+
	SW1_B,		//开关板1TEST-
	SW2_A,		//开关板2TEST+
	SW2_B,		//开关板2TEST-
	SW3_A,		//开关板3TEST+
	SW3_B,		//开关板3TEST-
	SW4_A,		//开关板4TEST+
	SW4_B,		//开关板4TEST-
	PWR_OUT,	//24V输出
	SW_OTHER	//主板上的隔离点
} HC595_TYPE;
	
void hc595_init(void);
void HC595SendData(HC595_TYPE type, uint16_t Data);

#endif
