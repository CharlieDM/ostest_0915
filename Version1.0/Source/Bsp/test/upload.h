#ifndef __UPLOAD_H
#define __UPLOAD_H

#include "sys.h"

#define EE_FLAG_ADDR		(0)
#define EE_FLAG				(50)
#define EE_OS_ADDR			(1)

#define USER_HEAD			(0x40)
#define USER_QUERY_FLAG		(0x01)
#define USER_RD_RESULT		(0x02)
#define USER_WR_OFFSET		(0x03)
#define USER_RD_OFFSET		(0x04)
#define USER_CLEAR_OFFSET   (0x05)
#define USER_READ_POINT     (0x06)

void send_result(void);
void comm_process(void);
void read_param(void);

#endif
