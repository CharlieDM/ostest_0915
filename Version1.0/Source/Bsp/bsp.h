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

#define KEY_MENU				DIN1
#define KEY_START				DIN2
#define KEY_PLACE1				DIN3
#define KEY_PLACE2				DIN4

#define KEY_START_SHORT			0x10
#define KEY_PLACE1_SHORT		0x20
#define KEY_MENU_SHORT			0x30
#define KEY_MENU_LONG			0x31

#define CYLINDER_1_ON			OUTPUT1_ON
#define CYLINDER_1_OFF			OUTPUT1_OFF
#define CYLINDER_2_ON			OUTPUT2_ON
#define CYLINDER_2_OFF			OUTPUT2_OFF
#define CYLINDER_3_ON			OUTPUT3_ON
#define CYLINDER_3_OFF			OUTPUT3_OFF
#define LED_ON					OUTPUT4_ON
#define LED_OFF					OUTPUT4_OFF

void bsp_init(void);
	 
#endif
