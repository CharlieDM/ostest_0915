#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

extern uint8_t rx4_rec_OK;

void TIM_Int_Init(void);
void timer_enable(uint8_t timer);
void timer_disable(uint8_t timer);

#endif

