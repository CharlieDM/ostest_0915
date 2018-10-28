#ifndef __OSTEST_H
#define __OSTEST_H

#include "sys.h"

#define PANEL_2_LEN              	(2)
#define CHAIN_40_LEN               	(40)
#define CONNECT_10_LEN              (10)
#define CONNECT_30_LEN              (30)
#define PAD_40_LEN               	(40)

#define TOTAL_POINT                 (86)
#define THRESHOLD_SHORT             (1000)
#define THRESHOLD_OPEN              (10)
#define THRESHOLD_PANEL             (5)

typedef struct _oschain_t
{
    u8 len;
    u8 point[TOTAL_POINT];
}OsChain_t;

u8 wait_start_sign(void);
void start_test(void);
u8 find_point(u8 *data);


#endif
