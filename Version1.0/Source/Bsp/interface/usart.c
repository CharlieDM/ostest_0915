#include "sys.h"
#include "usart.h"	  
 	
u8 USART_RX_BUF[USART_REC_LEN];     
u16 USART_RX_STA=0;      

//初始化IO 串口1 
//bound:波特率
void uart_init(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	
 	USART_DeInit(USART1);  
	 //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
    GPIO_Init(GPIOA, &GPIO_InitStructure); 
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);  

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
  
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
    USART_Init(USART1, &USART_InitStructure); 
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE);                    
}

void USART2Bytesend(u16 data)
{
		USART_SendData(USART1,(data>>8)); 
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET); 
		USART_SendData(USART1,(data%256)); 
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET); 
}

void USARTBytesend(u8 data)
{
		USART_SendData(USART1,data);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
}


void USARTDatasend(u8 *p,u8 len)
{
	u8 t=0;
	for(t=0;t<len;t++)
	{
		USART_SendData(USART1,p[t]);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET); 
	}
}

void USART1_IRQHandler(void)                	
{
    u8 Res;
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  
    {
        Res =USART_ReceiveData(USART1);
        USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
        USART_RX_STA++;
    }
} 


