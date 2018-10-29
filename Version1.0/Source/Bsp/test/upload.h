#ifndef __UPLOAD_H
#define __UPLOAD_H

#include "sys.h"

#define EEPROM_FLAG_ADDR		(4095)
#define EEPROM_FLAG				(0x55)
#define EEPROM_OS_ADDR			(0)

void send_result(void);
void comm_process(void);

#endif
