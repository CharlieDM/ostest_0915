#include "tim.h"
#include "usart.h"

uint8_t rx4_rec_OK = 0;

void TIM_Int_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 

	TIM_TimeBaseStructure.TIM_Period = 500-1; 
	TIM_TimeBaseStructure.TIM_Prescaler =7200-1; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);  
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);                 
}

void TIM3_IRQHandler(void)   
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		timer_disable(3);
		rx4_rec_OK= 1;	
	}
}

void timer_enable(uint8_t timer)
{
	if(2 == timer)
	{
		TIM2->CNT = 0;
		TIM2->CR1 |= TIM_CR1_CEN;
	}
	if(3 == timer)
	{
		TIM3->CNT = 0;
		TIM3->CR1 |= TIM_CR1_CEN;
	}
}

void timer_disable(uint8_t timer)
{
	if(2 == timer)
	{
		TIM2->CNT = 0;
		TIM2->CR1 &= ~TIM_CR1_CEN;
	}
	if(3 == timer)
	{
		TIM3->CNT = 0;
		TIM3->CR1 &= ~TIM_CR1_CEN;
	}
}

