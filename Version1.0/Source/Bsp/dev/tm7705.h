#ifndef __TM7705_H
#define __TM7705_H

#include "sys.h"

typedef enum
{
	TM7705_CHIP0 =0,
	TM7705_CHIP1
}TM7705_CHIP;

typedef enum
{
	TM7705_CHANNEL0 =0,
	TM7705_CHANNEL1
}TM7705_CHAMNEL;

void tm7705_io_config(void);
void tm7705_init(u8 chip);		  
u16 tm7705_read_data(u8 chip, u8 channel);

#endif

