#ifndef __DATA_H
#define __DATA_H	 
#include "sys.h"

#define PASS_STR        (u8*)"Pass"
#define FAIL_STR        (u8*)"Fail"

#define	OS_COMPENSATE_NUMBER		(30)
#define TEST_POINT_NUMBER			(86)

typedef enum 
{
    WAIT_START = 0,
    ON_TEST,
}eSysState;

typedef struct  _test_result_t
{
	u16 no;
	u8 result;
	u8 tp1;
	u8 tp2;
	u16 data;
}Testresult_t;

typedef struct  _compensate_t
{
	u16 no;
    u8 dir;
	u16 offset;
}Compensate_t;

extern u8 test_point[TEST_POINT_NUMBER];
extern Testresult_t result[1000];
extern u16 test_times;
extern u8 test_all_result;
extern Compensate_t oscompensate[OS_COMPENSATE_NUMBER];
extern Compensate_t panelcompensate[2];

#endif
