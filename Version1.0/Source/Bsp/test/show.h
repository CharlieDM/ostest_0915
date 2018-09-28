#ifndef __SHOW_H
#define __SHOW_H

#include "sys.h"

#define ERR_PROXIMITY_SWITCH		(0x1001)

void show_init(void);
void show_test(void);
void show_main(void);
void show_result(void);
void show_error(u16 type);
void show_pass(void);
void show_fail(void);
void show_test_times(void);
void show_page(u8 page);
void show_find_point(void);

#endif
