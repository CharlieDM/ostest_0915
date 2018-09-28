#ifndef __TPSWITCH_H
#define __TPSWITCH_H
#include "sys.h"

typedef struct _switch_t
{
  GPIO_TypeDef* GPIOx; 
  uint16_t GPIO_Pin;
}Switch_t;

void tp_switch_init(void);				
void tp1_switch(u16 tp1);
void tp2_switch(u16 tp2);
void tp_switch_off(void);
void show_find_point(void);


#endif

