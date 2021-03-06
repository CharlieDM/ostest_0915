#include "usart.h"
#include "tim.h"
#include "io.h"
#include <stdio.h>

DataTypedef rx4_data={0};
uint8_t rx4_buf[30];

#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE
{
	int handle;
 
};
FILE __stdout;
 
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x)
{
	x = x;
}
 
//重映射fputc函数，此函数为多个输出函数的基础函数
int fputc(int ch, FILE *f)
{
	while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
	USART_SendData(UART4, (uint8_t) ch);
	return ch;
}

void uart_init(u32 bound){
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
    
	data_init(&rx4_data, rx4_buf, sizeof(rx4_buf));
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	
	//UART4_TX   GPIOC.10	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//UART4_RX	  GPIOC.11	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//Usart2 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	

	//USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	

	USART_Init(UART4, &USART_InitStructure); 
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
	USART_Cmd(UART4, ENABLE);    
	USART_ClearFlag(UART4,USART_FLAG_TC);    
 
}

void UART4_IRQHandler(void)             
{
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(UART4, USART_IT_RXNE);
		rx4_data.push(&rx4_data, USART_ReceiveData(UART4));
		timer_enable(3);
	}	
} 

void uart_puts(USART_TypeDef* USARTx, uint8_t *data, uint16_t length)
{	
	while(length--)
	{
		USART_SendData(USARTx, *data++);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) ==	RESET);
	}
}


