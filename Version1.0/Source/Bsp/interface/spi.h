#ifndef __SPI_H
#define __SPI_H

#include "sys.h"
 				  	    													  
void spi3_init(void);			  
u8 spi3_read_byte(void);
void spi3_write_byte(u8 data);
		 
#endif

