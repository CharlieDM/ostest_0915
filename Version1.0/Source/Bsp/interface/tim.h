#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

extern uint8_t Rec_OK_USART2;
void TIM_Int_Init(void);
void timer_enable(uint8_t timer);
void timer_disable(uint8_t timer);
#endif
