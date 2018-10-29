#ifndef __BSP_H
#define __BSP_H	 

#include "adc.h"
#include "sys.h"
#include "io.h"
#include "delay.h"
#include "iic.h"
#include "show.h"
#include "tpswitch.h"
#include "lcd12864.h"
#include "74HC595.h"
#include "din.h"
#include "pwrctr.h"
#include "tm7705.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "fct.h"
#include "upload.h"
#include "24cxx.h" 

#define KEY_START				DIN1
#define KEY_MENU				DIN2
#define KEY_PLACE1				DIN3
#define KEY_PLACE2				DIN4

#define KEY_START_SHORT			0x10
#define KEY_PLACE1_SHORT		0x20
#define KEY_MENU_SHORT			0x30
#define KEY_MENU_LONG			0x31

#define LED_PASS_ON				OUTPUT8_ON
#define LED_PASS_OFF			OUTPUT8_OFF
#define LED_FAIL_ON				OUTPUT7_ON
#define LED_FAIL_OFF			OUTPUT7_OFF
#define CYLINDER_1_ON			OUTPUT6_ON
#define CYLINDER_1_OFF			OUTPUT6_OFF
#define CYLINDER_2_ON			OUTPUT5_ON
#define CYLINDER_2_OFF			OUTPUT5_OFF
#define CYLINDER_3_ON			OUTPUT4_ON
#define CYLINDER_3_OFF			OUTPUT4_OFF

/*
    input：启动，翻页，大气缸上，大气缸下，光栅 1,2,3,4,5
    output: 绿灯，红灯，大气缸，小气缸，真空吸  8,7,6,5,4
*/

void bsp_init(void);
	 
#endif
