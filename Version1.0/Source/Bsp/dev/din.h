#ifndef __DIN_H
#define __DIN_H
#include "sys.h"

typedef enum
{
	DIN1 = 0,
	DIN2,		
	DIN3,		
	DIN4,			
	DIN5,		
	DIN6,		
	DIN7,			
	DIN8,				
} DATA_IN_STATUS;

uint8_t Din_Status(DATA_IN_STATUS din);
#endif
