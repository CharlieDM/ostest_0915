#ifndef __74HC595_H
#define __74HC595_H
#include "stdint.h"

#define PIN_OFF			1
#define PIN_ON			0
#define PIN_ALL_OFF		0

typedef enum
{
	NONE_IC = 0,
	SW1_A,		//���ذ�1TEST+
	SW1_B,		//���ذ�1TEST-
	SW2_A,		//���ذ�2TEST+
	SW2_B,		//���ذ�2TEST-
	SW3_A,		//���ذ�3TEST+
	SW3_B,		//���ذ�3TEST-
	SW4_A,		//���ذ�4TEST+
	SW4_B,		//���ذ�4TEST-
	PWR_OUT,	//24V���
	SW_OTHER	//�����ϵĸ����
} HC595_TYPE;
	
void hc595_init(void);
void HC595SendData(HC595_TYPE type, uint16_t Data);

#endif
