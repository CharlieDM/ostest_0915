#ifndef __OSTEST_H
#define __OSTEST_H

#include "sys.h"

#define PANEL_2_LEN              	(2)
#define CHAIN_50_LEN               	(50)
#define CONNECT_10_LEN              (10)
#define CONNECT_30_LEN              (30)
#define PAD_40_LEN               	(44)

#define TOTAL_POINT                 (86)
#define THRESHOLD_SHORT             (1000)
#define THRESHOLD_OPEN              (10)
#define THRESHOLD_PANEL             (5)

#define TEST_TIMES                  3

typedef struct _oschain_t
{
    u8 len;
    u8 point[TOTAL_POINT];
}OsChain_t;

extern OsChain_t painchain[PANEL_2_LEN];
extern OsChain_t open_40_chain[CHAIN_50_LEN];


u8 wait_start_sign(void);
void start_test(void);
u8 find_point(u8 *data);


#endif
