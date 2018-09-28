#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

/* Key1 ~ Key4 : PE13-PE15,PB10 */ 
#define KEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_13)
#define KEY2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_14)
#define KEY3  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_15) 
#define KEY4  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10) 

/* 24IN1 ~ 24IN8: PD13,PD14,PD15,PC6,PC7,PC8,PC9,PA8 */
#define V24In1  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13)
#define V24In2  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_14)
#define V24In3  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15) 
#define V24In4  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)
#define V24In5  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)
#define V24In6  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)
#define V24In7  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9) 
#define V24In8  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)

/* 24EN1 ~ 24EN8: PB1,PB2,PE7,PE8,PE9,PE10,PE11,PE12 */
#define V24EN1  PBout(1)
#define V24EN2  PBout(2)
#define V24EN3  PEout(7)
#define V24EN4  PEout(8)        /* V24EN4 error always 24v*/
#define V24EN5  PEout(9)
#define V24EN6  PEout(10)
#define V24EN7  PEout(11)
#define V24EN8  PEout(12)

/* TEST_EN1 ~ TEST_EN4: PC15,PA0,PA1,PA2 */
#define TEST_EN1  PCout(15)
#define TEST_EN2  PAout(0)
#define TEST_EN3  PAout(1)
#define TEST_EN4  PAout(2)

#define KEY_START				V24In1
#define KEY_PLACE1				V24In2
#define KEY_PLACE2				V24In3
#define KEY_MENU				V24In4

#define KEY_START_SHORT			0x10
#define KEY_PLACE1_SHORT		0x20
#define KEY_MENU_SHORT			0x30
#define KEY_MENU_LONG			0x31

#define OUTPUT_1				V24EN1
#define OUTPUT_2				V24EN2
#define OUTPUT_3				V24EN2

void io_init(void);	 
	 
#endif
