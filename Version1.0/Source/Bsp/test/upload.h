#ifndef __UPLOAD_H
#define __UPLOAD_H

#include "sys.h"

#define EE_FLAG_ADDR		(0)
#define EE_FLAG				(0x55)
#define EE_OS_ADDR			(1)

void send_result(void);
void comm_process(void);
void read_param(void);

#endif
