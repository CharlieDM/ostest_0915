#ifndef __TM7705_H
#define __TM7705_H

#include "sys.h"

typedef enum
{
	CHIP0 = 0,
	CHIP1
}TM7705_CHIP;

typedef enum
{
	CHANNEL0 = 0,
	CHANNEL1
}TM7705_CHAMNEL;

void tm7705_io_config(void);
void tm7705_init(TM7705_CHIP chip);		  
u16 tm7705_read_data(TM7705_CHIP chip, TM7705_CHAMNEL channel);

#endif

