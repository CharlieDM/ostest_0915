#ifndef __DATA_H
#define __DATA_H	 
#include "sys.h"

#define PASS_STR        (u8*)"Pass"
#define FAIL_STR        (u8*)"Fail"

#define TEST_POINT_NUMBER			(86)
#define COMPENSATE_NUM              (42)

#define PASS			(0)
#define FAIL			(1)

typedef enum 
{
    WAIT_START = 0,
    ON_TEST,
}eSysState;

typedef struct  _item_result_t
{
	u16 no;
	u8 result;
	u8 tp1;
	u8 tp2;
	u16 data;
}Item_result_t;

typedef struct _test_result_t
{
	u16 times;
	u8 all_result;
	u8 complete_flag;
	
}Test_result_t;

typedef struct  _compensate_t
{
	s16 open_offset[COMPENSATE_NUM];
    s16 short_offset;
}Compensate_t;

extern Item_result_t item_result[1000];
extern Test_result_t test_result;
extern Compensate_t compensate;

#endif

