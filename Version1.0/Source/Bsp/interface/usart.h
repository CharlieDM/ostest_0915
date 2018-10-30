#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
#include "queue.h"

#define Msg_Length		4
extern	 DataTypedef rx4_data;

void uart_puts(USART_TypeDef* USARTx, uint8_t *data, uint16_t length);
void uart_init(u32 bound);

#endif
