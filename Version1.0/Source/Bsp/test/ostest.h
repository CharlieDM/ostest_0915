#ifndef __OSTEST_H
#define __OSTEST_H

#include "sys.h"

#define SHORTCHAIN_LEN              (5)
#define OPENCHAIN_LEN               (40)
#define PANELCHAIN_LEN              (2)
#define TOTAL_POINT                 (86)
#define THRESHOLD_SHORT             (1000000)
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
