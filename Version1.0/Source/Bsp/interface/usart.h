#ifndef __USART_H
#define __USART_H

#include "stdio.h"	
#include "sys.h" 
	
#define USART_REC_LEN  			(200)
  	
extern u8  USART_RX_BUF[USART_REC_LEN];
extern u16 USART_RX_STA;         		

void uart_init(u32 bound);
void USARTDatasend(u8 *p,u8 len);
void USARTBytesend(u8 data);
void USART2Bytesend(u16 data);

#endif


